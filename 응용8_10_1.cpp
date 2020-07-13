#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <time.h>
#include <windows.h>

double intro_game(char team_name[][7]);
void gotoxy(int x, int y);
void display_line(int rand);
void display_start(char t_name[][7], int s_w[], int s_l[]);
void make_decision(int r_s, int s_w[], int s_l[], char t_name[][7]);
void game_control(int *r_s, clock_t st, double *ps);

int main(void)
{
	int score_win[2]={0}, score_loose[2]={0}, r_start;
	char team_name[2][7];
	double pst, game_time;
	clock_t start;

	srand(time(NULL));
	game_time=intro_game(team_name);
	do
	{
		display_start(team_name, score_win, score_loose);
		r_start=20;
		start=clock(); // ���۽ð�. 
		pst=0;
		do
		{
		  game_control(&r_start, start, &pst);
		}while(pst<game_time && ((8<r_start) && (r_start<32))); // pst�� game_time���� �����鼭 r_start�� 8���� ũ�� r_start�� 32���� ���� ��� �ݺ�. 
		make_decision(r_start, score_win, score_loose, team_name);
	}while((score_win[0]<2) && (score_win[1]<2)); // score_win[0]�� 2���� �۰� score_win[1]�� 2���� ���� ��� �ݺ�. 
	gotoxy(1, 14);
	printf("������ �����մϴ�. \n");
	return 0;
}
double intro_game(char team_name[][7])
{
	double game_time;
	int i;
	printf("�ٴٸ��� ���� \n\n");
	printf("3�� �ο��� 2�� ���� �̱� ���� �����Դϴ�.\n\n");
	printf("�����ڴ� �� ���Դϴ�. \n");
	for(i=0;i<2;i++)
	{
		printf("%d�� �������� �̸��� �Է��ϰ� Enter>", i+1);
		scanf("%s", &team_name[i]);
	}

	printf("\n");
	printf("�ٴٸ��� ������ ���� �ð�(�� ����)�� �Է��ϰ� Enter>");
	scanf("%lf", &game_time);

	system("cls");

	gotoxy(1,1);
	printf("���ѽð� : %5.1f ��", game_time);
	gotoxy(30, 1);
	printf("����ð� : %4.1f��",0);
	
	gotoxy(38, 6);
	printf("������");
	gotoxy(40, 7);
	printf("��");
	gotoxy(40, 9);
	printf("��");
	return game_time;
}
void gotoxy(int x, int y)
{
   COORD Pos = {x - 1, y - 1};
   SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
}
void display_line(int rnd)
{
	int i, line[21]={0};
	line[10]=1;
	line[4]=2;
	line[16]=2;
	gotoxy(1, 8);
	for(i=0;i<78;i++)
		printf(" ");

	gotoxy(rnd, 8);
	
	for(i=0;i<21;i++)
		if (line[i]==0) // line[i]�� 0�ΰ�� 
			printf("��"); 
		else if (line[i]==1) // line[i]�� 1�� ���. 
			printf("��"); // ������. 
		else // line[i]�� 0, 1�� �ƴѰ��. 
			printf("��");

}

void display_start(char t_name[][7], int s_w[], int s_l[])
{
	int i, r_start=20;
	display_line(20);

		for(i=0;i<2;i++)
		{
			gotoxy(i*55+10, 6);
			printf("%s", t_name[i]);
			gotoxy(i*55+10, 7);
			printf("%d��, %d��", s_w[i], s_l[i]);
		}

		gotoxy(1,13);
		printf("�ƹ�Ű�� ������ ��⸦ �����մϴ�. ");
		getch();
		gotoxy(1, 12);
		printf("                                   ");
		gotoxy(1,13);
		printf("                                   ");
}
void make_decision(int r_s, int s_w[], int s_l[], char t_name[][7])
{
	int win;
	if (20<r_s)
	{ // r_s�� 20���� ū ���. 
		win=2; // user2�� ��. 
		s_w[1]+=1; // 1�� �߰�. 
		s_l[0]+=1; // user1 1�� �߰�. 
	}
	else if (r_s<20)
	{ // ���� r_s�� 20���� ���� ���. 
		win=1; // user1 ��. 
		s_w[0]+=1; // 1�� �߰�. 
		s_l[1]+=1; // user2 1�� �߰�. 
	}
	else
		win=0;
	gotoxy(1, 12);
	if (win) // win = 0(false)�� �ƴ� ���. 
		printf("%s���� �̰���ϴ�. ", t_name[win-1]);
	else // 0�� ���. 
		printf("�����ϴ�,");
		gotoxy(1,13);
		printf("�ƹ�Ű�� ��������. ");
		getch(); // ��������. 

}
void game_control(int *r_s, clock_t st, double *ps)
{
	int rnd, i;
	clock_t end;

	rnd=rand()%100; // ���� ����. 
	if (rnd%2) // rnd(����)�� 2�� ���� �������� 0�� �ƴ� ���. 
		rnd=rnd%4; // rnd�� 4�� ���� �������� rnd�� ����. 
	else // 0�� ���. 
		rnd=-rnd%4; 
	if (rnd<0)
	{ // rnd�� ������ ���. 
		for(i=*r_s;i>(*r_s+rnd);i--)  //���� ���ʹ������� �̵�
		{
			display_line(i);		
			Sleep(100);
		}
	}
	else
	{
		for(i=*r_s;i<(*r_s+rnd);i++) //���� �����ʹ������� �̵�
		{
			display_line(i);		
			Sleep(100);
		}
	}
	if (rnd<0)
		*r_s=i+1;   
	else
		*r_s=i-1;

		end=clock(); // ����ð�. 
		*ps=(double)(end-st)/CLK_TCK; // ����ð�. 
		gotoxy(30, 1);
		printf("����ð� : %4.1f��",*ps);
}
