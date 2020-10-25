//p1304
#include <stdio.h>
#include <string.h>

bool c[10010];
void mc(int n)
{
	memset(c,true,sizeof(c));
	c[1]=false;
	for(int i=2;i*i<=n;i++)
		if(c[i])
			for(int j=i;i*j<=n;j++)
				c[i*j]=false;
	return;
}
void fc(int x)
{
	for(int i=2;i<=x;i++)
		if(c[i]&&c[x-i])
		{
			printf("%d=%d+%d\n",x,i,x-i);
			return;
		}
}
int main()
{
	int n;
	scanf("%d",&n);
	mc(n);
	freopen("gdbh.out","w",stdout);
	for(int i=2;2*i<=n;i++)
		fc(i*2);
	return 0;
}
