#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
using namespace std;

int n,m;

vector<int> edge[100001];

void init()
{
	cin>>n>>m;
	for(int i=0;i<m;i++)
	{
		int x,y;
		cin>>x>>y;
		edge[x].push_back(y);
	}
	return;
}

int dfn[100001],low[100001],rnk[100001];
int cnt=0;
bool tkn[100001];

void tarjan(int root)
{
	low[root]=dfn[root]=++cnt;
	rnk[cnt]=root;
	for(auto i:edge[root])
	{
		if(!tkn[i])
		{
			if(dfn[i]==0)
			{
				tarjan(i);
				low[root]=min(low[root],low[i]);
			}
			else
			{
				low[root]=min(low[root],low[i]);
			}
		}
	}
	tkn[root]=true;
	return;
}

int idg[100001],odg[100001];
int cat[100001];

void work()
{
	for(int i=1;i<=n;i++)
		if(dfn[i]==0)
			tarjan(i);
	for(int i=1;i<=n;i++)
	{
		cat[rnk[low[i]]]++;
		for(auto tmp:edge[rnk[low[i]]])
		{
			odg[rnk[low[i]]]++;
			idg[tmp]++;
		}
	}
	int ans=0;
	for(int i=1;i<=n;i++)
		ans=max(ans,cat[i]);
	cout<<ans<<endl;
	int ai=0,ao=0;
	int nm=0;
	for(int i=1;i<=n;i++)
	{
		if(idg[i]==0)
			ao++;
		if(odg[i]==0)
			ai++;
	}
	cout<<max(ai,ao)<<endl;
	return;
}

int main()
{
	init();
	work();
	return 0;
}