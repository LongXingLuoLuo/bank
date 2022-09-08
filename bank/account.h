#pragma once
class SavingsAccount
{
private:
	//id
	int id;
	//余额
	double balance;
	//最后操作时间
	int lastDate;
	//利润
	double accumulation;
	//年利率
	double rate;
	void record(int date, double amount);
	double accumulate(int date);
public:
	SavingsAccount(int date, int id, double rate);
	int getId();
	double getBalance();
	double getRate();
	void show();
	//存款
	void deposit(int date, double amount);
	//取钱
	void withdraw(int date, double amount);
	//结算
	void settle(int date);
};

