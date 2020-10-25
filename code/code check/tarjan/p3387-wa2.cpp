//p3387-tarjan
#include <stdio.h>
#include <algorithm>

int n,m;
int value[10010];
bool map[10010][10010];
bool instack[10010];
int time_icon=1;
int dnf[10010];
int low[10010];
bool inmap[10010];
int ptr[10010];
int p(int);
void tarjan(int root)
{
	for(int i=1; i<=n; i++)
		if(i!=root&&inmap[i]&&map[root][i])
		{
			if(!instack[p(i)])
			{
				if(dnf[i]!=0)
					continue;
				dnf[i]=low[i]=time_icon++;
				instack[dnf[i]]=true;
				ptr[dnf[i]]=i;
				tarjan(i);
				low[root]=std::min(low[root],low[i]);
				instack[dnf[i]]=false;
				continue;
			}
			low[root]=std::min(low[root],dnf[i]);
		}
	return;
}

void merge(int x,int y)
{
	inmap[y]=false;
	value[x]+=value[y];
	for(int i=1;i<=n;i++)
	{
		map[i][x]=map[i][x]||map[i][y];
		map[x][i]=map[x][i]||map[y][i];
		map[i][y]=map[y][i]=false;
	}
}

int f[10010];
int search(int root)
{
	if(f[root]!=-1)
		return f[root];
	f[root]=value[root];
	for(int i=1;i<=n;i++)
		if(inmap[i]&&map[root][i]&&root!=i)
			f[root]=std::max(f[root],search(i)+value[root]);
	return f[root];
}
int p(int root)
{
	if(low[root]==dnf[root])
		return root;
	return p(ptr[low[root]]);
}
int main()
{
	freopen("p3387.in","r",stdin);
	freopen("p3387.out","w",stdout);
	scanf("%d%d",&n,&m);
	for(int i=1; i<=n; i++)
	{
		f[i]=-1;
		inmap[i]=true;
		scanf("%d",&value[i]);
	}
	for(int i=1; i<=m; i++)
	{
		int x,y;
		scanf("%d%d",&x,&y);
		map[x][y]=true;
	}
	/*for(int i=1;i<=n;i++)
		for(int j=i+1;j<=n;j++)
			if(inmap[i]&&inmap[j]&&map[i][j]&&map[j][i])
				merge(i,j);*/
	for(int t=1; t<=n; t++)
		if(dnf[t]==0&&inmap[t])
		{
			instack[t]=true;
			dnf[t]=low[t]=time_icon++;
			ptr[dnf[t]]=t;
			tarjan(t);
			instack[t]=false;
		}
	for(int i=1;i<=n;i++)
		if(dnf[i]!=low[i])
			merge(p(i),i);
	int ans=0;
	for(int i=1;i<=n;i++)
		if(inmap[i])
			ans=std::max(ans,search(i));
	printf("%d\n",ans);
	return 0;
}
