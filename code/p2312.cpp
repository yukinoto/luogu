#include <cstdio>
#include <cctype>

long long *a;
int n,m;

long long getn(long long mod=303700003)
{
	char c=getchar();
	long long ans=0;
	bool flag=false;
	while(isspace(c))
		c=getchar();
	if(c=='-')
	{
		flag=true;
		c=getchar();
	}
	while(isdigit(c))
	{
		ans=(ans*10+c-'0');
		if(ans>=mod)
			ans%=mod;
		c=getchar();
	}
	if(flag)
		ans=mod-ans;
	return ans;
}

bool check(long long x,long long mod=303700003)
{
	long long p=1;
	long long ans=0;
	for(int i=0;i<=n;i++)
	{
		ans+=p*a[i];
		p=p*x;
		if(p>=mod)
			p%=mod;
	}
	return ans%mod==0;
}

int main()
{
	//ios::sync_with_stdio(false);
	scanf("%d%d",&n,&m);
	a=new long long[n+1];
	for(int i=0;i<=n;i++)
		a[i]=getn();
	int cnt=0,*as=new int[m];
	for(int i=1;i<=m;i++)
		if(check(i))
			as[cnt++]=i;
	printf("%d\n",cnt);
	for(int i=0;i<cnt;i++)
		printf("%d\n",as[i]);
	delete[] a;
	delete[] as;
	return 0;
}