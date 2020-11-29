#include <stdio.h>
#include <string.h>
#include <algorithm>

int n,a[110],max;
bool f[25010];
void init()
{
	scanf("%d",&n);
	for(int i=0;i<n;i++)
		scanf("%d",a+i);
	memset(f,false,sizeof(f));
	std::sort(a,a+n);
	max=a[n-1];
	f[0]=true;
	return;
}
void work()
{
	init();
	int cnt=0;
	for(int i=0;i<n;i++)
		if(!f[a[i]])
		{
			cnt++;
			for(int j=0;a[i]+j<=max;j++)
				if(f[j])
					f[a[i]+j]=true;
		}
	printf("%d\n",cnt);
	return;
}
int main()
{
	int t;
	scanf("%d",&t);
	for(int i=0;i<t;i++)
		work();
	return 0;
}
