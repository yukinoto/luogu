#include <stdio.h>
#include <string.h>
#include <vector>
#include <queue>
using namespace std;

int n,q,p;
vector<int> mp[410];

void init()
{
	int x;
	scanf("%d%d%d",&n,&p,&q);
	for(int i=1;i<=p;i++)
		mp[0].push_back(i);
	for(int i=p+n*2+1;i<=p+n*2+q;i++)
		mp[i].push_back(p+n*2+q+1);
	for(int k=1;k<=n;k++)
		for(int i=1;i<=p;i++)
		{
			scanf("%d",&x);
			if(x==1)
				mp[i].push_back(k+p);
		}
	for(int k=1;k<=n;k++)
	{
		mp[q+k].push_back(q+n+k);
		for(int i=1;i<=q;i++)
		{
			scanf("%d",&x);
			if(x==1)
				mp[q+n+k].push_back(n*2+p+i);
		}
	}
}

int deepth[410];

bool bfs()
{
	memset(deepth,0,sizeof(deepth));
	queue<int> qu;
	qu.push(0);
	deepth[0]=1;
	while(!qu.empty())
	{
		int root=qu.back();
		qu.pop();
		for(auto i:mp[root])
		{
			if(deepth[i]==0)
			{
				deepth[i]=deepth[root]+1;
				qu.push(i);
			}
		}
	}
	return deepth[p+q+n*2+1]!=0;
}

int dfs(int root,int mx)
{
	if(mx==0)
		return 0;
	if(root==p+q+n*2+1)
		return mx;
	int sum=0;
	for(auto i:mp[root])
	{
		if(deepth[i]==deepth[root]+1)
			sum+=dfs(i,min(mx,1));
	}
	return sum;
}

int main()
{
	init();
	int ans=0;
	while(bfs())
		ans+=dfs(0,1);
	printf("%d\n",ans);
	return 0;
}
