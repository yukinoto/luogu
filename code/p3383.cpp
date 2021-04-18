#include <stdio.h>
#include <vector>
#include <bitset>
using namespace std;

vector<int> prim;
bitset<50000001> p;

inline int read()
{
	int ans=0;
	char x=getchar();
	while((x&0xf0)!=0x30)
		x=getchar();
	while((x&0xf0)==0x30)
	{
		ans=(ans<<3)+(ans<<1)+(x&0x0f);
		x=getchar();
	}
	return ans;
}

void pre(int n)
{
	p[0]=1;
	prim.push_back(2);
	for(int j=0;j<prim.size()&&prim[j]*2<=n;j++)
	{
		p[prim[j]*2]=1;
		if(2%prim[j]==0)
			break;
	}
	for(int i=3;i<=n;i+=2)
	{
		if(!p[i>>1])
			prim.push_back(i);
		for(int j=1;j<prim.size()&&prim[j]*i<=n;j++)
		{
			p[(prim[j]*i)>>1]=1;
			if(i%prim[j]==0)
				break;
		}
	}
	return;
}

int main()
{
	pre(read());
	int q=read();
	for(int i=0;i<q;i++)
		printf("%d\n",prim[read()-1]);
	return 0;
}
