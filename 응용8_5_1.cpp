#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>

void intro_game(void);
void horizontal_slide(int x, int y, char *c2);
void draw_rectangle(int r, int c);
void display_text(int count, int r_count);
void game_control(int* r_c, int rnd);
void gotoxy(int x, int y);

int main(void)
{
   int count=0, rnd;
   int r_count=0;
   char *target="□";
   srand(time(NULL));
   intro_game();	
   do
   { // count가 10보다 작은 경우 반복
      system("cls");
      draw_rectangle(20, 20);
      rnd=rand()%35+4; // 4~35 사이의 난수 생성 
      gotoxy(rnd, 2);
      printf("%s", target);
      count++;
      display_text(count, r_count);
      game_control(&r_count, rnd);
   }while(count<10);
   return 0;
}

void intro_game(void)
{
	printf("말타며 화살쏘기\n\n");
	printf("말을 타고 이동하면서 \n");
	printf("목표물(□)을 맞추는 게임입니다. \n");
	printf("화살은 스페이스키로 발사합니다. \n\n");
	printf("아무키나 누르면 시작합니다. ");
	getch();

}
void horizontal_slide(int x, int y, char *c2)
{
		gotoxy(x, y);
		printf("%s", c2);
		Sleep(50);
		printf("\b ");
}
void draw_rectangle(int r, int c)
{ // 직사각형 생성. 
    int i, j;
    unsigned char a=0xa6;
    unsigned char b[7]; 
    for(i=1;i<7;i++)
   	b[i]=0xa0+i;

    printf("%c%c",a, b[3]); 
    for(i=0;i<c;i++)
  	printf("%c%c", a, b[1]);
    printf("%c%c", a, b[4]);
    printf("\n");
    for(i=0;i<r;i++)
    {
	printf("%c%c", a, b[2]);
	for(j=0;j<c;j++)
		printf("  ");
	printf("%c%c",a, b[2]);
	printf("\n");
    }
    printf("%c%c", a, b[6]);
    for(i=0;i<c;i++)
	printf("%c%c", a, b[1]);
    printf("%c%c", a, b[5]);
    printf("\n");
}
void display_text(int count, int r_count)
{ // 게임 진행 및 게임 상태 출력 
	gotoxy(46, 2);
	printf("스페이스키를 누르면\n");
	gotoxy(46, 3);
	printf("화살이 발사됩니다.\n");
	gotoxy(46, 5);
	printf("횟수 : %d", count);
	gotoxy(46, 6);
	printf("성공 : %d", r_count);
}

void game_control(int* r_c, int rnd)
{
	int i=1, k=1, y;
	char *horse="▲", chr;
	do
	{ // 입력값이 있을 경우 실행. 
		i+=k; // i = i + k;
		if (i>39) // 만일 i가 39보다 클 경우. 
			k=-1; // k = -1;
		else if (i<3) // 만일 i가 3보다 작은 경우
			k=+1; // k = +1;
		horizontal_slide(i+1, 21, horse);
	}while(!kbhit());
	chr=getch();
	y=21;
	if (chr==32) // 만일 입력 값이 스페이스바인 경우. 
	{
		while(y>2) // y가 2보다 작을때까지 반복. 
		{
			y-=1;
			gotoxy(i+1, y);
			printf("↑");
			Sleep(50);
			printf("\b  ");
		}
		if ((rnd<=i) && (i<=(rnd+1)))
		{ // 만약 rnd가 i보다 작거나 같은 경우  그리고 i가 rnd+1보다 작거나 같은경우 
			gotoxy(rnd, 2);
			printf("☆");
			gotoxy(46, 8);
			printf("맞았습니다. ");
			Sleep(50);
			*r_c=*r_c+1; 
		}
		gotoxy(1, 24);
		printf("아무키나 누르면 다음 진행...");
		getch();
	}

}
void gotoxy(int x, int y)
{
   COORD Pos = {x - 1, y - 1};
   SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
}
