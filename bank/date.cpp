#include "date.h"
#include<iostream>
#include<string>
#include <sstream>
using namespace std;
const int DATS_BEFORE_MONTH[] = { 0,31,59,90,120,151,181,212,243,273,304,334,365 };
#define LEAP_YEAR_DAYS 366
#define AVERAGE_YEAR_DAYS 365
Date::Date(int year, int month, int day)
{
	this->year = year;
	this->month = month;
	this->day = day;
}
int Date::daysCount()const
{
	int years = year - 1;
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
int Date::operator-(const Date& date)
{
	return this->daysCount() - date.daysCount();
}
Date::operator int()
{
	return this->daysCount();
}
std::string Date::show()
{
	stringstream ss;
	ss << year << "-" << month << "-" << day;
	return ss.str();
}
int Date::getYearDays()
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