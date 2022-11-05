#include <windows.h>
#include <Mmsystem.h>
#pragma comment(lib,"winmm.lib")
#include <stdio.h>
#include <conio.h>
#include <fstream>
#include <sstream>
#include <vector>
#include<Algorithm>
#include "date.h"
#include "utils.h"
#include "config.h"
#include "error.h"
#include "log.h"

using namespace std;

// 创建账户数组，元素个数为0
vector<Account*> accounts;
// 是否开启记录命令
bool isRecord;
// 全局日期
Date global_date;
// commands.txt文件输出流
ofstream ofs;
void printBorder()
{
	printToScreen("/*", BORDER_LEFT, BORDER_TOP);
	printToScreen("\\*", BORDER_LEFT, BORDER_BOTTOM);
	printToScreen("*\\", BORDER_RIGHT, BORDER_TOP);
	printToScreen("*/", BORDER_RIGHT, BORDER_BOTTOM);
	for (int x = BORDER_LEFT + 2; x < BORDER_RIGHT; x++)
	{
		printToScreen("=", x, BORDER_TOP);
		printToScreen("=", x, BORDER_BOTTOM);
	}
	for (int y = BORDER_TOP + 1; y < BORDER_BOTTOM; y++)
	{
		printToScreen("||", BORDER_LEFT, y);
		printToScreen("||", BORDER_RIGHT, y);
	}
}
void printChoice()
{
	int x = BORDER_LEFT + 15, y = BORDER_TOP + 4;
	printToScreen("[a] add account",x,y++);
	printToScreen("[d] deposit", x, y++);
	printToScreen("[w] withdraw", x, y++);
	printToScreen("[s] show", x, y++);
	printToScreen("[c] change day", x, y++);
	printToScreen("[n] next month", x, y++);
	printToScreen("[q] query", x, y++);
	printToScreen("[e] exit", x, y++);
}
void clearBorder()
{
	string str = "";
	for (int i = BORDER_LEFT + 1; i < BORDER_RIGHT; i++)
	{
		str += " ";
	}
	for (int i = BORDER_TOP + 1; i < BORDER_BOTTOM; i++)
	{
		printToScreen(str,BORDER_LEFT+1,i);
	}
}
void utilsInit()
{
	HIDECURSOR();
	isRecord = false;
	global_date = Date(2008, 11, 1);
	printBorder();
	printChoice();

	try {
		read_commands_from_txt();
	}
	catch (exception& e) {
		Log::warnning(e.what());
	}
	beginRecord();
	showTime();
}

string getNowDateFromUtils()
{
	return global_date.toString();
}

void beginRecord()
{
	isRecord = true;
	if (ofs.is_open())
	{
		ofs.close();
	}
	ofs.open(COMMANDS_TXT_PATH, ios::app);
}

void gotoXY(const int x, const int y) //位置
{
	if (x >= 0 && y >= 0)
	{
		COORD pos = { (short int)x,(short int)y };
		HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);// 获取标准输出设备句柄
		SetConsoleCursorPosition(hOut, pos);//两参数分别是指定哪个窗体，具体位置
	}
};

void playGround()
{
	PlaySound(TEXT("./bg.wav"), NULL, SND_FILENAME | SND_ASYNC);
}

void printToScreen(const string str, const int x, const int y,const int color)
{
	gotoXY(x, y);
	CHANGECOLOR(color);
	wprintf(L"%S", str.c_str());
	CHANGECOLOR(7);
}

void save_to_file(string str)
{
	str = '\n' + str;
	if (!ofs.is_open())
	{
		ofs.open(COMMANDS_TXT_PATH,ios::app);
	}
	if (ofs.is_open() && isRecord)
	{
		ofs << str;
	}
	
}

void commands(istringstream& iss)
{
	char type;

	int index, day;

	double amount, credit, rate, fee;

	string id, desc;

	Account* account;

	Date date1, date2;

	ostringstream oss;
	char cmd;
	iss >> cmd;
	Log::info_clear();
	switch (cmd) {

	case 'a'://增加账户
		if (!(iss >> type >> id))
		{
			throw CommandFormatException(iss.str());
		}

		if (type == 's') {

			if (!(iss >> rate))
			{
				throw CommandFormatException(iss.str());
			}
			account = new SavingsAccount(global_date, id, rate);

			oss << cmd << " " << type << " " << id << " " << rate << "\n";

		}

		else {

			if (!(iss >> credit >> rate >> fee))
			{
				throw CommandFormatException(iss.str());
			}
			account = new CreditAccount(global_date, id, credit, rate, fee);

			oss << cmd << " " << type << " " << id << " " << credit << " " << rate << " " << fee << "\n";

		}

		accounts.push_back(account);
		break;

	case 'd'://存入现金
		if (!(iss >> index >> amount))
		{
			throw CommandFormatException(iss.str());
		}
		getline(iss, desc);
		accounts[index]->deposit(global_date, amount, desc);
		oss << cmd << " " << index << " " << amount << " " << desc << "\n";
		break;

	case 'w'://取出现金
		if (!(iss >> index >> amount))
		{
			throw CommandFormatException(iss.str());
		}
		getline(iss, desc);
		accounts[index]->withdraw(global_date, amount, desc);
		oss << cmd << " " << index << " " << amount << " " << desc << "\n";
		break;

	case 's'://查询各账户信息

		Log::info_clear();
		for (size_t i = 0; i < accounts.size(); i++) {

			ostringstream msg("");
			msg << "[" << i << "] " << accounts[i]->toString();
			Log::info(msg.str());
		}
		break;

	case 'c'://改变日期

		if (!(iss >> day))
		{
			throw CommandFormatException(iss.str());
		}
		if (day < global_date.getDay())
			Log::warnning("You cannot specify a previous day");
		else if (day > global_date.getMaxDay())
			Log::warnning("Invalid day");
		else
			global_date = Date(global_date.getYear(), global_date.getMonth(), day);
		oss << cmd << " " << day << "\n";
		showTime();
		break;

	case 'n'://进入下个月
		if (global_date.getMonth() == 12)
			global_date = Date(global_date.getYear() + 1, 1, 1);
		else
			global_date = Date(global_date.getYear(), global_date.getMonth() + 1, 1);
		for (vector<Account*>::iterator iter = accounts.begin(); iter != accounts.end(); ++iter)
			(*iter)->settle(global_date);
		oss << cmd << "\n" << endl;
		showTime();
		break;

	case 'q'://查询一段时间内的账目
		string str1,str2;
		if (!(iss >> str1 >> str2))
		{
			throw CommandFormatException(iss.str());
		}
		date1 = Date::stringToDate(str1);
		date2 = Date::stringToDate(str2);
		char work = 0;
		iss >> work;
		Log::info(date1.toString() + "-" + date2.toString());
		if (work)
		{
			Account::queryByAmount(date1, date2);
		}
		else {
			Account::query(date1, date2);
		}
		break;
	}
	showTime();
	if (oss.str() != "" && oss.str() != "\n")
	{
		// 保存到文件中
		save_to_file(oss.str());
	}
}

void read_commands_from_txt()
{
	// 文件输入流
	ifstream ifile;
	try {
		ifile.open(COMMANDS_TXT_PATH, ios::in);
	}catch (exception& e) {
		throw FileNotExistException(COMMANDS_TXT_PATH);
	}

	string str;
	// 每次获取一行内容，保存到str中
	while (getline(ifile, str, '\n'))
	{
		// 如果是空行则继续下一个
		if ((!str.compare("\n")) || (!str.compare("")))
		{
			continue;
		}
		// str转成string输出流
		istringstream iss(str);
		try {
			// 执行命令
			commands(iss);
		}
		catch (exception& e) {
			Log::warnning(e.what());
		}
	}
	ifile.close();
}

void utilsExit()
{
	if (ofs.is_open())
	{
		ofs.close();
	}
	try {
		for_each(accounts.begin(), accounts.end(), deleter());
	}
	catch (exception& e)
	{
		Log::warnning(e.what());
	}
}

void showTime()
{
	string str = "                 ";
	printToScreen("Time : " + str, TIME_LEFT, TIME_TOP);
	printToScreen("Time : " + global_date.toString(), TIME_LEFT, TIME_TOP);
}