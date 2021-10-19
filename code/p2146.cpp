#include <iostream>
#include <set>
#include <algorithm>
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
		int sum(int l,int r)
		{
			auto ed=split(r),bg=split(l);
			int s=0;
			for(auto i=bg;i!=ed;++i)
			{
				if(i->value)
				{
					s+=i->r-i->l;
				}
			}
			return s;
		}
};

int main()
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
			cout<<tr.sum(l,r)<<endl;
		}
		if(f==2)
		{
			bool z;
			cin>>z;
			tr.assign(l,r,z);
		}
	}
	return 0;
}
