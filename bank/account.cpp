#include "account.h"
#include<string>
#include<iostream>
#include<cmath>
#include <iomanip>
using namespace std;
double SavingsAccount::total = 0;
SavingsAccount::SavingsAccount(Date date, string id, double rate):lastDate(date)
{
	this->id = id;
	this->rate = rate;
	this->accumulation = 0;
	this->balance = 0;
	
	cout<<setw(16) <<setiosflags(ios::left)<<lastDate.show()<< this->getId() << " created" << endl;
}
double SavingsAccount::accumulate(Date date)
{
	return this->balance * (date - this->lastDate) * rate / lastDate.getYearDays();
}
void SavingsAccount::record(Date date, double amount,string desc)
{
	double temp = accumulate(date);
	temp = floor(temp * 100 + 0.5) / 100;
	this->accumulation += temp;
	this->lastDate = date;

	amount = floor(amount * 100 + 0.5) / 100;
	this->balance += amount;
	total += amount;
	lastDate.show();
	cout << setw(16) << setiosflags(ios::left) << lastDate.show() 
		<< setw(16) << this->getId()  
		<<setw(8) << setiosflags(ios::left) << amount 
		<< setw(8) << setiosflags(ios::left) << this->getBalance() << desc << endl;
}
void SavingsAccount::deposit(Date date, double amount, string desc)
{
	record(date, amount,desc);
}
void SavingsAccount::withdraw(Date date, double amount, string desc)
{
	if (amount > getBalance())
	{
		cout << "Error: not enough money" << endl;
	}
	else {
		record(date, -amount,desc);
	}
	
}
void SavingsAccount::settle(Date date)
{
	
	double temp = accumulate(date);
	temp = floor(temp * 100 + 0.5) / 100;
	this->accumulation += temp;

	this->lastDate = date;
	double amount = this->accumulation;
	amount = floor(amount * 100 + 0.5) / 100;
	this->accumulation = 0;
	record(date, amount,"interest");
}

double SavingsAccount::getTotal()
{
	return SavingsAccount::total;
}
void SavingsAccount::show() const
{
	cout << setw(16) << this->id << "" << "Balance: " << this->getBalance();
}
string SavingsAccount::getId() const
{
	return "#" + this->id;
}
double SavingsAccount::getBalance() const
{
	return this->balance;
}
double SavingsAccount::getRate() const
{
	return this->rate;
}
