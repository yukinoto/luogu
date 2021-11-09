#include <iostream>
#include <vector>
#include <string>
using namespace std;

struct node{
	int fa;
	vector<int>sons;
	int dpf0,dpf1,dps0,dps1;
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
	for(int i=1;i<n;i++)
	{
		int u,v;
		cin>>u>>v;
		edge[u].push_back(v);
		edge[v].push_back(u);
	}
}