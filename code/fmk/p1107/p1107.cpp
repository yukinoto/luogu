//p1107
#include <stdio.h>
#include <algorithm>

int n,h,del;
int st[4010][4010];
int f[4010][4010],lf[4010];
int main()
{
	freopen("p1107.in","r",stdin);
	freopen("p1107.out","w",stdout);
    scanf("%d%d%d",&n,&h,&del);
    for(int i=1;i<=n;i++)
    {
        int num,x;
        scanf("%d",&num);
        for(int j=1;j<=num;j++)
        {
            scanf("%d",&x);
            st[i][x]++;
        }
    }
    for(int i=h;i>0;i--)
    {
        for(int j=1;j<=n;j++)
        {
            if(i+del>h)
                f[i][j]=f[i+1][j]+st[j][i];
            else
                f[i][j]=st[j][i]+std::max(f[i+1][j],lf[i+del]);
            lf[i]=std::max(lf[i],f[i][j]);
        }
    }
    printf("%d\n",lf[1]);
    return 0;
}
