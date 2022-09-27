#pragma once
#include<string>
#include<map>
#include"date.h"
#include"accumulator.h"
#include"accountRecord.h"
using namespace std;
class AccountRecord;
class Account {
private:
	// id
	string id;
	// 本金
	double balance;
	// 所有用户总金
	static double total;
	// 账目记录
	static multimap<Date, AccountRecord> recordMap;

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
	virtual void settle(const Date& date) = 0;
	virtual string toString() const;
	string getId() const;
	double getBalance() const;
	static double getTotal();
	// 查询
	static void query(Date date1, Date date2);
	virtual ~Account();
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
	void settle(const Date& date);
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
	void settle(const Date& date);
	void show() const;
	string toString()const;
	double getCredit() const;
	double getRate() const;
	double getFee() const;
	// 剩余信用额度
	double getAvailable() const;
};
