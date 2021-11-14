#include <iostream>
#include <algorithm>
#include <cmath>
using namespace std;

int main()
{
	int n,m;
	cin>>n;
	long long a[n];
	for(int i=0;i<n;i++)
	{
		cin>>a[i];
	}
	cin>>m;
	for(int i=0;i<m;i++)
	{
		int f,l,r;
		cin>>f>>l>>r;
		if(l>r)
			swap(l,r);
		--l;
		if(f==0)
		{
			for(int i=l;i<r;i++)
				a[i]=sqrt(a[i]);
		}
		if(f==1)
		{
			long long ans=0;
			for(int i=l;i<r;i++)
				ans+=a[i];
			cout<<ans<<endl;
		}
	}
	return 0;
}