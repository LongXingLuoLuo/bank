#pragma once
#include<string>
#include"date.h"
#include"account.h"
using namespace std;
class Account;
class AccountRecord
{
private:
	// ÈÕÆÚ
	Date date;
	// ÕËºÅ
	const Account* account;
	// ½ğ¶î
	double amount;
	// Óà¶î
	double balance;
	// ÃèÊö
	string desc;
public:
	AccountRecord(Date date, Account* acc, double amount, double banlance,string desc);
	AccountRecord(const AccountRecord& record);
	void print() const;
};

