#include <iostream>
#include <algorithm>
using namespace std;

int top=0;
int ans[100000],a[1001];

int main()
{
	int n;
	cin>>n;
	for(int i=1;i<=n;i++)
		cin>>a[i];
	for(int i=1;i<n;i++)
		for(int j=1;j<n;j++)
		{
			if(a[j]>a[j+1])
			{
				swap(a[j],a[j+1]);
				ans[top++]=j;
			}
		}
	cout<<2<<endl<<top<<endl;
	for(int i=0;i<top;i++)
		cout<<ans[i]<<' '<<"0\n";
	return 0;
}