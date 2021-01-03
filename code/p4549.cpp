#include <stdio.h>

template<typename T>
inline void swap(T &x,T &y)
{
	T z=x;
	x=y;
	y=z;
	return;
}
template <typename T>
inline T abs(T x)
{
	if(x<0)
		return -x;
	return x;
}
template <typename T>
inline T gcd(T x,T y)
{
	x=abs(x),y=abs(y);
	if(x<y)
		swap(x,y);
	if(y==0)
		return x;
	int z=x%y;
	while(z!=0)
	{
		x=y;
		y=z;
		z=x%y;
	}
	return y;
}
int main()
{
	int n,ans=0;
	scanf("%d",&n);
	for(int i=0;i<n;i++)
	{
		static int x;
		scanf("%d",&x);
		ans=gcd(ans,x);
	}
	printf("%d\n",ans);
	return 0;
}
