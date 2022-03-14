#include <iostream>
#include <cstring>
#include <queue>
#include <algorithm>
using namespace std;

const int inf=0x3fffffff;

int mp[450][450];
int depth[450];

bool bfs(int n,int s,int t)
{
	memset(depth,-1,sizeof(depth));
	depth[s]=0;
	queue<int> q;q.push(s);
	while(!q.empty())
	{
		int p=q.front();q.pop();
		for(int i=0;i<=n;i++)
			if(mp[p][i]>0&&depth[i]==-1)
			{
				depth[i]=depth[p]+1;
				q.push(i);
			}
	}
	return depth[t]!=-1;
}

int dfs(int n,int s,int t,int ffl=inf)
{
	if(s==t)
		return ffl;
	int nfl=0;
	for(int i=0;i<=n;i++)
	{
		if(ffl==0)
			return nfl;
		if(mp[s][i]!=0&&depth[i]==depth[s]+1)
		{
			int cache=dfs(n,i,t,min(ffl,mp[s][i]));
			mp[s][i]-=cache,mp[i][s]+=cache;
			ffl-=cache,nfl+=cache;
		}
	}
	return nfl;
}

int dinic(int n,int s,int t)
{
	int ans=0;
	while(bfs(n,s,t))
		ans+=dfs(n,s,t);
	return ans;
}

void work()
{
	memset(mp,0,sizeof(mp));
	int n;
	cin>>n;
	for(int i=1;i<=n;i++)
	{
		mp[0][i]=mp[n+i][n*2+1]=1;
		for(int j=1;j<=n;j++)
		{
			int x;
			cin>>x;
			mp[i][n+j]=x;
		}
	}
	cout<<((dinic(n*2+1,0,n*2+1)==n)?"Yes\n":"No\n");
	return;
}

int main()
{
	int t;
	cin>>t;
	for(int i=0;i<t;i++)
		work();
	return 0;
}