#include <stdio.h>
#include <string.h>

bool prim[15000];
void mp(int n)
{
    memset(prim,true,sizeof(prim));
    prim[0]=prim[1]=false;
    for(int i=2;i*i<=n;i++)
        if(prim[i])
            for(int j=2;i*j<=n;j++)
                prim[i*j]=false;
}
bool pd[2001000];
int p[200010],top;
int main()
{
	//freopen("3.in","r",stdin);
    int n;
    scanf("%d",&n);
    int x=n;
    mp(n);
    for(int i=1;i*i<=n;i++)
        while(prim[i]&&x%i==0)
        {
            if(pd[i]==false)
                p[++top]=i;
            pd[i]=true;
            x/=i;
        }
    if(x>=2)
    {
        pd[x]=true;
        p[++top]=x;
    }
    int ans=0;
    for(int i=1;i<=n;i++)
    {
        bool flag=true;
        for(int j=1;j<=top;j++)
            if(i%p[j]==0)
            {
                flag=false;
                break;
            }
        if(flag)
            ans++;
    }
    printf("%d\n",ans);
    return 0;
}
