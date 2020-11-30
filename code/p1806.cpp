#include<stdio.h>

int n;
long long ans=0;
long long f[510][510];
int main()
{
	scanf("%d",&n);
	f[0][0]=1;
	for(int i=0;i<=n;i++)
		for(int j=0;j<=i;j++)
			if(f[i][j]!=0)
				for(int k=j+1;i+k<=n;k++)
					f[i+k][k]+=f[i][j];
	for(int i=0;i<n;i++)
		ans+=f[n][i];
	printf("%lld\n",ans);
	return 0;
}
