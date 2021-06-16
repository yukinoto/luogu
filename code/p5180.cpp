#include <iostream>
#include <vector>
using namespace std;

template<int N>
class Graph{
	public:
		vector<int>edge[N];
		void add_edge(int from,int to)
		{
			edge[from].push_back(to);
			return;
		}
};

int n,m;
Graph<200001> ps,anti;
int dfn[200001],p[200001];

void init()
{
	ios::sync_with_stdio(false);
	cin>>n>>m;
	for(int i=0;i<m;i++)
	{
		int x,y;
		cin>>x>>y;
		ps.add_edge(x,y),anti.add_edge(y,x);
	}
	return;
}

int fa[200001];
void dfs(int root)
{
	static int cnt=0;
	dfn[root]=++cnt;
	p[cnt]=root;
	for(int i=0;i<ps.edge[root].size();i++)
		if(fa[ps.edge[root][i]]==0)
		{
			fa[ps.edge[root][i]]=root;
			dfs(ps.edge[root][i]);
		}
	return;
}

int qst[200001],wei[200001];
int semi[200001],idom[200001];
int cst(int root)
{
	if(qst[root]==root) return root;
	int a=cst(qst[root]);
	if(dfn[semi[wei[qst[root]]]]<dfn[semi[wei[root]]]) wei[root]=wei[qst[root]];
	return qst[root]=a;
}

Graph<200001> str;

void tj()
{
	fa[1]=1;
	dfs(1);
	for(int i=1;i<=n;i++)
		semi[i]=qst[i]=wei[i]=i;
	for(int i=n;i>1;i--)
	{
		int tmp=p[i];
		for(int j=0;j<anti.edge[tmp].size();j++)
		{
			int f=anti.edge[tmp][j];
			cst(f);
			if(dfn[semi[wei[f]]]<dfn[semi[tmp]])
				semi[tmp]=semi[wei[f]];
		}
		qst[tmp]=fa[tmp];
		str.add_edge(semi[tmp],tmp);
		tmp=fa[tmp];
		for(int j=0;j<str.edge[tmp].size();j++)
		{
			int f=str.edge[tmp][j];
			cst(f);
			if(tmp==semi[wei[f]])
				idom[f]=tmp;
			else
				idom[f]=wei[f];
		}
		str.edge[tmp].clear();
	}
	for(int i=2;i<=n;i++)
	{
		int tmp=p[i];
		if(idom[tmp]!=semi[tmp])
			idom[tmp]=idom[idom[tmp]];
	}
}

Graph<200001> itr;
int size[200001];
void mks(int root)
{
	size[root]=1;
	for(int i=0;i<itr.edge[root].size();i++)
	{
		mks(itr.edge[root][i]);
		size[root]+=size[itr.edge[root][i]];
	}
	return;
}
void bdt()
{
	for(int i=1;i<=n;i++)
		itr.add_edge(idom[i],i);
	mks(1);
	return;
}

void opt()
{
	for(int i=1;i<n;i++)
		cout<<size[i]<<' ';
	cout<<size[n]<<endl;
	return;
}

void work()
{
	init();
	tj();
	bdt();
	opt();
	return;
}

int main()
{
	work();
	return 0;
}
