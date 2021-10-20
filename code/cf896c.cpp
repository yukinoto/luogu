#include <iostream>
#include <set>
#include <vector>
#include <algorithm>
using namespace std;

long long seed;
long long rnd()
{
	long long ret=seed;
	seed=(seed*7+13)%1000000007;
	return ret;
}

int n,m;
long long vmax;

template<typename T>
class odt{
	protected:
		class node{
			public:
				int l,r;
				mutable T value;
				bool operator <(const node&o)const
				{
					return l<o.l;
				}
				node(int _l,int _r,const T&_value)
				{
					l=_l,r=_r,value=_value;
				}
				node(){;}
				node(int _l)
				{
					l=_l;
				}
		};
		set<node>a;
		int l,r;
		auto split(int x)->decltype(a.end())
		{
			if(x>=r)
				return a.end();
			auto it=--a.upper_bound(x);
			if(it->l==x)
				return it;
			node p=*it;
			a.erase(it);
			a.insert(node(p.l,x,p.value));
			return a.insert(node(x,p.r,p.value)).first;
		}
	public:
		template<typename op>
		void init(int _l,int _r,op o)
		{
			l=_l,r=_r;
			int bef=l;
			T bf=o(bef);
			for(int i=l+1;i<r;i++)
			{
				T ti=o(i);
				if(ti==bf)
					continue;
				a.insert(node(bef,i,bf));
				bef=i;
				bf=ti;
			}
			a.insert(node(bef,r,bf));
			return;
		}
		void init(int l,int r,T *dt)
		{
			init(l,r,[dt](int x){return dt[x];});
			return;
		}
		void assign(int l,int r,const T&value)
		{
			auto ed=split(r),bg=split(l);
			a.erase(bg,ed);
			a.insert(node(l,r,value));
			return;
		}
		/*void performance(int l,int r)
		{
			auto ed=split(r),bg=split(l);
			for(auto i=bg;i!=ed;++i)
				//do something
			return;
		}*/
};

template<typename T>
T quickpow(T x,int r,T mod)
{
	if(r==1)
		return x;
	T as=quickpow(x,r>>1,mod);
	as*=as;
	as%=mod;
	if(r&1)
		return as*x%mod;
	return as;
}

class odt_ll:public odt<long long>
{
	public:
		long long sum(int l,int r,int x,long long y)
		{
			auto ed=split(r),bg=split(l);
			long long s=0;
			for(auto i=bg;i!=ed;++i)
			{
				s=(s+(i->r-i->l)*quickpow(i->value%y,x,y))%y;
			}
			return s;
		}
		long long kth(int l,int r,int k)
		{
			auto ed=split(r),bg=split(l);
			vector<node> v;
			for(auto i=bg;i!=ed;++i)
				v.push_back(*i);
			sort(v.begin(),v.end(),[](const node&x,const node&y){return x.value<y.value;});
			int cnt=0;
			for(auto&i:v)
			{
				cnt+=i.r-i.l;
				if(k<=cnt)
					return i.value;
			}
			throw "fuckccf!";
		}
		void add(int l,int r,long long x)
		{
			auto ed=split(r),bg=split(l);
			for(auto i=bg;i!=ed;++i)
			{
				i->value+=x;
			}
			return;
		}
};

odt_ll t;

void init()
{
	cin>>n>>m>>seed>>vmax;
	t.init(1,n+1,[&](int x){return (rnd()%vmax)+1;});
	return;
}

void work()
{
	for(int i=1;i<=m;i++)
	{
		int op=rnd()%4+1,l=rnd()%n+1,r=rnd()%n+1;
		if(l>r)
			swap(l,r);
		if(op==1)
		{
			t.add(l,r+1,rnd()%vmax+1);
		}
		if(op==2)
		{
			t.assign(l,r+1,rnd()%vmax+1);
		}
		if(op==3)
		{
			cout<<t.kth(l,r+1,rnd()%(r-l+1)+1)<<endl;
		}
		if(op==4)
		{
			int x=rnd()%vmax+1,y=rnd()%vmax+1;
			cout<<t.sum(l,r+1,x,y)<<endl;
		}
	}
	return;
}

int main()
{
	init();
	work();
	return 0;
}
