#include <iostream>
using namespace std;

int main()
{
	int n,m;
	cin>>n>>m;
	int *a=new int[n];
	for(int i=0;i<n;i++)
		cin>>a[i];
	int l=0,r=0,sum=0,ans=0,al=0,ar=0;
	while(r<=n)
	{
		sum+=a[r++];
		while(sum>m)
			sum-=a[l++];
		if(sum>ans)
		{
			ans=sum,al=l,ar=r;
		}
	}
	cout<<al+1<<" "<<ar<<" "<<ans<<endl;
	return 0;
}
