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
	printf("�����ڽ��й������:�������ɼ���\n����в�������");
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
		printf("�����������������롭��");
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
	printf("������༶:\n");
	int clas;
	scanf("%d",&clas);
	printf("��������%d��ĳɼ���\t",clas);
	printf("�Ƿ������(y/n):");
	scanf("%s", &ch);
	while (strcmp(ch, "y") == 0 || strcmp(ch, "Y") == 0) {
		printf("number:");
		scanf("%d", &inum);
		for (i = 0;i < m;i++) {//for ѭ�������ڲ����ļ����Ƿ��Ѿ����ڸ�ѧ���ŵ�ѧ��
			if (inum == fdx(i,uhead)->num&&fdx(i,uhead)&&clas==fdx(i,uhead)->clas) {
				printf("��ѧ���Ѵ���");
				system("pause");
				fclose(fp);
				return;
			}
		}
		up = (struct udata*)malloc(LEN);
		printf("����:");
		scanf("%s", &up->name);
		printf("��ѧ�ɼ�:");
		scanf("%lf", &up->math);
		printf("Ӣ��ɼ�:");
		scanf("%lf", &up->eng);
		printf("�����γɼ�:");
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
			printf("�޷�д��ɼ���");
			system("pause");
		}
		else {
			printf("%s�ĳɼ�����ɹ���", up->name);
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

void usearch() {
	int snum, i,clas, m = 0;
	FILE*fp;
	char ch[2];
	if ((fp = fopen("undergraduate.txt", "rb+")) == NULL)
	{
		fclose(fp);
		printf("�����������������롭��");
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
		printf("û��ѧ���ɼ���¼��");
		fclose(fp);
		return;
	}
	printf("������Ҫ��ѯ��ѧ����ѧ�źͰ༶:");
	scanf("%d%d", &snum,&clas);
	for (i = 1;i <= m;i++) {
		if (snum == fdx(i, uhead)->num&&clas==fdx(i,uhead)->clas) {
			printf("�ҵ���ѧ��,��ʾ��ѧ���ĳɼ���Ϣ��(y/n)");
			scanf("%s", &ch);
			if (strcmp(ch, "y") == 0 || strcmp(ch, "Y") == 0)
			{
				printf("number\tname\t\t��ѧ\t\tӢ��\t\t����\t\t�ܳɼ�\t\t����\n");
				printf(FORMAT, DATA);
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

void udelete() {
	int dnum, i,clas, m = 0;
	FILE*fp;
	char ch[2];
	if ((fp = fopen("undergraduate.txt", "rb")) == NULL)
	{
		fclose(fp);
		printf("�����������������롭��");
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
		printf("û��ѧ���ɼ���¼��");
		fclose(fp);
		return;
	}
	printf("������Ҫɾ����Ϣ��ѧ����ѧ�źͰ༶:");
	scanf("%d%d", &dnum,&clas);
	for (i = 1; i <= m; i++) {
		if (dnum == fdx(i, uhead)->num&&clas==fdx(i,uhead)->clas) {
			printf("number\tname\t\t��ѧ\t\tӢ��\t\t����\t\t�ܳɼ�\t\t����\n");
			printf(FORMAT, DATA);
			break;
		}
	}
	fclose(fp);
	printf("�ҵ��˸�ѧ���ĳɼ����Ƿ�ɾ����(y/n)\n");
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
		printf("�����������������롭��");
		system("pause");
		return;
	}
		for (i = 1; i <= m-1; i++) {
			if (fwrite(fdx(i, uhead), LEN, 1, fp) != 1) {
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

void umodify() {
	int mnum, i,clas, m = 0;
	FILE*fp;
	char ch[2];
	if ((fp = fopen("undergraduate.txt", "rb")) == NULL)
	{
		fclose(fp);
		printf("�����������������롭��");
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
		printf("û��ѧ���ɼ���¼��");
		fclose(fp);
		return;
	}
	printf("������Ҫ�޸���Ϣ��ѧ����ѧ�źͰ༶:");
	scanf("%d%d", &mnum,&clas);
	for (i = 1; i <= m; i++) {
		if (mnum == fdx(i, uhead)->num&&clas==fdx(i,uhead)->clas) {
			printf("number\tname\t\t��ѧ\t\tӢ��\t\t����\t\t�ܳɼ�\t\t����\n");
			printf(FORMAT, DATA);
			break;
		}
	}
	printf("�ҵ��˸�ѧ������Ϣ���Ƿ�����޸ģ�(y/n)");
	fclose(fp);
	scanf("%s", &ch);
	if ((strcmp(ch, "y")) == 0 || (strcmp(ch, "Y")) == 0) {

		printf("��ѧ�ɼ�:");
		scanf("%lf", &fdx(i,uhead)->math);
		printf("Ӣ��ɼ�:");
		scanf("%lf", &fdx(i,uhead)->eng);
		printf("�����γɼ�:");
		scanf("%lf", &fdx(i,uhead)->ath);
		fdx(i,uhead)->sum =fdx(i,uhead)->math + fdx(i,uhead)->eng +fdx(i,uhead)->ath;
		if ((fp = fopen("undergraduate.txt", "wb")) == NULL)
		{
			fclose(fp);
			printf("�����������������롭��");
			system("pause");
			return;
		}
		for (i = 1;i <= m;i++) {
			if (fwrite(fdx(i,uhead), LEN, 1, fp) != 1) {
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

void unumber() {
	int m = 0, clas;
	FILE*fp;
	if ((fp = fopen("undergraduate.txt", "rb")) == NULL)
	{
		fclose(fp);
		printf("�����������������롭��");
		system("pause");
		return;
	}
	printf("������༶:");
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
		printf("û��ѧ���ɼ���¼��");
	else
		printf("����༶ һ����%d��ͬѧ��", m);
	fclose(fp);
	return;
}

void uorder() {
	FILE*fp;
	int i = 0, j = 0, m = 0, k = 1;
	if ((fp = fopen("undergraduate.txt", "rb+")) == NULL)
	{
		fclose(fp);
		printf("�����������������롭��");
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
		printf("û�гɼ���Ϣ��");
		fclose(fp);
		return;
	}
	fclose(fp);
	printf("������Ҫ����İ༶(0Ϊ�꼶����):");
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
		printf("�����������������롭��");
		system("pause");
		return;
	}
	for (i = 1;i<=m;i++)
		if (fwrite(fdx(i,uhead), LEN, 1, fp) != 1) {
			printf("����ʧ�ܡ�");
			system("pause");
		}
	printf("����ɹ���");
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
		printf("�����������������롭��");
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
	printf("���سɹ����밴�༶ѡ��Ҫ��ʾ��ѧ����\n��ʾȫ��ѧ����ѡ��0��\n");
	int answer;
	scanf("%d", &answer);
	printf("number\tname\t\t\b����\t   �ۺ�\t\t\b�ܳɼ�\t\b����\t\b�༶\t\b�༶����\n");
	for (i = 1; i <= m; i++) {
		if (b % 10 == 0 && b >= 10) {
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
		if (answer == 0 || fdx(i, uhead)->clas == answer) {
			printf(FORMAT, DATA);
			b++;
		}
	}
	system("pause");
	fclose(fp);
	return;
}
