#include <iostream>
#include <cstring>
#include <queue>
#include <algorithm>

typedef long long Int;
Int Inf=0x7fffffffffffffffll;

Int n,m,s,t;
Int mp[4010][4010];
Int deepth[4010];
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
			}
	}
	return;
}
Int dfs(Int r,Int bef)
{
	if(r==t)
		return bef;
	Int as=0;
	for(int i=0;i<=n;i++)
		if(deepth[i]==deepth[r]+1&&mp[r][i]>0)
		{
			Int ts=dfs(i,std::min(bef,mp[r][i]));
			as+=ts;
			mp[r][i]-=ts;
			mp[i][r]+=ts;
			bef-=ts;
		}
	return as;
}
void init()
{
	Int x,y;
	std::cin>>x;
	for(int i=1;i<=x;i++)
	{
		std::cin>>mp[0][i];
		sum+=mp[0][i];
	}
	for(int i=1;i<=x;i++)
	{
		std::cin>>mp[i][x+1];
		sum+=mp[i][x+1];
	}
	std::cin>>y;
	for(int i=1;i<=y;i++)
	{
		Int k;
		std::cin>>k>>mp[0][x+(i<<1)]>>mp[x+(i<<1)+1][x+1];
		sum+=mp[0][x+(i<<1)]+mp[x+(i<<1)+1][x+1];
		for(int j=0;j<k;j++)
		{
			Int p;
			std::cin>>p;
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
	std::cout<<sum-ans<<std::endl;
}
int main()
{
	init();
	work();
	return 0;
}
