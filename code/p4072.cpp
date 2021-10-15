#include <iostream>
#include <algorithm>
#include <cstdlib>
using namespace std;

typedef int Int;

Int n,m;
Int *p,*f;
const Int inf=0x7fffffff;

void del()
{
	delete[]p,f;
	return;
}

void init()
{
	cin>>n>>m;
	p=new Int[n];
	f=new Int[n];
	cin>>p[0];
	for(int i=1;i<n;i++)
	{
		Int x;
		cin>>x;
		p[i]=p[i-1]+x;
		f[i]=inf;
	}
	f[0]=inf;
	atexit(del);
	return;
}

void work()
{
	for(int i=0;i<n;i++)
	{
		for(int j=0;j<i;j++)
			f[i]=min(f[i],f[j]+p[j]*p[j]-2*p[i]*p[j]);
		f[i]=min(f[i],p[i]*p[i]);
	}
}

int main()
{
	init();
	work();
	return 0;
}