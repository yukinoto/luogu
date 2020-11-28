#include <stdio.h>

inline int min(const int &x,const int &y)
{
	return x>y?y:x;
}

int a[40010],sum[40010];
int f[5010][5010];
int dp(int l,int r)
{
	if(f[l][r]!=0)
		return f[l][r];
	if(l>=r)
		return 0x0fffffff;
	if(l==r-1)
		return 0;
	f[l][r]=0x3fffffff;
	//int ans=0x0fffffff;
	for(int k=l+1;k<r;k++)
		f[l][r]=min(dp(l,k)+dp(k,r),f[l][r]);
	return f[l][r]=f[l][r]+sum[r]-sum[l];
}
int main()
{
	int n;
	scanf("%d",&n);
	for(int i=0;i<n;i++)
	{
		scanf("%d",a+i);
		for(int j=i+1;j<=n;j++)
			sum[j]+=a[i];
	}
	printf("%d\n",dp(0,n));
	return 0;
}
