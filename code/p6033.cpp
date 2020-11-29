#include <stdio.h>
#include <queue>
using namespace std;

priority_queue<long long,vector<long long>,greater<long long> > a;
int main()
{
	int n;
	long long ans=0ll;
	scanf("%d",&n);
	for(int i=0;i<n;i++)
	{
		long long x;
		scanf("%lld",&x);
		a.push(x);
	}
	for(int i=1;i<n;i++)
	{
		long long sum=a.top();
		a.pop();
		sum+=a.top();
		a.pop();
		ans+=sum;
		a.push(sum);
	}
	printf("%lld\n",ans);
	return 0;
} 
