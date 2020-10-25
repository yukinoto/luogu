//p1579
#include <stdio.h>
#include <string.h>

bool prim[20010];
void mp(int n)
{
	memset(prim,true,sizeof(prim));
	prim[0]=prim[1]=false;
	for(int i=2;i*i<=n;i++)
		if(prim[i])
			for(int j=i;i*j<=n;j++)
				prim[i*j]=false;
	return;
}
int main()
{
	int n;
	scanf("%d",&n);
	mp(n);
	for(int i=2;i<=n/3;i++)
		if(prim[i])
			for(int j=i;j<=(n-i)/2;j++)
				if(prim[j]&&prim[n-i-j])
				{
					printf("%d %d %d",i,j,n-i-j);
					return 0;
				}
	return -1;
}
