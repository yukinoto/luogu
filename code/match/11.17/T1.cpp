#include <iostream>
using namespace std;

long long pef(int n)
{
	long long ans=0;
	for(int i=1;i<=n;i=n/(n/i)+1)
	{
		long long ed=n/(n/i);
		ans+=(ed+i)*(ed-i+1)/2*(n/i);
	}
	return ans;
}

int main()
{
	int x,y;
	cin>>x>>y;
	cout<<pef(y)-pef(x-1)<<endl;
	return 0;
}