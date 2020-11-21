#include <stdio.h>
#include <string.h>
#include <algorithm>
using namespace std;

void fre()
{
	freopen("tree.in","r",stdin);
	freopen("tree.out","w",stdout);
}

namespace tre{
	int n;
	int pt[20010],nm[20010];
	bool edg[20010][20010];
	int edgcnt[20010];
	struct edge{
		int x1,x2;
	}e[20010];
	void init()
	{
		scanf("%d",&n);
		for(int i=1;i<=n;i++)
		{
			scanf("%d",nm+i);
			pt[nm[i]]=i;
		}
		memset(edgcnt,0,sizeof(edgcnt));
		for(int i=1;i<n;i++)
		{
			scanf("%d%d",&e[i].x1,&e[i].x2);
			edg[e[i].x1][e[i].x2]=edg[e[i].x2][e[i].x1]=true;
			edgcnt[e[i].x1]++;edgcnt[e[i].x2]++;
		}
		return;
	}
}

namespace work1_f{
	void change(int *,int *,int);
	int tim(int x)
	{
		int ans=1;
		for(int i=2;i<=x;i++)
			ans*=i;
		return ans;
	}
	bool cmp(int *a,int *b,int len)
	{
		int c[15],d[15];
		change(c,a,len);
		change(d,b,len);
		for(int i=1;i<=len;i++)
			if(c[i]!=d[i])
				return c[i]<d[i];
		return true;
	}
	void moni(int *a,int *b,int len)
	{
		for(int i=1;i<=len;i++)
			a[i]=tre::pt[i];
		for(int i=1;i<len;i++)
			swap(a[tre::e[b[i]].x1],a[tre::e[b[i]].x2]);
		return;
	}
	void cpy(int *a,int *b,int len)
	{
		for(int i=1;i<=len;i++)
			a[i]=b[i];
		return;
	}
	void change(int *a,int *b,int len)
	{
		for(int i=1;i<=len;i++)
			a[b[i]]=i;
		return;
	}
}

namespace work2_f{
	class set{
		private:
			int fa[20010];
		public:
			set()
			{
				for(int i=1;i<=20000;i++)
					fa[i]=i;
			}
			int checkc(int p)
			{
				if(fa[p]==p)
					return fa[p];
				return fa[p]=checkc(fa[p]);
			}
			bool ifInSameSet(int p1,int p2)
			{
				return checkc(p1)==checkc(p2);
			}
			void merge(int p1,int p2)
			{
				fa[checkc(p1)]=checkc(p2);
				return;
			}
	};
}

namespace work3_f{
	int findhead(int len)
	{
		
	}
}

void work1()
{
	int ansp[15],np[15];
	int answ[15];
	for(int i=1;i<tre::n;i++)
	{
		answ[i]=i;
	}
	work1_f::moni(ansp,answ,tre::n);
	int t=work1_f::tim(tre::n);
	for(int i=1;i<=t;i++)
	{
		work1_f::moni(np,answ,tre::n);
		if(work1_f::cmp(np,ansp,tre::n))
			work1_f::cpy(ansp,np,tre::n);
		next_permutation(answ+1,answ+tre::n);
	}
	int ans[15];
	work1_f::change(ans,ansp,tre::n);
	for(int i=1;i<tre::n;i++)\
		printf("%d ",ans[i]);
	printf("%d\n",ans[tre::n]);
	return;
}

void work2()
{
	work2_f::set s;
	bool visited[20010];
	memset(visited,false,sizeof(visited));
	for(int i=1;i<=tre::n;i++)
	{
		for(int j=1;j<=tre::n;j++)
		{
			if(!visited[j]&&(i==tre::n||!s.ifInSameSet(j,tre::nm[i])))
			{
				printf("%d",j);
				if(i==tre::n)
					printf("\n");
				else
					printf(" ");
				visited[j]=true;
				s.merge(j,tre::nm[i]);
				break;
			}
		}
	}
}

void work3()
{
}

void work()
{
	bool flag=true;
	for(int i=1;i<=tre::n;i++)
	{
		if(tre::edgcnt[i]==tre::n-1)
		{
			work2();
			return;
		}
		if(tre::edgcnt[i]!=1&&tre::edgcnt[i]!=2)
			flag=false;
	}
	if(flag)
	{
		work3();
		return;
	}
	work1();
}

int main()
{
	//fre();
	int t;
	scanf("%d",&t);
	for(int i=0;i<t;++i)
	{
		tre::init();
		work();
	}
	return 0;
}
