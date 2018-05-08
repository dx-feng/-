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

	printf("\t\t|--------------------ѧ���ɼ�����ϵͳ-------------------|\n");
	printf("\t\t|0.�˳�ϵͳ�� 	 					|\n");
	printf("\t\t|1.¼��ɼ��� 	 					|\n");
	printf("\t\t|2.�����ɼ��� 	 					|\n");
	printf("\t\t|3.ɾ���ɼ���  						|\n");
	printf("\t\t|4.�޸ĳɼ���  						|\n");
	printf("\t\t|5.����	 					|\n");
	printf("\t\t|6.ͳ��ѧ��������   			        	|\n");
	printf("\t\t|7.��ʾ��						|\n");
	printf("\t\t|-------------------------------------------------------|\n");
	printf("�����ڽ��й������:�о����ɼ���\n����в�������.");
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
		printf("�����������������롭��");
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
	printf("������༶:\n");
	int clas;
	scanf("%d", &clas);
	printf("��������%d��ĳɼ���\t", clas);
	printf("�Ƿ������(y/n):");
	scanf("%s", &ch);
	while (strcmp(ch, "y") == 0 || strcmp(ch, "Y") == 0) {
		printf("number:");
		scanf("%d", &inum);
		for (i = 0; i < m; i++) {//for ѭ�������ڲ����ļ����Ƿ��Ѿ����ڸ�ѧ���ŵ�ѧ��
			if (inum == pfdx(i, phead)->num&&pfdx(i, phead) && clas == pfdx(i, phead)->clas) {
				printf("��ѧ���Ѵ���");
				system("pause");
				fclose(fp);
				return;
			}
		}
		pp = (struct pdata*)malloc(LEN);
		printf("����:");
		scanf("%s", &pp->name);
		printf("���ĳɼ�:");
		scanf("%lf", &pp->paper);
		printf("�ۺϳɼ�:");
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
			printf("�޷�д��ɼ���");
			system("pause");
		}
		else {
			printf("%s�ĳɼ�����ɹ���", pp->name);
			fflush(fp);
			m++;
			printf("�Ƿ������(y/n):");
			scanf("%s", &ch);
		}
	}
	printf("OK��\n");
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
		printf("�����������������롭��");
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
		printf("û��ѧ���ɼ���¼��");
		fclose(fp);
		return;
	}
	printf("������Ҫ��ѯ��ѧ����ѧ�źͰ༶:");
	scanf("%d%d", &snum, &clas);
	for (i = 1; i <= m; i++) {
		if (snum == pfdx(i, phead)->num&&clas == pfdx(i, phead)->clas) {
			printf("�ҵ���ѧ��,��ʾ��ѧ���ĳɼ���Ϣ��(y/n)");
			scanf("%s", &ch);
			if (strcmp(ch, "y") == 0 || strcmp(ch, "Y") == 0)
			{
				printf("number\tname\t\t��ѧ\t\tӢ��\t\t����\t\t�ܳɼ�\t\t����\n");
				printf(FORMAT, PDATA);
			}
			break;
			fclose(fp);
			return;
		}
	}
	if (i == m)
		printf("�Ҳ�����ѧ����\n");
	fclose(fp);
}

void pdelete() {
	int dnum, i, clas, m = 0;
	FILE*fp;
	char ch[2];
	if ((fp = fopen("postgraduate.txt", "rb")) == NULL)
	{
		fclose(fp);
		printf("�����������������롭��");
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
		printf("û��ѧ���ɼ���¼��");
		fclose(fp);
		return;
	}
	printf("������Ҫɾ����Ϣ��ѧ����ѧ�źͰ༶:");
	scanf("%d%d", &dnum, &clas);
	for (i = 1; i <= m; i++) {
		if (dnum == pfdx(i, phead)->num&&clas == pfdx(i, phead)->clas) {
			printf("number\tname\t\t��ѧ\t\tӢ��\t\t����\t\t�ܳɼ�\t\t����\n");
			printf(FORMAT, PDATA);
			break;
		}
	}
	fclose(fp);
	printf("�ҵ��˸�ѧ���ĳɼ����Ƿ�ɾ����(y/n)\n");
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
			printf("�����������������롭��");
			system("pause");
			return;
		}
		for (i = 1; i <= m - 1; i++) {
			if (fwrite(pfdx(i, phead), LEN, 1, fp) != 1) {
				printf("�޷�д��ɼ���");
				system("pause");
				fclose(fp);
				return;
			}
		}
		printf("�ɼ�ɾ���ɹ���");
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
		printf("�����������������롭��");
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
		printf("û��ѧ���ɼ���¼��");
		fclose(fp);
		return;
	}
	printf("������Ҫ�޸���Ϣ��ѧ����ѧ�źͰ༶:");
	scanf("%d%d", &mnum, &clas);
	for (i = 1; i <= m; i++) {
		if (mnum == pfdx(i, phead)->num&&clas == pfdx(i, phead)->clas) {
			printf("number\tname\t\t��ѧ\t\tӢ��\t\t����\t\t�ܳɼ�\t\t����\n");
			printf(FORMAT, PDATA);
			break;
		}
	}
	printf("�ҵ��˸�ѧ������Ϣ���Ƿ�����޸ģ�(y/n)");
	fclose(fp);
	scanf("%s", &ch);
	if ((strcmp(ch, "y")) == 0 || (strcmp(ch, "Y")) == 0) {

		printf("���ĳɼ�:");
		scanf("%lf", &pfdx(i,phead)->paper);
		printf("�ۺϳɼ�:");
		scanf("%lf", &pfdx(i, phead)->overall);
		pfdx(i, phead)->sum =pfdx(i, phead)->paper + pfdx(i, phead)->overall;
		if ((fp = fopen("postgraduate.txt", "wb")) == NULL)
		{
			fclose(fp);
			printf("�����������������롭��");
			system("pause");
			return;
		}
		for (i = 1; i <= m; i++) {
			if (fwrite(pfdx(i, phead), LEN, 1, fp) != 1) {
				printf("�޷�д��ɼ���");
				system("pause");
				fclose(fp);
				return;
			}
			fflush(fp);
		}
		fclose(fp);
		printf("�ɼ��޸ĳɹ���");
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
		printf("�����������������롭��");
		system("pause");
		return;
	}
	printf("������༶:");
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
		printf("û��ѧ���ɼ���¼��");
	else
		printf("����༶ һ����%d��ͬѧ��", m);
	fclose(fp);
	return;
}

void porder() {
	FILE*fp;
	int i = 0, j = 0, m = 0, k = 1;
	if ((fp = fopen("postgraduate.txt", "rb+")) == NULL)
	{
		fclose(fp);
		printf("�����������������롭��");
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
		printf("û�гɼ���Ϣ��");
		fclose(fp);
		return;
	}
	fclose(fp);
	printf("������Ҫ����İ༶(0Ϊ�꼶����):");
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
		printf("�����������������롭��");
		system("pause");
		return;
	}
	for (i = 1; i <= m; i++)
		if (fwrite(pfdx(i, phead), LEN, 1, fp) != 1) {
			printf("����ʧ�ܡ�");
			system("pause");
		}
	printf("����ɹ���");
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
		printf("�����������������롭��");
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
	printf("���سɹ����밴�༶ѡ��Ҫ��ʾ��ѧ����\n��ʾȫ��ѧ����ѡ��0��\n");
	int answer;
	scanf("%d", &answer);
	printf("number\tname\t\t\b����\t   �ۺ�\t\t\b�ܳɼ�\t\b����\t\b�༶\t\b�༶����\n");
		for (i = 1; i <= m; i++) {
			if (b%10==0&&b>=10) {
				if (b / 10 == 1 && b % 10 == 0) {
					printf("\n������1,��һҳ.3,βҳ.\n");
					scanf("%d", &a);
				}
				else if (b / 10 > 1 && b % 10 == 0) {
					printf("\n������1,��һҳ.2,��һҳ.3,��ҳ.4,βҳ\n");
					scanf("%d", &a);
				}
				switch (a) {
				case 1: {system("cls");
					printf("number\tname\t\t\b����\t   �ۺ�\t\t\b�ܳɼ�\t\b����\t\b�༶\t\b�༶����\n"); }break;
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
