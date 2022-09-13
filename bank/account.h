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
	virtual void show() const;
	// 报错
	void error(string msg);
	// 存款
	virtual void deposit(Date date, double amount, string desc) = 0;
	// 取款
	virtual void withdraw(Date date, double amount, string desc) = 0;
	// 结算
	virtual void settle(Date date) = 0;
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
	// 存款
	void deposit(Date date, double amount, string desc);
	// 取钱
	void withdraw(Date date, double amount, string desc);
	// 结算
	void settle(Date date);
	double getRate() const;
};
class CreditAccount:public virtual Account {
private:
	// 利息
	Accumulator acc;
	// 信用额度
	double credit;
	// 日利率
	double rate;
	// 年费
	double fee;
public:
	CreditAccount(Date date, string id, double credit, double rate, double fee);
	// 存款
	void deposit(Date date, double amount, string desc);
	// 取钱
	void withdraw(Date date, double amount, string desc);
	// 结算
	void settle(Date date);
	void show() const;
	double getCredit() const;
	double getRate() const;
	double getFee() const;
	// 剩余信用额度
	double getAvailable() const;
};
