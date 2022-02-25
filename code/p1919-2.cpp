#include <iostream>
#include <algorithm>
using namespace std;

typedef long long Int;
const Int mod=998244353,org=3;
const size_t MAXN=3200000;

Int quickpow(Int x,size_t n)
{
	if(n==0)
		return 1;
	Int ans=quickpow(x,n>>1);
	ans=ans*ans%mod;
	if(n&1)
		ans=ans*x%mod;
	return ans;
}

size_t revbit(size_t x,size_t b)
{
	size_t ans=0;
	for(size_t i=0;i<b;i++)
	{
		ans=(ans<<1)|(x&1);
		x>>=1;
	}
	return ans;
}

size_t bitnum(size_t x)
{
	size_t ans=0;
	if((x&(x-1))==0)
		ans=-1;
	while(x!=0)
	{
		x>>=1;
		++ans;
	}
	return ans;
}

Int ps[MAXN];
Int ns;
void pre(size_t n)
{
	ps[0]=1;
	n=1<<(bitnum(MAXN)-1);
	ns=n;
	Int x=quickpow(org,(mod-1)/n);
	for(size_t i=1;i<n;i++)
		ps[i]=ps[i-1]*x%mod;
	return;
}

Int w(size_t k,size_t n)
{
	return ps[k*ns/n];
}

size_t NTT(Int *pt,size_t n)
{
	size_t b=bitnum(n),ren=1<<b;
	for(size_t i=n;i<ren;i++)
		pt[i]=0;
	for(size_t i=0;i<ren;i++)
		if(i<revbit(i,b))
			swap(pt[i],pt[revbit(i,b)]);
	for(size_t sep=1;sep<=b;++sep)
	{
		size_t jp=1<<sep,hp=jp>>1;
		for(size_t i=0;i<ren;i+=jp)
		{
			for(size_t j=0;j<hp;++j)
			{
				Int p=pt[i+j+hp]*w(j,jp)%mod;
				pt[i+j+hp]=(pt[i+j]-p)%mod;
				pt[i+j]=(pt[i+j]+p)%mod;
			}
		}
	}
	return ren;
}

size_t INTT(Int *pt,size_t n)
{
	size_t b=bitnum(n),ren=1<<b;
	NTT(pt,n);
	Int dv=quickpow(ren,mod-2);
	for(size_t i=0;i<ren;i++)
		pt[i]=(pt[i]*dv%mod+mod)%mod;
	reverse(pt+1,pt+ren);
	return n;
}

Int a[MAXN],b[MAXN];

int main()
{
	int n=0,m=0;
	pre(n+m+1);
	char cache=cin.get();
	while(isspace(cache)) cache=cin.get();
	while(isdigit(cache)){a[n++]=cache-'0';cache=cin.get();}
	reverse(a,a+n);
	while(isspace(cache)) cache=cin.get();
	while(isdigit(cache)){b[m++]=cache-'0';cache=cin.get();}
	reverse(b,b+m);
	size_t rn=(NTT(a,n+m-1),NTT(b,n+m-1));
	for(int i=0;i<rn;i++)
		a[i]=a[i]*b[i]%mod;
	INTT(a,rn);
	for(int i=n+m-1;i<=n+m+10;i++)
		a[i]=0;
	int cnt=0;
	for(int i=0;i<n+m-1;i++)
	{
		a[i+1]+=a[i]/10;
		a[i]%=10;
	}
	for(cnt=n+m-1;a[cnt]>0;cnt++)
	{
		a[cnt+1]+=a[cnt]/10;
		a[cnt]%=10;
	}
	for(int i=cnt-1;i>=0;--i)
		cout<<a[i];
	cout<<endl;
	return 0;
}