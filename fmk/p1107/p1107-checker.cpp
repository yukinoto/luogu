//p1107-checker
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>

int main()
{
	char st[100];
	int t,n,h;
	scanf("%d%d%d",&t,&n,&h);
	for(int i=0;i<t;i++)
	{
		srand(time(NULL));
		sprintf(st,"%d.in",i);
		FILE *fp=freopen(st,"w",stdout);
		printf("%d %d %d\n",n,h,rand()%(n/2)+1);
		for(int j=1;j<=n;j++)
		{
			int a=rand(),b=rand(),num=4000/*((a<<15)|b)%4001*/;
			printf("%d ",num);
			for(int k=1;k<num;k++)
				printf("%d ",rand()%h+1);
			printf("%d\n",rand()%h+1);
		}
		fflush(fp);
		freopen("data.txt","a+",stdout);
		printf("teatcase %d:\n",i);
		sprintf(st,"copy %d.in p1107.in",i);
		system(st);
		clock_t start,end;
		start=clock();
		system(".\\p1107.exe");
		end=clock();
		printf("mytime:%d\n",end-start);
		start=clock();
		system(".\\p1107-ans.exe");
		end=clock();
		printf("anstime:%d\n",end-start);
		system("fc p1107.out p1107-ans.out");
		printf("\n\n");
	}
}
