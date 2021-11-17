#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
using namespace std;

int n,m;
int w[10001];
int dfn[10001],low[10001];
bool tkn[10001];
vector<int> mp[10001];

void init()
{
	cin>>n>>m;
	for(int i=1;i<=n;i++)
		cin>>w[i];
	for(int i=0;i<m;i++)
	{
		int x,y;
		cin>>x>>y;
		mp[x].push_back(y);
		//mp[y].push_back(x);
	}
}

int cnt=0;
int rnk[100001];

class cst{
	private:
	int fa[100001];
	public:
	cst(int n)
	{
		for(int i=1;i<=n;i++)
			fa[i]=i;
		return;
	}
	int gf(int x)
	{
		if(fa[x]==x)
			return x;
		return fa[x]=gf(fa[x]);
	}
	bool ist(int x,int y)
	{
		return gf(x)==gf(y);
	}
	void merge(int x,int y)
	{
		fa[gf(x)]=gf(y);
	}
};

vector<int> nmp[100001];
int nw[100001],wa[10001];
int nnk[100001],top=0;
int idg[100001],odg[100001];

cst st(100000);

void tarjan(int root)
{
	low[root]=dfn[root]=++cnt;
	rnk[cnt]=root;
	for(auto i:mp[root])
	{
		if(!tkn[st.gf(i)])
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
	if(dfn[root]!=low[root])
		st.merge(root,rnk[low[root]]);
	tkn[root]=true;
	return;
}

void work()
{
	for(int i=1;i<=n;i++)
		if(!tkn[i])
			tarjan(i);
	for(int i=1;i<=n;i++)
	{
		if(nnk[st.gf(i)]==0)
			nnk[st.gf(i)]=++top;
		nw[nnk[st.gf(i)]]+=w[i];
		for(auto j:mp[i])
		{
			if(st.ist(i,j))
				continue;
			if(nnk[st.gf(j)]==0)
				nnk[st.gf(j)]=++top;
			nmp[nnk[st.gf(i)]].push_back(nnk[st.gf(j)]);
			odg[nnk[st.gf(i)]]++;
			idg[nnk[st.gf(j)]]++;
		}
	}
	queue<int> q;
	for(int i=1;i<=top;i++)
	{
		if(idg[i]==0)
		{
			q.push(i);
			wa[i]=nw[i];
		}
	}
	int ans=0;
	while(!q.empty())
	{
		int p=q.front();q.pop();
		for(auto i:nmp[p])
		{
			wa[i]=max(wa[p]+nw[i],wa[i]);
			idg[i]--;
			if(idg[i]==0)
				q.push(i);
		}
		if(odg[p]==0)
			ans=max(ans,wa[p]);
	}
	cout<<ans<<endl;
	return;
}

int main()
{
	init();
	work();
	return 0;
}