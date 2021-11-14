#include <iostream>
#include <vector>
#include <bitset>
using namespace std;

vector<int> p;
bitset<100000010> tb;

void pre(int n)
{
	for(int i=0;i<=n;i++)
		tb[i]=true;
	tb[1]=tb[0]=false;
	for(int i=2;i<=n;i++)
	{
		if(tb[i])
		{
			p.push_back(i);
		}
		for(auto j:p)
		{
			if(i*j>n)
				break;
			tb[i*j]=false;
			if(i%j==0)
				break;
		}
	}
	return;
}

int main()
{
	ios::sync_with_stdio(false);
	int n,q;
	cin>>n>>q;
	pre(n);
	for(int i=0;i<q;i++)
	{
		int x;
		cin>>x;
		cout<<p[x-1]<<endl;
	}
	return 0;
}