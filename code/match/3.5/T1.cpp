#include <iostream>
#include <cstring>
#include <vector>
using namespace std;

int sig[10000001],dbn[10000001];
vector<int>p;

void pre(int n)
{
	memset(sig,-1,sizeof(sig));
	sig[0]=sig[1]=1;
	for(int i=2;i<=n;i++)
	{
		if(sig[i]==-1)
		{
			sig[i]=2;
			p.push_back(i);
		}
		for(auto j:p)
		{
			if(i*j>n)
				break;
			if(i%j==0)
			{
				int k=i/j;
				while(k%j==0)	k/=j;
				sig[i*j]=sig[i]+sig[k];
				break;
			}
			else
				sig[i*j]=sig[i]*sig[j];
		}
	}
	return;
}

const int p10[]={1,10,100,1000,10000,100000,1000000,10000000};

void dbp(int b)
{
	for(int i=0;i<5;i++)
		dbn[i*2]=1,dbn[i*2+1]=0;
	for(int i=1;i<=b;i++)
	{
		for(int j=0;j<5;j++)
		{
			for(int k=0;k<p10[i];k++)
			{
				if(j!=0)
					dbn[p10[i]*(j*2)+k]=dbn[k]+1;
				dbn[p10[i]*(j*2+1)+k]=dbn[k];
			}
		}
	}
	return;
}

int main()
{
	ios::sync_with_stdio(false);
	pre(10000000);
	dbp(6);
	int t;
	cin>>t;
	for(int i=0;i<t;i++)
	{
		int n,m,k;
		cin>>n>>m>>k;
		vector<int>ans;
		for(int j=p10[n-1];j<p10[n];j++)
		{
			if(sig[j]==k&&dbn[j]==m)
				ans.push_back(j);
		}
		if(ans.empty())
			cout<<"-1\n";
		else
		{
			cout<<ans.size()<<'\n';
			for(auto it:ans)
				cout<<it<<'\n';
		}
	}
	return 0;
}