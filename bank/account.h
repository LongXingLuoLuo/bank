#pragma once
#include<string>
#include"date.h"
using namespace std;
class SavingsAccount
{
private:
	//id
	string id;
	//���
	double balance;
	//������ʱ��
	Date lastDate;
	//����
	double accumulation;
	//������
	double rate;
	void record(Date date, double amount, string desc);
	double accumulate(Date date);
	//�õ������û����ܽ��
	static double total;
public:
	SavingsAccount(Date date, string id, double rate);
	string getId() const;
	double getBalance() const;
	double getRate() const;
	void show() const;
	//���
	void deposit(Date date, double amount, string desc);
	//ȡǮ
	void withdraw(Date date, double amount, string desc);
	//����
	void settle(Date date);
	static double getTotal();
};

