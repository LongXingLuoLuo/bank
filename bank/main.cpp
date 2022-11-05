#include"log.h"
#include"utils.h"
#include<iostream>
#include<conio.h>
#include <windows.h>
#include"config.h"
#include<sstream>
using namespace std;
int main() 
{
	utilsInit();
	
	bool work = true;
	do
	{
		if (_kbhit())
		{
			clearBorder();
			gotoXY(BORDER_LEFT + 4, BORDER_TOP + 4);
			CHANGECOLOR(11);
			string str;
			getline(cin,str);
			istringstream iss(str);
			try {
				// 执行命令
				commands(iss);
			}
			catch (exception& e) {
				Log::warnning(e.what());
			}
			if (str[0] == 'e') {
				break;
			}
			clearBorder();
			printChoice();
		}
		Sleep(50);
	}while (work);

	utilsExit();
	return 0;
}