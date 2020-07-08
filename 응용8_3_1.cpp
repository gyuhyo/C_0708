#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <conio.h>

void time_pass(time_t start);
void display_time(long nhour, long nmin, long nsecond);
void control_watch(void);

int main(void)
{
	display_time(0, 0, 0);
	getch();
	control_watch();
	return 0;
}
void control_watch(void)
{
   char key;
   time_t start;
   start=time(NULL); // 현재 시간을 초단위로 start에 삽입 
   time_pass(start);
   do
   {
   	// key 값을 입력 받음
	key=getch();
	switch(key)
	{
		/*
			만약 Enter 키를 누른 경우 time_pass(start) 호출,
			spacebar를 누른 경우 start에 현재 시간을 삽입 후 time_pass(start) 호출 ,
			esc 키를 누른 경우 종료
			
			위 작업을 key가 esc가 아닌 경우 반복
		*/
	   case 10 :
		time_pass(start);
	   case 32 : 
		start=time(NULL);
		time_pass(start);
		break;
	   case 27 : 
		exit(0);
		break;
	}
   }while(key!=27);

}
void time_pass(time_t start)
{
double hour, min, second;
long nhour, nmin, nsecond;
time_t now;
while(!kbhit())
{
	/*
	키를 입력하지 않은 경우 반복하여 실행
	now에 현재 시간을 초단위로 담음.
	second 변수에 현재 시간에서 시작 시간을 빼서 저장.
	hour 변수에 second / 3600. 의 값을 저장.
	nhour 변수에 hour값을 명시적 형변환을 사용하여 long 형태로 저장.
	min 변수에 second/3600.의 부동소수점 나머지값 / 60의 값을 저장.
	nmin 변수에 min값을 long 형태로 변환하여 저장.
	second 변수에 second / 60의 부동소수점 나머지값을 저장.
	nsecond 변수에 second 값을 long 형태로 변환하여 저장.
	display_time(nhour, nmin, nsecond) 함수 호출 
	*/
	now=time(NULL);
	second=difftime(now, start);
	hour= (second/3600.);
	nhour= (long) hour;
	min= fmod(second, 3600.)/60;
	nmin= (long) min;
	second= fmod(second, 60);
	nsecond= (long) second;
	display_time(nhour, nmin, nsecond);
 }
}
void display_time(long nhour, long nmin, long nsecond)
{
	/*
		화면을 지우고 stopwatch를 출력후 줄바꿈 2번
		nhour시, nmin분, nsecond초를 출력
		Enter:(시작... 중략 출력
	*/ 
	system("cls");
	printf("stopwatch\n\n");
	printf("%.2ld시 %.2ld분 %.2ld초 \n\n", nhour, nmin, nsecond);
	printf("Enter:(시작/정지), SPACE:재시작, Esc:종료\n");

}
