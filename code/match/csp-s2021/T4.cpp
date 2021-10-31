#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
using namespace std;

int n,m,t;
vector<pair<int,int>>mp[400];

void init()
{
	cin>>n>>m>>t;
	for(int i=1;i<n;i++)
	{
		for(int j=1;j<=m;j++)
		{
			int x;
			cin>>x;
			mp[i*m+j].push_back(make_pair((i+1)*m+j,x));
			mp[(i+1)*m+j].push_back(make_pair(i*m+j,x));
		}
	}
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<m;j++)
		{
			int x;
			cin>>x;
			mp[i*m+j].push_back(make_pair(i*m+j+1,x));
			mp[i*m+j+1].push_back(make_pair(i*m+j,x));
		}
	}
	return;
}

vector<pair<int,int>>nmp[410];

int dep[410];

bool bfs(int root,int t)
{
	for(int i=0;i<=t;i++)
		dep[i]=-1;
	queue<int>q;
	q.push(root);
	dep[root]=0;
	while(!q.empty())
	{
		int p=q.front();
		q.pop();
		for(auto i:nmp[p])
		{
			if(dep[i.first]==-1&&i.second>0)
			{
				dep[i.first]=dep[p]+1;
				q.push(i.first);
			}
		}
	}
	return dep[t]!=-1;
}

int dfs(int root,int t,int flow=0x3fffffff)
{
	if(flow==0||root==t)
		return flow;
	int ans=0;
	for(auto &i:nmp[root])
	{
		if(dep[i.first]==dep[root]+1)
		{
			int s=dfs(i.first,t,min(flow,i.second));
			ans+=s;
			flow-=s;
			i.second-=s;
			nmp[i.first].push_back(make_pair(root,s));
		}
	}
	return ans;
}

int dinic(int s,int t)
{
	int ans=0;
	while(bfs(s,t))
	{
		ans+=dfs(s,t);
	}
	return ans;
}

void work()
{
	for(int i=0;i<=(n+1)*m;i++)
		nmp[i]=mp[i];
	int k;
	cin>>k;
	int end=n*m+m;
	for(int i=0;i<k;i++)
	{
		int x,p,t;
		cin>>x>>p>>t;
		if(p<=m)
		{
			nmp[end+p].push_back(make_pair(m+p,x));
			nmp[m+p].push_back(make_pair(end+p,x));
		}
		if(p>m&&p<=n+m)
		{
			nmp[end+p].push_back(make_pair(m*(p-m)+m,x));
			nmp[n*(p-m)+m].push_back(make_pair(end+p,x));
		}
		if(p>n+m&&p<=2*m+n)
		{
			nmp[end+p].push_back(make_pair(n*m+2*m+n+1-p,x));
			nmp[n*m+2*m+n+1-p].push_back(make_pair(end+p,x));
		}
		if(p>2*m+n)
		{
			nmp[end+p].push_back(make_pair(m*(2*m+2*n+1-p)+1,x));
			nmp[m*(2*m+2*n+1-p)+1].push_back(make_pair(end+p,x));
		}
		if(t)
		{
			nmp[0].push_back(make_pair(end+p,0x3fffffff));
		}
		else
		{
			nmp[end+p].push_back(make_pair(end+2*m+2*n+1,0x3fffffff));
		}
	}
	cout<<dinic(0,end+2*m+2*n+1)<<endl;
	return;
}

int main()
{
	init();
	for(int i=0;i<t;i++)
		work();
	return 0;
}