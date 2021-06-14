#include <cstdio>

class mts{
	private:
		int *st;
	public:
		mts(int n)
		{
			st=new int[n];
			for(int i=0;i<n;i++)
				st[i]=i;
			return;
		}
		~mts()
		{
			delete st;
			return;
		}
		int ist(int x)
		{
			if(st[x]==x)
				return x;
			return st[x]=ist(st[x]);
		}
		void merge(int x,int y)
		{
			st[ist(x)]=st[ist(y)];
			return;
		}
		bool issm(int x,int y)
		{
			return ist(x)==ist(y);
		}
};

mts *st;

void fun()
{
	int f,x,y;
	scanf("%d%d%d",&f,&x,&y);
	if(f==1)
		st->merge(x,y);
	if(f==2)
		printf("%c\n",(st->issm(x,y))?'Y':'N');
	return;
}

void work()
{
	int n,m;
	scanf("%d%d",&n,&m);
	st=new mts(n+1);
	for(int i=0;i<m;i++)
		fun();
	delete st;
}

int main()
{
	work();
	return 0;
}
