#include <cstddef>
template<typename Int,size_t size>
class tarray{
	private:
		Int a[size];
		size_t lowbit(size_t x){return x&(-x);}
	public:
		tarray(){;}
		void reset()
		{
			for(size_t i=0;i<size;i++)
				a[i]=0;
			return;
		}
		void add(size_t p,Int x)
		{
			if(p==0)
			{
				a[p]+=x;
				return;
			}
			while(p<size)
			{
				a[p]+=x;
				p+=lowbit(p);
			}
			return;
		}
		Int pre(size_t p)
		{
			if(p==0)
				return 0;
			Int ans=0;
			p--;
			while(p!=0)
			{
				ans+=a[p];
				p-=lowbit(p);
			}
			ans+=a[0];
			return ans;
		}
		Int range(size_t l,size_t r){return pre(r)-pre(l);}
		void set(size_t p,Int x){add(p,x-range(p,p+1));}
};

#include <iostream>
using namespace std;

tarray<long long,500010> a;
int n,m;
int main()
{
	ios::sync_with_stdio(false);
	cin>>n>>m;
	a.reset();
	for(int i=0;i<n;i++)
	{
		int x;
		cin>>x;
		a.add(i,x);
	}
	for(int i=0;i<m;i++)
	{
		int op,x,y;
		cin>>op>>x>>y;
		x--;
		if(op==1)
		{
			a.add(x,y);
		}
		else
		{
			cout<<a.range(x,y)<<'\n';
		}
	}
	return 0;
}