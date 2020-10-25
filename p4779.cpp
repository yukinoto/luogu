//p4779-dij-error
#include <cstdio>
class mp{
	private:
		int n,m;
		int head[100010],to[500010],wei[500010],nxt[500010],top;
		
		bool mak[100010];
		int dir[100010];
		
		void relax(int p)
		{
			int itera=head[p];
			while(itera!=0)
			{
				if(!mak[to[itera]]&&dir[to[itera]]>dir[p]+wei[itera])
					dir[to[itera]]=dir[p]+wei[itera];
				itera=nxt[itera];
			}
			return;
		}
		int fs()
		{
			int ansp=0;
			for(int i=1;i<=n;i++)
				if(!mak[i]&&dir[i]<dir[ansp])
					ansp=i;
			return ansp;
		}
	public:
		void set(int _n,int _m)
		{
			n=_n;m=_m;
			return;
		}
		void add(int f,int t,int w)
		{
			to[++top]=t;
			wei[top]=w;
			nxt[top]=head[f];
			head[f]=top;
			return;
		}
		void dij(int s)
		{
			for(int i=0;i<=n;i++)
			{
				mak[i]=false;
				dir[i]=0x7fffffff;
			}
			dir[s]=0;
			for(int i=1;i<n;i++)
			{
				int p=fs();
				mak[p]=true;
				relax(p);
			}
			for(int i=1;i<=n;i++)
				printf("%d ",dir[i]);
			printf("\n");
			return;
		}
};
mp s;

int main()
{
	int n,m,f;
	scanf("%d%d%d",&n,&m,&f);
	s.set(n,m);
	for(int i=1;i<=m;i++)
	{
		int l,r,w;
		scanf("%d%d%d",&l,&r,&w);
		s.add(l,r,w);
		s.add(r,l,w);
	}
	s.dij(f);
	return 0;
}
