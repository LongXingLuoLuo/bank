#pragma once
#include<string>
#include"account.h"
#include<vector>
using namespace std;

//����Ӧ����
#define KEYDOWN(VK_NONAME) ((GetAsyncKeyState(VK_NONAME) & 0x8000) ? 1:0) 
/*
	�ı������ɫ
	0 = ��ɫ 1 = ��ɫ 2 = ��ɫ 3 = ǳ��ɫ 4 = ��ɫ 5 = ��ɫ 6 = ��ɫ 7 = ��ɫ
	8 = ��ɫ 9 = ����ɫ 10 = ����ɫ 11 = ��ǳ��ɫ 12 = ����ɫ 13 = ����ɫ
	14 = ����ɫ 15 = ����ɫ
*/
#define CHANGECOLOR(color)(SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | color))
//���ع��
#define HIDECURSOR() (SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), new CONSOLE_CURSOR_INFO{ 1,0 }))

// �ƶ�����
void gotoXY(const int x, const int y);
// ���ű�������
void playGround();

// ɾ��
struct deleter {
	template <class T> void operator () (T* p) { delete p; }
};

// ��ʼ��
void utilsInit();
// ��ȡ��ǰʱ��
string getNowDateFromUtils();
// ��ʼ��¼
void beginRecord();

// ����̨���
void printToScreen(const string str,const int x, const int y,const int color = 7);
// ���浽�ļ�
void save_to_file(string str);

// ִ������
void commands(istringstream& is);
// ��ȡcommands.txt����
void read_commands_from_txt();

// ��ӡѡ��
void printChoice();
//��ձ߿�������
void clearBorder();

// ����
void utilsExit();

// ��ʾʱ��
void showTime();