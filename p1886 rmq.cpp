//p1886
#include <stdio.h>

int n,k;
int p1[1000100],w1[1000100],f1,l1=-1,p2[1000100],w2[1000100],f2,l2=-1;
int ans[1000100];
int main()
{
	scanf("%d%d",&n,&k);
	for(int i=0;i<k;i++)
	{
		int x;
		scanf("%d",&x);
		while(f1<=l1&&x>=w1[l1])
			--l1;
		while(f2<=l2&&x<=w2[l2])
			--l2;
		w1[++l1]=x;
		p1[l1]=i;
		w2[++l2]=x;
		p2[l2]=i;
	}
	printf("%d ",w2[f2]);
	ans[k-1]=w1[f1];
	for(int i=k;i<n;i++)
	{
		if(i-k>=p1[f1])
			++f1;
		if(i-k>=p2[f2])
			++f2;
		int x;
		scanf("%d",&x);
		while(f1<=l1&&x>=w1[l1])
			--l1;
		while(f2<=l2&&x<=w2[l2])
			--l2;
		w1[++l1]=x;
		p1[l1]=i;
		w2[++l2]=x;
		p2[l2]=i;
		printf("%d ",w2[f2]);
		//printf("%d ",w1[f1]);
		ans[i]=w1[f1];
	}
	printf("\n");
	for(int i=k-1;i<n;i++)
		printf("%d ",ans[i]);
	printf("\n");
	return 0;
}
