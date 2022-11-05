#include<algorithm>
#include "account.h"
#include<string>
#include<iostream>
#include<cmath>
#include <iomanip>
#include <sstream>
#include<vector>
#include"error.h"
#include"log.h"
using namespace std;
typedef pair<Date, AccountRecord> RECORDMAP_PAIR;
bool cmp_amount(const RECORDMAP_PAIR& a, const RECORDMAP_PAIR& b)
{
	return a.second.getAmount() > b.second.getAmount();
}


/*=============================================================================*/
/*================================= Account ===================================*/
/*=============================================================================*/
double Account::total = 0;
multimap<Date, AccountRecord> Account::recordMap;
Account::Account(Date date, string id)
{
	this->id = id;
	this->balance = 0.0f;
	ostringstream oss;
	oss << setw(16) << setiosflags(ios::left) << date << setiosflags(ios::left)<<"#" << this->getId() << " created" << endl;
	Log::info(oss.str());
}
// �����ʵ��
void Account::record(Date date, double amount, string desc) 
{
	// ����
	amount = floor(amount * 100 + 0.5) / 100;
	this->balance += amount;
	total += amount;

	// �����¼
	AccountRecord record(date, this, amount, balance,desc);
	recordMap.insert(pair<Date,AccountRecord>(date,record));

	// չʾ��Ϣ
	ostringstream oss;
	oss << setw(16) << setiosflags(ios::left) << date
		<< setiosflags(ios::left)
		<< "#" << setw(15) << this->getId()
		<< setw(8) << setiosflags(ios::left) << amount
		<< setw(8) << setiosflags(ios::left) << this->getBalance() << desc << endl;
	Log::info(oss.str());
}
string Account::toString() const
{
	ostringstream oss;
	oss << setw(16) << setiosflags(ios::left) << this->getId()
		<< "Balance: " << setw(7) << this->getBalance();
	return oss.str();
}
// չʾ
void Account::show() const
{
	Log::info( toString());
}
// ����
void Account::error(string msg)
{
	Log::warnning("Error: " + msg + "/n");
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
// date1 ǰ���ڣ�date2 ������
void Account::query(Date date1, Date date2)
{
	auto iter = recordMap.upper_bound(date1);
	auto end = recordMap.lower_bound(date2);
	Log::info_clear();
	for (; iter != end;iter++)
	{
		Log::info(iter->second.toString());
	}
}
void Account::queryByAmount(Date date1, Date date2)
{
	auto first = recordMap.upper_bound(date1);
	auto end = recordMap.lower_bound(date2);
	Log::info_clear();
	vector<RECORDMAP_PAIR> recordVector(first, end);
	sort(recordVector.begin(), recordVector.end(), cmp_amount);
	for (auto iter = recordVector.begin(); iter != recordVector.end(); iter++)
	{
		Log::info(iter->second.toString());
	}
}
Account::~Account()
{
	/*cout << this->getId()<<"is deleted" << endl;*/
}

/*==============================================================================================*/
/*================================= SavingsAccount =============================================*/
/*===============================================================================================*/
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
		// ����
		throw AccountWithdrawOverException(this);
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

/*=============================================================================================*/
/*================================= CreditAccountAccount ====================================*/
/*===========================================================================================*/
CreditAccount::CreditAccount(Date date, string id, double credit, double rate, double fee)
	:Account(date,id),acc(date,0) 
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
		// ����
		throw AccountWithdrawOverException(this);
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
	Log::info(this->toString());
}
string CreditAccount::toString()const
{
	ostringstream oss;
	oss << setw(16) << setiosflags(ios::left) << this->getId()
		<< "Balance: " << setw(7) << this->getBalance()
		<< "Available credit:" << this->getAvailable();
	return oss.str();
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