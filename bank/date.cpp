#include"date.h"
#include"error.h"
#include<iostream>
#include<string>
#include<sstream>
#include<iomanip>
using namespace std;
namespace {
	const int DAYS_BEFORE_MONTH[] = { 0,31,59,90,120,151,181,212,243,273,304,334,365 };
	const int DAYS_IN_MONTH_FORM_AVERAGE[] = { 31,28,31,30,31,30,31,31,30,31,30,31 };
	const int LEAP_YEAR_DAYS = 366;// 平年天数
	const int AVERAGE_YEAR_DAYS = 365; // 平年天数
}

Date::Date()
{
	this->year = 1;
	this->month = 1;
	this->day = 1;
	this->totalDays = this->distance();
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
	this->totalDays = this->distance();
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
Date Date::stringToDate(string str)
{
	istringstream iss(str);
	// 缓存区
	string token;

	int dates[3] = { 0,1,1 };
	int i = 0;
	for (; i < 3 && getline(iss, token, '/'); i++)
	{
		istringstream istrstream(token);
		istrstream >> dates[i];
	}
	if (i < 3)
	{
		throw DateReadFormat(str);
	}
	return Date(dates[0], dates[1], dates[2]);
}
string Date::toString() const
{
	ostringstream oss;
	oss << year << "-" << month << "-" << day;
	return oss.str();
}

Date Date::read()
{
	string str;
	cin >> str;
	return stringToDate(str);
}
void Date::show() const
{
	cout << setw(16) << setiosflags(ios::left) << toString();
}

/*===========================================================*/
/*=============== operator() ================================*/
/*===========================================================*/
int Date::operator-(const Date& date) const
{
	return this->distance() - date.distance();
}
Date::operator int() const
{
	return this->distance();
}
// 重载 < 运算符
bool Date::operator<(const Date& date) const
{
	return this->distance() < date.distance();
}
// 重载 > 运算符
bool Date::operator>(const Date& date) const
{
	return this->distance() > date.distance();
}
// ostream << Date
ostream& operator<<(ostream& os, const Date& date)
{
	os << date.toString();
	return os;
}
// istream >> Date
istream& operator>>(istream& is, Date& date)
{
	string str;
	is >> str;
	date = Date::stringToDate(str);
	return is;
}

/*===========================================================*/
/*================= get() ===================================*/
/*===========================================================*/
int Date::getMaxDay() const
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