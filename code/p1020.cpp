//p1020-n2
#include <stdio.h>
#include <algorithm>

int height[100010],f[100010],ans;
int mh[100010],top;

int main()
{
	mh[100005]=0x7fffffff;
    for(int i=0;~scanf("%d",height+i);i++)
    {
        f[i]=1;
        for(int j=0;j<i;j++)
            if(height[i]<=height[j])
                f[i]=std::max(f[i],f[j]+1);
        ans=std::max(f[i],ans);
        int m=100005;
        for(int j=0;j<top;j++)
            if(mh[j]>=height[i]&&mh[j]<mh[m])
                m=j;
        if(m==100005)
            m=top++;
        mh[m]=height[i];
    }
    printf("%d %d\n",ans,top);
    return 0;
}
