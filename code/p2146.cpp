#include <iostream>
#include <set>
#include <vector>
#include <algorithm>
#include <string>
using namespace std;

template<typename T>
class node{
	public:
		int l,r;
		mutable T value;
		bool operator <(const node &x)const
		{
			return l<x.l;
		}
		node(int _l,int _r,T _value)
		{
			l=_l,r=_r,value=_value;
			return;
		}
};

template<typename T>
class odt{
	public:
		set<node<T> >a;
		int left,right;
		template<typename op>
		void init(int l,int r,op o)
		{
			left=l,right=r;
			int bf=l;
			for(int i=l;i<r;i++)
			{
				if(o(i)==o(bf))
					continue;
				a.insert(node<T>(bf,i,o(bf)));
				bf=i;
			}
			a.insert(node<T>(bf,r,o(bf)));
			return;
		}
		void init(int l,int r,T *dt)
		{
			init(l,r,[dt](int x){return dt[x];});
			return;
		}
		auto split(int x)
		{
			if(x>=right)
				return a.end();
			auto pt=--a.upper_bound(node<T>(x,0,0));
			if(pt->l==x)
				return pt;
			node<T> p=*pt;
			a.erase(pt);
			a.insert(node<T>(p.l,x,p.value));
			return a.insert(node<T>(x,p.r,p.value)).first;
		}
		void assign(int l,int r,const T&value)
		{
			auto ed=split(r),bg=split(l);
			a.erase(bg,ed);
			a.insert(node<T>(l,r,value));
		}
};

class odt_bool:public odt<bool>
{
	public:
		int sum(int l,int r,bool value)
		{
			auto ed=split(r),bg=split(l);
			int s=0;
			for(auto i=bg;i!=ed;++i)
			{
				if(i->value==value)
				{
					s+=i->r-i->l;
				}
			}
			return s;
		}
};

//test for odt
/*int main()
{
	int n;
	cin>>n;
	bool *tb=new bool[n];
	for(int i=0;i<n;i++)
		cin>>tb[i];
	odt_bool tr;
	tr.init(0,n,tb);
	while(true)
	{
		int f;
		cin>>f;
		int l,r;
		cin>>l>>r;
		if(f==1)
		{
			cout<<tr.sum(l,r,true)<<endl;
		}
		if(f==2)
		{
			bool z;
			cin>>z;
			tr.assign(l,r,z);
		}
	}
	return 0;
}*/

class tree{
	private:
		class node{
			public:
				int fa,son;
				vector<int>sons;
				int dfn,dep,top,size;
				void init()
				{
					son=dep=-1;
					size=1;
				}
		};
		node *a;
		int *rnk;
		int n;
		void dfs1(int root)
		{
			a[root].init();
			a[root].dep=a[a[root].fa].dep+1;
			for(auto i:a[root].sons)
			{
				dfs1(i);
				a[root].size+=a[i].size;
				if(a[root].son==-1||a[i].size>a[a[root].son].size)
					a[root].son=i;
			}
		}
		void dfs2(int root,int top)
		{
			static int cnt=-1;
			a[root].dfn=++cnt;
			rnk[cnt]=root;
			a[root].top=top;
			if(a[root].son!=-1)
			{
				dfs2(a[root].son,top);
			}
			for(auto i:a[root].sons)
				if(i!=a[root].son)
				{
					dfs2(i,i);
				}
			return;
		}
		odt_bool dt;
	public:
		void init()
		{
			cin>>n;
			a=new node[n];
			rnk=new int[n];
			a[0].fa=0;
			for(int i=1;i<n;i++)
			{
				int fa;
				cin>>fa;
				a[fa].sons.push_back(i);
				a[i].fa=fa;
			}
			dfs1(0);
			dfs2(0,0);			
			dt.init(0,n,[&](int x){return false;});
			return;
		}
		int ist(int root)
		{
			if(dt.sum(a[root].dfn,a[root].dfn+1,true)>0)
				return 0;
			int sum=0;
			while(a[root].top!=0)
			{
				sum+=dt.sum(a[a[root].top].dfn,a[root].dfn+1,false);
				dt.assign(a[a[root].top].dfn,a[root].dfn+1,true);
				root=a[a[root].top].fa;
			}
			sum+=dt.sum(a[0].dfn,a[root].dfn+1,false);
			dt.assign(a[0].dfn,a[root].dfn+1,true);
			return sum;
		}
		int ust(int root)
		{
			if(dt.sum(a[root].dfn,a[root].dfn+1,false)>0)
				return 0;
			int sum=dt.sum(a[root].dfn,a[root].dfn+a[root].size,true);
			dt.assign(a[root].dfn,a[root].dfn+a[root].size,false);
			return sum;
		}
		~tree()
		{
			delete[]rnk,a;
		}
};

int main()
{
	cin.sync_with_stdio(false);
	cout.sync_with_stdio(false);
	tree t;
	t.init();
	int m;
	cin>>m;
	for(int i=0;i<m;i++)
	{
		string o;
		int r;
		cin>>o>>r;
		if(o=="install")
			cout<<t.ist(r)<<endl;
		if(o=="uninstall")
			cout<<t.ust(r)<<endl;
	}
	return 0;
}
