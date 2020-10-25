//p3387-tarjan
#include <stdio.h>
#include <string.h>

namespace algo{
	inline int min(int x,int y)
	{
		if(x>y)
			return y;
		return x;
	}
	inline int max(int x,int y)
	{
		if(x>y)
			return x;
		return y;
	}
}
namespace map{
	int n,m;
	bool map[10010][10010];
	bool inmap[1010];
	int value[10010];
}
namespace tarjan{
	int dfn[10010];
	int low[10010];
	bool visited[10010];
	bool finished[10010];
	int nr[10010];
	void merge(int x,int y)
	{
		map::inmap[y]=false;
		nr[y]=x;
		for(int i=1;i<=map::n;i++)
		{
			if(nr[i]==y)
				nr[i]=x;
			map::map[x][i]=map::map[x][i]||map::map[y][i];
			map::map[i][x]=map::map[i][x]||map::map[i][y];
		}
		map::value[x]+=map::value[y];
		return;
	}
	int tarjan(int root,int st)
	{
		for(int i=1;i<=map::n;i++)
			if(i!=root&&map::map[root][i]&&!finished[i]&&map::inmap[i])
			{
				if(visited[i])
				{
					if(low[i]<low[root])
					{
						/*for(int j=1;j<=map::n;j++)
							if(visited[j]&&!finished[j])
							{
								int tmp=low[j];
								for(int k=1;k<=map::n;k++)
									if(low[k]==tmp)
										low[k]=low[i];
							}*/
						merge(i,root);
						return tarjan(i,st);
					}
					continue;
				}
				visited[i]=true;
				low[i]=dfn[i]=st+1;
				st=algo::max(tarjan(i,st+1),st);
				if(!map::inmap[i])
					merge(nr[i],nr[root]);
				finished[i]=true;
			}
		return st;
	}
}
namespace dp{
	int f[10010];
	int search(int root)
	{
		if(f[root]!=-1)
			return f[root];
		f[root]=map::value[root];
		for(int i=1;i<=map::n;i++)
			if(i!=root&&map::inmap[i]&&map::map[root][i])
				f[root]=algo::max(f[root],search(i)+map::value[root]);
		return f[root];
	}
}
int main()
{
	freopen("p3387.in","r",stdin);
	freopen("p3387.out","w",stdout);
	scanf("%d%d",&map::n,&map::m);
	for(int i=1;i<=map::n;i++)
	{
		scanf("%d",&map::value[i]);
		tarjan::nr[i]=i;
	}
	for(int i=1;i<=map::m;i++)
	{
		int f,t;
		scanf("%d%d",&f,&t);
		map::map[f][t]=true;
	}
	{
		int dfn=1;
		memset(map::inmap,true,sizeof(map::inmap));
		for(int i=1;i<=map::n;i++)
			if(!tarjan::visited[i]&&map::inmap[i])
			{
				tarjan::visited[i]=true;
				tarjan::dfn[i]=tarjan::low[i]=dfn;
				dfn=tarjan::tarjan(i,dfn)+1;
				tarjan::finished[i]=true;
			}
	}
	memset(dp::f,-1,sizeof(dp::f));
	int ans=0;
	for(int i=1;i<=map::n;i++)
		if(map::inmap[i]!=0)
			ans=algo::max(ans,dp::search(i));
	printf("%d\n",ans);
	return 0;
}
