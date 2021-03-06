#include <iostream>
#include <cstring>
#include <queue>
#include <algorithm>

typedef int Int;
Int Inf=0x7fffffff;

Int n,m,s,t;
Int mp[610][610];
Int deepth[610];
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
	Int x,p,q;
	std::cin>>x>>p>>q;
	for(int i=1;i<=x;i++)
	{
		for(int j=1;j<=p;j++)
		{
			Int f;
			std::cin>>f;
			if(f==1)
				mp[0][j]=mp[j][j+p]=mp[j+p][p*2+i]=1;
		}
	}
	for(int i=p*2+x+1;i<=p*2+x*2;i++)
	{
		mp[i-x][i]=1;
		for(int j=(x+p)*2+1;j<=(x+p)*2+q;j++)
		{
			Int f;
			std::cin>>f;
			if(f==1)
				mp[i][j]=mp[j][j+q]=mp[j+q][(x+p+q)*2+1]=1;
		}
	}
	s=0,t=(x+p+q)*2+1;
	n=(x+p+q)*2+1;
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
