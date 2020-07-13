#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <time.h>
#include <windows.h>

void gotoxy(int x, int y);
void game_control(int order, char name[7], char sol[][10], double check[][10], int quest);
void display_result(int user, int order[], double check[][10], char name[][7], char sol[][10], int quest);
void display_rule(void);

int main(void)
{
	int i, user_number, quest_number, rnd, temp;
	int order[4]={0, 1, 2, 3};
	char solution[4][10]={0}; 
	double time_check[4][10]={0};
	char user_name[4][7];
	srand(time(NULL));

	printf("청기/백기 게임\n\n");
	printf("게임에 참가할 인원수를 입력하고 Enter>");
	scanf("%d", &user_number);
	printf("\n문제의 개수를 입력하고 Enter>");
	scanf("%d", &quest_number);

	for(i=0;i<user_number;i++)
	{ // 참가 인원만큼 반복하여 이름을 입력받음. 
		printf("%d번 참가자의 이름을 입력하고 Enter>", i+1);
		scanf("%s", &user_name[i]);
	}
	printf("만약 한글을 사용하였다면 영문키로 바꾸십시오.\n");
	printf("아무키나 누르시오.\n");
	getch(); // 버퍼제거. 
   printf("\n게임의 순서는 다음과 같습니다. \n");
   for(i=0;i<user_number;i++)
   { // 참가인원 만큼 반복. 
 	rnd=rand()%user_number; // 0부터 참가인원 사이의 난수 생성.
 	// swap
	temp=order[i];
	order[i]=order[rnd];
	order[rnd]=temp;
   }
   for(i=0;i<user_number;i++)
   {
	printf("%d번 : %s\n", i+1, user_name[order[i]]);
   }
   printf("아무키나 누르시오.\n");
   getch(); // 버퍼제거. 

   for(i=0;i<user_number;i++) // 참여 인원만큼 반복 
	game_control(order[i], user_name[order[i]], solution, 
		time_check, quest_number);

   printf("\n\n");
   printf("모든 게임이 끝났습니다. \n");
   printf("아무키나 누르면 결과를 표시합니다. \n");
   getch();
   display_result(user_number, order, time_check, user_name, 
	solution, quest_number); // 결과 출력. 
   getch();
   return 0;
}

void gotoxy(int x, int y)
{
   COORD Pos = {x - 1, y - 1};
   SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
}
void game_control(int order, char name[7], char sol[][10], double check[][10], int quest)
{
   char *flag[]={"청기", "백기"};
   char *question[]={"내려!", "올려!", "내리지말고", "올리지말고"};
   clock_t start, end;
   int i, rnd[4];
   char key;
   system("cls");
   gotoxy(1, 3);
   printf("%s님 순서입니다. 키 조작은 다음과 같습니다.", name);
   display_rule();
   for(i=0;i<quest;i++)
   {
  	system("cls");
	rnd[0]=rand()%2; // 0 ~ 2사이 난수. 
	rnd[1]=rand()%4; // 0 ~ 4사이 난수. 
	start=clock(); // 시작시간. 
	gotoxy(5, 10);
	if (rnd[1]>1) // rnd[1]이 1보다 큰 경우. 
	{
	       rnd[2]=rand()%2; // 0 ~ 2사이 난수. 
	       rnd[3]=rand()%2; // 0 ~ 2 사이 난수. 
	       printf("%d: %s %s %s %s", i+1, flag[rnd[0]], question[rnd[1]], flag[rnd[2]], question[rnd[3]]); // 배열에 저장된 난수의 인덱스로 미션 출력. 
  	}
	else
	printf("%d: %s %s", i+1, flag[rnd[0]], question[rnd[1]]);
    	key=getch();
	end=clock(); // 종료시간. 
	check[order][i]=(double)(end-start)/CLK_TCK; // 수행시간. 
	if (rnd[1]>1)
	{ // rnd[1]이 1보다 큰 경우. 
		if ((rnd[2]==0) && (rnd[3]==0) && (key=='z')) // rnd[2]가 0과 같고 rnd[3]이 0과 같고 key가 z인 경우 
			sol[order][i]=1;
		else if ((rnd[2]==0) && (rnd[3]==1) && (key=='a'))	// rnd[2]가 0과 같고 rnd[3]이 1과 같고 key가 a인 경우 
			sol[order][i]=1;
		else if ((rnd[2]==1) && (rnd[3]==0) && (key=='m'))	// rnd[2]가 1과 같고 rnd[3]이 0과 같고 key가 m인 경우 
			sol[order][i]=1;
		else if ((rnd[2]==1) && (rnd[3]==1) && (key=='k'))	// rnd[2]가 1과 같고 rnd[3]이 1과 같고 key가 k인 경우 
	                             sol[order][i]=1;
		else // 아닌 경우. 
			sol[order][i]=0;
	}
	else // rnd[1]이 1보다 작거나 같은 경우.		
	{
		if ((rnd[0]==0) && (rnd[1]==0) && (key=='z')) // rnd[0]가 0과 같고 rnd[1]이 0과 같고 key가 z인 경우
			sol[order][i]=1;
		else if ((rnd[0]==0) && (rnd[1]==1) && (key=='a'))	// rnd[0]가 0과 같고 rnd[1]이 1과 같고 key가 a인 경우 
			sol[order][i]=1;
		else if ((rnd[0]==1) && (rnd[1]==0) && (key=='m'))	// rnd[0]가 1과 같고 rnd[1]이 0과 같고 key가 m인 경우 
			sol[order][i]=1;
		else if ((rnd[0]==1) && (rnd[1]==1) && (key=='k'))	// rnd[0]가 1과 같고 rnd[1]이 1과 같고 key가 k인 경우
			sol[order][i]=1;
		else
			sol[order][i]=0;
	}
    }
}

void display_result(int user, int order[], double check[][10], char name[][7], char sol[][10], int quest)
{
   int i, j, result[4]={0};
   double min_time[4]={0};
   system("cls"); // 화면을 지움. 
   printf("       ");
   for(i=0;i<user;i++) // 유저 인원만큼 반복. 
	printf("%8s  ", name[order[i]]);
   printf("\n");
   for(j=0;j<quest;j++)
   { // 문제 갯수 만큼 반복. 
	printf("    %d번 : ", j+1);
	for(i=0;i<user;i++)
	{   // 참여 인원만큼 반복. 
		if (sol[order[i]][j]  && check[order[i]][j]<1) // 만일 sol[order[i]][j]가 0보다 크고 check[order[i]][j]가 1보다 작은 경우. 
		{
			printf("O");
			result[order[i]]+=1;
		}
		else // 아닌 경우. 
			printf("X");
		printf("%5.2f     ",check[order[i]][j]);
		if ((sol[order[i]][j]==1) && (check[order[i]][j]<1)) // 만일 sol[order[i]][j]가 1과 같고 check[order[i]][j]가 1보다 작은 경우. 
			min_time[order[i]]+=check[order[i]][j];
	}
	printf("\n");
   }
   printf("\n");
   printf("맞은개수:");
   for(i=0;i<user;i++)
	 printf("%7d    ", result[order[i]]);
   printf("\n");
   printf("소요시간:");
   for(i=0;i<user;i++)
	 printf("%7.2f    ", min_time[order[i]]);
   printf("\n");
}
void display_rule(void)
{
	gotoxy(1,4);
	printf("게임시작전까지 키를 누르지 마세요!");
	gotoxy(1, 6);
	printf("청기 올려 : a    백기 올려 : k");
	gotoxy(1, 7);
	printf("청기 내려 : z    백기 내려 : m");
	Sleep(2000);
	gotoxy(1, 8);
	printf("5초 후에 게임을 시작합니다. 준비하세요.");
	Sleep(5000);

}
