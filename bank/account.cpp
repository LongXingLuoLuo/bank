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
}
// 存入款实现
void Account::record(Date date, double amount, string desc) 
{
	amount = floor(amount * 100 + 0.5) / 100;
	this->balance += amount;
	total += amount;
	cout << setw(16) << setiosflags(ios::left) << date.show()
		<< "#" << setw(15) << this->getId()
		<< setw(8) << setiosflags(ios::left) << amount
		<< setw(8) << setiosflags(ios::left) << this->getBalance() << desc << endl;
}
// 展示
string Account::show() const
{
	stringstream ss;
	ss <<"#" << setw(15) << this->id << "Balance: " << this->getBalance();
	return ss.str();
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


double SavingsAccount::total = 0;
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
void SavingsAccount::settle(Date date)
{
	
	double amount = acc.getSum();
	amount = floor(amount * 100 + 0.5) / 100;
	record(date, amount,"interest");
	acc.reset(date, this->getBalance());
}
double SavingsAccount::getRate() const
{
	return this->rate;
}
