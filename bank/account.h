#pragma once
#include<string>
#include"date.h"
#include"accumulator.h"
using namespace std;
class Account {
private:
	// id
	string id;
	// 本金
	double balance;
	// 所有用户总金
	static double total;
public:
	Account(Date date, string id);
	// 存入款实现
	void record(Date date, double amount, string desc);
	// 展示
	string show() const;
	// 报错
	void error(string msg);

	string getId() const;
	double getBalance() const;
	static double getTotal();
};
class SavingsAccount :public Account {
private:
	// 利息计算函数
	Accumulator acc;
	// 年利率
	double rate;
public:
	SavingsAccount(Date date, string id, double rate);
	double getRate() const;
	// 存款
	void deposit(Date date, double amount, string desc);
	// 取钱
	void withdraw(Date date, double amount, string desc);
	// 结算
	void settle(Date date);
};

