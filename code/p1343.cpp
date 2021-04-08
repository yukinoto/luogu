#include <iostream>
#include <cstring>
#include <queue>
#include <algorithm>

typedef long long Int;
Int Inf=0x7fffffffffffffffll;

Int n,m,s,t,p;
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
	std::cin>>n>>m>>p;
	s=1,t=n;
	for(int i=0;i<m;i++)
	{
		Int f,t,w;
		std::cin>>f>>t>>w;
		mp[f][t]+=w;
	}
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
	if(ans!=0)
		std::cout<<ans<<" "<<(p-1)/ans+1<<std::endl;
	else
		std::cout<<"Orz Ni Jinan Saint Cow!"<<std::endl;
}
int main()
{
	init();
	work();
	return 0;
}
