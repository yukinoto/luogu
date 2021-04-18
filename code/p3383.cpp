#include <stdio.h>
#include <vector>
#include <bitset>
using namespace std;

vector<int> prim;
bitset<100000001> p;

void pre(int n)
{
	p[0]=p[1]=1;
	for(int i=2;i<=n;i++)
	{
		if(!p[i])
			prim.push_back(i);
		for(int j=0;j<prim.size()&&prim[j]*i<=n;j++)
		{
			p[prim[j]*i]=1;
			if(i%prim[j]==0)
				break;
		}
	}
	return;
}

int main()
{
	int n,q;
	scanf("%d%d",&n,&q);
	pre(n);
	for(int i=0;i<q;i++)
	{
		int x;
		scanf("%d",&x);
		printf("%d\n",prim[x-1]);
	}
	return 0;
}
