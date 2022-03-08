#include <iostream>
#include <algorithm>
using namespace std;

typedef long long Int;

const Int mod=20100403;

Int tol(Int x)
{
	Int ans=1;
	for(Int i=2;i<=x;i++)
		ans=ans*i%mod;
	return ans;
}

Int quickpow(Int x,size_t n)
{
	if(n==0)
		return 1;
	Int ans=quickpow(x,n>>1);
	ans=ans*ans%mod;
	if(n&1)
		ans=ans*x%mod;
	return ans;
}

Int cnm(Int n,Int m)
{
	return tol(n)*quickpow(tol(n-m)*tol(m)%mod,mod-2)%mod;
}

int main()
{
	int n,m;
	cin>>n>>m;
	//cout<<cnm(4,2)<<endl;
	cout<<((n-m+1)%mod*quickpow((n+1)%mod,mod-2)%mod*cnm(n+m,m)%mod+mod)%mod<<endl;
	return 0;
}