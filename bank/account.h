#pragma once
#include<string>
#include"date.h"
using namespace std;
class SavingsAccount
{
private:
	//id
	std::string id;
	//余额
	double balance;
	//最后操作时间
	Date lastDate;
	//利润
	double accumulation;
	//年利率
	double rate;
	void record(Date date, double amount, string desc);
	double accumulate(Date date);
	//得到所有用户的总金额
	static double total;
public:
	SavingsAccount(Date date, std::string id, double rate);
	// 展示
	void show() const;
	// 存款
	void deposit(Date date, double amount, std::string desc);
	// 取钱
	void withdraw(Date date, double amount, std::string desc);
	// 结算
	void settle(Date date);
	std::string getId() const;
	double getBalance() const;
	double getRate() const;
	static double getTotal();
};

