#pragma once
#include<string>
#include"date.h"
#include"accumulator.h"
using namespace std;
class Account {
private:
	// id
	string id;
	// ����
	double balance;
	// �����û��ܽ�
	static double total;
public:
	Account(Date date, string id);
	// �����ʵ��
	void record(Date date, double amount, string desc);
	// չʾ
	string show() const;
	// ����
	void error(string msg);

	string getId() const;
	double getBalance() const;
	static double getTotal();
};
class SavingsAccount :public Account {
private:
	// ��Ϣ���㺯��
	Accumulator acc;
	// ������
	double rate;
public:
	SavingsAccount(Date date, string id, double rate);
	double getRate() const;
	// ���
	void deposit(Date date, double amount, string desc);
	// ȡǮ
	void withdraw(Date date, double amount, string desc);
	// ����
	void settle(Date date);
};

