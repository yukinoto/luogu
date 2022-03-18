#include <iostream>
#include <cstring>
#include <vector>
#include <utility>
#include <algorithm>
using namespace std;

const int MAXN=200001,MAXC=50001;

namespace meta_data{
	int n,m,c;
	int p[MAXC],ap[MAXC];
	int w[MAXN];
	vector<int> edges[MAXN];
	void init()
	{
		cin>>n>>m>>c;
		for(int i=1;i<=c;i++)
		{
			cin>>p[i];
			ap[p[i]]=i;
		}
		for(int i=1;i<=n;i++)
		{
			cin>>w[i];
			w[i]=ap[w[i]];
		}
		for(int i=1;i<n;i++)
		{
			int u,v;
			cin>>u>>v;
			edges[u].push_back(v),edges[v].push_back(u);
		}
		return;
	}
}

namespace real_tree{
	using meta_data::n,meta_data::c,meta_data::w,meta_data::edges;
	
	bool tkn[MAXN];
	int depth[MAXN];
	int fa[MAXN][19];
	vector<int>sons[MAXN];
	void build(int root)
	{
		tkn[root]=true;
		depth[root]=depth[fa[root][0]]+1;
		for(auto i:edges[root])
			if(!tkn[i])
			{
				fa[i][0]=root;
				sons[root].push_back(i);
				build(i);
			}
		return;
	}
	void init()
	{
		memset(fa,-1,sizeof(fa));
		fa[1][0]=1;
		build(1);
		return;
	}
	int gf(int root,int b)
	{
		if(fa[root][b]==-1)
			return fa[root][b]=gf(gf(root,b-1),b-1);
		return fa[root][b];
	}
	int jmp(int root,int sep)
	{
		int cnt=0;
		while(sep)
		{
			if(sep&1)
			{
				root=gf(root,cnt);
			}
			sep>>=1,cnt++;
		}
		return root;
	}
	int lca(int x,int y)
	{
		if(depth[y]>depth[x])
			swap(x,y);
		x=jmp(x,depth[x]-depth[y]);
		for(int i=15;i>=0;i--)
		{
			if(gf(x,i)!=gf(y,i))
				x=gf(x,i),y=gf(y,i);
		}
		return gf(x,0);
	}
}

namespace virtual_tree_up{
	using meta_data::w,meta_data::n,real_tree::sons,real_tree::depth;
	int fa[MAXN][19];
	int cls[MAXN],tmp[MAXC];
	void build(int root)
	{
		fa[root][0]=tmp[w[root]+1];
		int cache=tmp[w[root]];
		tmp[w[root]]=root;
		cls[root]=tmp[1];
		for(auto i:sons[root])
			build(i);
		tmp[w[root]]=cache;
	}
	void init()
	{
		memset(fa,-1,sizeof(fa));
		build(1);
	}
	int gf(int root,int b)
	{
		if(fa[root][b]==-1)
			return fa[root][b]=gf(gf(root,b-1),b-1);
		return fa[root][b];
	}
	int quest(int x,int y)
	{
		if(depth[x]<depth[y])
			throw -1;
		x=cls[x];
		if(depth[x]<depth[y])
			return 0;
		for(int i=15;i>=0;i--)
			if(depth[gf(x,i)]>=depth[y])
				x=gf(x,i);
		return w[x];
	}
}

namespace virtual_tree_down{
	using meta_data::w,meta_data::n,real_tree::sons,real_tree::depth;
	int fa[MAXN][19];
	int tmp[MAXC];
	void build(int root)
	{
		fa[root][0]=tmp[w[root]-1];
		int cache=tmp[w[root]];
		tmp[w[root]]=root;
		for(auto i:sons[root])
			build(i);
		tmp[w[root]]=cache;
	}
	void init()
	{
		memset(fa,-1,sizeof(fa));
		build(1);
	}
	int gf(int root,int b)
	{
		if(fa[root][b]==-1)
			return fa[root][b]=gf(gf(root,b-1),b-1);
		return fa[root][b];
	}
	int quest(int x,int y)
	{
		if(depth[x]<depth[y])
			return 0x7fffffff;
		for(int i=15;i>=0;i--)
			if(depth[gf(x,i)]>=depth[y])
				x=gf(x,i);
		return w[x];
	}
}

void init()
{
	meta_data::init();
	real_tree::init();
	virtual_tree_down::init();
	virtual_tree_up::init();
	return;
}

//
void work()
{
	int q;
	cin>>q;
	for(int i=0;i<q;i++)
	{
		int s,t;
		cin>>s>>t;
		int l=real_tree::lca(s,t),x=virtual_tree_up::quest(s,l);
		int ans=x;
		while(t!=l)
		{
			int y=virtual_tree_down::quest(t,l);
			if(y<=x+1)
				ans=max(ans,meta_data::w[t]);
			t=real_tree::gf(t,0);
		}
		cout<<ans<<endl;
	}
	return;
}

int main()
{
	init();
	work();
	return 0;
}