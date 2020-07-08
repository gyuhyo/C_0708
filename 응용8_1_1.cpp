#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>

// 함수 사용을 위한 함수 원형 선언 
void move_arrow_key(char chr, int *x, int *y, int x_b, int y_b);
void gotoxy(int x, int y);
void draw_check01(int c, int r);
void game_control(void);

int main(void)
{
	// game_control 함수 호출 
	game_control();
	return 0;
}


void gotoxy(int x, int y) // 커서를 이동하는 함 
{
   COORD Pos = {x - 1, y - 1}; // typedef struct COORD = 좌표값을 저장하는 구조체 
   SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
   // SetConsoleCursorPosition 함수에 콘솔의 출력 핸들을 주고,
   // 위치를 정해주면 커서가 이동. 
}

void draw_check01(int c, int r)
{
    int i, j; // 정수형 변수 i, j 선언 
    unsigned char a=0xa6; // 특수기호 ┘ 코드 
    unsigned char b[12]; // 문자형 배열 b 선언 
    for(i=1;i<12;i++) // i가 1부터 11까지 1씩 증가하며 반복 
	b[i]=0xa0+i; //i가 반복될때 마다 b 배열의 i번째 인덱스에 0xa0+i를 저장 
    printf("%c%c",a, b[3]); // 특수기호 ┌ 출력 
    for(i=0;i<c-1;i++)
	 printf("%c%c", a, b[8]); // 특수기호 ┬출력 
    printf("%c%c", a, b[4]); // 특수기호 │ 출력 
    printf("\n");
    for(i=0;i<r-1;i++)
    {
	printf("%c%c", a, b[7]); // 특수기호 ├ 출력 
	for(j=0;j<c-1;j++)
	    printf("%c%c", a, b[11]); // 특수기호 ┼ 출력 
	printf("%c%c",a, b[9]); // 특수기호 ┤ 출력 
	printf("\n");
    }
    printf("%c%c", a, b[6]); // 특수기호 └ 출력 
    for(i=0;i<c-1;i++)
	printf("%c%c", a, b[10]); // 특수기호 ┴ 출력 
    printf("%c%c", a, b[5]); // 특수기호 ┘ 출력 
    printf("\n");
}

void game_control(void)
{
    int x=1, y=1;
    char key;
    do
    {
	gotoxy(1,1);
	draw_check01(18, 18);
	gotoxy(x, y);
	printf("○");
	gotoxy(1, 21);
	printf("방향키를 누르시오.");
	key=getch(); // 문자 입력 받음 
	if (key==27) // 왼쪽 화살키일 경우 
		exit(0); // 정상종료 
	else if (key>=72) // 다른 방향키일 경우 
		move_arrow_key(key, &x, &y, 37, 19); // 함수 호출
   }while(1); // 무한반복 
}

void move_arrow_key(char key, int *x1, int *y1, int x_b, int y_b)
{
	switch(key)
	{
	case 72:  //위쪽(상) 방향의 화살표 키 입력
		*y1=*y1-1;
		if (*y1<1)	*y1=1; //y좌표의 최소값
		break;
	case 75:  //왼쪽(좌) 방향의 화살표 키 입력
		*x1=*x1-2;             //좌측방향으로 2씩 감소
		if (*x1<1)	*x1=1; //x좌표의 최소값
		break;
	case 77:  //오른쪽(우) 방향의 화살표 키 입력
		*x1=*x1+2;               //우측방향으로 2씩 증가
		if (*x1>x_b)  *x1=x_b; //x좌표의 최대값(경계)
		break;
	case 80:  //아래쪽(하) 방향의 화살표 키 입력
		*y1=*y1+1;
		if (*y1>y_b)  *y1=y_b; //y좌표의 최대값(경계)
		break;
	default:
		return;
	}
}

