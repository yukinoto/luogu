#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <cstring>
using namespace std;

long long p;

template <typename T>
class xds{
	private:
		class node{
			private:
				T num,tag;
				node *lc,*rc;
			public:
				template<typename op>
				node(int l,int r,op a)
				{
					tag=0;
					if(r==l+1)
					{
						lc=rc=nullptr;
						num=a(l)%p;
						return;
					}
					int mid=(l+r)/2;
					lc=new node(l,mid,a);
					rc=new node(mid,r,a);
					num=lc->num+rc->num%p;
					return;
				}
				~node()
				{
					if(lc!=nullptr)
						delete lc;
					if(rc!=nullptr)
						delete rc;
					return;
				}
				void add(int l,int r,int left,int right,const T &x)
				{
					if(min(right,r)<=max(left,l))
						return;
					if(l>=left&&r<=right)
					{
						tag=(tag+x)%p;
						num=(num+x*(r-l))%p;
						return;
					}
					int mid=(l+r)/2;
					lc->add(l,mid,left,right,x);
					rc->add(mid,r,left,right,x);
					num=(num+(min(r,right)-max(l,left))*x)%p;
					return;
				}
				void getTag(int l,int r,T _tag)
				{
					num=(num+_tag*(r-l))%p;
					tag=(tag+_tag)%p;
					return;
				}
				void pushTag(int l,int r)
				{
					if(lc!=nullptr)
					{
						int mid=(l+r)/2;
						lc->getTag(l,mid,tag);
						rc->getTag(mid,r,tag);
					}
					tag=0;
					return;
				}
				T quest(int l,int r,int left,int right)
				{
					if(min(right,r)<=max(left,l))
						return 0;
					if(l>=left&&r<=right)
					{
						return num;
					}
					int mid=(l+r)/2;
					pushTag(l,r);
					return (lc->quest(l,mid,left,right)+rc->quest(mid,r,left,right))%p;
				}
		};
		node *root;
		int l,r;
	public:
		template<typename op>
		xds(int left,int right,op a)
		{
			l=left,r=right;
			root=new node(l,r,a);
			return;
		}
		~xds()
		{
			delete root;
		}
		void add(int left,int right,T x)
		{
			root->add(l,r,left,right,x);
			return;
		}
		T quest(int left,int right)
		{
			return root->quest(l,r,left,right);
		}
};

int n,m,r;

template<typename T>
class tree{
	private:
		class node{
			public:
				T value;
				int fa,son;
				vector<int>sons;
				int size,top,dep;
				int dfn,rnk;
				void init(int _fa,vector<int>&ed,bool *tb,T vl)
				{
					value=vl;
					fa=_fa;
					for(int i:ed)
					{
						if(!tb[i])
						{
							sons.push_back(i);
							tb[i]=false;
						}
					}
					son=top=dfn=dep=0;
					size=1;
				}
		};
		node *a;
		int *rnk;
		xds<T> *dt;
		void build(int fa,int r,vector<int>*mp,bool*tb,T *vl)
		{
			a[r].init(fa,mp[r],tb,vl[r]);
			a[r].dep=a[fa].dep+1;
			for(int i:a[r].sons)
			{
				build(r,i,mp,tb,vl);
				if(a[r].son==0||a[a[r].son].size<a[i].size)
					a[r].son=i;
				a[r].size+=a[i].size;
			}
			a[r].sons.erase(lower_bound(a[r].sons.begin(),a[r].sons.end(),a[r].son));
		}
		void dfs(int top,int root)
		{
			static int cnt=0;
			a[root].dfn=++cnt;
			rnk[cnt]=cnt;
			a[root].top=top;
			dfs(top,a[root].son);
			for(int i:a[root].sons)
				dfs(i,i);
		}
	public:
		void init(int n,int r,vector<int>*mp,bool* tb,T *vl)
		{
			a=new node[n+1];
			build(r,r,mp,tb,vl);
			dfs(r,r);
			dt=new xds<T>(1,n,[&](int x){return a[rnk[x]].value;});
			return;
		}
		void a_l(int x,int y,T v)
		{
			while(a[x].top!=a[y].top)
			{
				if(a[a[x].top].dep<a[a[y].top].dep)
					swap(x,y);
				dt->add()
			}
		}
		tree(){;}
		~tree()
		{
			delete[]a;
			delete[]rnk;
			return;
		}
};

tree<long long>tr;

void init()
{
	cin>>n>>m>>r>>p;
	auto mp=new vector<int>[n+1];
	bool *tb=new bool[n+1];
	long long *vl=new long long[n+1];
	for(int i=1;i<=n;i++)
	{
		cin>>vl[i];
		tb[i]=false;
	}
	for(int i=0;i<m;i++)
	{
		int x,y;
		cin>>x>>y;
		mp[x].push_back(y),mp[y].push_back(x);
	}
	tr.init(n,r,mp,tb,vl);
	delete[]mp;
	delete[]tb;
	delete[]vl;
}
