#include <iostream>
#include <vector>
using namespace std;

int n;
vector<int>a;
long long ans=0;

int main()
{
	cin>>n;
	a.push_back(0x3fffffff);
	for(int i=1;i<=n;i++)
		a.push_back([](istream& ins){int x;ins>>x;return x;}(cin));
	a.push_back(0x3fffffff);
	for(int i=1;i<n;i++)
	{
		int k=1;
		for(;k<=(n-i+1);k++)
			if(a[k-1]<a[k+1])
				break;
		int j=k-2;
		int s=a[k]+a[k-1];
		for(;j>=0;j--)
			if(a[j]>s)
				break;
		a.erase(a.begin()+k-1,a.begin()+k+1);
		a.insert(a.begin()+j+1,s);
		ans+=s;
	}
	cout<<ans<<endl;
	return 0;
}