#pragma once
#include<string>
class Date
{
private:
	int year, month, day;
public:
	Date(int year, int month, int day);
	Date(const Date &date);
	// 获取距离初始日期的总天数
	int daysCount()const;
	// 是否为闰年
	bool isLeapYear()const;
	// 转换为int
	operator int();
	// 定义-，返回两个总天数之差
	int operator-(const Date& date);
	// 展示
	std::string show();
	// 返回总天数
	int getYearDays();
};

