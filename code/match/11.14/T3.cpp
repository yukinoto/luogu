#include <iostream>
#include <algorithm>
using namespace std;

int main()
{
	int n,m;
	cin>>n>>m;
	long long a[n];
	for(int i=0;i<n;i++)
		cin>>a[i];
	sort(a,a+n);
	for(int i=0;i<m;i++)
	{
		int k;
		cin>>k;
		if(k==1)
		{
			long long bf=a[n-1],ed=a[n-1];
			long long ans=0;
			for(int i=n-2;i>0;i--)
				if(bf>ed)
				{
					ans+=a[i]*bf;
					bf=a[i];
				}
				else
				{
					ans+=a[i]*ed;
					ed=a[i];
				}
			ans+=a[0]*(bf+ed);
			cout<<ans<<endl;
		}
		if(k==0)
		{
			long long ans=0;
			for(int i=0;i<n;i++)
				ans+=a[i]*a[i];
			cout<<ans<<endl;
		}
	}
}