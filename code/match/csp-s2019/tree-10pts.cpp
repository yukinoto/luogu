#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <algorithm>
using namespace std;

#define Inf 0x3fffffff

int n;
int weigh[2010];
bool mp[2010][2010];
struct edge{
	int x1,x2;
};
edge tr[2010];

int pre(int x)
{
	int ans=1;
	for(int i=2;i<=x;i++)
		ans*=i;
	return ans;
}

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

bool cmp(int *a,int *b,int len)
{
	for(int i=1;i<=len;i++)
		if(a[i]!=b[i])
			return a[i]<b[i];
	return false;
}

inline void cpy(int *from,int *to,int len)
{
	for(int i=1;i<=len;i++)
		to[i]=from[i];
	return;
}

void work()
{
	init();
	int order[2010];
	int ans[2010],a[2010],cache[2010];
	for(int i=1;i<n;i++)
	{
		order[i]=i;
		ans[i]=Inf;
	}
	int end=pre(n-1);
	for(int i=1;i<=end;i++)
	{
		cpy(weigh,a,n);
		int wor[2010];
		for(int j=1;j<n;j++)
			wor[order[j]]=j;
		for(int j=1;j<n;j++)
			swap(a[tr[wor[j]].x1],a[tr[wor[j]].x2]);
		for(int j=1;j<=n;j++)
			cache[a[j]]=j;
		if(cmp(cache,ans,n))
			cpy(cache,ans,n);
		next_permutation(order+1,order+n);
	}
	for(int i=1;i<n;i++)
		printf("%d ",ans[i]);
	printf("%d\n",ans[n]);
	return;
}

int main()
{
	int t;
	scanf("%d",&t);
	for(int i=0;i<t;i++)
		work();
	return 0;
}
