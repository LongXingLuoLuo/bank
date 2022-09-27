#pragma once
#include<string>
#include<utility>
#include<iostream>
using namespace std;
class Date
{
private:
	int year, month, day;
	int totalDays;
public:
	Date();
	Date(int year, int month, int day);
	Date(const Date &date);
	// ��ȡ�����ʼ���ڵ�������
	int distance()const;
	// �Ƿ�Ϊ����
	bool isLeapYear()const;
	string toString() const;
	// stringתDate
	static Date stringToDate(string str);
	// �ӿ���̨�����ȡ����
	static Date read();
	
	// չʾ
	void show() const;
	// ����һ����������
	int getMaxDay() const;
	// ����һ������������
	int getMonthDays();
	
	// ת��Ϊint
	operator int() const;
	// ����-����������������֮��
	int operator-(const Date& date) const;
	// ���� < �����
	bool operator<(const Date& date) const;
	// ���� > �����
	bool operator>(const Date& date) const;
	// ostream << Date
	friend ostream& operator<<(ostream& os,const Date& date);
	// istream >> Date
	friend istream& operator>>(istream& is, const Date& date);
	int getYear() const;
	int getDay() const;
	int getMonth() const;

};

