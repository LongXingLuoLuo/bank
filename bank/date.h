#pragma once
#include<string>
class Date
{
private:
	int year, month, day;
	int totalDays;
public:
	Date(int year, int month, int day);
	Date(const Date &date);
	// ��ȡ�����ʼ���ڵ�������
	int distance()const;
	// �Ƿ�Ϊ����
	bool isLeapYear()const;
	// ת��Ϊint
	operator int() const;
	// ����-����������������֮��
	int operator-(const Date& date) const;
	// չʾ
	void show() const;
	// ����һ����������
	int getMaxDay();
	// ����һ������������
	int getMonthDays();

	int getYear() const;
	int getDay() const;
	int getMonth() const;

};

