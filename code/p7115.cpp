#include <cstdio>

int n,m;
int stk[51][401],top[51];
int ept,k;
int fa[820000],tt[820000];

void init()
{
	scanf("%d%d",&n,&m);
	for(int i=0;i<n;i++)
	{
		for(int j=0;j<m;j++)
			scanf("%d",&stk[i][j]);
		top[i]=m;
	}
	ept=n;
	return;
}

namespace pts{
	void move(int from,int to)
	{
		stk[to][top[to]++]=stk[from][--top[from]];
		fa[k]=from+1,tt[k]=to+1;
		k++;
		return;
	}

	int get_top(int s)
	{
		if(top[s]==0)
			return -1;
		return stk[s][top[s]-1];
	}

	void uplift(int p,int color)
	{
		int f=0;
		if(f==p||f==ept)
			f=1;
		if(f==p||f==ept)
			f=2;
		int cnt=0;
		for(int i=0;i<m;i++)
			if(stk[p][i]==color)
				cnt++;
		for(int i=0;i<cnt;i++)
			move(f,ept);
		int mvd=0;
		for(int i=0;i<m;i++)
		{
			if(get_top(p)==color)
			{
				mvd++;
				move(p,f);
			}
			else
				move(p,ept);
			if(mvd==cnt)
				break;
		}
		for(int i=top[ept];i>cnt;i--)
			move(ept,p);
		for(int i=cnt;i>0;i--)
			move(f,p);
		for(int i=cnt;i>0;i--)
			move(ept,f);
		return;
	}

	bool isfull(int p)
	{
		return top[p]==m;
	}

	void fullfill(int p)
	{
		int ptr=0;
		while(top[p]!=0)
		{
			while(isfull(ptr)||ptr==p)
				ptr++;
			move(p,ptr);
		}
		ept=p;
		return;
	}

	void coltoept(int color)
	{
		for(int i=0;i<=n;i++)
			if(i!=ept)
				while(top[i]!=0&&stk[i][top[i]-1]==color)
					move(i,ept);
		return;
	}

	void fincol(int color,int ufp)
	{
		for(int i=0;i<=n;i++)
			if(i!=ept)
				uplift(i,color);
		coltoept(color);
		fullfill(ufp);
		return;
	}

	void work()
	{
		init();
		for(int i=n;i>0;i--)
			fincol(i,i);
		printf("%d\n",k);
		for(int i=0;i<k;i++)
			printf("%d %d\n",fa[i],tt[i]);
		return;
	}
}

int main()
{
	pts::work();
	return 0;
}
