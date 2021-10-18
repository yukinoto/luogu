#include <iostream>
#include <vector>
#include <cstring>
#include <algorithm>
#include <set>
using namespace std;

int n,m;
vector<int> mp[20001];

int cnt=0;
int dfn[20001],low[20001];

set<int> ans;

void init()
{
	memset(dfn,-1,sizeof(dfn));
	memset(low,-1,sizeof(low));
	cin>>n>>m;
	for(int i=0;i<m;i++)
	{
		int x,y;
		cin>>x>>y;
		mp[x].push_back(y);
		mp[y].push_back(x);
	}
	return;
}


void tarjan(int root,int from)
{
	dfn[root]=++cnt;
	low[root]=dfn[root];
	int st=0;
	for(int i:mp[root])
	{
		if(i==from)
			continue;
		if(dfn[i]==-1)
		{
			tarjan(i,root);
			low[root]=min(low[root],low[i]);
			st++;
			if(low[i]>=dfn[root]&&root!=from)
			{
				ans.insert(root);
			}
		}
		else
		{
			low[root]=min(low[root],dfn[i]);
		}
	}
	if(root==from&&st>1)
		ans.insert(root);
	return;
}

void pt()
{
	cout<<ans.size()<<'\n';
	for(int i:ans)
		cout<<i<<' ';
	cout<<endl;
	cout.flush();
	return;
}

int main()
{
	init();
	for(int i=1;i<=n;i++)
		if(dfn[i]==-1)
			tarjan(i,i);
	pt();
	return 0;
}
