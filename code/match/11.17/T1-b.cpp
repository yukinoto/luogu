#include <iostream>
#include <vector>
using namespace std;

bool isp[10000001];
long long sigma[10000001];
vector<int> p;

long long quickpow(long long x,int n)
{
	if(n==1)
		return x;
	long long ans=quickpow(x,n>>1);
	ans*=ans;
	if(n&1)
		ans*=x;
	return ans;
}

void pre(int n)
{
	isp[0]=isp[1]=false;
	sigma[0]=0;sigma[1]=1;
	for(int i=2;i<=n;i++)
		isp[i]=true;
	for(int i=2;i<=n;i++)
	{
		if(isp[i])
		{
			p.push_back(i);
			sigma[i]=i+1;
		}
		for(auto j:p)
		{
			if(j*i>n)
				break;
			if(i%j==0)
			{
				isp[i*j]=false;
				int cnt=1,x=i;
				while(x%j==0)
				{
					x/=j;
					cnt++;
				}
				sigma[i*j]=sigma[x]*(quickpow(j,cnt+1)-1)/(j-1);
				break;
			}
			isp[i*j]=false;
			sigma[i*j]=sigma[i]*sigma[j];
		}
	}
}

int main()
{
	int x,y;
	cin>>x>>y;
	pre(y);
	long long ans=0;
	for(int i=x;i<=y;i++)
		ans+=sigma[i];
	cout<<ans<<endl;
	return 0;
}