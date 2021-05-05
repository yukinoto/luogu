#include <iostream>
using namespace std;

typedef long long Int;

const Int mod=998244353;
Int n,k;
Int x[2010],y[2010];

long long ExE(long long a,long long b,long long &x,long long &y)
{
	if(b==0)
	{
		x=1,y=0;
		return a;
	}
	long long as=ExE(b,a%b,y,x);
	y-=a/b*x;
	return as;
}

int main()
{
	cin>>n>>k;
	for(int i=0;i<n;i++)
		cin>>x[i]>>y[i];
	Int ans=0;
	for(int i=0;i<n;i++)
	{
		Int up=y[i],dw=1;
		for(int j=0;j<n;j++)
			if(i!=j)
			{
				up=up*(k-x[j])%mod;
				dw=dw*(x[i]-x[j])%mod;
			}
		if(up%dw==0)
			ans+=(up/dw%mod+mod)%mod;
		else
		{
			Int at,d;ExE(dw,mod,at,d);
			at=(at%mod+mod)%mod;
			ans+=up*at%mod;
			ans%=mod;
		}
	}
	cout<<ans<<endl;
	return 0;
}
