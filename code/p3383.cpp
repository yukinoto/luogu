#include <stdio.h>
#include <vector>
#include <bitset>
using namespace std;

vector<int> prim;
unsigned char p[(50000001>>3)+1];

const unsigned char b[8]={0x01,0x02,0x04,0x08,0x10,0x20,0x40,0x80};

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
	p[0]|=b[0];
	prim.push_back(2);
	for(int i=3;i<=n;i+=2)
	{
		if(!(p[i>>2]&b[(i<<1)&0x07]))
			prim.push_back(i);
		for(int j=1;j<prim.size()&&prim[j]*i<=n;j++)
		{
			p[(prim[j]*i)>>4]|=b[(((prim[j]*i)>>1)&0x07-1)];
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
