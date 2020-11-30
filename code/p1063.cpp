#include <stdio.h>

inline int max(const int &x,const int &y)
{
	return x>y?x:y;
}

int a[210];
int f[210][210];
int dp(int l,int r)//[]
{
	if(f[l][r]!=0||l==r-1)
		return f[l][r];
	for(int i=l+1;i<r;i++)
		f[l][r]=max(f[l][r],dp(l,i)+dp(i,r)+a[l]*a[i]*a[r]);
	return f[l][r];
}
int main()
{
	int n;
	scanf("%d",&n);
	for(int i=0;i<n;i++)
		scanf("%d",a+i);
	for(int i=n;i<n*2;i++)
		a[i]=a[i-n];
	int ans=0;
	for(int i=0;i<n;i++)
		ans=max(ans,dp(i,i+n));
	printf("%d\n",ans);
	return 0;
}
