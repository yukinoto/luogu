#include <iostream>
#include <algorithm>
using namespace std;

int rol(int n,int p)
{
	bool tb[n];
	int cnt=0;
	for(int i=0;!tb[i];i=(i+p)%n)
	{
		tb[i]=true;
		++cnt;
	}
	return n/cnt;
}

long long a[200000];
int main()
{
	ios::sync_with_stdio(false);
	int n,m;
	cin>>n>>m;
	for(int i=0;i<n;i++)
		cin>>a[i];
	sort(a,a+n);
	for(int i=0;i<m;i++)
	{
		int k;
		long long ans=0;
		cin>>k;
		int r=rol(n,k),c=n/r;
		for(int j=0;j<r;j++)
		{
			long long bf=a[n-1-c*j],ed=a[n-1-c*j];
			for(int l=n-2-c*j;l>n-c*(j+1);l--)
			{
				if(bf>ed)
				{
					ans+=bf*a[l];
					bf=a[l];
				}
				else
				{
					ans+=ed*a[l];
					ed=a[l];
				}
			}
			ans+=(bf+ed)*a[n-c*(j+1)];
		}
		if(k==0)
			cout<<ans/2<<endl;
		else
			cout<<ans<<endl;
	}
	return 0;
}