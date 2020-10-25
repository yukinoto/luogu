#include <stdio.h>

int n,p;
int map[110][110];
int value[110],u[110];
int indeg[110];
bool opt[110];
int main()
{
	scanf("%d%d",&n,&p);
	for(int i=1;i<=n;i++)
		scanf("%d%d",value+i,u+i);
	for(int i=1;i<=p;i++)
	{
		int x,y,w;
		scanf("%d%d%d",&x,&y,&w);
		map[x][y]=w;
		indeg[y]++;
	}
	for(int k=1;k<=n;k++)
	{
		int p;
		for(p=1;indeg[p]!=0&&p<=n;p++);
		value[p]-=u[p];
		bool flag=true;
		for(int i=1;i<=n;i++)
			if(map[p][i]!=0)
			{
				indeg[i]--;
				if(value[p]>0)
					value[i]+=value[p]*map[p][i];
				flag=false;
			}
		opt[p]=flag;
		indeg[p]=-1;
	}
	bool flag=true;
	for(int i=1;i<=n;i++)
		if(opt[i])
		{
			flag=false;
			printf("%d %d\n",i,value[i]);
		}
	if(flag)
		printf("NULL\n");
	return 0;
}
