#include <stdio.h>

int ___[2000010],p[2000010];
int top,front;
int main()
{
	int n,m;
	scanf("%d%d",&n,&m);
	for(register int i=1;i<=n;i++)
	{
		int x;
		scanf("%d",&x);
		while(p[front]<i-m)
			++front;
		printf("%d\n",___[front]);
		while(top>front&&___[top-1]>=x)
			--top;
		___[top]=x;
		p[top++]=i;
	}
	return 0;
}
