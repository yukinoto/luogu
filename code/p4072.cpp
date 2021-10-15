#include <iostream>
#include <algorithm>
#include <cstdlib>
using namespace std;

typedef int Int;

Int n,m;
Int *p,**f;
const Int inf=0x3fffffff;

void del()
{
	delete[]p;
	delete[]f[0],f[1];
	delete[]f;
	return;
}

void init()
{
	cin>>n>>m;
	p=new Int[n];
	f=new Int*[2];
	f[0]=new Int[n],f[1]=new Int[n];
	cin>>p[0];
	for(int i=1;i<n;i++)
	{
		Int x;
		cin>>x;
		p[i]=p[i-1]+x;
		f[1][i]=inf;
	}
	f[1][0]=inf;
	atexit(del);
	return;
}

void work()
{
	for(int i=0;i<m;i++)
	{
		for(int j=0;j<n;j++)
		{
			f[i&1][j]=f[(i&1)^1][j];
			for(int k=0;k<j;k++)
			{
				f[i&1][j]=min(f[i&1][j],f[(i&1)^1][k]+p[j]*p[j]-2*p[i]*p[j]);
			}
			f[i&1][j]=min(f[i&1][j],p[j]*p[j]);
		}
	}
	cout<<f[(m-1)&1][n-1]<<endl;
	return;
}

int main()
{
	init();
	work();
	return 0;
}