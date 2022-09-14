#include "account.h"
#include<string>
#include<iostream>
#include<cmath>
#include <iomanip>
#include <sstream>
using namespace std;

double Account::total = 0;
Account::Account(Date date, string id)
{
	this->id = id;
	this->balance = 0.0f;
	date.show();
	cout << setiosflags(ios::left)<<"#" << this->getId() << " created" << endl;
}
// �����ʵ��
void Account::record(Date date, double amount, string desc) 
{
	amount = floor(amount * 100 + 0.5) / 100;
	this->balance += amount;
	total += amount;

	date.show();
	cout << setiosflags(ios::left) 
		<< "#" << setw(15) << this->getId()
		<< setw(8) << setiosflags(ios::left) << amount
		<< setw(8) << setiosflags(ios::left) << this->getBalance() << desc << endl;
}
// չʾ
void Account::show() const
{
	cout<< setw(16) << this->id << "Balance: " << this->getBalance();
}
// ����
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
		error("not enough money");
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
// ���
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
// ȡǮ
void CreditAccount::withdraw(Date date, double amount, string desc)
{
	if (getBalance() - amount < -getCredit())
	{
		error("not credit");
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
// ����
void CreditAccount::settle(const Date& date)
{
	if (date.getDay() == 1)
	{
		// ������Ϣ
		acc.change(date, getBalance());
		double amount = -acc.getSum() * rate;
		amount = floor(amount * 100 + 0.5) / 100;
		acc.reset(date, this->getBalance());
		if (amount > 1e-5) {
			withdraw(date, amount, "interest");
		}

		// ���֧��
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
// ʣ�����ö��
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