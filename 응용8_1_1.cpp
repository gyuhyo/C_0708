#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>

// �Լ� ����� ���� �Լ� ���� ���� 
void move_arrow_key(char chr, int *x, int *y, int x_b, int y_b);
void gotoxy(int x, int y);
void draw_check01(int c, int r);
void game_control(void);

int main(void)
{
	// game_control �Լ� ȣ�� 
	game_control();
	return 0;
}


void gotoxy(int x, int y) // Ŀ���� �̵��ϴ� �� 
{
   COORD Pos = {x - 1, y - 1}; // typedef struct COORD = ��ǥ���� �����ϴ� ����ü 
   SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
   // SetConsoleCursorPosition �Լ��� �ܼ��� ��� �ڵ��� �ְ�,
   // ��ġ�� �����ָ� Ŀ���� �̵�. 
}

void draw_check01(int c, int r)
{
    int i, j; // ������ ���� i, j ���� 
    unsigned char a=0xa6; // Ư����ȣ �� �ڵ� 
    unsigned char b[12]; // ������ �迭 b ���� 
    for(i=1;i<12;i++) // i�� 1���� 11���� 1�� �����ϸ� �ݺ� 
	b[i]=0xa0+i; //i�� �ݺ��ɶ� ���� b �迭�� i��° �ε����� 0xa0+i�� ���� 
    printf("%c%c",a, b[3]); // Ư����ȣ �� ��� 
    for(i=0;i<c-1;i++)
	 printf("%c%c", a, b[8]); // Ư����ȣ ����� 
    printf("%c%c", a, b[4]); // Ư����ȣ �� ��� 
    printf("\n");
    for(i=0;i<r-1;i++)
    {
	printf("%c%c", a, b[7]); // Ư����ȣ �� ��� 
	for(j=0;j<c-1;j++)
	    printf("%c%c", a, b[11]); // Ư����ȣ �� ��� 
	printf("%c%c",a, b[9]); // Ư����ȣ �� ��� 
	printf("\n");
    }
    printf("%c%c", a, b[6]); // Ư����ȣ �� ��� 
    for(i=0;i<c-1;i++)
	printf("%c%c", a, b[10]); // Ư����ȣ �� ��� 
    printf("%c%c", a, b[5]); // Ư����ȣ �� ��� 
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
	printf("��");
	gotoxy(1, 21);
	printf("����Ű�� �����ÿ�.");
	key=getch(); // ���� �Է� ���� 
	if (key==27) // ���� ȭ��Ű�� ��� 
		exit(0); // �������� 
	else if (key>=72) // �ٸ� ����Ű�� ��� 
		move_arrow_key(key, &x, &y, 37, 19); // �Լ� ȣ��
   }while(1); // ���ѹݺ� 
}

void move_arrow_key(char key, int *x1, int *y1, int x_b, int y_b)
{
	switch(key)
	{
	case 72:  //����(��) ������ ȭ��ǥ Ű �Է�
		*y1=*y1-1;
		if (*y1<1)	*y1=1; //y��ǥ�� �ּҰ�
		break;
	case 75:  //����(��) ������ ȭ��ǥ Ű �Է�
		*x1=*x1-2;             //������������ 2�� ����
		if (*x1<1)	*x1=1; //x��ǥ�� �ּҰ�
		break;
	case 77:  //������(��) ������ ȭ��ǥ Ű �Է�
		*x1=*x1+2;               //������������ 2�� ����
		if (*x1>x_b)  *x1=x_b; //x��ǥ�� �ִ밪(���)
		break;
	case 80:  //�Ʒ���(��) ������ ȭ��ǥ Ű �Է�
		*y1=*y1+1;
		if (*y1>y_b)  *y1=y_b; //y��ǥ�� �ִ밪(���)
		break;
	default:
		return;
	}
}

