#include "date.h"
#include<iostream>
#include<string>
#include <sstream>
#include <iomanip>
using namespace std;
namespace {
	const int DAYS_BEFORE_MONTH[] = { 0,31,59,90,120,151,181,212,243,273,304,334,365 };
	const int DAYS_IN_MONTH_FORM_AVERAGE[] = { 31,28,31,30,31,30,31,31,30,31,30,31 };
	int LEAP_YEAR_DAYS = 366;// 平年天数
	int AVERAGE_YEAR_DAYS = 365; // 平年天数
}
Date::Date(int year, int month, int day)
{
	this->year = year;
	this->month = month;
	this->day = day;
	this->totalDays = this->distance();
}
Date::Date(const Date& date)
{
	this->year = date.year;
	this->month = date.month;
	this->day = date.day;
	this->totalDays = date.totalDays;
}
int Date::distance()const
{
	int years = this->year - 1;
	int results = years * 365 + years / 4 - years / 100 + years / 400
		+ DAYS_BEFORE_MONTH[month - 1] + day;
	if (isLeapYear() && month > 2)
	{
		results++;
	}
	return results;
}
bool Date::isLeapYear()const
{
	if (year % 4 == 0)
	{
		if (year % 100 != 0)
		{
			return true;
		}
		if (year % 400 == 0)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	else {
		return false;
	}
}
int Date::operator-(const Date& date) const
{
	return this->distance() - date.distance();
}
Date::operator int() const
{
	return this->distance();
}
void Date::show() const
{
	stringstream ss;
	ss << year << "-" << month << "-" << day;
	cout << setw(16) << setiosflags(ios::left) << ss.str();
}
int Date::getMaxDay()
{
	if (this->isLeapYear())
	{
		return LEAP_YEAR_DAYS;
	}
	else
	{
		return AVERAGE_YEAR_DAYS;
	}
}
// 返回一年中总天数
int Date::getMonthDays()
{
	if (month == 2 && isLeapYear())
	{
		return DAYS_IN_MONTH_FORM_AVERAGE[month - 1] + 1;
	}
	else {
		return DAYS_IN_MONTH_FORM_AVERAGE[month - 1];
	}
}
int Date::getYear() const
{
	return this->year;
}
int Date::getDay() const
{
	return this->day;
}
int Date::getMonth() const
{
	return this->month;
}