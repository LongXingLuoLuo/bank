//step6.cpp

#include "account.h"

#include <iostream>

#include <vector>

#include <algorithm>

#include<fstream>

#include<sstream>

#define COMMANDS_TXT_PATH "./commands.txt"
using namespace std;



struct deleter {

	template <class T> void operator () (T* p) { delete p; }

};

vector<Account*> accounts;//创建账户数组，元素个数为0
Date date(2008, 11, 1);//起始日期
char cmd;

// 执行命令
void commands(istream* is)
{
	char type;

	int index, day;

	double amount, credit, rate, fee;

	string id, desc;

	Account* account;

	Date date1, date2;

	*is >> cmd;

	switch (cmd) {

	case 'a'://增加账户

		*is >> type >> id;

		if (type == 's') {

			*is >> rate;

			account = new SavingsAccount(date, id, rate);

		}

		else {

			*is >> credit >> rate >> fee;

			account = new CreditAccount(date, id, credit, rate, fee);

		}

		accounts.push_back(account);

		break;

	case 'd'://存入现金

		*is >> index >> amount;

		getline(*is, desc);

		accounts[index]->deposit(date, amount, desc);

		break;

	case 'w'://取出现金

		*is >> index >> amount;

		getline(*is, desc);

		accounts[index]->withdraw(date, amount, desc);

		break;

	case 's'://查询各账户信息

		for (size_t i = 0; i < accounts.size(); i++) {

			cout << "[" << i << "] ";

			accounts[i]->show();

			cout << endl;

		}

		break;

	case 'c'://改变日期

		*is >> day;

		if (day < date.getDay())

			cout << "You cannot specify a previous day";

		else if (day > date.getMaxDay())

			cout << "Invalid day";

		else

			date = Date(date.getYear(), date.getMonth(), day);

		break;

	case 'n'://进入下个月

		if (date.getMonth() == 12)

			date = Date(date.getYear() + 1, 1, 1);

		else

			date = Date(date.getYear(), date.getMonth() + 1, 1);

		for (vector<Account*>::iterator iter = accounts.begin(); iter != accounts.end(); ++iter)

			(*iter)->settle(date);

		break;

	case 'q'://查询一段时间内的账目

		date1 = Date::read();

		date2 = Date::read();

		Account::query(date1, date2);

		break;

	}
}

// 读取commands.txt命令
void read_commands_from_txt()
{
	ifstream ifile(COMMANDS_TXT_PATH, ios::in);
	string str;
	while (getline(ifile, str, '\n'))
	{
		if (str[0] == '\n' || str == "")
		{
			continue;
		}
		stringstream iss(str);
		commands(&iss);
	}
	ifile.close();
}

int main() {
	read_commands_from_txt();

	cout << "(a)add account (d)deposit (w)withdraw (s)show (c)change day (n)next month (q)query (e)exit" << endl;

	do {

		//显示日期和总金额

		date.show();

		cout << "Total: " << Account::getTotal() << "        command> ";
		commands(&cin);

	} while (cmd != 'e');
	//for_each(accounts.begin(), accounts.end(), deleter());

	return 0;
	
}