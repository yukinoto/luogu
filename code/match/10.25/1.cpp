#include <stdio.h>
#include <string.h>

int ans=0x7fffffff;
int n,m,r;
int map[15][15];
int time_token[15];
void search(int root)
{
	bool flag=false;
	int cnt=1;
	for(int i=1;i<=n;i++)
		if(map[root][i]!=0&&time_token[i]==-1)
		{
			time_token[i]=time_token[root]+map[root][i]*cnt;
			cnt++;
			search(i);
			time_token[i]=-1;
			flag=true;
		}
	if(!flag)
	{
		int x=0;
		for(int i=1;i<=n;i++)
			if(time_token[i]>x)
				x=time_token[i];
		if(x<ans)
			ans=x;
	}
}
int main()
{
	scanf("%d%d%d",&n,&m,&r);
	for(int i=1;i<=m;i++)
	{
		int x,y,t;
		scanf("%d%d%d",&x,&y,&t);
		map[x][y]=map[y][x]=t;
	}
	memset(time_token,-1,sizeof(time_token));
	time_token[r]=0;
	search(r);
	printf("%d\n",ans);
	return 0;
}
