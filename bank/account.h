#pragma once
#include<string>
#include"date.h"
using namespace std;
class SavingsAccount
{
private:
	//id
	std::string id;
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
	SavingsAccount(Date date, std::string id, double rate);
	// չʾ
	void show() const;
	// ���
	void deposit(Date date, double amount, std::string desc);
	// ȡǮ
	void withdraw(Date date, double amount, std::string desc);
	// ����
	void settle(Date date);
	std::string getId() const;
	double getBalance() const;
	double getRate() const;
	static double getTotal();
};

