#include <iostream>
#include <set>
#include <cmath>
#include <algorithm>
using namespace std;

class odt{
	private:
		struct node{
			size_t l,r;
			mutable long long value;
			bool operator<(const node&x)const
			{
				return l<x.l;
			}
			node(size_t _l,size_t _r,long long _value)
			{
				l=_l,r=_r,value=_value;
				return;
			}
			node(size_t _l)
			{
				l=_l;
				return;
			}
			node(){;}
		};
		set<node> st;
		set<node>::iterator split(size_t x)
		{
			auto p=--st.upper_bound(x);
			if(p->l==x)
				return p;
			auto t=*p;
			st.erase(p);
			st.insert(node(t.l,x,t.value));
			return st.insert(node(x,t.r,t.value)).first;
		}
		void merge(size_t l,size_t r)
		{
			node tmp=*st.lower_bound(l);
			bool flag=true;
			while(flag)
			{
				flag=false;
				size_t br=-1;
				for(auto i=st.lower_bound(tmp);;++i)
				{
					if(i==st.end()||i->l>=r||i->value!=tmp.value)
						break;
					flag=true;
					br=i->r;
				}
				if(flag&&br!=tmp.r)
				{
					st.erase(st.lower_bound(tmp.l),st.lower_bound(br));
					st.insert(node(tmp.l,br,tmp.value));
				}
				tmp=*(++st.lower_bound(tmp));
			}
			return;
		}
	public:
		odt(size_t l,size_t r,long long *a)
		{
			int bef=l;
			for(int i=l+1;i<r;i++)
			{
				if(a[i]!=a[bef])
				{
					st.insert(node(bef,i,a[bef]));
					bef=i;
				}
			}
			st.insert(node(bef,r,a[bef]));
			return;
		}
		void assign(size_t l,size_t r,long long value)
		{
			auto pr=split(r),pl=split(l);
			st.erase(pl,pr);
			st.insert(node(l,r,value));
			return;
		}
		void sq(size_t l,size_t r)
		{
			auto pr=split(r),pl=split(l);
			for(auto it=pl;it!=pr;++it)
			{
				it->value=(long long)(sqrt(it->value));
			}
			merge(l,r);
			return;
		}
		/*long long quest(size_t l,size_t r)
		{
			long long ans=0;
			auto pr=split(r),pl=split(l);
			for(auto i=pl;i!=pr;++i)
			{
				ans+=i->value*(i->r-i->l);
			}
			return ans;
		}*/
		long long quest(size_t l,size_t r)
		{
			long long ans=0;
			auto pl=--st.upper_bound(l),pr=st.lower_bound(r);
			for(auto i=pl;i!=pr;i++)
				ans+=i->value*(min(i->r,r)-max(i->l,l));
			return ans;
		}
};

int main()
{
	int n;
	cin>>n;
	long long a[n];
	for(int i=0;i<n;i++)
		cin>>a[i];
	odt tr(0,n,a);
	int m;
	cin>>m;
	for(int i=0;i<m;i++)
	{
		int f,l,r;
		cin>>f>>l>>r;
		if(l>r)
			swap(l,r);
		--l;
		if(f==0)
			tr.sq(l,r);
		if(f==1)
			cout<<tr.quest(l,r)<<endl;
	}
	return 0;
}