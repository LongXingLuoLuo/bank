#include "account.h"
#include<string>
#include<iostream>
#include<cmath>
#include <iomanip>
#include <sstream>
#include"error.h"
using namespace std;

double Account::total = 0;
multimap<Date, AccountRecord> Account::recordMap;
Account::Account(Date date, string id)
{
	this->id = id;
	this->balance = 0.0f;
	date.show();
	cout << setiosflags(ios::left)<<"#" << this->getId() << " created" << endl;
}
// 存入款实现
void Account::record(Date date, double amount, string desc) 
{
	// 操作
	amount = floor(amount * 100 + 0.5) / 100;
	this->balance += amount;
	total += amount;

	// 保存记录
	AccountRecord record(date, this, amount, balance,desc);
	recordMap.insert(pair<Date,AccountRecord>(date,record));

	// 展示信息
	date.show();
	cout << setiosflags(ios::left) 
		<< "#" << setw(15) << this->getId()
		<< setw(8) << setiosflags(ios::left) << amount
		<< setw(8) << setiosflags(ios::left) << this->getBalance() << desc << endl;
}
// 展示
void Account::show() const
{
	cout<< setw(16) << this->id << "Balance: " << this->getBalance();
}
// 报错
void Account::error(string msg)
{
	cout << "Error: " << msg << endl;
}
string Account::getId() const
{
	return id;
}
double Account::getBalance() const
{
	return balance;
}
double Account::getTotal()
{
	return total;
}
// date1 前日期，date2 后日期
void Account::query(Date date1, Date date2)
{
	auto iter = recordMap.upper_bound(date1);
	auto end = recordMap.lower_bound(date2);

	for (; iter != end;iter++)
	{
		iter->second.print();
	}
}
Account::~Account()
{
	/*cout << this->getId()<<"is deleted" << endl;*/
}

SavingsAccount::SavingsAccount(Date date, string id, double rate):Account(date,id),acc(date,0.0f)
{
	this->rate = rate;
}
void SavingsAccount::deposit(Date date, double amount, string desc)
{
	record(date, amount,desc);
	acc.change(date, this->getBalance());
}
void SavingsAccount::withdraw(Date date, double amount, string desc)
{
	if (amount > getBalance())
	{
		// 报错
		throw AccountWithdrawOverBalance();
	}
	else {
		record(date, -amount,desc);
		acc.change(date, this->getBalance());
	}
	
}
void SavingsAccount::settle(const Date& date)
{
	if (date.getMonth() == 1)
	{
		Date temp(date.getYear() - 1, 1, 1);
		acc.change(date, getBalance());
		double amount = acc.getSum() * rate / temp.getMaxDay();
		acc.reset(date, this->getBalance());
		amount = floor(amount * 100 + 0.5) / 100;
		deposit(date, amount, "interest");
	}
}
double SavingsAccount::getRate() const
{
	return this->rate;
}


CreditAccount::CreditAccount(Date date, string id, double credit, double rate, double fee):Account(date,id),acc(date,0) 
{
	this->credit = credit;
	this->rate = rate;
	this->fee = fee;
}
// 存款
void CreditAccount::deposit(Date date, double amount, string desc)
{
	record(date, amount, desc);
	if (getBalance() < 0)
	{
		acc.change(date, getBalance());
	}
	else {
		acc.change(date, 0);
	}
}
// 取钱
void CreditAccount::withdraw(Date date, double amount, string desc)
{
	if (getBalance() - amount < -getCredit())
	{
		// 报错
		throw AccountWithdrawOverCredit();
	}
	else {
		record(date, -amount,desc);
		if (getBalance() < 0)
		{
			acc.change(date, getBalance());
		}
		else {
			acc.change(date, 0);
		}
	}
}
// 结算
void CreditAccount::settle(const Date& date)
{
	if (date.getDay() == 1)
	{
		// 结算利息
		acc.change(date, getBalance());
		double amount = -acc.getSum() * rate;
		amount = floor(amount * 100 + 0.5) / 100;
		acc.reset(date, this->getBalance());
		if (amount > 1e-5) {
			withdraw(date, amount, "interest");
		}

		// 年费支出
		if (date.getMonth() == 1)
		{
			withdraw(date, fee, "annual fee");
		}
	}
}

void CreditAccount::show() const {
	cout << setw(16) << setiosflags(ios::left) << this->getId()
		<< "Balance: " << setw(7) << this->getBalance()
		<< "Available credit:" << this->getAvailable();
}

double CreditAccount::getCredit() const
{
	return credit;
}
double CreditAccount::getRate() const
{
	return rate;
}
double CreditAccount::getFee() const
{
	return fee;
}
// 剩余信用额度
double CreditAccount::getAvailable() const
{
	if (getBalance() < 0)
	{
		return credit + getBalance();
	}
	else {
		return credit;
	}
	
}