#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <time.h>
#include <windows.h>

void display_rule(void);
void draw_check02(int c, int r);
void reel_series(int r[][3]);
void gotoxy(int x, int y);
int game_progress(int money);
void display_reel(char rc[][3], int r[][3], int index);
void clear_text(void);
void game_control(char reel[][3], int reel_num[][3], int *money);
int  return_money(int r[], int betting, int *case_n);

int main(void)
{
	char reel[6][3]={"★", "♠", "◆", "♥", "♣", "○"};
	int  i, reel_num[3][3];
	int money=10000;
	srand(time(NULL));
	printf("  슬롯머신 게임\n\n");
	display_rule();
	gotoxy(3, 5);
	printf("릴1 릴2 릴3");
	gotoxy(1,6);
	draw_check02(3, 3);
	for(i=0;i<3;i++)
		reel_num[0][i]=rand()%5;
	reel_series(reel_num);
	
	do
	{
		game_control(reel, reel_num, &money);
	}while(money); // money가 0이 될때까지 반복. 
	gotoxy(3,20);
	return 0;
}
void display_rule(void)
{
	gotoxy(30, 3); 
	printf("   릴1   릴2  릴3  사례금\n"); 
	gotoxy(30, 4); 
	printf("--------------------------\n");
	gotoxy(30, 5); 
	printf(" 1: ★   ★   ★\t*10\n"); 
	gotoxy(30, 6); 
	printf(" 2: ♠   ♠   ♠\t *7\n"); 
	gotoxy(30, 7); 
	printf(" 3: ◆   ◆   ◆\t *5\n"); 
	gotoxy(30, 8); 
	printf(" 4: ★   ★   기타\t *4\n"); 
	gotoxy(30, 9); 
	printf(" 5: ♠   ♠   기타\t *3\n"); 
	gotoxy(30, 10); 
	printf(" 6: ◆   ◆   기타\t *3\n"); 
	gotoxy(30, 11); 
	printf(" 7: ♥   ♥   기타\t *3\n"); 
	gotoxy(30, 12); 
	printf(" 8: ♣   ♣   기타\t *2\n"); 
	gotoxy(30, 13); 
	printf(" 9: ○   ○   기타\t *1\n"); 

}

void draw_check02(int c, int r)
{ // 가로 3칸 세로 3칸의 격자판 출력. 
    int i, j;
    unsigned char a=0xa6;
    unsigned char b[12]; 
    for(i=1;i<12;i++)
	b[i]=0xa0+i;
    printf("%c%c",a, b[3]);
    for(i=0;i<c-1;i++)
    {
	printf("%c%c", a, b[1]);
	printf("%c%c", a, b[8]);
    }
    printf("%c%c", a, b[1]);
    printf("%c%c", a, b[4]);
    printf("\n");
    for(i=0;i<r-1;i++)
    {
	printf("%c%c", a, b[2]);
	for(j=0;j<c;j++)
	{
		printf("  ");
		printf("%c%c",a, b[2]);
	}
	printf("\n");
	printf("%c%c", a, b[7]);
	for(j=0;j<c-1;j++)
	{
		printf("%c%c", a, b[1]);
		printf("%c%c", a, b[11]);
	}
	printf("%c%c",a, b[1]);
	printf("%c%c",a, b[9]);
	printf("\n");
    }
    printf("%c%c", a, b[2]);
    for(j=0;j<c;j++)
    {
	printf("  ");
	printf("%c%c",a, b[2]);
    }
    printf("\n");
    printf("%c%c", a, b[6]);
    for(i=0;i<c-1;i++)
    {
	printf("%c%c", a, b[1]);
	printf("%c%c", a, b[10]);
    }
    printf("%c%c", a, b[1]);
    printf("%c%c", a, b[5]);
    printf("\n");
}

void reel_series(int r[][3])
{
	int i, j;
	for(i=0;i<3;i++)
		for(j=0;j<3;j++)
			r[j][i]=(r[0][i]+j)%6; // r[j][i]에 r[0][i]+j를 6으로 나눈 나머지를 저장. 

}
void gotoxy(int x, int y)
{
   COORD Pos = {x - 1, y - 1};
   SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
}
int game_progress(int money)
{
    int bet;
	gotoxy(43, 17);
	printf("현재 남은 금액 : %d원", money);
	gotoxy(1, 17);
	printf("배팅금액을 입력하고 Enter키를 누르면 ");
	gotoxy(1, 19);
	printf("0을 입력하면 종료합니다.");
	gotoxy(1, 18);
	printf("게임을 시작합니다. 금액 입력>");
	gotoxy(30, 18);
	scanf("%d", &bet);
	if (bet==0) // 배팅금액이 0원인경우 종료. 
		exit(0);
	gotoxy(1, 19);
	printf("아무키나 한번만 키를 누르면 릴이 멈춥니다.");
	return bet;

}
void display_reel(char rc[][3], int r[][3], int index)
{
	int i, j;
	for(i=0;i<3;i++)
		for(j=index;j<3;j++)
		{
			gotoxy(3+j*4, 7+i*2);
			printf("%s", rc[r[i][j]]); // rc에 저장된 슬롯 문자를 출력. 
		}

}

void clear_text(void)
{
	int i, j;
	for(i=17;i<20;i++)
	{
		gotoxy(1, i);
		for(j=0;j<42;j++)
			printf(" "); // (17, 0) ~ (19, 41) 좌표의 문자를 지움. 
	}

}
void game_control(char reel[][3], int reel_num[][3], int *money)
{
	int i, j, bet, case_num=0, thank, num[3];
	double pst;
	clock_t start, end;

	display_reel(reel, reel_num, 0);
	bet=game_progress(*money);

	for(i=0;i<3;i++)
	{
		start=clock(); // 시작시간. 
		do
		{
			for(j=i;j<3;j++)
				reel_num[0][j]=reel_num[1][j];
			reel_series(reel_num);		
			display_reel(reel, reel_num, i);
			end=clock();
			pst=(double)(end-start)/CLK_TCK; // 수행시간. 
		}while(!kbhit() || (pst<1)); // 입력문자가 없거나 pst가 1보다 작은 경우 반복. 
		num[i]=reel_num[1][i];
	}
	getch();
	thank=return_money(num, bet, &case_num);
	if (thank==0)
		*money-=bet;
	else
		*money+=thank;
	if (case_num)
	{ // 이긴 경우(case_num이 0(false)이 아닌 경우) 실행. 
	  gotoxy(43, 18);
	  printf("사례:%d, 배팅:%d원, 사례금:%d", case_num, bet, thank);
	}
	clear_text();

}
int  return_money(int r[], int betting, int *case_num)
{
	int total=0;
	if (r[0]==r[1] && r[1]==r[2]  && r[0]==r[2])
	{ // 만약 r[0]이 r[1]과 같고, r[1]이 r[2]와 같고 r[0]이 r[2]와 같은 경우. 
		if (r[0]==0)
		{ // 만약 r[0]이 0과 같을 경우. 
			total=betting*10; // 배팅금액의 10을 곱함. 
			*case_num=1;
		}
		else if (r[0]==1)
		{ // r[0]이 1과 같을 경우. 
			total=betting*7; // 배팅금액 * 7 
			*case_num=2;
		}
		else if (r[0]==2)
		{ // r[0]이 2와 같을 경우. 
			total=betting*5; // 배팅금액 * 5 
			*case_num=3;
		}
	}
	else if((r[0]==0 && r[1]==0) || (r[1]==0 && r[2]==0) || 		   (r[0]==0 && r[2]==0))
	{ // 만약 r[0]이 0과 같고 r[1]이 0과 같거나 r[1]이 0과 같고 r[2]가 0과 같거나 r[0]이 0과 같고 r[2]가 0과 같은 경우. 
		total=betting*4; // 배팅금액 * 4 
		*case_num=4;
	}
	else if( (r[0]==1 && r[1]==1) || (r[1]==1 && r[2]==1 ) || 		   (r[0]==1 && r[2]==1))
	{ // 만약 r[0]이 1과 같고 r[1]이 1과 같거나 r[1]이 1과 같고 r[2]가 1과 같거나 r[0]이 1과 같고 r[2]가 1과 같은 경우. 
		total=betting*3; // 배팅금액 * 3
		*case_num=5;
	}
	else if( (r[0]==2 && r[1]==2) || (r[1]==2 && r[2]==2 ) || 		   (r[0]==2 && r[2]==2))
	{ // 만약 r[0]이 2과 같고 r[1]이 2과 같거나 r[1]이 2과 같고 r[2]가 2과 같거나 r[0]이 2과 같고 r[2]가 2과 같은 경우. 
		total=betting*3; // 배팅금액 * 3 
		*case_num=6;
	}
	else if( (r[0]==3 && r[1]==3) || (r[1]==3 && r[2]==3 ) || 		   (r[0]==3 && r[2]==3))
	{ // 만약 r[0]이 3과 같고 r[1]이 3과 같거나 r[1]이 3과 같고 r[2]가 3과 같거나 r[0]이 3과 같고 r[2]가 3과 같은 경우. 
		total=betting*3; // 배팅금액 * 3 
		*case_num=7;
	}
	else if( (r[0]==4 && r[1]==4) || (r[1]==4 && r[2]==4 ) || 		   (r[0]==4 && r[2]==4))
	{ // 만약 r[0]이 4과 같고 r[1]이 4과 같거나 r[1]이 4과 같고 r[2]가 4과 같거나 r[0]이 4과 같고 r[2]가 4과 같은 경우. 
		total=betting*2; // 배팅금액 * 2 
		*case_num=8;
	}
	else if( (r[0]==5 && r[1]==5) || (r[1]==5 && r[2]==5 ) || 		   (r[0]==5 && r[2]==5))
	{ // 만약 r[0]이 5과 같고 r[1]이 5과 같거나 r[1]이 5과 같고 r[2]가 5과 같거나 r[0]이 5과 같고 r[2]가 5과 같은 경우. 
		total=betting*1; // 배팅금액 * 1 
		*case_num=9;
	}
	return total; // total 반환. 
}
