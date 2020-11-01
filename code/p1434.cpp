#include <stdio.h>

int n,m;
int f[110][110],map[110][110];
int dx[4]={1,-1,0,0},dy[4]={0,0,-1,1};
int max(int x,int y)
{
    if(x>y)
        return x;
    return y;
}
void init()
{
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++)
        for(int j=1;j<=m;j++)
            scanf("%d",&map[i][j]);
}
int search(int x,int y)
{
    if(f[x][y]!=0)
        return f[x][y];
    f[x][y]=1;
    for(int i=0;i<4;i++)
    {
        int nx=x+dx[i],ny=y+dy[i];
        if(nx>n||nx<1||ny>m||ny<1)
            continue;
        if(map[nx][ny]>=map[x][y])
            continue;
        f[x][y]=max(f[x][y],search(nx,ny)+1);
    }
    return f[x][y];
}
int main()
{
	//freopen("in.in","r",stdin);
	//freopen("out.out","w",stdout);
    init();
    int ans=0;
    for(int i=1;i<=n;i++)
        for(int j=1;j<=m;j++)
            ans=max(ans,search(i,j));
    printf("%d\n",ans);
    return 0;
}
