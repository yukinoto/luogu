#include <iostream>
#include <vector>
#include <queue>
using namespace std;

vector<int> mp[10001],ap[100001];
int n,m;
bool tn[10001],tkn[10001];
int dis[10001];
int s,t;

void init()
{
	cin>>n>>m;
	for(int i=0;i<m;i++)
	{
		int x,y;
		cin>>x>>y;
		mp[x].push_back(y);
		ap[y].push_back(x);
	}
	cin>>s>>t;
	return;
}

void prebfs(int s,int t)
{
	queue<int> q;
	q.push(s);
	tkn[s]=true;
	while(!q.empty())
	{
		int p=q.front();
		q.pop();
		for(auto i:ap[p])
		{
			if(!tkn[i])
			{
				tkn[i]=true;
				q.push(i);
			}
		}
	}
	for(int i=1;i<=n;i++)
	{
		tn[i]=true;
		for(auto j:mp[i])
			if(!tkn[j])
			{
				tn[i]=false;
				break;
			}
	}
	for(int i=1;i<=n;i++)
		tkn[i]=false;
	return;
}

int fmp()
{
	int p=0;
	for(int i=1;i<=n;i++)
		if(!tkn[i]&&tn[i]&&(p==0||dis[i]<=dis[p]))
				p=i;
	return p;
}

void relax(int root)
{
	for(auto i:mp[root])
	{
		if(!tkn[i]&&tn[i]&&dis[i]>dis[root]+1)
			dis[i]=dis[root]+1;
	}
	return;
}

int dij(int s,int t)
{
	for(int i=1;i<=n;i++)
		dis[i]=0x3fffffff;
	dis[s]=0;
	tkn[s]=true;
	relax(s);
	for(int i=2;i<=n;i++)
	{
		int p=fmp();
		if(p!=0)
		{
			tkn[p]=true;
			relax(p);
		}
		else
			break;
	}
	if(!tkn[t])
		return -1;
	return dis[t];
}

int main()
{
	init();
	prebfs(t,s);
	cout<<dij(s,t)<<endl;
	return 0;
}
