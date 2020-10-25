#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <windows.h>

int main()
{
	int t,n,m;
	scanf("%d%d%d",&t,&n,&m);
	srand(time(NULL));
	freopen("results.txt","w",stdout);
	for(int i=0;i<t;i++)
	{
		char cache[50];
		freopen("results.txt","a",stdout);
		printf("state %d:\n",i);
		fflush(stdout);
		freopen("dij.in","w",stdout);
		printf("%d %d 1\n",n,m);
		for(int j=1;j<=m;j++)
			printf("%d %d %d\n",rand()%n+1,rand()%n+1,rand()%20+1);
		fflush(stdout);
		freopen("results.txt","a",stdout);
		sprintf(cache,"copy dij.in dij-%d.in",i);
		system(cache);
		clock_t st=clock(),ed;
		system("dij.exe");
		ed=clock();
		printf("code-1:%dms\n",ed-st);
		st=clock();
		system("dij2.exe");
		ed=clock();
		printf("code-2:%dms\n",ed-st);
		system("fc dij.out dij2.out");
		printf("\n\n");
		fflush(stdout);
	}
}
