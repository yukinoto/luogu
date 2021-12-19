#include <iostream>
#include <bitset>
#include <vector>
using namespace std;

bitset<500000001>isp;
vector<int>prim;

const int maxn=1000000000;

void pre()
{
	isp[0]=false;
	for(int i=1;i<=maxn/2;i++)
		isp[i]=true;
	for(int i=3;i<=maxn;i+=2)
	{
		if(isp[i>>1])
			prim.push_back(i);
		for(auto j:prim)
		{
			if(j>i||i*j>maxn)
				break;
			isp[(i*j)>>1]=false;
		}
	}
	return;
}

int main()
{
	pre();
	int n;
	cin>>n;
	for(int i=1;i<=n;i++)
	{
		int x,y;
		cin>>x>>y;
		if((prim[x]^prim[y])==1)
			cout<<"Yes\n";
		else
			cout<<"No\n";
	}
	return 0;
}