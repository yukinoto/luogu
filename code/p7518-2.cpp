#include <iostream>
#include <cstring>
#include <vector>
#include <algorithm>
#include <cstdlib>
using namespace std;


template<typename Int>
class stlt{
	private:
		class node{
			public:
				Int value,tag;
				node *lc,*rc;
				bool up_to_date;
				virtual ~node()
				{
					if(up_to_date)
					{
						delete lc;delete rc;
					}
					return;
				}
		};
		vector<node*>roots;
		int ll,rl;
		void pushtag(node* pt,int left,int right)
		{
			if(pt->lc==nullptr)
				return;
			int mid=(left+right)/2;
			if(!pt->up_to_date)
			{
				pt->up_to_date=true;
				pt->lc=new node(*pt->lc),pt->rc=new node(*pt->rc);
				pt->lc->up_to_date=pt->rc->up_to_date=false;
			}
			pt->lc->value+=pt->tag*(mid-left),pt->rc->value+=pt->tag*(right-mid);
			pt->lc->tag+=pt->tag,pt->rc->tag+=pt->tag;
			pt->tag=0;
		}
		node* build(int left,int right,Int* a)
		{
			node* pt=new node;
			if(left==right-1)
			{
				pt->value=a[left],pt->lc=pt->rc=nullptr;
				pt->tag=0,pt->up_to_date=true;
			}
			else
			{
				int mid=(left+right)/2;
				pt->lc=build(left,mid,a),pt->rc=build(mid,right,a);
				pt->value=pt->lc->value+pt->rc->value,pt->tag=0;
				pt->up_to_date=true;
			}
			return pt;
		}
		node* build(int left,int right)
		{
			node* pt=new node;
			if(left==right-1)
			{
				pt->value=pt->tag=0;
				pt->lc=pt->rc=nullptr;
				pt->up_to_date=true;
			}
			else
			{
				int mid=(left+right)/2;
				pt->lc=build(left,mid),pt->rc=build(mid,right);
				pt->value=pt->tag=0;
				pt->up_to_date=true;
			}
			return pt;
		}
		Int quest(node* pt,int left,int right,int l,int r)
		{
			if(left>=r||right<=l)
				return 0;
			if(left>=l&&right<=r)
				return pt->value;
			pushtag(pt,left,right);
			int mid=(left+right)/2;
			return quest(pt->lc,left,mid,l,r)+quest(pt->rc,mid,right,l,r);
		}
		void add(node* pt,int left,int right,int l,int r,Int x)
		{
			if(left>=r||right<=l)
				return;
			if(left>=l&&right<=r)
			{
				pt->value+=(right-left)*x;
				pt->tag+=x;pt->up_to_date=false;
				return;
			}
			pushtag(pt,left,right);
			int mid=(left+right)/2;
			add(pt->lc,left,mid,l,r,x),add(pt->rc,mid,right,l,r,x);
			pt->value=pt->lc->value+pt->rc->value;
			return;
		}
		void set(node* pt,int left,int right,int p,Int x)
		{
			if(left>p||right<=p)
				return;
			if(left==right-1)
			{
				pt->value=x,pt->tag=0;
				return;
			}
			pushtag(pt,left,right);
			int mid=(left+right)/2;
			set(pt->lc,left,mid,p,x),set(pt->rc,mid,right,p,x);
			pt->value=pt->lc->value+pt->rc->value;
			return;
		}
	public:
		typedef node* version;
		version basic(){return *roots.begin();}
		stlt(int left,int right)
		{
			ll=left,rl=right;
			roots.push_back(build(left,right));
			return;
		}
		stlt(int left,int right,Int*x)
		{
			ll=left,rl=right;
			roots.push_back(build(left,right,x));
			return;
		}
		version add(version v,int left,int right,Int x)
		{
			node* pt=new node(*v);
			pt->up_to_date=false;
			roots.push_back(pt);
			add(pt,ll,rl,left,right,x);
			return pt;
		}
		Int quest(version v,int left,int right)
		{
			node* pt=new node(*v);
			pt->up_to_date=false;
			Int ans=quest(pt,ll,rl,left,right);
			delete pt;
			return ans;
		}
		version set(version v,int p,Int x)
		{
			node* pt=new node(*v);
			pt->up_to_date=false;
			roots.push_back(pt);
			set(pt,ll,rl,p,x);
			return pt;
		}
};


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
	stlt<int> *sp;
	stlt<int>::version v[MAXN];
	bool tkn[MAXN];
	int depth[MAXN];
	int fa[MAXN][19];
	vector<int>sons[MAXN];
	void build(int root)
	{
		tkn[root]=true;
		v[root]=sp->set(v[fa[root][0]],w[root],root);
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
	void ex(){delete sp;}
	void init()
	{
		memset(fa,-1,sizeof(fa));
		sp=new stlt<int>(0,c+1);atexit(ex);
		fa[1][0]=1;
		v[1]=sp->basic();
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
		if(x==y)
			return x;
		for(int i=18;i>=0;i--)
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
		for(int i=18;i>=0;i--)
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
		for(int i=18;i>=0;i--)
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
		int left=x,right=meta_data::c+1;
		while(left!=right-1)
		{
			int mid=(left+right)/2;
			if(virtual_tree_down::quest(real_tree::sp->quest(real_tree::v[t],mid,mid+1),l)<=x+1)
				left=mid;
			else
				right=mid;
		}
		cout<<left<<endl;
	}
	return;
}

int main()
{
	ios::sync_with_stdio(false);
	init();
	work();
	return 0;
}