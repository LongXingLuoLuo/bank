#include "accountRecord.h"
#include <iomanip>
#include<iostream>
using namespace std;
AccountRecord::AccountRecord(Date date, Account* acc, double amount, double banlance):account(acc),date(date)
{
	this->amount = amount;
	this->balance = balance;
}
void AccountRecord::show()const
{
	date.show();
	cout << setiosflags(ios::left)
		<< "#" << setw(15) << account->getId()
		<< setw(8) << setiosflags(ios::left) << amount
		<< setw(8) << setiosflags(ios::left) << balance << desc << endl;
}