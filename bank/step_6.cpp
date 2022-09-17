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

vector<Account*> accounts;//�����˻����飬Ԫ�ظ���Ϊ0
Date date(2008, 11, 1);//��ʼ����
char cmd;
bool beginRecord = false;

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
			oss << cmd << " " << type << " " << id << " " << credit << " " << rate << " " << fee << "\n";
			account = new CreditAccount(date, id, credit, rate, fee);

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
		*is >> index >> amount;
		getline(*is, desc);
		accounts[index]->withdraw(date, amount, desc);
		oss << cmd << " " << index << " " << amount << " " << desc << "\n";
		break;

	case 's'://��ѯ���˻���Ϣ
		
		for (size_t i = 0; i < accounts.size(); i++) {

			cout << "[" << i << "] ";

			accounts[i]->show();

			cout << endl;

		}
		oss<< cmd << "\n";
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
		date1 = Date::read(is);
		date2 = Date::read(is);
		Account::query(date1, date2);
		oss << cmd << " " 
			<< date1.getYear() << "/" << date1.getMonth() << "/" << date1.getDay() << " " 
			<< date2.getYear() << "/" << date2.getMonth() << "/" << date2.getDay() << "\n" ;
		break;
	}
	if (beginRecord)
	{
		save_to_file(oss.str());
	}
}

// ��ȡcommands.txt����
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

		//��ʾ���ں��ܽ��

		date.show();

		cout << "Total: " << Account::getTotal() << "        command> ";
		//break; // ֱ�ӷ���
		beginRecord = true;
		commands(&cin);

	} while (cmd != 'e');

	//for_each(accounts.begin(), accounts.end(), deleter());
	
	ofs.close();
	return 0;
	
}