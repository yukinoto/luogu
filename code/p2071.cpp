//ce
#include <cstdio>
#include <queue>
using namespace std;

int n;

int getint()
{
	int x;
	scanf("%d",&x);
	return x;
}

void getint(int &x)
{
	scanf("%d",&x);
	return;
}

int mp[80002][80002];

void link(int from,int to)
{
	mp[from][to]++;
	return;
}

int deepth[80002];
bool taken[80002];

void bfs(int root)
{
	queue<int> q;
	deepth[root]=0;
	q.push(root);
	for(int i=0;i<=4*n+1;i++)
		taken[i]=false;
	taken[root]=true;
	while(!q.empty())
	{
		int p=q.front();
		q.pop();
		for(int i=0;i<=n*4+1;i++)
			if(mp[p][i]>0&&!taken[i])
			{
				deepth[i]=deepth[p]+1;
				taken[i]=true;
				q.push(i);
			}
	}
	return;
}

int ans;

int dfs(int root,int flow)
{
	int rcd=flow;
	if(root==4*n+1)
		return flow;
	for(int i=0;i<=n*4+1;i++)
		if(mp[root][i]>0&&deepth[i]==deepth[root]+1)
		{
			int f=dfs(i,min<int>(mp[root][i],flow));
			flow-=f;
			mp[root][i]-=f;
			mp[i][root]+=f;
		}
	return rcd-flow;
}

void dinic(int from,int to)
{
	bfs(from);
	while(taken[to])
	{
		while(true)
		{
			int x=dfs(from,n*2);
			if(x==0)
				break;
			else
				ans+=x;
		}
		bfs(from);
	}
	return;
}

int main()
{
	n=getint();
	for(int i=1;i<=n*2;i++)
	{
		int x=getint(),y=getint();
		link(0,i),link(i,n*2+x),link(i,n*2+y);
	}
	for(int i=n*2+1;i<=n*3;i++)
	{
		link(i,i+n);
		link(i,i+n);
		link(i+n,n*4+1);
		link(i+n,n*4+1);
	}
	dinic(0,n*4+1);
	printf("%d\n",ans);
	return 0;
}
