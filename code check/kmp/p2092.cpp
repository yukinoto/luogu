//p2092
#include <stdio.h>

int main()
{
	long long n;
	int ans=1,cnt=0;
	scanf("%lld",&n);
	if(n<=1)
	{
		printf("1\n0\n");
		return 0;
	}
	for(int i=2;(long long)i*i<=n; i++)
	{
		while(n%i==0)
		{
			//printf("%d\n",i);
			n/=i;
			ans*=i;
			cnt++;
			if(cnt==2)
			{
				if(n==1)
				{
					printf("2\n");
					return 0;
				}
				printf("1\n%d\n",ans);
				return 0;
			}
		}
	}
	printf("2\n");
	return 0;
}
