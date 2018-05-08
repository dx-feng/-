#include<stdio.h>
#include<stdlib.h>
#include<conio.h>
#include<dos.h>
#include<string.h>
#include"malloc.h"
#define LEN sizeof(struct udata)
#define FORMAT "%-8d%-15s%-12.1lf%-12.1lf%-12.1lf%-12.1lf%-8d%-8d%-8d\n"
#define DATA fdx(i,uhead)->num,fdx(i,uhead)->name,fdx(i,uhead)->math,fdx(i,uhead)->eng,fdx(i,uhead)->ath,fdx(i,uhead)->sum,fdx(i,uhead)->order,fdx(i,uhead)->clas,fdx(i,uhead)->corder

struct udata {
	int num;
	int order;
	int corder;
	int clas;
	char name[15];
	double math;
	double eng;
	double ath;
	double sum;
	struct udata *next;
};
static struct udata *uhead, *up;

void uinput();
void usearch();
void udelete();
void umodify();
void uorder();
void unumber();
void ushow();
void umenu();
struct udata *fdx(int m, struct udata *uhead) {
    struct udata *p=uhead;
	if (m <= 1) {
		return p;
	}
	else {
		struct udata *p = uhead->next;
		m--;
		fdx(m, p);
	}
}
void exchange(struct udata*up,struct udata*uq) {
	up->ath = uq->ath;
	up->clas = uq->clas;
	up->eng = uq->eng;
	up->math = uq->math;
	strcpy(up->name, uq->name);
	up->num = uq->num;
	up->sum = uq->sum;
}
void umenu() {
	system("cls");
	printf("\n\n\n\n\n\n");

	printf("\t\t|--------------------学生成绩管理系统-------------------|\n");
	printf("\t\t|0.退出系统。 	 					|\n");
	printf("\t\t|1.录入成绩。 	 					|\n");
	printf("\t\t|2.检索成绩。 	 					|\n");
	printf("\t\t|3.删除成绩。  						|\n");
	printf("\t\t|4.修改成绩。  						|\n");
	printf("\t\t|5.排序。	 					|\n");
	printf("\t\t|6.统计学生人数。   			        	|\n");
	printf("\t\t|7.显示。						|\n");
	printf("\t\t|-------------------------------------------------------|\n");
	printf("您现在进行管理的是:本科生成绩。\n请进行操作……");
}


void ustart() {
	umenu();
	int n;
	scanf("%d", &n);
	while (n) {
		switch (n) {
		case 1:uinput();break;
		case 2:usearch();break;
		case 3:udelete();break;
		case 4:umodify();break;
		case 5:uorder();break;
		case 6:unumber();break;
		case 7:ushow();break;
		default:break;
		}
		system("pause");
		umenu();
		scanf("%d", &n);
	}
}

void uinput() {
	int i, inum, m = 0;
	FILE*fp;
	char ch[2];
	if ((fp = fopen("undergraduate.txt", "rb+")) == NULL)
	{
		fclose(fp);
		printf("输入有误，请重新输入……");
		system("pause");
		return;
	}
	while (!feof(fp)) {
		up = (struct udata*)malloc(LEN);
		if ((fread(up, LEN, 1, fp) == 1) && up->name != 0)
		{
			if (m == 0)
				uhead = up;
			else
				fdx(m, uhead)->next = up;
				m++;
		}
	}
	printf("请输入班级:\n");
	int clas;
	scanf("%d",&clas);
	printf("即将输入%d班的成绩。\t",clas);
	printf("是否继续？(y/n):");
	scanf("%s", &ch);
	while (strcmp(ch, "y") == 0 || strcmp(ch, "Y") == 0) {
		printf("number:");
		scanf("%d", &inum);
		for (i = 0;i < m;i++) {//for 循环，用于查找文件中是否已经存在该学生号的学生
			if (inum == fdx(i,uhead)->num&&fdx(i,uhead)&&clas==fdx(i,uhead)->clas) {
				printf("该学号已存在");
				system("pause");
				fclose(fp);
				return;
			}
		}
		up = (struct udata*)malloc(LEN);
		printf("姓名:");
		scanf("%s", &up->name);
		printf("数学成绩:");
		scanf("%lf", &up->math);
		printf("英语成绩:");
		scanf("%lf", &up->eng);
		printf("体育课成绩:");
		scanf("%lf", &up->ath);
		up -> clas = clas;
		up->num = inum;
		up->sum = up->math + up->eng +up->ath;
		if (m == 0)
			uhead = up;
		else {
			fdx(m, uhead)->next = up;
		}
		if (fwrite(up, LEN, 1, fp) != 1) {
			printf("无法写入成绩。");
			system("pause");
		}
		else {
			printf("%s的成绩保存成功。", up->name);
			fflush(fp);
			m++;
			printf("是否继续？(y/n):");
			scanf("%s", &ch);
		}
	}
	printf("OK！\n");
	fclose(fp);
	return;
}

void usearch() {
	int snum, i,clas, m = 0;
	FILE*fp;
	char ch[2];
	if ((fp = fopen("undergraduate.txt", "rb+")) == NULL)
	{
		fclose(fp);
		printf("输入有误，请重新输入……");
		system("pause");
		return;
	}
	while (!feof(fp)) {
		up = (struct udata*)malloc(LEN);
		if ((fread(up, LEN, 1, fp) == 1) && up->name != 0)
		{
			if (m == 0)
				uhead = up;
			else
				fdx(m, uhead)->next = up;
			m++;
		}
	}
	if (m == 0) {
		printf("没有学生成绩记录。");
		fclose(fp);
		return;
	}
	printf("请输入要查询的学生的学号和班级:");
	scanf("%d%d", &snum,&clas);
	for (i = 1;i <= m;i++) {
		if (snum == fdx(i, uhead)->num&&clas==fdx(i,uhead)->clas) {
			printf("找到该学生,显示该学生的成绩信息。(y/n)");
			scanf("%s", &ch);
			if (strcmp(ch, "y") == 0 || strcmp(ch, "Y") == 0)
			{
				printf("number\tname\t\t数学\t\t英语\t\t体育\t\t总成绩\t\t名次\n");
				printf(FORMAT, DATA);
			}
			break;
			fclose(fp);
			return;
		}
	}
	if (i == m)
		printf("找不到该学生。\n");
	fclose(fp);
}

void udelete() {
	int dnum, i,clas, m = 0;
	FILE*fp;
	char ch[2];
	if ((fp = fopen("undergraduate.txt", "rb")) == NULL)
	{
		fclose(fp);
		printf("输入有误，请重新输入……");
		system("pause");
		return;
	}
	while (!feof(fp)) {
		up = (struct udata*)malloc(LEN);
		if ((fread(up, LEN, 1, fp) == 1) && up->name != 0)
		{
			if (m == 0)
				uhead = up;
			else
				fdx(m, uhead)->next = up;
			m++;
		}
	}
	if (m == 0) {
		printf("没有学生成绩记录。");
		fclose(fp);
		return;
	}
	printf("请输入要删除信息的学生的学号和班级:");
	scanf("%d%d", &dnum,&clas);
	for (i = 1; i <= m; i++) {
		if (dnum == fdx(i, uhead)->num&&clas==fdx(i,uhead)->clas) {
			printf("number\tname\t\t数学\t\t英语\t\t体育\t\t总成绩\t\t名次\n");
			printf(FORMAT, DATA);
			break;
		}
	}
	fclose(fp);
	printf("找到了该学生的成绩，是否删除？(y/n)\n");
	scanf("%s", &ch);
	if (strcmp(ch, "y") == 0 || strcmp(ch, "Y") == 0)
	{
		if (fdx(i, uhead)->next != NULL) {
			if (i == 1) {
				up = uhead;
				uhead = up->next;
				free(up);
			}
			else {
				fdx(i - 1, uhead)->next = fdx((i + 1), uhead);
				free(fdx(i, uhead));
			}
		}
		else {
			fdx((i - 1), uhead)->next = NULL;
			free(fdx(i,uhead));
		}
	if ((fp = fopen("undergraduate.txt", "wb")) == NULL)
	{
		fclose(fp);
		printf("输入有误，请重新输入……");
		system("pause");
		return;
	}
		for (i = 1; i <= m-1; i++) {
			if (fwrite(fdx(i, uhead), LEN, 1, fp) != 1) {
				printf("无法写入成绩。");
				system("pause");
				fclose(fp);
				return;
			}
		}
		printf("成绩删除成功。");
		fflush(fp);
	}
	system("pause");
	fclose(fp);
}

void umodify() {
	int mnum, i,clas, m = 0;
	FILE*fp;
	char ch[2];
	if ((fp = fopen("undergraduate.txt", "rb")) == NULL)
	{
		fclose(fp);
		printf("输入有误，请重新输入……");
		system("pause");
		return;
	}
	while (!feof(fp)) {
		up = (struct udata*)malloc(LEN);
		if ((fread(up, LEN, 1, fp) == 1) && up->name != 0)
		{
			if (m == 0)
				uhead = up;
			else
				fdx(m, uhead)->next = up;
			m++;
		}
	}
	if (m == 0) {
		printf("没有学生成绩记录。");
		fclose(fp);
		return;
	}
	printf("请输入要修改信息的学生的学号和班级:");
	scanf("%d%d", &mnum,&clas);
	for (i = 1; i <= m; i++) {
		if (mnum == fdx(i, uhead)->num&&clas==fdx(i,uhead)->clas) {
			printf("number\tname\t\t数学\t\t英语\t\t体育\t\t总成绩\t\t名次\n");
			printf(FORMAT, DATA);
			break;
		}
	}
	printf("找到了该学生的信息，是否继续修改？(y/n)");
	fclose(fp);
	scanf("%s", &ch);
	if ((strcmp(ch, "y")) == 0 || (strcmp(ch, "Y")) == 0) {

		printf("数学成绩:");
		scanf("%lf", &fdx(i,uhead)->math);
		printf("英语成绩:");
		scanf("%lf", &fdx(i,uhead)->eng);
		printf("体育课成绩:");
		scanf("%lf", &fdx(i,uhead)->ath);
		fdx(i,uhead)->sum =fdx(i,uhead)->math + fdx(i,uhead)->eng +fdx(i,uhead)->ath;
		if ((fp = fopen("undergraduate.txt", "wb")) == NULL)
		{
			fclose(fp);
			printf("输入有误，请重新输入……");
			system("pause");
			return;
		}
		for (i = 1;i <= m;i++) {
			if (fwrite(fdx(i,uhead), LEN, 1, fp) != 1) {
				printf("无法写入成绩。");
				system("pause");
				fclose(fp);
				return;
			}
			fflush(fp);
		}
		fclose(fp);
		printf("成绩修改成功。");
	}
	fclose(fp);
	return;

}

void unumber() {
	int m = 0, clas;
	FILE*fp;
	if ((fp = fopen("undergraduate.txt", "rb")) == NULL)
	{
		fclose(fp);
		printf("输入有误，请重新输入……");
		system("pause");
		return;
	}
	printf("请输入班级:");
	scanf("%d",&clas);
	while (!feof(fp)) {
		up = (struct udata*)malloc(LEN);
		if ((fread(up, LEN, 1, fp) == 1) && up->name != 0)
		{
			if (m == 0)
				uhead = up;
			else
				fdx(m, uhead)->next = up;
			if(up->clas==clas)
			m++;
		}
	}
	if (m == 0) 
		printf("没有学生成绩记录。");
	else
		printf("这个班级 一个有%d名同学。", m);
	fclose(fp);
	return;
}

void uorder() {
	FILE*fp;
	int i = 0, j = 0, m = 0, k = 1;
	if ((fp = fopen("undergraduate.txt", "rb+")) == NULL)
	{
		fclose(fp);
		printf("输入有误，请重新输入……");
		system("pause");
		return;
	}
	while (!feof(fp)) {
		up = (struct udata*)malloc(LEN);
		if ((fread(up, LEN, 1, fp) == 1) && up->name != 0)
		{
			if (m == 0)
				uhead = up;
			else
				fdx(m, uhead)->next = up;
			m++;
		}
	}
	if (m == 0) {
		printf("没有成绩信息。");
		fclose(fp);
		return;
	}
	fclose(fp);
	printf("请输入要排序的班级(0为年级排序):");
	int answer;
	scanf("%d", &answer);
	for (i = 1;i <m ;i++) {
		for (j = i + 1;j <= m;j++) {
			if (fdx(i, uhead)->sum < fdx(j, uhead)->sum) {
				struct udata*up = (struct udata*)malloc(LEN);
				exchange(up, fdx(i, uhead));
				exchange(fdx(i, uhead), fdx(j, uhead));
				exchange(fdx(j, uhead), up);
				free(up);
			}
		}
	}
	if (answer == 0) {
		for (i = 1; i <= m; i++) {
			if (i > 1 && fdx(i, uhead)->sum == fdx(i - 1, uhead)->sum) {
				fdx(i, uhead)->order = fdx(i - 1, uhead)->order;
			}
			else
				fdx(i, uhead)->order = i;
		}
	}
	else {
		for (i = 1; i <= m; i++) {
			if (fdx(i, uhead)->clas == answer) {
				for (j = i+1; j <= m; j++) {
					if (fdx(j, uhead)->clas == answer && fdx(i, uhead)->sum < fdx(j, uhead)->sum)
						fdx(j, uhead)->corder = k;
					fdx(i, uhead)->corder = k;
				}
				fdx(i, uhead)->corder = k;
				k++;
			}
		}
	}
	if ((fp = fopen("undergraduate.txt", "wb")) == NULL)
	{
		fclose(fp);
		printf("输入有误，请重新输入……");
		system("pause");
		return;
	}
	for (i = 1;i<=m;i++)
		if (fwrite(fdx(i,uhead), LEN, 1, fp) != 1) {
			printf("排序失败。");
			system("pause");
		}
	printf("排序成功！");
	fflush(fp);
	fclose(fp);
	return;
}

void ushow() {
	int i, m = 0, a, b=0;
	FILE*fp;
	if ((fp = fopen("undergraduate.txt", "rb+")) == NULL)
	{
		fclose(fp);
		printf("输入有误，请重新输入……");
		system("pause");
		return;
	}
	while (!feof(fp)) {
		up = (struct udata*)malloc(LEN);
		if ((fread(up, LEN, 1, fp) == 1) && up->name != 0)
		{
			if (m == 0)
				uhead = up;
			else 
				fdx(m, uhead)->next = up;
				m++;
			
		}
	}
	printf("加载成功，请按班级选择要显示的学生。\n显示全部学生请选择0。\n");
	int answer;
	scanf("%d", &answer);
	printf("number\tname\t\t\b论文\t   综合\t\t\b总成绩\t\b名次\t\b班级\t\b班级名次\n");
	for (i = 1; i <= m; i++) {
		if (b % 10 == 0 && b >= 10) {
			if (b / 10 == 1 && b % 10 == 0) {
				printf("\n请输入1,下一页.3,尾页.\n");
				scanf("%d", &a);
			}
			else if (b / 10 > 1 && b % 10 == 0) {
				printf("\n请输入1,下一页.2,上一页.3,首页.4,尾页\n");
				scanf("%d", &a);
			}
			switch (a) {
			case 1: {system("cls");
				printf("number\tname\t\t\b论文\t   综合\t\t\b总成绩\t\b名次\t\b班级\t\b班级名次\n"); }break;
			case 2:i -= 19; break;
			case 3: i = 1; break;
			case 4:i = m - 9; break;
			default:return;
			}
		}
		if (answer == 0 || fdx(i, uhead)->clas == answer) {
			printf(FORMAT, DATA);
			b++;
		}
	}
	system("pause");
	fclose(fp);
	return;
}
