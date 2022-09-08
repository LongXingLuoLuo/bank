#pragma once
class SavingsAccount
{
private:
	//id
	int id;
	//���
	double balance;
	//������ʱ��
	int lastDate;
	//����
	double accumulation;
	//������
	double rate;
	void record(int date, double amount);
	double accumulate(int date);
public:
	SavingsAccount(int date, int id, double rate);
	int getId();
	double getBalance();
	double getRate();
	void show();
	//���
	void deposit(int date, double amount);
	//ȡǮ
	void withdraw(int date, double amount);
	//����
	void settle(int date);
};

