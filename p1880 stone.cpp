//p1880
#include <stdio.h>

#define min(A,B) ((A)<(B)?(A):(B))
#define max(A,B) ((A)>(B)?(A):(B))

int n,a[210],bef[210],f[210][210],ans=0x7fffffff;
int dp(int l,int r)
{
	if(f[l][r]!=0)
		return f[l][r];
	if(r<=l+1)
		return 0;
	int ans=0x7fffffff;
	for(int i=l+1;i<r;i++)
		ans=min(ans,dp(l,i)+dp(i,r));
	return f[l][r]=ans+bef[r]-bef[l];
}
int f2[210][210],ans2;
int dp2(int l,int r)
{
	if(f2[l][r]!=0)
		return f2[l][r];
	if(r<=l+1)
		return 0;
	int ans=0;
	for(int i=l+1;i<r;i++)
		ans=max(ans,dp2(l,i)+dp2(i,r));
	return f2[l][r]=ans+bef[r]-bef[l];
}
int main()
{
	scanf("%d",&n);
	for(int i=0;i<n;i++)
	{
		scanf("%d",a+i);
		a[n+i]=a[i];
	}
	for(int i=0;i<n*2;i++)
		for(int j=i+1;j<=n*2;j++)
			bef[j]+=a[i];
	/*for(int i=0;i<=n*2;i++)
		printf("%d ",bef[i]);*/
	for(int i=0;i<n;i++)
		ans=min(ans,dp(i,i+n));
	printf("%d\n",ans);
	for(int i=0;i<n;i++)
		ans2=max(ans2,dp2(i,i+n));
	printf("%d\n",ans2);
	/*for(int i=0;i<n*2;i++)
	{
		for(int j=0;j<n*2;j++)
			printf("%d ",f[i][j]);
		printf("\n");
	}*/
	return 0;
}
