#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <windows.h>

int main()
{
	int t,n,m;
	scanf("%d%d",&t,&n);
	srand(time(NULL));
	freopen("results.txt","w",stdout);
	for(int i=0;i<t;i++)
	{
		char cache[50];
		freopen("results.txt","a",stdout);
		printf("state %d:\n",i);
		fflush(stdout);
		freopen("4.in","w",stdout);
		printf("%d\n",n);
		int cnt=0;
		for(int j=1;j<=n;j++)
		{
			int f=rand()%5+1;
			if(f==5)
			{
				printf("%d\n",f);
				continue;
			}
			if(f==3||f==4)
			{
				printf("%d %d\n",f,rand()%cnt+1);
				continue;
			}
			if(f==1||f==2)
			{
				printf("%d %d\n",1,rand()%100+1);
				cnt++;
				continue;
			}
		}
		fflush(stdout);
		freopen("results.txt","a",stdout);
		sprintf(cache,"copy 4.in 4-%d.in",i);
		system(cache);
		clock_t st=clock(),ed;
		system("4.exe");
		ed=clock();
		printf("code-1:%dms\n",ed-st);
		st=clock();
		system("4-b.exe");
		ed=clock();
		printf("code-2:%dms\n",ed-st);
		system("fc 4.out 4-b.out");
		printf("\n\n");
		fflush(stdout);
	}
}
