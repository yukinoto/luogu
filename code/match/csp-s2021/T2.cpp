#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

const long long mod=1000000007;

long long n,k;
long long f[510][510],g[510][510];
//long long ans[510];
string x;

/*template<typename T>
T quickpow(T x,long long n)
{
	long long a=0;
	long long cnt=0;
	while(n!=0)
	{
		a<<=1;
		a|=(n&1);
		n>>=1;
		++cnt;
	}
	T ans=1;
	for(;cnt>0;--cnt)
	{
		ans=ans*ans%mod;
		if(a&1)
		{
			ans=ans*x%mod;
		}
        a>>=1;
	}
	return ans;
}

template<typename T>
T anti(T x)
{
	return quickpow(x,mod-2);
}*/

int main()
{
	cin>>n>>k>>x;
	//k--;
	for(int i=0;i<n;i++)
	{
		if(x[i]=='('||x[i]=='?')
			for(int j=i+1;j<=min(n-1,i+k+1);j++)
			{
				if(x[j]==')'||x[j]=='?')
					f[i][j]=1;
				if(x[j]==')'||x[j]=='(')
					break;
			}
	}
	for(int l=3;l<n;l++)
	{
		for(int i=0;i+l<n;i++)
			if((x[i]=='('||x[i]=='?')&&(x[i+l]=='?'||x[i+l]==')'))
			{
				//case 1:ASB+AB
				/*for(int j=i+1;j<=i+l-2;j++)
				{
					//if(x[j+1]=='?'||x[j+1]=='*')
					//{
					for(int r=j+1;r<=min<long long>(i+l-1,j+k+1);r++)
					{
						g[i][i+l]=(g[i][i+l]+(f[i][j]+g[i][j])*f[r][i+l])%mod;
						if(x[r]=='('||x[r]==')')
							break;
					}
					//}
				}*/
				//case 1:ASB+AB
				int r=i+1;
				long long sm;
				for(int j=i+1;j<=i+l-2;j++)
				{
					if(j==r)
					{
						sm=0;
						for(r=j+1;;r++)
						{
							sm=(sm+f[r][i+l])%mod;
							if(x[r]=='('||x[r]==')'||r==min<long long>(i+l-1,j+k+1))
								break;
						}
					}
					else
					{
						sm-=f[j][i+l];
						if(x[r]=='*'||x[r]=='?')
						{
							r++;
							sm+=f[r][i+l];
						}
						sm=(sm%mod+mod)%mod;
					}
					g[i][i+l]=(g[i][i+l]+(f[i][j]+g[i][j])*sm)%mod;
				}
				//case 2:(SA)
				if(x[i+1]=='*'||x[i+1]=='?')
					for(int j=i+2;j<=min<long long>(i+l-2,i+k+1);j++)
					{
						f[i][i+l]=(f[i][i+l]+f[j][i+l-1]+g[j][i+l-1])%mod;
						if(x[j]=='('||x[j]==')')
							break;
					}
				//case 3:(AS)
				if(x[i+l-1]=='*'||x[i+l-1]=='?')
					for(int j=i+l-2;j>=max<long long>(i+2,i+l-k-1);j--)
					{
						f[i][i+l]=(f[i][i+l]+f[i+1][j]+g[i+1][j])%mod;
						if(x[j]=='('||x[j]==')')
							break;
					}
				//case 4:(A)
				f[i][i+l]=(f[i][i+l]+f[i+1][i+l-1]+g[i+1][i+l-1])%mod;
				//case 5:AB
				//for(int j=i+1;j<=i+l-2;j++)
				//	g[i][i+l]=(g[i][i+l]+(f[i][j]+g[i][j])*f[j+1][i+l])%mod;
			}
	}
	/*for(int i=1;i<n;i++)
	{
		ans[i]=f[0][i];
		for(int j=1;j<i;j++)
		{
			if(f[j][i]!=0)
				ans[i]=(ans[i]+ans[j-1]*f[j][i])%mod;
		}

	}*/
	//cout<<ans[n-1]<<endl;
	cout<<(f[0][n-1]+g[0][n-1])%mod<<endl;
	return 0;
}