#pragma once
#include<string>
class Date
{
private:
	int year, month, day;
public:
	Date(int year, int month, int day);
	Date(const Date &date);
	int daysCount()const;
	bool isLeapYear()const;
	operator int();
	int operator-(const Date& date);
	std::string show();
	int getYearDays();
};

