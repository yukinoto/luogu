#include <cstdio>
#include <cstring>
#include <queue>
#include <algorithm>

typedef int Int;
Int Inf=0x7fffffff;

Int n,m,s,t;
Int mp[3010][3010];
Int deepth[3010];
Int ans=0,sum=0;
void bfs(Int r)
{
	memset(deepth,-1,sizeof(deepth));
	deepth[r]=1;
	std::queue<Int> q;
	q.push(r);
	while(!q.empty())
	{
		r=q.front();
		q.pop();
		for(int i=0;i<=n;i++)
			if(deepth[i]==-1&&mp[r][i]>0)
			{
				deepth[i]=deepth[r]+1;
				q.push(i);
				if(i==t)
					return;
			}
	}
	return;
}
Int now[3010];
Int dfs(Int r,Int bef)
{
	if(r==t||bef==0)
		return bef;
	Int as=0;
	for(int i=now[r];i<=n;i++)
		if(deepth[i]==deepth[r]+1&&mp[r][i]>0)
		{
			Int ts=dfs(i,std::min(bef,mp[r][i]));
			as+=ts;
			mp[r][i]-=ts;
			mp[i][r]+=ts;
			bef-=ts;
			if(i==now[r]&&mp[r][i]==0)
				now[r]++;
		}
	return as;
}
void init()
{
	Int x,y;
	scanf("%d",&x);
	for(int i=1;i<=x;i++)
	{
		scanf("%d",&mp[0][i]);
		sum+=mp[0][i];
		now[i]=x+1;
	}
	for(int i=1;i<=x;i++)
	{
		scanf("%d",&mp[i][x+1]);
		sum+=mp[i][x+1];
	}
	scanf("%d",&y);
	for(int i=1;i<=y;i++)
	{
		Int k;
		scanf("%d%d%d",&k,&mp[0][x+(i<<1)],&mp[x+(i<<1)+1][x+1]);
		sum+=mp[0][x+(i<<1)]+mp[x+(i<<1)+1][x+1];
		for(int j=0;j<k;j++)
		{
			Int p;
			scanf("%d",&p);
			mp[x+(i<<1)][p]=mp[p][x+(i<<1)+1]=Inf;
		}
	}
	n=x+y*2+1;
	s=0,t=x+1;
}
void work()
{
	Int ts=0;
	do
	{
		bfs(s);
		ts=dfs(s,Inf);
		ans+=ts;
	}while(ts!=0);
	printf("%d\n",sum-ans);
}
int main()
{
	init();
	work();
	return 0;
}
