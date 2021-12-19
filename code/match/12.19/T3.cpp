#include <iostream>
#include <algorithm>
using namespace std;

int a[1010];

int main()
{
	int n;
	cin>>n;
	int ma=0,mi=0x7fffffff;
	for(int i=0;i<n;i++)
	{
		cin>>a[i];
		ma=max(ma,a[i]);
		mi=min(mi,a[i]);
	}
	for(int i=0;i<n;i++)
	{
		cout<<int(100*(double)(a[i]-mi)/(ma-mi)+0.001)<<' ';
	}
	cout<<endl;
	return 0;
}