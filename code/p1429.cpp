#include <cstdio>

inline long long min(const long long& x,const long long& y)
{
	return x>y?y:x;
}

inline long long abs(const long long& x)
{
	return x>0?x:-x;
}
struct node{
	long long x,y;
};
inline void get(node &x)
{
	scanf("%d%d",&x.x,&x.y);
	return;
}
inline double dis(const node& x,const node& y)
{
	long long a=abs(x.x-y.x),b=abs(x.y-y.y);
	return sqrt(a*a+b*b);
}
node a[200010];
int main()
{
	double ans=2000000000.0;
	int n;
	scanf("%d",&n);
	for(register int i=1;i<=n;i++)
		get(a[i]);
	for(register int i=1;i<=n;i++)
		for(register int j=i+1;j<=n;j++)
			ans=min(ans,dis(a[i],a[j]));
	printf("%.4f\n",ans);
	return 0;
}
