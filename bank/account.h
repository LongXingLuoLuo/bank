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
	virtual void show() const;
	// ����
	void error(string msg);
	// ���
	virtual void deposit(Date date, double amount, string desc) = 0;
	// ȡ��
	virtual void withdraw(Date date, double amount, string desc) = 0;
	// ����
	virtual void settle(Date date) = 0;
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
	// ���
	void deposit(Date date, double amount, string desc);
	// ȡǮ
	void withdraw(Date date, double amount, string desc);
	// ����
	void settle(Date date);
	double getRate() const;
};
class CreditAccount:public virtual Account {
private:
	// ��Ϣ
	Accumulator acc;
	// ���ö��
	double credit;
	// ������
	double rate;
	// ���
	double fee;
public:
	CreditAccount(Date date, string id, double credit, double rate, double fee);
	// ���
	void deposit(Date date, double amount, string desc);
	// ȡǮ
	void withdraw(Date date, double amount, string desc);
	// ����
	void settle(Date date);
	void show() const;
	double getCredit() const;
	double getRate() const;
	double getFee() const;
	// ʣ�����ö��
	double getAvailable() const;
};
