#include <iostream>
#include <utility>
using namespace std;

int main()
{
	int n,m;
	cin>>n>>m;
	pair<int,int> a[n];
	for(int i=0;i<n;i++)
		cin>>a[i].first>>a[i].second;
	char f[m];
	int p[m],q[m];
	for(int i=m-1;i>=0;--i)
	{
		cin>>f[i];
		if(f[i]=='m')
			cin>>p[i]>>q[i];
	}
	for(int i=0;i<m;i++)
	{
		if(f[i]=='m')
		{
			for(int j=0;j<n;j++)
			{
				a[j].first+=p[i],a[j].second+=q[i];
			}
		}
		if(f[i]=='x')
		{
			for(int j=0;j<n;j++)
				a[j].first=-a[j].first;
		}
		if(f[i]=='y')
		{
			for(int j=0;j<n;j++)
				a[j].second=-a[j].second;
		}
	}
	for(int i=0;i<n;i++)
		cout<<a[i].first<<' '<<a[i].second<<endl;
	return 0;
}