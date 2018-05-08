#include<stdio.h>
#include<stdlib.h>
#include<conio.h>
#include<dos.h>
#include<string.h>
#include"malloc.h"
#define LEN sizeof(struct pdata)
#define FORMAT "%-8d%-15s%-12.1lf%-12.1lf%-12.1lf%-8d%-8d%-8d\n"
#define PDATA pfdx(i,phead)->num,pfdx(i,phead)->name,pfdx(i,phead)->paper,pfdx(i,phead)->overall,pfdx(i,phead)->sum,pfdx(i,phead)->order,pfdx(i,phead)->clas,pfdx(i,phead)->corder

struct pdata {
	int num;
	int order;
	int corder;
	int clas;
	char name[15];
	double paper;
	double overall;
	double sum;
	struct pdata *next;
};
static struct pdata *phead, *pp;

void pinput();
void psearch();
void pdelete();
void pmodify();
void porder();
void pnumber();
void pshow();
void pmenu();
struct pdata *pfdx(int m, struct pdata *phead) {
	struct pdata *p = phead;
	if (m <= 1) {
		return p;
	}
	else {
		struct pdata *p = phead->next;
		m--;
		pfdx(m, p);
	}
}
void pexchange(struct pdata*pp, struct pdata*pq) {
	pp->paper = pq->paper;
	pp->clas = pq->clas;
	pp->overall = pq->overall;
	strcpy(pp->name, pq->name);
	pp->num = pq->num;
	pp->sum = pq->sum;
}
void pmenu() {
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
	printf("您现在进行管理的是:研究生成绩。\n请进行操作…….");
}


void pstart() {
	pmenu();
	int n;
	scanf("%d", &n);
	while (n) {
		switch (n) {
		case 1:pinput(); break;
		case 2:psearch(); break;
		case 3:pdelete(); break;
		case 4:pmodify(); break;
		case 5:porder(); break;
		case 6:pnumber(); break;
		case 7:pshow(); break;
		default:break;
		}
		system("pause");
		pmenu();
		scanf("%d", &n);
	}
}

void pinput() {
	int i, inum, m = 0;
	FILE*fp;
	char ch[2];
	if ((fp = fopen("postgraduate.txt", "rb+")) == NULL)
	{
		fclose(fp);
		printf("输入有误，请重新输入……");
		system("pause");
		return;
	}
	while (!feof(fp)) {
		pp = (struct pdata*)malloc(LEN);
		if ((fread(pp, LEN, 1, fp) == 1) && pp->name != 0)
		{
			if (m == 0)
				phead = pp;
			else
				pfdx(m, phead)->next = pp;
			m++;
		}
	}
	printf("请输入班级:\n");
	int clas;
	scanf("%d", &clas);
	printf("即将输入%d班的成绩。\t", clas);
	printf("是否继续？(y/n):");
	scanf("%s", &ch);
	while (strcmp(ch, "y") == 0 || strcmp(ch, "Y") == 0) {
		printf("number:");
		scanf("%d", &inum);
		for (i = 0; i < m; i++) {//for 循环，用于查找文件中是否已经存在该学生号的学生
			if (inum == pfdx(i, phead)->num&&pfdx(i, phead) && clas == pfdx(i, phead)->clas) {
				printf("该学号已存在");
				system("pause");
				fclose(fp);
				return;
			}
		}
		pp = (struct pdata*)malloc(LEN);
		printf("姓名:");
		scanf("%s", &pp->name);
		printf("论文成绩:");
		scanf("%lf", &pp->paper);
		printf("综合成绩:");
		scanf("%lf", &pp->overall);
		pp->clas = clas;
		pp->num = inum;
		pp->sum = pp->paper + pp->overall;
		if (m == 0)
			phead = pp;
		else {
			pfdx(m, phead)->next = pp;
		}
		if (fwrite(pp, LEN, 1, fp) != 1) {
			printf("无法写入成绩。");
			system("pause");
		}
		else {
			printf("%s的成绩保存成功。", pp->name);
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

void psearch() {
	int snum, i, clas, m = 0;
	FILE*fp;
	char ch[2];
	if ((fp = fopen("postgraduate.txt", "rb+")) == NULL)
	{
		fclose(fp);
		printf("输入有误，请重新输入……");
		system("pause");
		return;
	}
	while (!feof(fp)) {
		pp = (struct pdata*)malloc(LEN);
		if ((fread(pp, LEN, 1, fp) == 1) && pp->name != 0)
		{
			if (m == 0)
				phead = pp;
			else
				pfdx(m, phead)->next = pp;
			m++;
		}
	}
	if (m == 0) {
		printf("没有学生成绩记录。");
		fclose(fp);
		return;
	}
	printf("请输入要查询的学生的学号和班级:");
	scanf("%d%d", &snum, &clas);
	for (i = 1; i <= m; i++) {
		if (snum == pfdx(i, phead)->num&&clas == pfdx(i, phead)->clas) {
			printf("找到该学生,显示该学生的成绩信息。(y/n)");
			scanf("%s", &ch);
			if (strcmp(ch, "y") == 0 || strcmp(ch, "Y") == 0)
			{
				printf("number\tname\t\t数学\t\t英语\t\t体育\t\t总成绩\t\t名次\n");
				printf(FORMAT, PDATA);
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

void pdelete() {
	int dnum, i, clas, m = 0;
	FILE*fp;
	char ch[2];
	if ((fp = fopen("postgraduate.txt", "rb")) == NULL)
	{
		fclose(fp);
		printf("输入有误，请重新输入……");
		system("pause");
		return;
	}
	while (!feof(fp)) {
		pp = (struct pdata*)malloc(LEN);
		if ((fread(pp, LEN, 1, fp) == 1) && pp->name != 0)
		{
			if (m == 0)
				phead = pp;
			else
				pfdx(m, phead)->next = pp;
			m++;
		}
	}
	if (m == 0) {
		printf("没有学生成绩记录。");
		fclose(fp);
		return;
	}
	printf("请输入要删除信息的学生的学号和班级:");
	scanf("%d%d", &dnum, &clas);
	for (i = 1; i <= m; i++) {
		if (dnum == pfdx(i, phead)->num&&clas == pfdx(i, phead)->clas) {
			printf("number\tname\t\t数学\t\t英语\t\t体育\t\t总成绩\t\t名次\n");
			printf(FORMAT, PDATA);
			break;
		}
	}
	fclose(fp);
	printf("找到了该学生的成绩，是否删除？(y/n)\n");
	scanf("%s", &ch);
	if (strcmp(ch, "y") == 0 || strcmp(ch, "Y") == 0)
	{
		if (pfdx(i, phead)->next != NULL) {
			if (i == 1) {
				pp = phead;
				phead = pp->next;
				free(pp);
			}
			else {
				pfdx(i - 1, phead)->next = pfdx((i + 1), phead);
				free(pfdx(i, phead));
			}
		}
		else {
			pfdx((i - 1), phead)->next = NULL;
			free(pfdx(i, phead));
		}
		if ((fp = fopen("postgraduate.txt", "wb")) == NULL)
		{
			fclose(fp);
			printf("输入有误，请重新输入……");
			system("pause");
			return;
		}
		for (i = 1; i <= m - 1; i++) {
			if (fwrite(pfdx(i, phead), LEN, 1, fp) != 1) {
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

void pmodify() {
	int mnum, i, clas, m = 0;
	FILE*fp;
	char ch[2];
	if ((fp = fopen("postgraduate.txt", "rb")) == NULL)
	{
		fclose(fp);
		printf("输入有误，请重新输入……");
		system("pause");
		return;
	}
	while (!feof(fp)) {
		pp = (struct pdata*)malloc(LEN);
		if ((fread(pp, LEN, 1, fp) == 1) && pp->name != 0)
		{
			if (m == 0)
				phead = pp;
			else
				pfdx(m, phead)->next = pp;
			m++;
		}
	}
	if (m == 0) {
		printf("没有学生成绩记录。");
		fclose(fp);
		return;
	}
	printf("请输入要修改信息的学生的学号和班级:");
	scanf("%d%d", &mnum, &clas);
	for (i = 1; i <= m; i++) {
		if (mnum == pfdx(i, phead)->num&&clas == pfdx(i, phead)->clas) {
			printf("number\tname\t\t数学\t\t英语\t\t体育\t\t总成绩\t\t名次\n");
			printf(FORMAT, PDATA);
			break;
		}
	}
	printf("找到了该学生的信息，是否继续修改？(y/n)");
	fclose(fp);
	scanf("%s", &ch);
	if ((strcmp(ch, "y")) == 0 || (strcmp(ch, "Y")) == 0) {

		printf("论文成绩:");
		scanf("%lf", &pfdx(i,phead)->paper);
		printf("综合成绩:");
		scanf("%lf", &pfdx(i, phead)->overall);
		pfdx(i, phead)->sum =pfdx(i, phead)->paper + pfdx(i, phead)->overall;
		if ((fp = fopen("postgraduate.txt", "wb")) == NULL)
		{
			fclose(fp);
			printf("输入有误，请重新输入……");
			system("pause");
			return;
		}
		for (i = 1; i <= m; i++) {
			if (fwrite(pfdx(i, phead), LEN, 1, fp) != 1) {
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

void pnumber() {
	int m = 0, clas;
	FILE*fp;
	if ((fp = fopen("postgraduate.txt", "rb")) == NULL)
	{
		fclose(fp);
		printf("输入有误，请重新输入……");
		system("pause");
		return;
	}
	printf("请输入班级:");
	scanf("%d", &clas);
	while (!feof(fp)) {
		pp = (struct pdata*)malloc(LEN);
		if ((fread(pp, LEN, 1, fp) == 1) && pp->name != 0)
		{
			if (m == 0)
				phead = pp;
			else
				pfdx(m, phead)->next = pp;
			if (pp->clas == clas)
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

void porder() {
	FILE*fp;
	int i = 0, j = 0, m = 0, k = 1;
	if ((fp = fopen("postgraduate.txt", "rb+")) == NULL)
	{
		fclose(fp);
		printf("输入有误，请重新输入……");
		system("pause");
		return;
	}
	while (!feof(fp)) {
		pp = (struct pdata*)malloc(LEN);
		if ((fread(pp, LEN, 1, fp) == 1) && pp->name != 0)
		{
			if (m == 0)
				phead = pp;
			else
				pfdx(m, phead)->next = pp;
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
	for (i = 1; i <m; i++) {
		for (j = i + 1; j <= m; j++) {
			if (pfdx(i, phead)->sum < pfdx(j, phead)->sum) {
				struct pdata*pp = (struct pdata*)malloc(LEN);
				pexchange(pp, pfdx(i, phead));
				pexchange(pfdx(i, phead), pfdx(j, phead));
				pexchange(pfdx(j, phead), pp);
				free(pp);
			}
		}
	}
	if (answer == 0) {
		for (i = 1; i <= m; i++) {
			if (i > 1 && pfdx(i, phead)->sum == pfdx(i - 1, phead)->sum) {
				pfdx(i, phead)->order = pfdx(i - 1, phead)->order;
			}
			else
				pfdx(i, phead)->order = i;
		}
	}
	else {
		for (i = 1; i <= m; i++) {
			if (pfdx(i, phead)->clas == answer) {
				for (j = i + 1; j <= m; j++) {
					if (pfdx(j, phead)->clas == answer && pfdx(i, phead)->sum < pfdx(j, phead)->sum)
						pfdx(j, phead)->corder = k;
					pfdx(i, phead)->corder = k;
				}
				pfdx(i, phead)->corder = k;
				k++;
			}
		}
	}
	if ((fp = fopen("postgraduate.txt", "wb")) == NULL)
	{
		fclose(fp);
		printf("输入有误，请重新输入……");
		system("pause");
		return;
	}
	for (i = 1; i <= m; i++)
		if (fwrite(pfdx(i, phead), LEN, 1, fp) != 1) {
			printf("排序失败。");
			system("pause");
		}
	printf("排序成功！");
	fflush(fp);
	fclose(fp);
	return;
}

void pshow() {
	int i, m = 0, a, b=0;
	FILE*fp;
	if ((fp = fopen("postgraduate.txt", "rb+")) == NULL)
	{
		fclose(fp);
		printf("输入有误，请重新输入……");
		system("pause");
		return;
	}
	while (!feof(fp)) {
		pp = (struct pdata*)malloc(LEN);
		if ((fread(pp, LEN, 1, fp) == 1) && pp->name != 0)
		{
			if (m == 0)
				phead = pp;
			else
				pfdx(m, phead)->next = pp;
			m++;

		}
	}
	printf("加载成功，请按班级选择要显示的学生。\n显示全部学生请选择0。\n");
	int answer;
	scanf("%d", &answer);
	printf("number\tname\t\t\b论文\t   综合\t\t\b总成绩\t\b名次\t\b班级\t\b班级名次\n");
		for (i = 1; i <= m; i++) {
			if (b%10==0&&b>=10) {
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
			if (answer == 0 || pfdx(i, phead)->clas == answer) {
			printf(FORMAT, PDATA);
			b++;
		}
	}
	system("pause");
	fclose(fp);
	return;
}
