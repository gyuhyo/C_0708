#include <stdio.h>
#include <conio.h>
#include <string.h>
#include <windows.h>

void control_scoreboard(int st,int end,int r[],int h[],int e[], int b[]);
void display_scoreboard(int r[], int h[], int e[], int b[]);
void draw_check02(int c, int r);
void gotoxy(int x, int y);

int main(void)
{
	int  baseball[12][2]={0},r[2]={0},h[2]={0},e[2]={0},b[2]={0};
	display_scoreboard(r, h, e, b);
	control_scoreboard(1, 9, r, h, e, b);
	control_scoreboard(10, 12, r, h, e, b);
	gotoxy(1, 15);
	printf("무승부입니다. 아무키나 누르시오\n");
	getch();
	return 0;
}

void draw_check02(int c, int r)
{
	/*
		17 x 3 크기의 격자판 생성 
	*/
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

void display_scoreboard(int r[], int h[], int e[], int b[])
{
	int i, j;
	printf("스코어보드 \n");
	draw_check02(17, 3);
	for(i=1;i<=12;i++)
	{
		// (7, 3) ~ (51, 3) 까지 x 좌표를 4씩 증가 시켜가며 해당 좌표에 i 값을 출력 
		gotoxy(i*4+3, 3);
		printf("%2d", i);
	}
	/*
		56, 3 좌표 : R 출력
		60, 3 좌표 : H 출력 
		64, 3 좌표 : E 출력 
		68, 3 좌표 : B 출력
		3, 5 좌표 : CL 출력 
		3, 7 좌표 : TG 출력
	*/
	gotoxy(13*4+4, 3); 
	printf("R");
	gotoxy(14*4+4, 3);
	printf("H");
	gotoxy(15*4+4, 3);
	printf("E");
	gotoxy(16*4+4, 3);
	printf("B");
	gotoxy(3, 5);
	printf("CL");
	gotoxy(3, 7);
	printf("TG");
	for(j=0;j<=1;j++)
	{
		/*
			(55, 5), (55, 7) 좌표 : r[j] 값 출력
			(59, 5), (59, 7) 좌표 : h[j] 값 출력
			(63, 5), (63, 7) 좌표 : e[j] 값 출력
			(67, 5), (67, 7) 좌표 : b[j] 값 출력
		*/
		gotoxy(13*4+3, 5+2*j);
		printf("%2d", r[j]);
		gotoxy(14*4+3, 5+2*j);
		printf("%2d", h[j]);
		gotoxy(15*4+3, 5+2*j);
		printf("%2d", e[j]);
		gotoxy(16*4+3, 5+2*j);
		printf("%2d", b[j]);
	}
}
void control_scoreboard(int st,int end, int r[], int h[], int e[], int b[])
{
   int i, j, k, rr, hh, ee, bb;
   char state[3];
   for(i=st;i<=end;i++)
   {// st부터 end까지 i값을 1씩 증가시키며 반복 
 	for(j=0;j<=1;j++)
	{
		/*
			j가 0인경우 state = 초, 아닌경우 state = 말
			(i*4+3, 5+2*j) 좌표로 이동하여 0을 출력
			(1, 10) 좌표로 이동하여 n회 말 or 초 결과 출력
			(1, 11) 좌표로 이동하여 안타수 입력 출력 후 hh값을 입력받음
			h배열의 j인덱스에 h[j]의 값 + 입력한 hh값을 더하여 저장
			(14*4+3, 5+2*j) 좌표로 이동하여 h[j]값 출력
			실책, 포볼, 점수 또한 안타 실행문들과 마찬가지로 실행
			(1, 15) 좌표로 이동하여 아무키나 입력... 출력,
			키를 입력 받음. 
		*/
		if (j==0) 
			strcpy(state, "초");
		else
			strcpy(state, "말");
		gotoxy(i*4+3, 5+2*j);
		printf("%2d", 0);
		gotoxy(1, 10);
		printf("%d회%s 결과 ", i, state);
		gotoxy(1, 11);

		printf("안타수 입력 : ");
		scanf("%d", &hh);
		h[j]+=hh;
		gotoxy(14*4+3, 5+2*j);
		printf("%2d", h[j]);
		gotoxy(1, 12);

		printf("실책수 입력 : ");
		scanf("%d", &ee);
		e[j]+=ee;
		gotoxy(15*4+3, 5+2*(1-j));
		printf("%2d", e[j]);

		gotoxy(1, 13);
		printf("포볼수 입력 : ");
		scanf("%d", &bb);
		b[j]+=bb;
		gotoxy(16*4+3, 5+2*j);
		printf("%2d", b[j]);
		gotoxy(1, 14);
		printf("점수   입력 : ");
		scanf("%d", &rr);
		r[j]+=rr;
		gotoxy(13*4+3, 5+2*j);
		printf("%2d", r[j]);

		gotoxy(i*4+3, 5+2*j);
		printf("%2d", rr);

		gotoxy(1, 15);
		printf("아무키나 누르시오....");
		getch();
		for(k=10; k<=15; k++)
		{
			/*
				k를 10부터 15까지 1씩 증가하면서 반복하며,
				(1, 10~15) 좌표에 공백문을 출력 
			*/
			gotoxy(1, k);
		    	printf("                       ");
		}
		if (9<=i&&((j==0&& r[0]<r[1]) || (j==1 && r[0]!=r[1])))
		{
			/* 
				만약 i가 9보다 크거나 같으면서 j가 0이고 r[1]이 r[0]보다 크거나 아니면 j가 1이고 r[0]과 r[1]이 같지 않은 경우,
				(1, 15) 좌표로 이동하여 경기가 끝났습니다...를 출력후 아무키나 입력을 받은 후 종료
			*/ 
			gotoxy(1, 15);
			printf("경기가 끝났습니다. 아무키나 누르시오\n");
			getch();
			exit(0);
		}
	}
   }
}

void gotoxy(int x, int y)
{
   COORD Pos = {x - 1, y - 1};
   SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
}

