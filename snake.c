#include<stdio.h>
#include<time.h>//调用系统时间
#include<stdlib.h>//使用srand()
#include<windows.h>//使用Sleep()
#include<conio.h>//为了使用getch()
#include<string.h>//为使用memset()
#define MAX1 21
#define MAX2 41
void food(void);
int move(void);
int square[MAX1][MAX2];//场地
int cla;//级别
int sum=4;//分数
int main(void)
{
	FILE *fp;
	int m,n;
	int flag,sum2=0;
	fp=fopen("scores","r+");
	fscanf(fp,"%d",&sum2);
	entrance:for(m=0,n=0;n<MAX2;n++)//为场地边界赋值
		square[m][n]=1111;
	for(m=MAX1-1,n=0;n<MAX2;n++)
		square[m][n]=1111;
	for(m=1,n=0;m<MAX1-1;m++)
		square[m][n]=2222;
	for(m=1,n=MAX2-1;m<MAX1-1;m++)
		square[m][n]=2222;
	printf("游戏说明：使用wasd键移动\n请选择你要挑战的级别！\n");
	printf("初级：1\n中级：2\n高级：3\n");
	scanf("%d",&cla);
	getchar();
	square[(MAX1-1)/2][(MAX2-1)/2-1]=2;//为蛇身赋初值
	square[(MAX1-1)/2][(MAX2-1)/2]=3;
	square[(MAX1-1)/2][(MAX2-1)/2+1]=4;
    food();//放置食物
	for(flag=1;flag==1;)
		flag=move();//移动并检测是否存活
	system("cls");
	if(sum2<sum)
	{
		printf("你获得了高分！\n");
		rewind(fp);
		fprintf(fp,"%d",sum);
	}
	fclose(fp);
	printf("GAME OVER\n你的成绩是：%d分\n是否继续(y/n)?",sum-4);
	if(getchar()=='y')
	{
		system ("cls");
		memset(square,0,sizeof(square));
		sum=4;
		goto entrance;
	}
	return 0;
}
void food(void)
{
	int m,n,flag=0;
	srand((unsigned)time(NULL));
	while(flag==0)
	{
		m=rand()%(MAX1-1)+1;
		n=rand()%(MAX2-1)+1;
		if(square[m][n]==0)
		{
			flag=1;
			square[m][n]=1000;
		}
		else
			continue;
	}
}
int move(void)
{
	char dire='a';
	int m,n,m1,n1;
	int flag1=0,flag2=1;
	for(m=0;m<MAX1;m++)//找到蛇头
	{
		for(n=0;n<MAX2;n++)
		{
			if(square[m][n]==2)
				break;
		}
		if(square[m][n]==2)
			break;
	}
	while(flag2==1)//存活时执行
	{
		entrance:if(cla==1)//检测级别
		    Sleep(400);
		else if(cla==2)
			Sleep(250);
		else if(cla==3)
			Sleep(100);
		else
		{
			printf("请输入正确的级别\n");
			scanf("%d",&cla);
			goto entrance;
		}
		if(kbhit())//检测是否输入转向指令
		dire=getch();
		if(dire=='a')//朝左走
		{
			if(square[m][n-1]==0||square[m][n-1]==1000)
			{
				n--;
				if(square[m][n]==1000)
				{
					food();
					flag1=1;//吃到食物的标记
				}
				square[m][n]=1;
			}
			else
				flag2=0;
		}
		else if(dire=='s')//朝下走
		{
			if(square[m+1][n]==0||square[m+1][n]==1000)//前方为空地或食物
			{
				m++;
				if(square[m][n]==1000)
				{
					food();//重新放置食物
					flag1=1;
				}
				square[m][n]=1;//将此点定为蛇头
			}
			else
				flag2=0;//GG
		}
		else if(dire=='d')//朝右走
		{
			if(square[m][n+1]==0||square[m][n+1]==1000)
			{
				n++;
				if(square[m][n]==1000)
				{
					food();
					flag1=1;
				}
				square[m][n]=1;
			}
			else
				flag2=0;
		}
		else if(dire=='w')//朝上走
		{
			if(square[m-1][n]==0||square[m-1][n]==1000)
			{
				m--;
				if(square[m][n]==1000)
				{
					food();
					flag1=1;
				}
				square[m][n]=1;
			}
			else
				flag2=0;
		}
		else
			continue;//输入其它字符则暂停
		for(m1=1;m1<MAX1-1;m1++)
			for(n1=1;n1<MAX2-1;n1++)
			{
				if(square[m1][n1]>0&&square[m1][n1]<1000)
					square[m1][n1]++;//将蛇身元素数值加1，使蛇头数值保持为2
			}
	    for(m1=1;m1<MAX1-1;m1++)
	    {
		    for(n1=1;n1<MAX2-1;n1++)
		    {
			     if(square[m1][n1]==(sum+1))
					 if(flag1==1)
					 {
				        sum++;//加分
						flag1=0;//重置
					 }
					 else
						 square[m1][n1]=0;//蛇身长度不变
		     }
	     }
		system("cls");
	for(m1=0;m1<MAX1;m1++)//打印场地
	{
		for(n1=0;n1<MAX2;n1++)
		{
			if(square[m1][n1]==0)
				printf(" ");
		    else if(square[m1][n1]==1111)
				printf("=");
			else if(square[m1][n1]==2222)
				printf("|");
			else
				printf("o");
		}
		printf("\n");
	 }
	printf("YOUR SCORE:%d\n按回车或空格暂停",sum-4);
   }
   return flag2;//存活的标志
}


