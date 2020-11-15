#include <stdio.h>

bool ifp[100000010];
void pre(int n)
{
	for(int i=2;i<=n;i++)
		ifp[i]=true;
	for(int i=2;i*i<=n;i++)
		if(ifp[i])
			for(int j=i+1;i*j<=n;j++)
				ifp[i*j]=false;
	return;
}
int main()
{
	int k,cnt1=0,cnt2=0;
	scanf("%d",&k);
	pre(4*k+1);
	for(int i=1;i<=k;i++)
	{
		if(ifp[4*i-1])
			cnt1++;
		if(ifp[4*i+1])
			cnt2++;
	}
	printf("%d %d\n",cnt1,cnt2);
	return 0;
}