#include <cstdio>

float sqrt(float x)
{

    float xhalf = 0.5f*x;
    int i = *(int*)&x; 
    
    if(!x) return 0;
    
    i = 0x5f375a86- (i>>1); // beautiful number
    x = *(float*)&i; 
    x = x*(1.5f-xhalf*x*x); // 牛顿迭代法，提高精度
    x = x*(1.5f-xhalf*x*x); // 牛顿迭代法，提高精度
    x = x*(1.5f-xhalf*x*x); // 牛顿迭代法，提高精度

    return 1/x;
}

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
