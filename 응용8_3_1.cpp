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
   start=time(NULL); // ���� �ð��� �ʴ����� start�� ���� 
   time_pass(start);
   do
   {
   	// key ���� �Է� ����
	key=getch();
	switch(key)
	{
		/*
			���� Enter Ű�� ���� ��� time_pass(start) ȣ��,
			spacebar�� ���� ��� start�� ���� �ð��� ���� �� time_pass(start) ȣ�� ,
			esc Ű�� ���� ��� ����
			
			�� �۾��� key�� esc�� �ƴ� ��� �ݺ�
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
	Ű�� �Է����� ���� ��� �ݺ��Ͽ� ����
	now�� ���� �ð��� �ʴ����� ����.
	second ������ ���� �ð����� ���� �ð��� ���� ����.
	hour ������ second / 3600. �� ���� ����.
	nhour ������ hour���� ����� ����ȯ�� ����Ͽ� long ���·� ����.
	min ������ second/3600.�� �ε��Ҽ��� �������� / 60�� ���� ����.
	nmin ������ min���� long ���·� ��ȯ�Ͽ� ����.
	second ������ second / 60�� �ε��Ҽ��� ���������� ����.
	nsecond ������ second ���� long ���·� ��ȯ�Ͽ� ����.
	display_time(nhour, nmin, nsecond) �Լ� ȣ�� 
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
		ȭ���� ����� stopwatch�� ����� �ٹٲ� 2��
		nhour��, nmin��, nsecond�ʸ� ���
		Enter:(����... �߷� ���
	*/ 
	system("cls");
	printf("stopwatch\n\n");
	printf("%.2ld�� %.2ld�� %.2ld�� \n\n", nhour, nmin, nsecond);
	printf("Enter:(����/����), SPACE:�����, Esc:����\n");

}
