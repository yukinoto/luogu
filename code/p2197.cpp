#include <iostream>
using namespace std;

void work()
{
	int n;
	cin>>n;
	int ans=0;
	for(int i=0;i<n;i++)
	{
		int x;
		cin>>x;
		ans^=x;
	}
	if(ans==0)
		cout<<"No\n";
	else
		cout<<"Yes\n";
	return;
}

int main()
{
	int t;
	cin>>t;
	for(int i=0;i<t;i++)
		work();
	fflush(stdout);
}