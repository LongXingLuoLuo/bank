#pragma once
#include<string>
#include<utility>
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
	// չʾ
	void show() const;
	// ����һ����������
	int getMaxDay();
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

	int getYear() const;
	int getDay() const;
	int getMonth() const;

};

