#include <cstdio>

int main()
{
	int n,m;
	long long k;
	scanf("%d%d%lld",&n,&m,&k);
	n%=10,m%=10;
	int a=n,b=m,c=n*m%10;
	if(k<100000)
	{
		for(int i=1;i<k;i++)
			a=b,b=c,c=a*b%10;
		printf("%d\n",a);
	}
	else
	{
		k-=100000;
		for(int i=0;i<100000;i++)
			a=b,b=c,c=a*b%10;
		n=a,m=b;
		int l=0;
		do
		{
			a=b,b=c,c=a*b%10;
			l++;
		}while(a!=n||b!=m);
		k%=l;
		if(k==0)
			k=l;
		for(int i=1;i<k;i++)
			a=b,b=c,c=a*b%10;
		printf("%d\n",a);
	}
	return 0;
}
