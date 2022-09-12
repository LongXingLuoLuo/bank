#include "date.h"
#include<iostream>
#include<string>
#include <sstream>
using namespace std;
const int DATS_BEFORE_MONTH[] = { 0,31,59,90,120,151,181,212,243,273,304,334,365 };
#define LEAP_YEAR_DAYS 366 // 闰年天数
#define AVERAGE_YEAR_DAYS 365 // 平年天数
Date::Date(int year, int month, int day)
{
	this->year = year;
	this->month = month;
	this->day = day;
	this->totalDays = this->distance();
}
int Date::distance()const
{
	int years = this->year - 1;
	int results = years * 365 + years / 4 - years / 100 + years / 400
		+ DATS_BEFORE_MONTH[month - 1] + day;
	if (isLeapYear() && month > 2)
	{
		results++;
	}
	return results;
}
Date::Date(const Date& date)
{
	this->year = date.year;
	this->month = date.month;
	this->day = date.day;
	this->totalDays = date.totalDays;
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
std::string Date::show() const
{
	stringstream ss;
	ss << year << "-" << month << "-" << day;
	return ss.str();
}
int Date::getMaxDays()
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