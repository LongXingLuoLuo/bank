#include "log.h"
#include"utils.h"
#include "config.h"
using namespace std;
int info_i = 0;
int warnning_i = 0;
void Log::info(string str)
{
	if(info_i >= 5)
	{
		info_clear();
	}
	int x = INFO_X, y = INFO_Y + info_i,len = INFO_LEN;
	if (str.length() > len)
	{
		str = str.substr(0, len) + "\0";
	}
	printToScreen(str, x, y, INFO_COLOR);
	info_i++;
	
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
	
	int x = WARNNING_X, y = WARNNING_Y + warnning_i, len = WARNNING_LEN;
	warnning_i++;
	if (str.length() > len)
	{
		str = str.substr(0, len) + "\0";
	}
	printToScreen(str, x,y, WARNNING_COLOR);
}
void Log::warnning_clear()
{

}