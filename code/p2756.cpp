#include <iostream>
#include <algorithm>
#include <queue>
using namespace std;

const int MAXN=110;
int n,m;
bool tb[MAXN][MAXN];
int mp[MAXN][MAXN];

void init()
{
	cin>>m>>n;
	int x,y;
	cin>>x>>y;
	while(x!=-1)
	{
		if(x>y)
			swap(x,y);
		mp[x][y]++;
		cin>>x>>y;
	}
	for(int i=1;i<=m;i++)
	{
		mp[0][i]++;
	}
	for(int i=m+1;i<=n;i++)
	{
		mp[i][n+1]++;
	}
	return;
}

int dep[MAXN];

bool bfs(int from,int to)
{
	for(int i=0;i<=n+1;i++)
		dep[i]=-1;
	dep[from]=0;
	queue<int>q;
	q.push(from);
	while(!q.empty())
	{
		int p=q.front();
		q.pop();
		for(int i=0;i<=n+1;i++)
			if(mp[p][i]&&dep[i]==-1)
			{
				dep[i]=dep[p]+1;
				q.push(i);
			}
	}
	return dep[to]!=-1;
}

const int inf=0x3fffffff;

int dfs(int root,int to,int flow=inf)
{
	if(flow==0)
		return 0;
	if(root==to)
		return flow;
	int ans=0;
	for(int i=0;i<=n+1;i++)
	{
		if(mp[root][i]&&dep[i]==dep[root]+1)
		{
			int ths=dfs(i,to,min(mp[root][i],flow));
			flow-=ths;
			ans+=ths;
			mp[i][root]+=ths;
			mp[root][i]-=ths;
			if(ths>0)
			{
				int x=root,y=i;
				if(x>y)
					swap(x,y);
				tb[x][y]=!tb[x][y];
			}
		}
	}
	return ans;
}

int dinic(int from,int to)
{
	int ans=0;
	while(bfs(from,to))
	{
		ans+=dfs(0,n+1);
	}
	return ans;
}

int main()
{
	init();
	cout<<dinic(0,n+1)<<endl;
	for(int i=1;i<=m;i++)
		for(int j=m+1;j<=n;j++)
			if(tb[i][j])
				cout<<i<<' '<<j<<endl;
	return 0;
}
