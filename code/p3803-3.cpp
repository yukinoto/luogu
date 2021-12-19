#include <iostream>
#include <complex>
#include <cmath>
using namespace std;

const double pi=acos(-1);

complex<double> w(int k,int n){return complex<double>(cos(2*pi*k/n),sin(2*pi*k/n));}

complex<double> p[1048576];

template<typename comp,comp(*w)(int,int)>
void _fft(comp *f,int n)
{
	if(n==1)
	{
		f[0]=w(0,n)*f[0];
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
		f[i]=tmp1[i]+tmp2[i]*w(i,n);
		f[i+(n>>1)]=tmp1[i]-tmp2[i]*w(i,n);
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
		f[0]=w(n-0,n)*f[0];
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
		f[i]=tmp1[i]+tmp2[i]*w(n-i,n);
		f[i+(n>>1)]=tmp1[i]-tmp2[i]*w(n-i,n);
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
		tmp[i]/=(1<<t);
	}
	return tmp;
}

int main()
{
	//freopen("p3803.in","r",stdin);
	int n,m;
	cin>>n>>m;
	complex<double>*a=new complex<double>[n+m+1],*b=new complex<double>[n+m+1];
	for(int i=0;i<=n;i++)
	{
		int x;
		cin>>x;
		a[i]=complex<double>(x,0);
	}
	for(int i=0;i<=m;i++)
	{
		int x;
		cin>>x;
		b[i]=complex<double>(x,0);
	}
	for(int i=n+1;i<=n+m;i++)
		a[i]=0;
	for(int i=m+1;i<=n+m;i++)
		b[i]=0;
	complex<double>*a1=fft<complex<double>,w>(a,n+m+1),*a2=fft<complex<double>,w>(b,n+m+1);
	int t=0;
	while((1<<t)<m+n+1) ++t;
	for(int i=0;i<(1<<t);i++)
	{
		a1[i]*=a2[i];
	}
	delete a2;
	complex<double>*ans=ifft<complex<double>,w>(a1,(1<<t));
	for(int i=0;i<n+m+1;i++)
	{
		cout<<int(abs(ans[i])+0.5)<<' ';
	}
	delete[] a1;
	delete[] ans;
	delete[] a;
	delete[] b;
	return 0;
}