#include <iostream>
#include <algorithm>
using namespace std;

int main()
{
	int n,m;
	cin>>n>>m;
	int a[n+1];
	for(int i=1;i<=n;i++)
		cin>>a[i];
	for(int i=0;i<m;i++)
	{
		int f;
		cin>>f;
		if(f==1)
		{
			int l,r,c;
			cin>>l>>r>>c;
			int cnt=0;
			for(int j=l;j<=r;j++)
				if(a[j]==c)
					cnt++;
			cout<<cnt<<endl;
		}
		else
		{
			int x;
			cin>>x;
			swap(a[x],a[x+1]);
		}
	}
	return 0;
}