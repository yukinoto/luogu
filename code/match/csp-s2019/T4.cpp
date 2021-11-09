#include <iostream>
using namespace std;

long long n,m;
long long g[110][110],a[110][2010],s[110],f[110][310];
const long long mod=998244353;

void init()
{
	cin>>n>>m;
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=m;j++)
		{
			cin>>a[i][j];
			s[i]=(s[i]+a[i][j])%mod;
		}
	}
	return;
}

long long dp1()
{
	g[0][0]=1;
	for(int i=1;i<=n;i++)
	{
		for(int j=0;j<=n;j++)
		{
			g[i][j]=(g[i-1][j]+(j==0?0:g[i-1][j-1]*s[i]))%mod;
			//cout<<i<<' '<<j<<' '<<g[i][j]<<endl;
		}
	}
	long long ans=0;
	for(int j=1;j<=n;j++)
		ans=(ans+g[n][j])%mod;
	return ans;
}

long long dp2(int rol)
{
	f[0][0]=1;
	long long ans=0;
	for(int i=1;i<=n;i++)
	{
		for(int j=0;j<=n*3;j++)
		{
			f[i][j]=(f[i-1][j]*(s[i]-a[i][rol])+
				(j==0?0:f[i-1][j-1])+
				(j<=1?0:f[i-1][j-2]*a[i][rol]))%mod;
		}
	}
	for(int i=n+1;i<=n*3;i++)
		ans=(ans+f[n][i])%mod;
	return ans;
}

void work()
{
	long long jt=0;
	for(int i=1;i<=m;i++)
		jt=(jt+dp2(i))%mod;
	cout<<(dp1()+mod-jt)%mod<<endl;
	return;
}

int main()
{
	init();
	work();
	return 0;
}