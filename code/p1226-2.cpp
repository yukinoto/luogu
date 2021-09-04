#include <cstdio>

template<typename T,typename opt>
T quickpow(T x,long long n,opt mod)
{
	if(n==1)
		return x;
	T x2=mod(quickpow(x,n>>1,mod));
    x2=mod(x2*x2);
	if(n&1==1)
		return mod(x2*x);
	return x2;
}

int main()
{
    long long a,b,p;
    scanf("%lld%lld%lld",&a,&b,&p);
    printf("%lld^%lld mod %lld=%lld\n",a,b,p,
	quickpow(a,b,[p](long long x){return x%p;}));
}