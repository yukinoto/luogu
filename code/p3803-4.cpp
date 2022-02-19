#include <iostream>
#include <algorithm>
using namespace std;

const long long mod=998244353;

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

size_t gn;
long long ps[4000010];
void pre(size_t n)
{
	gn=n;
	ps[0]=1;
	long long x=quickpow<long long>(3,(mod-1)/n%mod,mod);
	for(int i=1;i<n;i++)
		ps[i]=ps[i-1]*x%mod;
}

long long w(size_t k,size_t n)
{
	return ps[k*gn/n];
}

template<typename Int>
Int anti(Int x,size_t b)
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

template<typename Int>
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

template<typename Int>
Int* fft(const Int *pt,size_t n,size_t b)
{
	size_t ren=1<<(b);
	Int *t[2];t[0]=new Int[ren],t[1]=new Int[ren];
	for(int i=0;i<n;++i)
	{
		t[0][anti(i,b)]=pt[i];
	}
	for(int i=n;i<ren;++i)
	{
		t[0][anti(i,b)]=0;
	}
	for(int sep=1;sep<=b;sep++)
	{
		for(int i=0;i<ren;i+=(1<<sep))
		{
			_fft<long long>(t[(sep&1)^1]+i,t[sep&1]+i,sep);
		}
	}
	delete t[(b&1)^1];
	return t[b&1];
}

template<typename Int>
Int* ifft(const Int *pt,size_t n,size_t b)
{
	Int *t=fft(pt,n,b),dv=quickpow<long long>(n,mod-2,mod);
	for(int i=0;i<(1<<b);++i)
	{
		t[i]=t[i]*dv%mod;
		t[i]=(t[i]+mod)%mod;
	}
	reverse(t+1,t+(1<<b));
	return t;
}

long long a[2000010],b[2000010];

int main()
{
	//freopen("P3803_8.in","r",stdin);
	ios::sync_with_stdio(false);
	int n,m;
	cin>>n>>m;
	pre(1<<(bitnum(n+m+1)));
	for(int i=0;i<=n;++i)
		cin>>a[i];
	for(int i=0;i<=m;++i)
		cin>>b[i];
	long long *t1=fft(a,n+1,bitnum(n+m+1)),*t2=fft(b,m+1,bitnum(n+m+1));
	int ren=1<<(bitnum(n+m+1));
	for(int i=0;i<ren;++i)
		t1[i]=t1[i]*t2[i]%mod;
	long long *t=ifft<long long>(t1,ren,bitnum(n+m+1));
	delete t1;delete t2;
	for(int i=0;i<=m+n;i++)
		cout<<t[i]<<' ';
	cout<<endl;
	delete t;
	return 0;
}