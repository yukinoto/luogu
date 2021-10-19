#include <iostream>
using namespace std;

int main()
{
	int n,m;
	cin>>n>>m;
	long long *a=new long long[n];
	for(int i=0;i<n;i++)
		cin>>a[i];
	for(int i=0;i<m;i++)
	{
		int f,l,r;
		cin>>f>>l>>r;
		if(f==1)
		{
			long long sum=0;
			for(int j=l;j<r;j++)
				sum+=a[j];
			cout<<sum<<endl;
		}
		if(f==2)
		{
			long long x;
			cin>>x;
			for(int j=l;j<r;j++)
				a[j]+=x;
		}
		if(f==3)
		{
			long long x;
			cin>>x;
			for(int j=l;j<r;j++)
				a[j]=x;
		}
	}
	delete[]a;
	return 0;
}
