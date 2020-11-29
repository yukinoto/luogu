#include <stdio.h>
#include <queue>
using namespace std;

priority_queue<int,vector<int>,greater<int> > a;
int main()
{
	int n,ans=0;
	scanf("%d",&n);
	for(int i=0;i<n;i++)
	{
		int x;
		scanf("%d",&x);
		a.push(x);
	}
	for(int i=1;i<n;i++)
	{
		int sum=a.top();
		a.pop();
		sum+=a.top();
		a.pop();
		ans+=sum;
		a.push(sum);
	}
	printf("%d\n",ans);
	return 0;
} 
