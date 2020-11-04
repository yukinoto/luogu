#include <stdio.h>
#include <string.h>
#include <algorithm>

int n,max,a[110];
bool f[26010];

void init()
{
    scanf("%d",&n);
    max=0;
    memset(f,false,sizeof(f));
    for(int i=0;i<n;i++)
    {
        scanf("%d",a+i);
        max=(max<a[i])?a[i]:max;
    }
    std::sort(a,a+n);
    return;
}

void work()
{
    init();
    f[0]=true;
    int cnt=n;
    for(int i=0;i<n;i++)
    {
    	if(f[a[i]])
    	{
    		cnt--;
    		continue;
		}
        for(int j=0;j+a[i]<=max;j++)
            if(f[j])
                f[j+a[i]]=true;
	}
    printf("%d\n",cnt);
    return;
}

int main()
{
    freopen("money.in","r",stdin);
    freopen("money.out","w",stdout);
    int t;
    scanf("%d",&t);
    for(int i=0;i<t;i++)
        work();
    fclose(stdin);
    fclose(stdout);
    return 0;
}
