#include <stdio.h>

#define NULL 0x7fffffff

struct node{
	int a,bef,nxt;
};
node a[40010];
int head,ans=0;
int main()
{
	//freopen("p5569.in","r",stdin);
	//freopen("p5569.out","w",stdout);
	int n;
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
	{
		scanf("%d",&a[i].a);
		a[i].bef=i-1,a[i].nxt=i+1;
	}
	a[0].bef=a[n+1].nxt=NULL;
	a[0].nxt=1,a[n+1].bef=n;
	a[0].a=a[n+1].a=NULL;
	head=0;
	for(int i=1;i<n;i++)
	{
		int p=a[head].nxt;
		while(a[a[p].bef].a>=a[a[p].nxt].a)
			p=a[p].nxt;
		a[p].a=a[a[p].bef].a+a[p].a;
		a[a[a[p].bef].bef].nxt=a[p].nxt;
		a[a[p].nxt].bef=a[a[p].bef].bef;
		int k=a[a[p].bef].bef;
		while(a[k].a<=a[p].a)
			k=a[k].bef;
		a[p].bef=k,a[p].nxt=a[k].nxt;
		a[a[k].nxt].bef=p;
		a[k].nxt=p;
		ans+=a[p].a;
	}
	printf("%d\n",ans);
	return 0;
}
