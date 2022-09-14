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
	// 获取距离初始日期的总天数
	int distance()const;
	// 是否为闰年
	bool isLeapYear()const;
	// 展示
	void show() const;
	// 返回一年中总天数
	int getMaxDay();
	// 返回一个月中总天数
	int getMonthDays();
	// 转换为int
	operator int() const;
	// 定义-，返回两个总天数之差
	int operator-(const Date& date) const;
	// 重载 < 运算符
	bool operator<(const Date& date) const;
	// 重载 > 运算符
	bool operator>(const Date& date) const;

	int getYear() const;
	int getDay() const;
	int getMonth() const;

};

