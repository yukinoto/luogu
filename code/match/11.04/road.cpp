#include <stdio.h>
#include <queue>
using namespace std;

inline int min(const int &x,const int &y)
{
	if(x>y)
		return y;
	return x;
}

int a[100010];
int n,ans=0;

void change(int l,int r)
{
    if(l>=r)
        return;
    queue<int> q;
    int m=0x7fffffff;
    for(int i=l;i<r;i++)
        m=min(m,a[i]);
    if(m==0)
    	return;
    for(int i=l;i<r;i++)
    {
        a[i]-=m;
        if(a[i]==0)
            q.push(i);
    }
    ans+=m;
    int p=l-1;
    while(!q.empty())
    {
        change(p+1,q.front());
        p=q.front();
        q.pop();
    }
    change(p+1,r);
	return;
}

int main()
{
    freopen("road.in","r",stdin);
    freopen("road.out","w",stdout);
	scanf("%d",&n);
    for(int i=0;i<n;i++)
        scanf("%d",a+i);
    int p=0;
    for(int i=0;i<=n;i++)
    	if(a[i]==0)
    	{
    		change(p,i);
    		p=i+1;
		}
	printf("%d\n",ans);
    fclose(stdin);
    fclose(stdout);
    return 0;
}
