#include <stdio.h>
#include <windows.h>
#include <time.h>
#include <string.h>
#include <stdlib.h>

void fmk_chr(int n)
{
	freopen("tree.in","a",stdout);
	printf("%d\n",n);
	int ans[20010],cnt=n;
	memset(ans,0,sizeof(ans));
	srand(time(NULL));
	for(int i=1;i<=n;i++)
	{
		int x=rand()%cnt+1;
		int c=0;
		for(int j=1;j<=n;j++)
		{
			if(ans[j]==0)
				c++;
			if(c==x)
			{
				ans[j]=i;
				cnt--;
				break;
			}
		}
	}
	for(int i=1;i<n;i++)
		printf("%d ",ans[i]);
	printf("%d\n",ans[n]);
	for(int i=2;i<=n;i++)
		printf("1 %d\n",i);
	fclose(stdout);
	return;
}

int main()
{
	int n,t1,t2;
	clock_t start,end;
	scanf("%d%d%d",&t1,&t2,&n);
	for(int i=1;i<=t1;i++)
	{
		freopen("tree.in","w",stdout);
		printf("%d\n",t2);
		for(int j=1;j<=t2;j++)
			fmk_chr(n);
		freopen("results.res","a+",stdout);
		printf("state: %d\n",i);
		start=clock();
		system("tree-10pts.exe");
		end=clock();
		printf("time 1:%dms",end-start);
		start=clock();
		system("tree.exe");
		end=clock();
		printf("time 2:%dms",end-start);
		char cache[50];
		sprintf(cache,"copy tree.in tree_%d.in",i);
		system(cache);
		system("fc tree-ans.out tree.out");
		printf("\n");
		fflush(stdout);
	}
}
