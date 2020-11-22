#include <stdio.h>
#include <math.h>
#include <string.h>

namespace algo{
	int max(const int&a,const int&b)
	{
		return a>b?a:b;
	}
}

class stTable{
	private:
		int n;
		int st[24][100010];
		inline int rst(const int &x,const int &y)
		{
			if(st[x][y]!=-1)	return st[x][y];
			return st[x][y]=algo::max(rst(x-1,y),rst(x-1,y+(1<<(x-1))));
		}
	public:
		stTable()
		{
			memset(st,-1,sizeof(st));
		}
		inline int ask(const int &l,const int &r)
		{
			int m=log2(r-l);
			//printf("%d ",m);
			//printf("%d %d ",rst(m,l),rst(m,algo::max(0,r-(1<<m))));
			return algo::max(rst(m,l),rst(m,algo::max(0,r-(1<<m))));
		}
		inline void insert(const int &p,const int &x)
		{
			st[0][p]=x;
			return;
		}
};

stTable st;
int main()
{
	int n,q;
	scanf("%d%d",&n,&q);
	for(int i=1;i<=n;i++)
	{
		int x;
		scanf("%d",&x);
		st.insert(i,x);
	}
	for(int i=0;i<q;++i)
	{
		int l,r;
		scanf("%d%d",&l,&r);
		printf("%d\n",st.ask(l,r+1));
	}
	return 0;
}
