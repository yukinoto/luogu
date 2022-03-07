#include <iostream>
#include <algorithm>
using namespace std;

typedef long long Int;

const Int mod=20100403;
Int a[2001];

int main()
{
	int n,m;
	cin>>m>>n;
	n+=m;
	a[1]=1;
	for(int i=2;i<=n;i++)
	{
		for(int j=min(m,i-1);j>=(i-2)/2+1;j--)
		{
			a[j+1]=(a[j+1]+a[j])%mod;
		}
	}
	cout<<a[m]<<endl;
	return 0;
}