#include"accountRecord.h"
#include"log.h"
#include <iomanip>
#include<iostream>
#include<sstream>
using namespace std;
AccountRecord::AccountRecord(Date date, Account* acc, double amount, double balance,string desc) :date(date),account(acc)
{
	this->amount = amount;
	this->balance = balance;
	this->desc = desc;
}
AccountRecord::AccountRecord(const AccountRecord& record) :date(record.date),account(record.account)
{
	this->amount = record.amount;
	this->balance = record.balance;
	this->desc = record.desc;
}
void AccountRecord::print()const
{
	date.show();
	Log::info(toString());
}
string AccountRecord::toString() const
{
	ostringstream oss;
	oss << setiosflags(ios::left)
		<< "#" << setw(15) << account->getId()
		<< setw(8) << setiosflags(ios::left) << amount
		<< setw(8) << setiosflags(ios::left) << balance << desc;
	return oss.str();
}