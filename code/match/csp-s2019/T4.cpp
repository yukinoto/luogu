#include <iostream>
using namespace std;

long long n,m;
long long g[110][110],a[110][2010],s[110],f[110][110][110];
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
	f[0][0][0]=1;
	long long ans=0;
	for(int i=1;i<=n;i++)
	{
		for(int j=0;j<=n;j++)
		{
			for(int k=0;k<=n;k++)
			{
				f[i][j][k]=(f[i-1][j][k]+(j==0?0:(f[i-1][j-1][k]*(s[i]-a[i][rol])))+(j==0||k==0?0:(f[i-1][j-1][k-1]*a[i][rol])))%mod;
			}
		}
	}
	for(int j=1;j<=n;j++)
		for(int k=j/2+1;k<=j;k++)
			ans=(ans+f[n][j][k])%mod;
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