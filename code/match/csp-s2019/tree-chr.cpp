#include <stdio.h>
#include <string.h>

int n;
int weigh[2010];
bool mp[2010][2010];
struct edge{
	int x1,x2;
};
edge tr[2010];

void init()
{
	memset(mp,false,sizeof(mp));
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
	{
		int x;
		scanf("%d",&x);
		weigh[x]=i;
	}
	for(int i=1;i<n;i++)
	{
		scanf("%d%d",&tr[i].x1,&tr[i].x2);
		mp[tr[i].x1][tr[i].x2]=mp[tr[i].x2][tr[i].x1]=true;
	}
	return;
}

void work2()
{
    init();
    
}

int main()
{
	int t;
	scanf("%d",&t);
	for(int i=0;i<t;i++)
		work2();
	return 0;
}