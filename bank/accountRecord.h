#pragma once
#include<string>
#include"date.h"
#include"account.h"
using namespace std;
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
	AccountRecord(Date date, Account* acc, double amount, double banlance);
	void show() const;
};

