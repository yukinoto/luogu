#include <stdio.h>
#include <stdlib.h>

class node{
	private:
		unsigned long long x;
	public:
		node(){x=0;}
		void insert(int p,unsigned long long num)
		{
			num&=0x0000000000000003ull;
			x&=(~(3<<(p<<1)));
			x|=(num<<(p<<1));
			return;
		}
		void write(unsigned long long in)
		{
			x=in;
			return;
		}
		int read(int p)
		{
			return (x>>(p<<1))&0x3;
		}
		unsigned long long read()
		{
			return x;
		}
		node make(unsigned long long _x)
		{
			node ans;
			ans.x=x;
			return ans;
		}
};

class hush{
	private:
		int row;
		const int mod=4001;
		int a[2][mod+1];
		bool taken[2][mod+1];
	public:
		void change()
		{
			row^=1;
			for(int i=0;i<=mod;i++)
				taken[row][i]=false;
			return;
		}
		void insert(int x,unsigned long long p)
		{
			a[row][p%mod]=x;
			if(taken[row][p%mod]==true)
				exit(-1);
			taken[row][p%mod]=true;
			return;
		}
		int readnow(unsigned long long p)
		{
			if(!taken[row][p%mod])
				return -1;
			return a[row][p%mod];
		}
		int readbef(unsigned long long p)
		{
			if(!taken[row^1][p%mod])
				return -1;
			return a[row^1][p%mod];
		}
};

class queue{
	private:
		int row;
		int front[2],end[2];
		const int size=4000;
		unsigned long long a[2][size];
	public:
		void change()
		{
			row^=1;
			front[row]=end[row]=0;
			return;
		}
		bool emptynow()
		{
			return front[row]>=end[row];
		}
		bool emptybef()
		{
			return front[row^1]>=end[row^1];
		}
		void pushnow(unsigned long long x)
		{
			if(end[row]>=size)
				exit(-2);
			a[row][end[row]++]=x;
			return;
		}
		void pushbef(unsigned long long x)
		{
			if(end[row^1]>=size)
				exit(-2);
			a[row^1][end[row^1]++]=x;
			return;
		}
		unsigned long long topnow()
		{
			if(!this->emptynow())
				return a[row][front[row]];
			return -1;
		}
		unsigned long long topbef()
		{
			if(!this->emptybef())
				return a[row^1][front[row^1]];
			return -1;
		}
		void popnow()
		{
			if(!this->emptynow())
				front[row]++;
			return;
		}
		void popbef()
		{
			if(!this->emptybef())
				front[row^1]++;
			return;
		}
};

int n,m;
bool map[15][15];

void init()
{
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)
	{
		getchar();
		for(int j=1;j<=m;j++)
			map[i][j]=(getchar()=='.');
	}
}

void fl(int &x,int &y)
{
	for(int i=n;i>0;i--)
		for(int j=m;j>0;j--)
			if(map[i][j]==false)
				return;
	exit(-4);
}
void work()
{
	int lx,ly;
	fl(lx,ly);
	hush sto;
	queue q;
}

int main()
{
	init();
	work();
	return 0;
}