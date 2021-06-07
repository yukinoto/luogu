#include <cstdio>

int main()
{
	long long a=0,b=1,c=1;
	int n;
	scanf("%d",&n);
	if(n==0)
		printf("%.2f",0.0);
	else
	{
		for(int i=1;i<n;i++)
		{
			a=b,b=c,c=a+b;
		}
		printf("%lld.00\n",b);
	}
	return 0;
}
