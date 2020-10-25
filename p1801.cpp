#include <cstdio>
#include <queue>
using namespace std;

int n,m;
int a[200010];
priority_queue <int> down;
priority_queue <int,vector<int>,greater<int> > up;
void swap()
{
	int x=down.top(),y=up.top();
	down.pop();up.pop();
	up.push(x);down.push(y);
	return; 
}
void add(int x)
{
	up.push(x);
	while(!down.empty()&&!up.empty()&&down.top()>up.top())
		swap();
	return; 
}
void get()
{
	printf("%d\n",up.top());
	down.push(up.top());
	up.pop();
	return; 
}
int main()
{
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;++i)
		scanf("%d",a+i);
	int j=1;
	for(int i=0;i<m;++i)
	{
		int c;
		scanf("%d",&c);
		for(;j<=c;++j)
			add(a[j]);
		get();
	}
	return 0;  
}
