#pragma once
#include<string>
class Date
{
private:
	int year, month, day;
public:
	Date(int year, int month, int day);
	Date(const Date &date);
	// ��ȡ�����ʼ���ڵ�������
	int daysCount()const;
	// �Ƿ�Ϊ����
	bool isLeapYear()const;
	// ת��Ϊint
	operator int();
	// ����-����������������֮��
	int operator-(const Date& date);
	// չʾ
	std::string show();
	// ����������
	int getYearDays();
};

