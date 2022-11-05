#include "account.h"
#include "error.h"
#include "config.h"
#include "utils.h"
#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
#include <sstream>
using namespace std;

int step_6() {
	// 读取文件
	read_commands_from_txt();
	wcout << "(a)add account (d)deposit (w)withdraw (s)show (c)change day (n)next month (q)query (e)exit" << endl;
	do {

		//显示日期和总金额

		//date.show();
		wcout << "Total: " << Account::getTotal() << "        command> ";
		string str;
		getline(cin,str);
		istringstream iss(str);
		commands(iss);

	} while (true);


	return 0;
	
}