#include <iostream>
#include <complex>
#include <cmath>
using namespace std;

const long long p=998244353;
template<typename T>
T quickpow(T x,long long n)
{
	long long a=0;
	long long cnt=0;
	while(n!=0)
	{
		a<<=1;
		a|=(n&1);
		n>>=1;
		++cnt;
	}
	T ans=1;
	for(;cnt>0;--cnt)
	{
		ans=ans*ans%p;
		if(a&1)
		{
			ans=ans*x%p;
		}
        a>>=1;
	}
	return ans;
}
long long mw[998244352/17/7];
long long w(int k,int n)
{
	if(mw[(p-1)/(17*7)/n*k]!=0)
		return mw[(p-1)/(17*7)/n*k];
	return mw[(p-1)/(17*7)/n*k]=quickpow(3ll,k*(p-1)/n);
}

template<typename comp,comp(*w)(int,int)>
void _fft(comp *f,int n)
{
	if(n==1)
	{
		f[0]=w(0,n)*f[0]%p;
		return;
	}
	_fft<comp,w>(f,n>>1),_fft<comp,w>(f+(n>>1),n>>1);
	comp *tmp1=new comp[n>>1],*tmp2=new comp[n>>1];
	for(int i=0;i<(n>>1);i++)
		tmp1[i]=f[i];
	for(int i=0;i<(n>>1);i++)
		tmp2[i]=f[i+(n>>1)];
	for(int i=0;i<(n>>1);i++)
	{
		f[i]=(tmp1[i]+tmp2[i]*w(i,n))%p;
		f[i+(n>>1)]=(tmp1[i]-tmp2[i]*w(i,n))%p;
	}
	delete[] tmp1;
	delete[] tmp2;
	return;
}

template<typename comp,comp(*w)(int,int)>
void _ifft(comp *f,int n)
{
	if(n==1)
	{
		f[0]=w(n-0,n)*f[0]%p;
		return;
	}
	_ifft<comp,w>(f,n>>1),_ifft<comp,w>(f+(n>>1),n>>1);
	comp *tmp1=new comp[n>>1],*tmp2=new comp[n>>1];
	for(int i=0;i<(n>>1);i++)
		tmp1[i]=f[i];
	for(int i=0;i<(n>>1);i++)
		tmp2[i]=f[i+(n>>1)];
	for(int i=0;i<(n>>1);i++)
	{
		f[i]=(tmp1[i]+tmp2[i]*w(n-i,n))%p;
		f[i+(n>>1)]=(tmp1[i]-tmp2[i]*w(n-i,n))%p;
	}
	delete[] tmp1;
	delete[] tmp2;
	return;
}

template<typename comp,comp(*w)(int,int)>
comp* fft(comp*f,int n)
{
	int t=0;
	while((1<<t)<n) ++t;
	comp *tmp=new comp[(1<<t)];
	for(int i=0;i<(1<<t);i++)
	{
		int p=0,x=i;
		for(int j=0;j<t;j++)
		{
			p<<=1;
			p|=x&1;
			x>>=1;
		}
		if(i<n)
			tmp[p]=f[i];
		else
			tmp[p]=comp(0);
	}
	_fft<comp,w>(tmp,1<<t);
	return tmp;
}

template<typename comp,comp(*w)(int,int)>
comp* ifft(comp*f,int n)
{
	int t=0;
	while((1<<t)<n) ++t;
	comp *tmp=new comp[1<<t];
	for(int i=0;i<(1<<t);i++)
	{
		int p=0,x=i;
		for(int j=0;j<t;j++)
		{
			p<<=1;
			p|=x&1;
			x>>=1;
		}
		if(i<n)
			tmp[p]=f[i];
		else
			tmp[p]=comp(0);
	}
	_ifft<comp,w>(tmp,1<<t);
	for(int i=0;i<(1<<t);i++)
	{
		tmp[i]=quickpow(1ll<<t,p-2)*tmp[i]%p;
	}
	return tmp;
}

int main()
{
	//freopen("p3803.in","r",stdin);
	int n,m;
	cin>>n>>m;
	long long*a=new long long[n+m+1],*b=new long long[n+m+1];
	for(int i=0;i<=n;i++)
	{
		int x;
		cin>>x;
		a[i]=x;
	}
	for(int i=0;i<=m;i++)
	{
		int x;
		cin>>x;
		b[i]=x;
	}
	for(int i=n+1;i<=n+m;i++)
		a[i]=0;
	for(int i=m+1;i<=n+m;i++)
		b[i]=0;
	long long*a1=fft<long long,w>(a,n+m+1),*a2=fft<long long,w>(b,n+m+1);
	int t=0;
	while((1<<t)<m+n+1) ++t;
	for(int i=0;i<(1<<t);i++)
	{
		a1[i]=a1[i]*a2[i]%p;
	}
	delete a2;
	long long*ans=ifft<long long,w>(a1,(1<<t));
	for(int i=0;i<n+m+1;i++)
	{
		cout<<(ans[i]+p)%p<<' ';
	}
	//cout<<endl<<w(1,4)*w(3,4)%p<<endl;
	delete[] a1;
	delete[] ans;
	delete[] a;
	delete[] b;
	return 0;
}