#include <iostream>
#include <cstring>
#include <queue>
#include <algorithm>

typedef long long Int;
Int Inf=0x7fffffffffffffffll;

Int n,m,s,t;
Int mp[210][210];
Int deepth[210];
Int ans=0;
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
	std::cin>>n>>m>>s>>t;
	s<<=1,t=(t<<1)-1;
	for(int i=0;i<m;i++)
	{
		Int f,t;
		std::cin>>f>>t;
		mp[t<<1][(f<<1)-1]=mp[f<<1][(t<<1)-1]=1;
	}
	for(int i=1;i<=n;i++)
		mp[i<<1][(i<<1)-1]=mp[(i<<1)-1][i<<1]=1;
	n<<=1;
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
	std::cout<<ans<<std::endl;
}
int main()
{
	init();
	work();
	return 0;
}
