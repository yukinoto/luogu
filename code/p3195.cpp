#include <cstdlib>
#include <iostream>
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
		f[i]=0x0;
	}
	atexit(del);
	return;
}

int main()
{
	init();
	
}