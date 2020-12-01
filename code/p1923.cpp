#include <stdio.h>
#include <algorithm>

int n,k;
int a[5000010];
int main()
{
	scanf("%d%d",&n,&k);
	for(int i=0;i<n;i++)
		scanf("%d",a+i);
	std::sort(a,a+n);
	printf("%d\n",a[k]);
	return 0;
}
