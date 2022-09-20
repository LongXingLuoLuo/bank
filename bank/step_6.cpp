//step6.cpp

#include "account.h"
#include"error.h"

#include <iostream>

#include <vector>

#include <algorithm>

#include<fstream>

#include<sstream>

#define COMMANDS_TXT_PATH "./commands.txt"
using namespace std;





vector<Account*> accounts;//�����˻����飬Ԫ�ظ���Ϊ0

struct deleter {

	template <class T> void operator () (T* p){delete p;}

};

Date date(2008, 11, 1);//��ʼ����
char cmd;
// �Ƿ�����¼����
bool isRecord = false;

static ofstream ofs(COMMANDS_TXT_PATH, ios::app);
void save_to_file(string str)
{
	str = '\n' + str;
	if (ofs.is_open())
	{
		//cout << str << endl;
		ofs << str;
	}

}

// ִ������
void commands(istream* is)
{
	char type;

	int index, day;

	double amount, credit, rate, fee;

	string id, desc;

	Account* account;

	Date date1, date2;

	ostringstream oss;

	*is >> cmd;

	switch (cmd) {

	case 'a'://�����˻�
		*is >> type >> id;

		if (type == 's') {

			*is >> rate;
			account = new SavingsAccount(date, id, rate);

			oss << cmd << " " << type << " " << id << " " << rate << "\n";

		}

		else {

			*is >> credit >> rate >> fee;
			account = new CreditAccount(date, id, credit, rate, fee);

			oss << cmd << " " << type << " " << id << " " << credit << " " << rate << " " << fee << "\n";

		}

		accounts.push_back(account);
		break;

	case 'd'://�����ֽ�
		*is >> index >> amount;
		getline(*is, desc);
		accounts[index]->deposit(date, amount, desc);
		oss << cmd << " " << index << " " << amount << " " << desc << "\n";
		break;

	case 'w'://ȡ���ֽ�
		try {
			*is >> index >> amount;
			getline(*is, desc);
			accounts[index]->withdraw(date, amount, desc);
			oss << cmd << " " << index << " " << amount << " " << desc << "\n";
		}
		catch (WithdrawOver& e)
		{
			cerr << e.what() << endl;
			
			// ��ջ�����
			cin.clear();
			//string str;
			//getline(cin, str, '\n');
			
			
		}
		break;

	case 's'://��ѯ���˻���Ϣ
		
		for (size_t i = 0; i < accounts.size(); i++) {

			cout << "[" << i << "] ";

			accounts[i]->show();

			cout << endl;

		}
		break;

	case 'c'://�ı�����
		
		*is >> day;
		if (day < date.getDay())

			cout << "You cannot specify a previous day";

		else if (day > date.getMaxDay())

			cout << "Invalid day";

		else

			date = Date(date.getYear(), date.getMonth(), day);
		oss << cmd << " " << day << "\n";
		break;

	case 'n'://�����¸���
		if (date.getMonth() == 12)

			date = Date(date.getYear() + 1, 1, 1);

		else

			date = Date(date.getYear(), date.getMonth() + 1, 1);

		for (vector<Account*>::iterator iter = accounts.begin(); iter != accounts.end(); ++iter)

			(*iter)->settle(date);
		oss << cmd <<"\n" << endl;
		break;

	case 'q'://��ѯһ��ʱ���ڵ���Ŀ
		try {
			date1 = Date::read();
			date2 = Date::read();
			Account::query(date1, date2);
		}
		catch (DateReadFormat &e)
		{
			cerr << e.what() << endl;
			cin.clear();
			// ��ջ�����
			string str;
			getline(cin, str,'\n');
		}
		break;
	}
	if (isRecord&&oss.str() != ""&&oss.str() != "\n")
	{
		// ���浽�ļ���
		save_to_file(oss.str());
	}
}

// ��ȡcommands.txt����
void read_commands_from_txt()
{
	// �ļ�������
	ifstream ifile(COMMANDS_TXT_PATH, ios::in);
	string str;
	// ÿ�λ�ȡһ�����ݣ����浽str��
	while (getline(ifile, str, '\n'))
	{
		// ����ǿ����������һ��
		if ((!str.compare("\n")) || (!str.compare("")))
		{
			continue;
		}
		// strת��string�����
		istringstream iss(str);
		// ִ������
		commands(&iss);
	}
	ifile.close();
}

int main() {
	// ��ȡ�ļ�
	read_commands_from_txt();
	// ��ʼ��¼ָ��
	isRecord = true;
	cout << "(a)add account (d)deposit (w)withdraw (s)show (c)change day (n)next month (q)query (e)exit" << endl;
	do {

		//��ʾ���ں��ܽ��

		date.show();

		cout << "Total: " << Account::getTotal() << "        command> ";
		//break; // ֱ�ӷ���
		
		commands(&cin);

	} while (cmd != 'e');

	try {
		for_each(accounts.begin(), accounts.end(), deleter());
	}
	catch (exception& e)
	{
		cout << e.what() << endl;
	}
	
	ofs.close();
	return 0;
	
}