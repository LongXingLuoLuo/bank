#pragma once
#include"date.h"
class Accumulator
{
private:
	// ����޸�����
	Date lastDate;
	// ����
	double value;
	// ����Ϣ
	double sum;
public:
	Accumulator(Date date, double value);
	double getSum() const;
	// �ı䱾�𣬼�����Ϣ
	void change(Date date,double value);
	// ���㣬��������Ϣ
	void reset(Date date, double value);
};

