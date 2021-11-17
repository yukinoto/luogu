#include <iostream>
#include <vector>
#include <cstdlib>
using namespace std;

int n,m,k;
vector<pair<int,int>> mp[500001];
bool tkn[500001];
int mm[500001];

long long mod=1e9+7;
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

bool flag=true;

void init()
{
	cin>>n>>m>>k;
	if(n==1)
	{
		cout<<k+1<<endl;
		exit(0);
	}
	if(m==0)
	{
		cout<<quickpow(k+1,n)<<endl;
		exit(0);
	}
	for(int i=0;i<m;i++)
	{
		int x,y,z;
		cin>>x>>y>>z;
		if(z!=0)
			flag=false;
		mp[x].push_back(make_pair(y,z));
		mp[y].push_back(make_pair(x,z));
	}
}

int dt[500001];
int tp=0;

void dfs(int root)
{
	dt[root]=tp;
	for(auto i:mp[root])
	{
		if(dt[i.first]==0)
			dfs(i.first);
	}
	return;
}

int p=1;
void pre()
{
	while(p<=k)
		p<<=1;
	return;
}

bool pm[33];
void dfs2(int root,int xo)
{
	dt[root]=tp;
	for(int i=k+1;i<=p;i++)
		pm[i^xo]=false;
	for(auto i:mp[root])
	{
		if(dt[i.first]==0)
			dfs2(i.first,xo^i.second);
		else
		{
			if(xo!=i.second)
			{
				cout<<0<<endl;
				exit(0);
			}
		}
	}
	return;
}

void work()
{
	if(flag)
	{
		for(int i=1;i<=n;i++)
			if(dt[i]==0)
			{
				++tp;
				dfs(i);
			}
		cout<<quickpow(k+1,tp)<<endl;
	}
	else
	{
		if(k<=16)
		{
			pre();
			int ans=1;
			for(int i=1;i<=n;i++)
			if(dt[i]==0)
				{
					for(int j=0;j<=p;j++)
						pm[j]=true;
					++tp;
					dfs2(i,0);
					int cnt=0;
					for(int j=0;j<=k;j++)
						if(pm[j])
							cnt++;
					ans=ans*cnt%mod;
				}
			cout<<ans<<endl;
		}
	}
}

int main()
{
	init();
	work();
	return 0;
}