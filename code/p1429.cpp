#include <cstdio>
#include <cmath>
#include <algorithm>
using namespace std;

struct node{
	int x,y;
};
inline void get(node &x)
{
	scanf("%d%d",&x.x,&x.y);
	return;
}
double dis(node x,node y)
{
	int a=abs(x.x-y.x),b=abs(x.y-y.y);
	return sqrt(a*a+b*b);
}
node a[200010];
int main()
{
	double ans=2000000000.0;
	int n;
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
		get(a[i]);
	for(int i=1;i<=n;i++)
		for(int j=i+1;j<=n;j++)
			ans=min(ans,dis(a[i],a[j]));
	printf("%.4f\n",ans);
	return 0;
}
