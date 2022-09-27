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
	// ����
	double balance;
	// �����û��ܽ�
	static double total;
	// ��Ŀ��¼
	static multimap<Date, AccountRecord> recordMap;

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
	virtual void settle(const Date& date) = 0;
	virtual string toString() const;
	string getId() const;
	double getBalance() const;
	static double getTotal();
	// ��ѯ
	static void query(Date date1, Date date2);
	virtual ~Account();
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
	void settle(const Date& date);
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
	void settle(const Date& date);
	void show() const;
	string toString()const;
	double getCredit() const;
	double getRate() const;
	double getFee() const;
	// ʣ�����ö��
	double getAvailable() const;
};
