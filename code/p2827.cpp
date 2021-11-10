#include <iostream>
#include <queue>
using namespace std;

int main()
{
	int n,m;
	int q,t;long long u,v;
	cin>>n>>m>>q>>u>>v>>t;
	priority_queue<long long> len;
	for(int i=0;i<n;i++)
	{
		long long a;
		cin>>a;
		len.push(a);
	}
	for(int i=1;i<=m;i++)
	{
		long long x=len.top();len.pop();
		x+=q*(i-1);
		len.push(x*u/v-q*i),len.push(x-x*u/v-q*i);
		if(i%t==0)
			cout<<x<<' ';
	}
	cout<<endl;
	for(int i=1;!len.empty();i++)
	{
		if(i%t==0)
			cout<<len.top()+q*m<<' ';
		len.pop();
	}
	cout<<endl;
	return 0;
}