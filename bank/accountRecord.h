#pragma once
#include<string>
#include"date.h"
#include"account.h"
using namespace std;
class Account;
class AccountRecord
{
private:
	// ����
	Date date;
	// �˺�
	const Account* account;
	// ���
	double amount;
	// ���
	double balance;
	// ����
	string desc;
public:
	AccountRecord(Date date, Account* acc, double amount, double banlance,string desc);
	AccountRecord(const AccountRecord& record);
	void print() const;
};

