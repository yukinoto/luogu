#include <iostream>
#include <vector>
#include <cstring>
#include <algorithm>
using namespace std;

bool isp[2000010];

vector<int>prim;

void pre()
{
	const int maxn=2000000;
	memset(isp,true,sizeof(isp));
	isp[0]=isp[1]=false;
	for(int i=2;i<=maxn;i++)
	{
		if(isp[i])
		{
			prim.push_back(i);
			for(int j=i*2;j<=maxn;j+=i)
			{
				isp[j]=false;
			}
		}
	}
}

int ans[1000100];

int main()
{
	int t;
	cin>>t;
	pre();
	for(int i=0;i<t;i++)
	{
		int x,cnt=0;
		cin>>x;
		if(ans[x]!=0)
		{
			cout<<ans[x]<<'\n';
			continue;
		}
		for(auto i:prim)
		{
			if((x^i)<x)
				cnt++;
			if(i>2*x)
				break;
		}
		cout<<(ans[x]=cnt)<<'\n';
	}
	return 0;
}
