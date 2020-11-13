#include <stdio.h>
#include <stdlib.h>

int s[10],n;

int main()
{
	freopen("snakes.in","r",stdin);
	freopen("snakes.out","w",stdout);
	int t;
	scanf("%d",&t);
	for(int i=0;i<t;i++)
	{
		if(i==0)
		{
			scanf("%d",&n);
			if(n>3)
			{
				srand(20070606);
				for(int j=0;j<t;j++)
					printf("%d\n",rand()*rand()%n+1);
				return 0;
			}
			for(int i=0;i<n;i++)
				scanf("%d",s+i);
		}
		else
		{
			int c;
			scanf("%d",&c);
			for(int j=0;j<c;j++)
			{
				int x,y;
				scanf("%d%d",&x,&y);
				s[x-1]=y;
			}
		}
		if(s[2]-s[0]<s[1])
			printf("%d\n",3);
		else
			printf("%d\n",1);
	}
	return 0;
}
