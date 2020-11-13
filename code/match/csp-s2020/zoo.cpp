#include <stdio.h>

unsigned long long contBit(unsigned long long a,unsigned long long b,int k)
{
	unsigned long long ans=0;
	for(int i=0;i<k;i++)
	{
		bool f1=(a&(1ull<<i))==0,f2=(b&(1ull<<i))==0;
		if(!f1||f2)
			ans++;
	}
	return ans;
}
int main()
{
	//freopen("zoo.in","r",stdin);
	//freopen("zoo.out","w",stdout);
	int n,m,k;
	unsigned long long animal=0,cond=0;
	scanf("%d%d%*d%d",&n,&m,&k);
	for(int i=0;i<n;i++)
	{
		 long long unsigned x;
		scanf("%llud",&x);
		animal=x|animal;
	}
	for(int i=0;i<m;i++)
	{
		unsigned long long p,q;
		scanf("%llud%llud",&p,&q);
		cond=cond|(1<<p);
	}
	unsigned long long b=contBit(animal,cond,k);
	printf("%llud\n",(1ull<<b)-n);
	return 0;
}
