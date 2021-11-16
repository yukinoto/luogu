#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
using namespace std;

/*class cst{
	public:
	int n;
	int *f;
	cst(int _n=300000)
	:n(_n)
	{
		f=new int(n+1);
		for(int i=0;i<=n;i++)
			f[i]=i;
	}
	~cst()
	{
		delete[] f;
	}
	int fa(int x)
	{
		if(f[x]==x)
			return x;
		return f[x]=fa(f[x]);
	}
	bool ist(int x,int y)
	{
		return fa(x)==fa(y);
	}
	void merge(int x,int y)
	{
		f[fa(x)]=fa(y);
		return;
	}
};*/

int n,m;
//cst st;

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
				low[root]=min(low[root],dfn[i]);
			}
		}
	}
	tkn[root]=true;
	return;
}

vector<int>node;
vector<int>nmp[100001];
int cat[100001];

int idg[100001],odg[100001];
vector<pair<int,int>>mmp[100001];

void pre_dfs(int root,int from)
{
	if(odg[root]==0)
	{
		mmp[root].push_back(make_pair(from,1));
		return;
	}
	for(auto i:nmp[root])
	{
		pre_dfs(i,from);
	}
}

int mem[100001];
int top=0;
int dep[100001];

bool bfs(int s,int t)
{
	queue<int>q;
	q.push(s);
	for(int i=0;i<top;i++)
		dep[mem[i]]=-1;
	dep[s]=0;
	while(!q.empty())
	{
		int p=q.front();
		q.pop();
		for(auto i:mmp[p])
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

int now[100001];

int dfs(int root,int t,int flow)
{
	if(root==t)
		return flow;
	int anf=0;
	for(int i=now[root];i<mmp[root].size();i++)
	{
		if(flow==0)
			break;
		if(mmp[root][i].second!=0&&dep[mmp[root][i].first]==dep[root]+1)
		{
			int tmp=dfs(mmp[root][i].first,t,min(flow,mmp[root][i].second));
			anf+=tmp;
			flow-=tmp;
			mmp[root][i].second-=tmp;
			mmp[mmp[root][i].first].push_back(make_pair(root,tmp));
			now[root]=i;
		}
	}
	return anf;
}

int dinic(int s,int t)
{
	int ans=0;
	while(bfs(s,t))
		ans+=dfs(s,t,0x3fffffff);
	return ans;
}

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
			nmp[rnk[low[i]]].push_back(tmp);
			odg[rnk[low[i]]]++;
			idg[tmp]++;
		}
	}
	int ans=0;
	for(int i=1;i<=n;i++)
		ans=max(ans,cat[i]);
	cout<<ans<<endl;
	int sz=0;
	for(int i=1;i<=n;i++)
	{
		if(cat[i]!=0)
		{
			if(idg[i]==0)
			{
				pre_dfs(i,i);
			}
			if(odg[i]==0)
			{
				mmp[n+1].push_back(make_pair(i,1));
				sz++;
				mem[top++]=i;
			}
			if(idg[i]==0)
			{
				mmp[i].push_back(make_pair(0,1));
				sz++;
				mem[top++]=i;
			}
		}
	}
	mem[top++]=0,mem[top++]=n+1;
	cout<<sz-dinic(n+1,0)<<endl;
	return;
}

int main()
{
	init();
	work();
	return 0;
}