#include <stdio.h>
#include <string.h>
#include <algorithm>

int n,l,r;
int v[200010];
int front,end;
int q[200010],p[200010];
int f[200010];

void init()
{
    scanf("%d%d%d",&n,&l,&r);
    r++;n++;
    for(int i=0;i<n;i++)
        scanf("%d",v+i);
}

int main()
{
    init();
    memset(f,0x80,sizeof(f));
    f[0]=v[0];
    q[end]=f[0];
    p[end++]=0;
    for(int i=0;i<n;i++)
    {
        int lft=i-r+1,rgh=i-l+1;
        if(rgh<=0)
            continue;
        while(front<end&&p[front]<lft)
            front++;
        while(front<end&&q[end-1]<=f[rgh-1])
            end--;
        q[end]=f[rgh-1];
        p[end++]=rgh-1;
        if(front>=end)
            return -1;
        f[i]=std::max(f[i],q[front]+v[i]);
    }
    int ans=0x80000000;
    for(int i=n-r+1;i<n;i++)
    	ans=std::max(ans,f[i]);
    printf("%d\n",ans);
    return 0;
}
