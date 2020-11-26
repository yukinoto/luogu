#include <stdio.h>

int ___[2000010],p[2000010];
int top,front;
inline int read()
{
	int x=0;
	char c=getchar();
	while(c<'0'||c>'9')
		c=getchar();
	while(c>='0'&&c<='9')
	{
		x=x*10+c-'0';
		c=getchar();
	}
	return x;
}
int main()
{
	int n=read(),m=read();
	for(register int i=1;i<=n;i++)
	{
		int x=read();
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
