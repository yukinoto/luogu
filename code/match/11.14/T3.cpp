#include <iostream>
#include <algorithm>
using namespace std;

int gcd(int a,int b)
{
	if(b==0)
		return a;
	return gcd(b,a%b);
}

long long a[200000];
long long rem[200001];
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
		int r=gcd(n,k),c=n/r;
		if(rem[r]!=0)
			cout<<rem[r]<<'\n';
		else
		{
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
				cout<<(rem[r]=ans/2)<<'\n';
			else
				cout<<(rem[r]=ans)<<'\n';
		}
	}
	cout.flush();
	return 0;
}