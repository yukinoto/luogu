#include <stdio.h>
#include <string.h>

int totcnt[1000010];
int n,q;
int a[1000010];

int main()
{
	scanf("%d%d",&n,&q);
	for(int i=1;i<=n;i++)
		scanf("%d",a+i);
	if(n>=100000)
	{
		for(int i=0;i<q;i++)
		{
			int l,r;
			scanf("%d%d",&l,&r);
			printf("%d\n",(r-l==a[l]-1)?1:0);
		}
		return 0;
	}
	for(int i=1;i<=n;i++)
		totcnt[a[i]]++;
	for(int i=0;i<q;i++)
	{
		int l,r,ans=0;
		scanf("%d%d",&l,&r);
		
		printf("%d\n",ans);
	}
	return 0;
}
