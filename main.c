#include<stdio.h>
#include<conio.h>
#include<dos.h>
#include<string.h>
#include"stdlib.h"
#include"share.h"
#include<windows.h>
FILE*fp;

main() {

	system("mode con cols=120 lines=46");
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO CursorInfo;
	GetConsoleCursorInfo(handle, &CursorInfo);
	CursorInfo.bVisible = 0;
	SetConsoleCursorInfo(handle, &CursorInfo);
	while (1)
	{
		int m;
		printf("\n");
		printf("\n");
		printf("\t\t\t\t@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@\n");
		printf("\t\t\t\t$\t\t\t\t\t\t$\n");
		printf("\t\t\t\t$\t\t\t\t\t\t$\n");
		printf("\t\t\t\t$\t欢迎使用波多野结衣成绩管理系统。\t$\n");
		printf("\t\t\t\t$\t\t\t\t\t\t$\n");
		printf("\t\t\t\t$\t\t\t\t\t\t$\n");
		printf("\t\t\t\t$\t\t\t\t\t\t$\n");
		printf("\t\t\t\t$\t  输入1进入本科生成绩管理。\t\t$\n");
		printf("\t\t\t\t$\t  输入2进入研究生成绩管理。\t\t$\n");
		printf("\t\t\t\t$\t\t\t\t\t\t$\n");
		printf("\t\t\t\t@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@\n");
		scanf("%d", &m);
		if (m == 1)
		{
			ustart();
		}
		else if (m == 2)
		{
			pstart();
		}
		else
			printf("您的输入有误，请重新输入。");
	}
}