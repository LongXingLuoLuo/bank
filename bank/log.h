#pragma once
#include<string>
using namespace std;


class Log
{
private:
	static int info_i;
	static int warnning_i;
public:
	static void info(string str);
	static void info_clear();
	static void warnning(string str);
	static void warnning_clear();
};

