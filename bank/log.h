#pragma once
#include<string>
using namespace std;


class Log
{
public:
	static void info(string str);
	static void info_clear();
	static void warnning(string str);
	static void warnning_clear();
};

