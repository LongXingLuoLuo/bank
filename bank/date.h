#pragma once
#include<string>
class Date
{
private:
	int year, month, day;
public:
	Date(int year, int month, int day);
	Date(const Date &date);
	// 获取距离对应年数的天数
	int daysCount()const;
	// 是否为闰年
	bool isLeapYear()const;
	// 转换为int
	operator int();
	// 初始化
	int operator-(const Date& date);
	// 展示
	std::string show();
	// 获取本年天数
	int getYearDays();
};

