#include <cstdlib>
#include <iostream>
#include <algorithm>
using namespace std;

long long n,l;
long long *c,*p,*s,*f;

void del()
{
	delete[]c,p,s,f;
}

void init()
{
	cin>>n>>l;
	--l;
	c=new long long[n];
	p=new long long[n];
	s=new long long[n];
	f=new long long[n];
	for(int i=0;i<n;i++)
	{
		cin>>c[i];
		if(i==0)
		{
			p[i]=c[i];
			s[i]=p[i]+i;
		}
		else
		{
			p[i]=p[i-1]+c[i];
			s[i]=p[i]+i;
		}
		f[i]=0x3fffffffffffffffull;
	}
	atexit(del);
	return;
}

int main()
{
	init();
	long long ans=0x7fffffffffffffff;
	for(int i=0;i<n;i++)
	{
		for(int j=0;j<i;j++)
			f[i]=min(f[i],f[j]+s[j]*s[j]-2*s[j]*(s[i]-l));
		if(i>0)
			f[i]+=(s[i]-l)*(s[i]-l);
		else
			f[i]=(s[i]-l-1)*(s[i]-l-1);
		ans=min(ans,f[i]);
	}
	cout<<ans<<endl;
	return 0;
}