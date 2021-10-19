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

class odt_ll:public odt<long long>{
	public:
		long long sum(int l,int r)
		{
			auto ed=split(r),bg=split(l);
			long long s=0;
			for(auto i=bg;i!=ed;++i)
			{
				s+=i->value*(i->r-i->l);
			}
			return s;
		}
		void add(int l,int r,long long value)
		{
			auto ed=split(r),bg=split(l);
			for(auto i=bg;i!=ed;++i)
			{
				i->value+=value;
			}
			return;
		}
		
};

int main()
{
	cin.sync_with_stdio(false);
	cout.sync_with_stdio(false);
	int n,m;
	cin>>n>>m;
	long long *a=new long long [n];
	for(int i=0;i<n;i++)
	{
		cin>>a[i];
	}
	odt_ll t;
	t.init(0,n,a);
	for(int i=0;i<m;i++)
	{
		int f,l,r;
		cin>>f>>l>>r;
		if(f==1)
			cout<<t.sum(l,r)<<endl;
		if(f==2)
		{
			long long x;
			cin>>x;
			t.add(l,r,x);
		}
		if(f==3)
		{
			long long x;
			cin>>x;
			t.assign(l,r,x);
		}
	}
	delete[]a;
	return 0;
}
