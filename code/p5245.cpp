#include <iostream>
#include <vector>
#include <stddef.h>
#include <algorithm>
using std::reverse;
#define MAXN 280000
typedef long long Int;
const Int mod=998244353,org=3;
namespace NTT{
	namespace lib{
		Int quickpow(Int x,Int n)
		{
			if(n==0)
				return 1;
			if(n==1)
				return x;
			Int ans=quickpow(x,n>>1);
			ans=ans*ans%mod;
			if(n&1)
				ans=ans*x%mod;
			return ans;
		}
		size_t revbit(size_t x,size_t b)
		{
			size_t ans=0;
			for(int i=0;i<b;i++)
			{
				ans=(ans<<1)|(x&1);
				x>>=1;
			}
			return ans;
		}
		size_t bitnum(size_t n)
		{
			size_t cnt=0;
			if(n&(n-1))
			{
				while(n!=1)
				{
					++cnt;
					n>>=1;
				}
				++cnt;
			}
			else
			{
				while(n!=1)
				{
					++cnt;
					n>>=1;
				}
			}
			return cnt;
		}
		long long ps[MAXN],md=-1,mn;
		void pre(size_t n)
		{
			ps[0]=1;
			mn=n;
			long long x=quickpow(org,(mod-1)/n);
			for(size_t i=1;i<n;i++)
				ps[i]=ps[i-1]*x%mod;
			//std::cerr<<"doit!"<<std::endl;
			return;
		}
		long long w(size_t k,size_t n)
		{
			//if(mn%n!=0)	throw -1;
			return ps[k*mn/n];
		}
		void _fft(Int *f,const size_t n)
		{
			size_t hn=n>>1;
			for(size_t i=0;i<hn;++i)
			{
				Int p=w(i,n)*f[i+hn];
				f[i+hn]=(f[i]-p)%mod;
				f[i]=(f[i]+p)%mod;
			}
			return;
		}
		Int* fft(const Int *pt,size_t n,size_t b)
		{
			size_t ren=1<<(b);
			Int *t=new Int[ren];
			for(size_t i=0;i<n;++i)
			{
				t[revbit(i,b)]=pt[i];
			}
			for(size_t i=n;i<ren;++i)
			{
				t[revbit(i,b)]=0;
			}
			for(size_t sep=1;sep<=b;sep++)
			{
				size_t jp=(1<<sep);
				for(size_t i=0;i<ren;i+=jp)
				{
					_fft(t+i,jp);
				}
			}
			return t;
		}
		Int* ifft(const Int *pt,size_t n,size_t b)
		{
			Int *t=fft(pt,n,b),dv=quickpow(n,mod-2);
			for(int i=0;i<(1<<b);++i)
			{
				t[i]=t[i]*dv%mod;
				if(t[i]<0)
					t[i]=(t[i]+mod)%mod;
			}
			reverse(t+1,t+(1<<b));
			return t;
		}
	}
	class ploy{
		private:
			Int *p;
			size_t n;
		public:
			ploy(){p=nullptr;}
			ploy(size_t n){this->n=n;p=new Int[n];}
			ploy(Int *pt,size_t n){this->p=pt,this->n=n;}
			virtual ~ploy(){delete p;}
			template<typename STL>
			ploy(const STL &data)
			{
				p=new Int[data.size()];
				n=0;
				for(auto i=data.begin();i!=data.end();++i)
					p[n++]=*i;
				return;
			}
#ifdef _GLIBCXX_ISTREAM
			std::istream& init(size_t n,std::istream& ins)
			{
				if(p!=nullptr)	delete p;
				p=new Int[n];
				this->n=n;
				for(size_t i=0;i<n;++i)
				{
					ins>>p[i];
				}
				return ins;
			}
			std::istream& init(std::istream& ins)
			{
				ins>>this->n;
				return init(n,ins);
			}
#endif
#ifdef _GLIBCXX_OSTREAM
			std::ostream& output(std::ostream& ous)
			{
				for(size_t i=0;i<n-1;i++)
					ous<<p[i]<<' ';
				return ous<<p[n-1]<<'\n';
			}
#endif
			ploy& operator=(const ploy&x)
			{
				this->n=x.n;
				delete this->p;
				this->p=new Int[x.n];
				for(size_t i=0;i<x.n;i++)
					this->p[i]=x.p[i];
				return *this;
			}
			ploy& operator=(ploy&&x)
			{
				this->n=x.n;
				this->p=x.p;
				x.p=nullptr;
				x.n=0;
				return *this;
			}
			ploy(const ploy&x)
			{
				this->n=x.n;
				this->p=new Int[x.n];
				for(size_t i=0;i<x.n;i++)
					this->p[i]=x.p[i];
			}
			ploy(ploy&&x)
			{
				this->n=x.n;
				delete this->p;
				this->p=x.p;
				x.p=nullptr;
			}
			ploy& operator +=(const ploy &x)
			{
				if(this->n>=x.n)
				{
					for(size_t i=0;i<x.n;i++)
						this->p[i]=(this->p[i]+x.p[i])%mod;
				}
				else
				{
					Int *pt=new Int[x.n];
					for(size_t i=0;i<this->n;i++)
						pt[i]=(this->p[i]+x.p[i])%mod;
					for(size_t i=this->n;i<x.n;i++)
						pt[i]=x.p[i];
					this->n=x.n;
					delete this->p;
					this->p=pt;
				}
				return *this;
			}
			ploy& operator -=(const ploy &x)
			{
				if(this->n>=x.n)
				{
					for(size_t i=0;i<x.n;i++)
						this->p[i]=(this->p[i]-x.p[i]+mod)%mod;
				}
				else
				{
					Int *pt=new Int[x.n];
					for(size_t i=0;i<this->n;i++)
						pt[i]=(this->p[i]-x.p[i]+mod)%mod;
					for(size_t i=this->n;i<x.n;i++)
						pt[i]=x.p[i];
					this->n=x.n;
					delete this->p;
					this->p=pt;
				}
				return *this;
			}
			ploy& operator *=(const ploy &x)
			{
				size_t nn=this->n+x.n-1,b=lib::bitnum(nn),fn=1<<b;
				Int *t1=lib::fft(this->p,this->n,b),*t2=lib::fft(x.p,x.n,b);
				for(size_t i=0;i<fn;i++)
					t1[i]=t1[i]*t2[i]%mod;
				delete t2;delete this->p;
				this->p=lib::ifft(t1,fn,b);
				delete t1;
				this->n=nn;
				return *this;
			}
			void cut(size_t n)
			{
				if(this->n>n)
					this->n=n;
			}
	};
}

#include <cctype>

using NTT::ploy;
using namespace std;

ploy zero(vector<long long>(1,{1}));

ploy quickpow(const ploy &a,int n,int p)
{
	ploy ans=zero;
	for(int i=29;i>=0;i--)
	{
		ans*=ans;ans.cut(p);
		if(n&(1ull<<i))
		{
			ans*=a;
			ans.cut(p);
		}
	}
	return ans;
}

int main()
{
	ios::sync_with_stdio(false);
	NTT::lib::pre(1<<NTT::lib::bitnum(200000));
	long long n,k;
	cin>>n;
	k=0;
	char c=cin.get();
	while(isspace(c))	c=cin.get();
	while(isdigit(c))
	{
		k=k*10+c-'0';
		k%=998244353;
		c=cin.get();
	}
	k%=998244353;
	ploy x;
	x.init(n,cin);
	x=quickpow(x,k,n);
	x.output(cout);
	return 0;
}