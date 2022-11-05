#include "log.h"
#include"utils.h"
#include "config.h"
using namespace std;
int Log::info_i = 0;
int Log::warnning_i = 0;
void Log::info(string str)
{
	warnning_clear();
	if (info_i > INFO_MAX)
	{
		info_clear();
	}
	int x = INFO_X, y = INFO_Y + Log::info_i,len = INFO_LEN;
	if (str.length() > len)
	{
		str = str.substr(0, len) + "\0";
	}
	printToScreen(str, x, y, INFO_COLOR);
	info_i = info_i+1;
	
}
void Log::info_clear()
{
	char ch[INFO_LEN + 1] = {};
	for (int i = 0; i < INFO_LEN; i++)
	{
		ch[i] = ' ';
	}
	ch[INFO_LEN] = '\0';
	while (info_i)
	{
		int x = INFO_X, y = INFO_Y + info_i - 1, len = INFO_LEN;
		printToScreen(ch, x, y);
		info_i--;
	}
}
void Log::warnning(string str)
{
	info_clear();
	if (warnning_i > WARNNING_MAX)
	{
		warnning_clear();
	}
	int x = WARNNING_X, y = WARNNING_Y + warnning_i, len = WARNNING_LEN;
	if (str.length() > len)
	{
		str = str.substr(0, len) + "\0";
	}
	printToScreen(str, x,y, WARNNING_COLOR);
	warnning_i++;
}
void Log::warnning_clear()
{
	char ch[WARNNING_LEN + 1] = {};
	for (int i = 0; i < WARNNING_LEN; i++)
	{
		ch[i] = ' ';
	}
	ch[WARNNING_LEN] = '\0';
	while (warnning_i)
	{
		int x = WARNNING_X, y = WARNNING_Y + warnning_i - 1, len = WARNNING_LEN;
		printToScreen(ch, x, y);
		warnning_i--;
	}
}