#include "account.h"
#include<iostream>
#include<cmath>
#include <iomanip>
using namespace std;
SavingsAccount::SavingsAccount(int date, int id, double rate)
{
	this->id = id;
	this->rate = rate;
	this->lastDate = date;
	this->accumulation = 0;
	this->balance = 0;
	cout <<setw(8) << setiosflags(ios::left) << date  << "#" << this->getId() << " is created" << endl;
}
double SavingsAccount::accumulate(int date)
{
	return this->balance * (date - this->lastDate)*rate / 365;
}
void SavingsAccount::record(int date, double amount)
{
	this->accumulation += accumulate(date);
	this->lastDate = date;

	amount = floor(amount * 100 + 0.5) / 100;
	this->balance += amount;
	cout << setw(8) << setiosflags(ios::left) << date
		<< "#" << setw(15) << this->getId()
		<< setw(8) << amount  << this->getBalance() << endl;
}
void SavingsAccount::deposit(int date, double amount)
{
	record(date, amount);
}
void SavingsAccount::withdraw(int date, double amount)
{
	if (amount > balance)
	{
		cout << "Error!" << endl;
	}
	else {
		record(date, -amount);
	}
	
}
void SavingsAccount::settle(int date)
{
	this->accumulation += accumulate(date);
	this->lastDate = date;
	double amount = this->accumulation;
	this->accumulation = 0;
	record(date, amount);
}

void SavingsAccount::show()
{
	cout << setiosflags(ios::left) << "#" << setw(15) << this->getId() << "Balance: " << this->getBalance();
}
int SavingsAccount::getId()
{
	return this->id;
}
double SavingsAccount::getBalance()
{
	return this->balance;
}
double SavingsAccount::getRate()
{
	return this->rate;
}
