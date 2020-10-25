#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>

int main()
{
	int t,n,m;
	scanf("%d%d%d",&t,&n,&m);
	srand(time(NULL));
	for(int i=0;i<t;i++)
	{
		char fn[50];
		sprintf(fn,"p3387.in");
		freopen(fn,"w",stdout);
		printf("%d %d\n",n,m);
		for(int j=1;j<=n;j++)
			printf("%d ",rand()%20+1);
		printf("\n");
		for(int j=1;j<=m;j++)
		{
			int a=rand()%n+1,b=rand()%n+1;
			if(a==b)
				b=b%n+1;
			printf("%d %d\n",a,b);
		}
		fflush(stdout);
		freopen("results.txt","a",stdout);
		sprintf(fn,"copy p3387.in p3387-%d.in",i);
		system(fn);
		system("p3387.exe");
		system("p3387-ans.exe");
		printf("state %d:",i);
		system("fc p3387.out p3387-ans.out");
		fflush(stdout);
	}
	return 0;
}
