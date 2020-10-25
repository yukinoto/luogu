#include <stdio.h>
#include <algorithm>
using namespace std;

int a[2000010],top;
int main()
{
	freopen("4.in","r",stdin);
	freopen("4-b.out","w",stdout);
	int n;
	scanf("%d",&n);
	for(int i=0;i<n;i++)
	{
		int f;
		scanf("%d",&f);
		if(f==1)
		{
			int x;
			scanf("%d",&x);
			a[top++]=x;
			sort(a,a+top);
		}
		if(f==2)
		{
			int x;
			scanf("%d",&x);
			int* p=lower_bound(a,a+top,x);
			for(int* i=p;i<a+top;i++)
				*(i+1)=*i;
			top--;
		}
		if(f==3)
		{
			int k;
			scanf("%d",&k);
			printf("%d\n",a[top-k]);
		}
		if(f==4)
		{
			int k;
			scanf("%d",&k);
			printf("%d\n",a[k-1]);
		}
		if(f==5)
			printf("%d\n",top);
	}
	for(int i=0;i<top-1;i++)
		printf("%d ",a[i]);
	printf("%d\n",a[top-1]);
	return 0;
}
