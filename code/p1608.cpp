#include <stdio.h>
#include <string.h>

#define Inf 0x3fffffff

int n,m;
int map[2010][2010],cnt[2010][2010];
bool token[2010];
int dis[2010],f[2010];

void init()
{
	scanf("%d%d",&n,&m);
	for(int i=0;i<m;i++)
	{
		int x,y,w;
		scanf("%d%d%d",&x,&y,&w);
		if(map[x][y]==w)
			cnt[x][y]=1;
		if(map[x][y]==0||map[x][y]>w)
			map[x][y]=w,cnt[x][y]=1;
	}
	for(int i=0;i<=n;i++)
		dis[i]=Inf;
	return;
}

int find()
{
	int ansp=0;
	for(int i=1;i<=n;i++)
		if(!token[i]&&dis[i]<dis[ansp])
			ansp=i;
	return ansp;
}

void relax(int p)
{
	token[p]=true;
	for(int i=1;i<=n;i++)
		if(token[i])
		{
			if(dis[p]+map[p][i]==dis[i])
				f[i]+=f[p]*cnt[p][i];
		}
		else
		{
			if(cnt[p][i]>0)
				if(dis[p]+map[p][i]<dis[i])
				{
					dis[i]=dis[p]+map[p][i];
					f[i]=f[p]*cnt[p][i];
				}
				else
					if(dis[p]+map[p][i]==dis[i])
						f[i]+=f[p]*cnt[p][i];
		}
	return;
}

void dij()
{
	dis[1]=0;f[1]=1;
	for(int i=1;i<=n;i++)
	{
		int p=find();
		relax(p);
	}
	return;
}

int main()
{
	init();
	dij();
	if(dis[n]==Inf)
	{
		printf("No answer\n");
		return 0;
	}
	printf("%d %d\n",dis[n],f[n]);
	return 0;
}
