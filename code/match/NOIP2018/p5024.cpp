#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

struct node{
	int fa;
	vector<int>sons;
	long long w;
	long long dpf0,dpf1,dps0,dps1;
};

int n,m;
node tr[100010];
vector<int>edge[100010];

void build(int root)
{
	for(auto i:edge[root])
	{
		if(i!=tr[root].fa)
		{
			tr[i].fa=root;
			tr[root].sons.push_back(i);
			build(i);
		}
	}
	return;
}

void init()
{
	string x;
	cin>>n>>m>>x;
	for(int i=1;i<=n;i++)
		cin>>tr[i].w;
	for(int i=1;i<n;i++)
	{
		int u,v;
		cin>>u>>v;
		edge[u].push_back(v);
		edge[v].push_back(u);
	}
	build(1);
	return;
}

void dp1(int root)
{
	int s0=0,s1=0;
	for(auto i:tr[root].sons)
	{
		dp1(i);
		s0+=tr[i].dps1;
		s1+=min(tr[i].dps1,tr[i].dps0);
	}
	tr[root].dps0=s0;
	tr[root].dps1=s1+tr[root].w;
	return;
}

void dp2(int root,long long f0,long long f1)
{
	f0-=tr[root].dps1;
	f1-=min(tr[root].dps0,tr[root].dps1);
	tr[root].dpf0=f1;
	tr[root].dpf1=f0+tr[root].w;
	f0=tr[root].dpf0;
	f1=tr[root].dpf1;
	for(auto i:tr[root].sons)
	{
		f0+=tr[i].dps1;
		f1+=min(tr[i].dps0,tr[i].dps1);
	}
	for(auto i:tr[root].sons)
	{
		dp2(i,f0,f1);
	}
	return;
}

