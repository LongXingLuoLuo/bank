#include "accumulator.h"
Accumulator::Accumulator(Date date, double value) :lastDate(date)
{
	this->value = value;
	this->sum = 0.0f;
}
double Accumulator::getSum() const
{
	return this->sum;
}
void Accumulator::change(Date date, double value)
{
	double temp =  this->value * (date - this->lastDate) / lastDate.getMaxDays();
	temp = floor(temp * 100 + 0.5) / 100;
	sum += temp;
}
void Accumulator::reset(Date date, double value)
{
	this->lastDate = date;
	this->value = value;
	this->sum = 0.0f;
}