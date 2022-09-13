#pragma once
#include"date.h"
class Accumulator
{
private:
	// 最后修改日期
	Date lastDate;
	// 本金
	double value;
	// 总利息
	double sum;
public:
	Accumulator(Date date, double value);
	double getSum() const;
	// 改变本金，计算利息
	void change(Date date,double value);
	// 归零，不计算利息
	void reset(Date date, double value);
};

