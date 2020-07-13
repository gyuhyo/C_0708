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
		start=clock(); // 시작시간. 
		pst=0;
		do
		{
		  game_control(&r_start, start, &pst);
		}while(pst<game_time && ((8<r_start) && (r_start<32))); // pst가 game_time보다 작으면서 r_start가 8보다 크고 r_start가 32보다 작을 경우 반복. 
		make_decision(r_start, score_win, score_loose, team_name);
	}while((score_win[0]<2) && (score_win[1]<2)); // score_win[0]이 2보다 작고 score_win[1]이 2보다 작은 경우 반복. 
	gotoxy(1, 14);
	printf("게임을 종료합니다. \n");
	return 0;
}
double intro_game(char team_name[][7])
{
	double game_time;
	int i;
	printf("줄다리기 게임 \n\n");
	printf("3번 싸워서 2번 먼저 이긴 팀이 승자입니다.\n\n");
	printf("참가자는 두 팀입니다. \n");
	for(i=0;i<2;i++)
	{
		printf("%d번 참가팀의 이름을 입력하고 Enter>", i+1);
		scanf("%s", &team_name[i]);
	}

	printf("\n");
	printf("줄다리기 게임의 제한 시간(초 단위)을 입력하고 Enter>");
	scanf("%lf", &game_time);

	system("cls");

	gotoxy(1,1);
	printf("제한시간 : %5.1f 초", game_time);
	gotoxy(30, 1);
	printf("경과시간 : %4.1f초",0);
	
	gotoxy(38, 6);
	printf("기준점");
	gotoxy(40, 7);
	printf("▼");
	gotoxy(40, 9);
	printf("▲");
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
		if (line[i]==0) // line[i]가 0인경우 
			printf("□"); 
		else if (line[i]==1) // line[i]가 1인 경우. 
			printf("■"); // 기준점. 
		else // line[i]가 0, 1이 아닌경우. 
			printf("◆");

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
			printf("%d승, %d패", s_w[i], s_l[i]);
		}

		gotoxy(1,13);
		printf("아무키나 누르면 경기를 시작합니다. ");
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
	{ // r_s가 20보다 큰 경우. 
		win=2; // user2가 승. 
		s_w[1]+=1; // 1승 추가. 
		s_l[0]+=1; // user1 1패 추가. 
	}
	else if (r_s<20)
	{ // 만약 r_s가 20보다 작은 경우. 
		win=1; // user1 승. 
		s_w[0]+=1; // 1승 추가. 
		s_l[1]+=1; // user2 1패 추가. 
	}
	else
		win=0;
	gotoxy(1, 12);
	if (win) // win = 0(false)이 아닌 경우. 
		printf("%s팀이 이겼습니다. ", t_name[win-1]);
	else // 0인 경우. 
		printf("비겼습니다,");
		gotoxy(1,13);
		printf("아무키나 누르세요. ");
		getch(); // 버퍼제거. 

}
void game_control(int *r_s, clock_t st, double *ps)
{
	int rnd, i;
	clock_t end;

	rnd=rand()%100; // 난수 생성. 
	if (rnd%2) // rnd(난수)를 2로 나눈 나머지가 0이 아닌 경우. 
		rnd=rnd%4; // rnd를 4로 나눈 나머지를 rnd에 저장. 
	else // 0인 경우. 
		rnd=-rnd%4; 
	if (rnd<0)
	{ // rnd가 음수인 경우. 
		for(i=*r_s;i>(*r_s+rnd);i--)  //줄을 왼쪽방향으로 이동
		{
			display_line(i);		
			Sleep(100);
		}
	}
	else
	{
		for(i=*r_s;i<(*r_s+rnd);i++) //줄을 오른쪽방향으로 이동
		{
			display_line(i);		
			Sleep(100);
		}
	}
	if (rnd<0)
		*r_s=i+1;   
	else
		*r_s=i-1;

		end=clock(); // 종료시간. 
		*ps=(double)(end-st)/CLK_TCK; // 수행시간. 
		gotoxy(30, 1);
		printf("경과시간 : %4.1f초",*ps);
}
