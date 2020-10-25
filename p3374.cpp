//p3374
#include <stdio.h>

#define MAXN 500010

class tmg{
	private:
		int sgp[MAXN];
	public:
		void add(int p,int x)
		{
			while(p<=MAXN)
			{
				sgp[p]+=x;
				bool flag=false;
				for(int i=0;;i++)
				{
					if((p&(1<<i))!=0)
					{
						flag=true;
						p^=(1<<i);
						continue;
					}
					if((p&(1<<i))==0&&flag)
					{
						p|=1<<i;
						break;
					}
				}
			}
			return;
		}
		int bef(int p)
		{
			int sum=0;
			while(p!=0)
			{
				sum+=sgp[p];
				p&=p-1;
			}
			return sum;
		}
		int slr(int l,int r)
		{
			return bef(r-1)-bef(l-1);
		}
		int read(int p)
		{
			return slr(p,p+1);
		}
		void set(int p,int x)
		{
			add(p,x-read(p));
			return;
		}
};

int main()
{
	int n,m;
	tmg a;
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)
	{
		int x;
		scanf("%d",&x);
		a.set(i,x);
	}
	for(int i=1;i<=m;i++)
	{
		int f,x,y;
		scanf("%d%d%d",&f,&x,&y);
		if(f==1)
			a.add(x,y);
		if(f==2)
			printf("%d\n",a.slr(x,y+1));
	}
	return 0;
}
