//p3366
#include <stdio.h>
#include <string.h>

int n,m;
int map[5010][5010];
int dis[5010];
bool intre[5010];
int main()
{
    scanf("%d%d",&n,&m);
    memset(map,0x3f,sizeof(map));
    for(int i=1;i<=m;i++)
    {
        int x,y,v;
        scanf("%d%d%d",&x,&y,&v);
        if(map[x][y]>v)
        	map[x][y]=map[y][x]=v;
    }
    memset(dis,0x3f,sizeof(dis));
    dis[1]=0;
    int ans=0;
    for(int i=1;i<=n;i++)
    {
        int p=0;
        for(int j=1;j<=n;j++)
            if(dis[j]<dis[p]&&!intre[j])
                p=j;
        if(p==0)
        {
            printf("orz\n");
            return 0;
        }
        ans+=dis[p];
        intre[p]=true;
        for(int j=1;j<=n;j++)
            if(!intre[j]&&map[p][j]<dis[j])
                dis[j]=map[p][j];
    }
    printf("%d\n",ans);
    return 0;
}
