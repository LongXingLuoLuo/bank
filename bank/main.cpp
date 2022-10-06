#include"log.h"
#include"utils.h"
#include<iostream>
#include<conio.h>
#include <windows.h>
using namespace std;
int main() 
{
	utilsInit();
	read_commands_from_txt();
	while (true)
	{
		gotoXY(0, 0);
		if (_kbhit())
		{
			char a[2] = {};
			a[0] = _getch();
			Log::info(a);
			if (a[0] == 'e')
			{
				break;
			}
		}
		Sleep(50);
	}

	utilsExit();
	return 0;
}