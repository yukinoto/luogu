#include <stdio.h>
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
    for(int i=0;i<=n;i++)
    {
        f[i]=v[i];
        int lft=i-r+1,rgh=i-l+1;
        if(rgh<=0)
            continue;
        while(front<end&&p[front]<lft)
            front++;
        while(front<end&&q[end-1]<=f[rgh-1])
            end--;
        q[end]=f[rgh-1];
        p[end++]=rgh-1;
        f[i]=std::max(f[i],q[front]+v[i]);
    }
    printf("%d\n",f[n]);
    return 0;
}