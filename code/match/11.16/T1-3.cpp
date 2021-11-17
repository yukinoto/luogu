#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdlib>
using namespace std;

class cst{
	private:
	int *fa;
	public:
	cst(int n)
	{
		fa=new int[n+1];
		for(int i=0;i<=n;i++)
			fa[i]=i;
		return;
	}
	~cst()
	{
		delete[] fa;
	}
	int gv(int x)
	{
		if(fa[x]==x)
			return x;
		return fa[x]=gv(fa[x]);
	}
	void merge(int x,int y)
	{
		fa[gv(x)]=gv(y);
	}
	bool ist(int x,int y)
	{
		return gv(x)==gv(y);
	}
	int operator()(int x)
	{
		return gv(x);
	}
};

cst *st;

int n,m;
vector<int> mp[100001];
int dfn[100001],low[100001];

void del()
{
	delete st;
}

void init()
{
	cin>>n>>m;
	for(int i=0;i<m;i++)
	{
		int x,y;
		cin>>x>>y;
		mp[x].push_back(y);
	}
	st=new cst(n);
	atexit(del);
	return;
}

int cnt=0;
bool tkn[100001];
int rnk[100001];

void tarjan(int root)
{
	dfn[root]=low[root]=++cnt;
	rnk[cnt]=root;
	for(auto i:mp[root])
	{
		if(!tkn[(*st)(i)])
		{
			if(dfn[i]==0)
			{
				tarjan(i);
				low[root]=min(low[root],low[i]);
			}
			else
			{
				low[root]=min(low[root],dfn[i]);
			}
		}
	}
	if(low[root]!=dfn[root])
		st->merge(root,rnk[low[root]]);
	tkn[root]=true;
	return;
}

int cat[100001];
int idg[100001],odg[100001];

void work()
{
	for(int i=1;i<=n;i++)
		if(!tkn[i])
			tarjan(i);
	for(int i=1;i<=n;i++)
	{
		cat[(*st)(i)]++;
		for(auto j:mp[i])
		{
			if(!st->ist(i,j))
			{
				idg[(*st)(j)]++;
				odg[(*st)(i)]++;
			}
		}
	}
	int ans=0;
	for(int i=1;i<=n;i++)
		ans=max(ans,cat[i]);
	cout<<ans<<endl;
	int ai=0,ao=0;
	for(int i=1;i<=n;i++)
	{
		if(cat[i]!=0)
		{
			if(idg[i]==0)
				ai++;
			if(odg[i]==0)
				ao++;
		}
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