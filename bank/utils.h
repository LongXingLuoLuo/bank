#pragma once
#include<string>
#include"account.h"
#include<vector>
using namespace std;

//检测对应按键
#define KEYDOWN(VK_NONAME) ((GetAsyncKeyState(VK_NONAME) & 0x8000) ? 1:0) 
/*
	改变输出颜色
	0 = 黑色 1 = 蓝色 2 = 绿色 3 = 浅绿色 4 = 红色 5 = 紫色 6 = 黄色 7 = 白色
	8 = 灰色 9 = 淡蓝色 10 = 淡绿色 11 = 淡浅绿色 12 = 淡红色 13 = 淡紫色
	14 = 淡黄色 15 = 亮白色
*/
#define CHANGECOLOR(color)(SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | color))
//隐藏光标
#define HIDECURSOR() (SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), new CONSOLE_CURSOR_INFO{ 1,0 }))

// 移动函数
void gotoXY(const int x, const int y);
// 播放背景音乐
void playGround();

// 删除
struct deleter {
	template <class T> void operator () (T* p) { delete p; }
};

// 初始化
void utilsInit();
// 获取当前时间
string getNowDateFromUtils();
// 开始记录
void beginRecord();

// 控制台输出
void printToScreen(const string str,const int x, const int y,const int color = 7);
// 保存到文件
void save_to_file(string str);

// 执行命令
void commands(istringstream& is);
// 读取commands.txt命令
void read_commands_from_txt();

// 打印选择
void printChoice();
//清空边框内内容
void clearBorder();

// 结束
void utilsExit();

// 显示时间
void showTime();