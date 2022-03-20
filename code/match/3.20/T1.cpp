#include <iostream>
using namespace std;

const long long maxn=1000000000000000002ll;

long long p9[30];

void pre()
{
	p9[1]=9;
	for(int i=2;p9[i-1]*9<=maxn;i++)
		p9[i]=p9[i-1]*10+9;
	return;
}

void work()
{
	int k;long long n;
	cin>>k>>n;
	for(int i=18;i>0;i--)
	{
		if(i%k==0)
			n%=p9[i];
	}
	if(n==0)
		cout<<"aya\n";
	else
		cout<<"baka\n";
	return;
}

int main()
{
	pre();
	int t;
	cin>>t;
	for(int i=0;i<t;i++)
		work();
	return 0;
}