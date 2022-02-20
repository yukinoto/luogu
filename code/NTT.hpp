#include <stddef.h>
#include <algorithm>
using std::reverse;
#define MAXN 2200000
namespace NTT{
	namespace lib{
		template<typename Int>
		Int quickpow(Int x,Int n,const Int mod)
		{
			if(n==0)
				return 1;
			if(n==1)
				return x;
			Int ans=quickpow(x,n>>1,mod);
			ans=ans*ans%mod;
			if(n&1)
				ans=ans*x%mod;
			return ans;
		}
		template<typename Int>
		Int revbit(Int x,size_t b)
		{
			Int ans=0;
			for(int i=0;i<b;i++)
			{
				ans=(ans<<1)|(x&1);
				x>>=1;
			}
			return ans;
		}
		template<typename Int>
		size_t bitnum(Int n)
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
		void pre(size_t n,long long mod,long long org)
		{
			if(md==mod&&mn==n)
				return;
			ps[0]=1;
			mn=n;
			long long x=quickpow<long long>(org,(mod-1)/n,mod);
			for(size_t i=1;i<n;i++)
				ps[i]=ps[i-1]*x%mod;
			return;
		}
		long long w(size_t k,size_t n)
		{
			return ps[k*mn/n];
		}
		template<typename Int,Int mod>
		void _fft(Int * const f,Int *t,const size_t b)
		{
			size_t hn=1<<(b-1),n=hn<<1;
			for(size_t i=0;i<hn;++i)
			{
				t[i]=(f[i]+w(i,n)*f[i+hn])%mod;
				t[i+hn]=(f[i]-w(i,n)*f[i+hn])%mod;
			}
			return;
		}
		template<typename Int,Int mod,Int org>
		Int* fft(const Int *pt,size_t n,size_t b)
		{
			size_t ren=1<<(b);
			pre(ren,mod,org);
			Int *t[2];t[0]=new Int[ren],t[1]=new Int[ren];
			for(size_t i=0;i<n;++i)
			{
				t[0][revbit(i,b)]=pt[i];
			}
			for(size_t i=n;i<ren;++i)
			{
				t[0][revbit(i,b)]=0;
			}
			for(size_t sep=1;sep<=b;sep++)
			{
				for(size_t i=0;i<ren;i+=(1<<sep))
				{
					_fft<Int,mod>(t[(sep&1)^1]+i,t[sep&1]+i,sep);
				}
			}
			delete t[(b&1)^1];
			return t[b&1];
		}
		template<typename Int,Int mod,Int org>
		Int* ifft(const Int *pt,size_t n,size_t b)
		{
			Int *t=fft<Int,mod,org>(pt,n,b),dv=quickpow<long long>(n,mod-2,mod);
			for(int i=0;i<(1<<b);++i)
			{
				t[i]=t[i]*dv%mod;
				t[i]=(t[i]+mod)%mod;
			}
			reverse(t+1,t+(1<<b));
			return t;
		}
	}
	template<typename Int,Int mod,Int org>//mod x^n
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
			ploy<Int,mod,org>& operator=(const ploy<Int,mod,org>&x)
			{
				this->n=x.n;
				delete this->p;
				this->p=new Int[x.n];
				for(size_t i=0;i<x.n;i++)
					this->p[i]=x.p[i];
				return *this;
			}
			ploy<Int,mod,org>& operator=(ploy<Int,mod,org>&&x)
			{
				this->n=x.n;
				this->p=x.p;
				x.p=nullptr;
				x.n=0;
				return *this;
			}
			ploy(const ploy<Int,mod,org>&x)
			{
				this->n=x.n;
				this->p=new Int[x.n];
				for(size_t i=0;i<x.n;i++)
					this->p[i]=x.p[i];
			}
			ploy(ploy<Int,mod,org>&&x)
			{
				this->n=x.n;
				delete this->p;
				this->p=x.p;
				x.p=nullptr;
			}
			ploy<Int,mod,org>& operator +=(const ploy<Int,mod,org> &x)
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
			ploy<Int,mod,org>& operator -=(const ploy<Int,mod,org> &x)
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
			ploy<Int,mod,org>& operator *=(const ploy<Int,mod,org> &x)
			{
				size_t nn=this->n+x.n-1,b=lib::bitnum(nn),fn=1<<b;
				Int *t1=lib::fft<Int,mod,org>(this->p,this->n,b),*t2=lib::fft<Int,mod,org>(x.p,x.n,b);
				for(size_t i=0;i<fn;i++)
					t1[i]=t1[i]*t2[i]%mod;
				delete t2;delete this->p;
				this->p=lib::ifft<Int,mod,org>(t1,fn,b);
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

typedef NTT::ploy<long long,998244353,3> ploy;