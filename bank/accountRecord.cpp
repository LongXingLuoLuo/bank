#include"accountRecord.h"
#include <iomanip>
#include<iostream>
using namespace std;
AccountRecord::AccountRecord(Date date, Account* acc, double amount, double balance,string desc) :account(acc), date(date)
{
	this->amount = amount;
	this->balance = balance;
	this->desc = desc;
}
AccountRecord::AccountRecord(const AccountRecord& record) :account(record.account), date(record.date)
{
	this->amount = record.amount;
	this->balance = record.balance;
}
void AccountRecord::print()const
{
	date.show();
	cout << setiosflags(ios::left)
		<< "#" << setw(15) << account->getId()
		<< setw(8) << setiosflags(ios::left) << amount
		<< setw(8) << setiosflags(ios::left) << balance << desc << endl;
}