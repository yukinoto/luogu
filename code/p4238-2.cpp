#include <iostream>
using namespace std;

typedef long long Int;

const Int mod=998244353,org=3;

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

size_t btn(size_t n)
{
	size_t ans=0;
	while(n)
	{
		n>>=1;
		ans++;
	}
	return ans;
}

size_t reversebit(size_t x,size_t bit)
{
	size_t ans=0;
	for(int i=0;i<bit;i++)
	{
		ans=(ans<<1)|(x&1);
		x>>=1;
	}
	return ans;
}

const size_t MAXN=320000;

Int ps[MAXN];
size_t ren;

void pre(size_t n)
{
	ren=1<<btn(n);
	ps[0]=1;
	Int x=quickpow(org,(mod-1)/ren);
	for(size_t i=1;i<ren;i++)
		ps[i]=ps[i-1]*x%mod;
}

Int w(size_t k,size_t n)
{
	return ps[k*ren/n];
}

void _NTT(Int *pt,size_t n)
{
	size_t hn=n>>1;
	for(size_t i=0;i<hn;i++)
	{
		Int p=pt[hn+i]*w(i,n);
		pt[hn+i]=(pt[i]-p)%mod;
		pt[i]=(pt[i]+p)%mod;
	}
	return;
}

Int* NTT(Int *pt,size_t n,size_t b)
{
	size_t ren=(1<<b);
	Int* t=new Int[ren];
	for(size_t i=0;i<n;i++)
		t[reversebit(i,b)]=pt[i];
	for(size_t i=n;i<ren;i++)
		t[reversebit(i,b)]=0;
	for(size_t sep=1;sep<=b;sep++)
	{
		size_t jp=(1<<sep);
		for(size_t i=0;i<ren;i+=jp)
			_NTT(t+i,jp);
	}
	return t;
}

#include <algorithm>

Int* INTT(Int *pt,size_t b)
{
	size_t ren=(1<<b);
	Int* t=NTT(pt,ren,b),div=quickpow(ren,mod-2);
	reverse(t+1,t+ren);
	for(int i=0;i<ren;i++)
		t[i]=(t[i]*div%mod+mod)%mod;
	return t;
}

int main()
{
	size_t n;
	cin>>n;
	Int *pt=new Int[n];
	for(size_t i=0;i<n;i++)
		cin>>pt[i];
	size_t b=btn(n),ren=(1<<b);
	pre(ren);
	Int *f=NTT(pt,n,b);
	Int *t[2];t[0]=new Int[ren],t[1]=new Int[ren];
	Int x=quickpow(pt[0],mod-2);
	delete[] pt;
	for(size_t i=0;i<ren;i++)	t[0][i]=x;
	for(size_t i=1;i<b;i++)
	{
		for(size_t j=0;j<ren;j++)
			t[i&1][j]=(t[(i&1)^1][j]*2-f[j]*t[(i&1)&1][j]%mod*t[(i&1)^1][j])%mod;
	}
	delete[] f;
	pt=INTT(t[(b&1)^1],b);
	for(size_t i=0;i<n;i++)
		cout<<pt[i]<<' ';
	delete[] t[0];delete[] t[1];delete[] pt;
	return 0;
}

/*long long a[2000010],b[2000010];

int main()
{
	//freopen("P3803_8.in","r",stdin);
	int n,m;
	cin>>n>>m;
	pre(1<<(btn(n+m+1)));
	for(int i=0;i<=n;++i)
		cin>>a[i];
	for(int i=0;i<=m;++i)
		cin>>b[i];
	long long *t1=NTT(a,n+1,btn(n+m+1)),*t2=NTT(b,m+1,btn(n+m+1));
	int ren=1<<(btn(n+m+1));
	for(int i=0;i<ren;++i)
		t1[i]=t1[i]*t2[i]%mod;
	long long *t=NTT(t1,ren,btn(n+m+1)),dv=quickpow(ren,mod-2);
	delete t1;delete t2;
	for(int i=0;i<ren;++i)
	{
		t[i]=t[i]*dv%mod;
		t[i]=(t[i]+mod)%mod;
	}
	reverse(t+1,t+ren);
	for(int i=0;i<=m+n;i++)
		cout<<t[i]<<' ';
	cout<<endl;
	delete t;
	return 0;
}*/