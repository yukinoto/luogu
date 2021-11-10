#include <iostream>
using namespace std;

const long long mod=1000000007;
long long peng[300010],atpeng[300010];

long long quickpow(long long x,int n)
{
	if(n==1)
		return x;
	long long ans=quickpow(x,n>>1);
	ans=ans*ans%mod;
	if(n&1)
		ans=ans*x%mod;
	return ans;
}

void ppeng(int n)
{
	peng[0]=1;
	for(int i=1;i<=n;i++)
		peng[i]=(peng[i-1]*i)%mod;
	return;
}

void patpeng(int n)
{
	long long *pret=new long long[n+1];
	long long *pretat=new long long[n+1];
	pret[0]=peng[0];
	for(int i=1;i<=n;i++)
	{
		pret[i]=pret[i-1]*peng[i]%mod;
	}
	pretat[n]=quickpow(pret[n],mod-2);
	
}