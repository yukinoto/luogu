#include <stdio.h>
#include <string.h>
#include <algorithm>

int d,g;
struct node{
	int t,f,h;
	bool operator < (const node &x)const{
		return this->t<x.t;
	}
};
node a[110];
int f[140][140],ans=-1;
int main()
{
	scanf("%d%d",&d,&g);
	memset(f,-1,sizeof(f));
	f[0][0]=10;
	for(int i=1;i<=g;i++)
		scanf("%d%d%d",&a[i].t,&a[i].f,&a[i].h);
	std::sort(a+1,a+g+1);
	for(int i=0;i<=g;i++)
		for(int j=0;j<=d;j++)
			if(f[i][j]>=0)
			{
				if(j+a[i].h>=d)
				{
					printf("%d\n",a[i].t);
					return 0;
				}
				if(f[i][j]>=a[i+1].t-a[i].t)
					f[i+1][j+a[i].h]=std::max(f[i+1][j+a[i].h],f[i][j]+a[i].t-a[i+1].t);
				f[i+1][j]=std::max(f[i+1][j],f[i][j]+a[i].f+a[i].t-a[i+1].t);
			}
	for(int i=0;i<=g;i++)
		ans=std::max(ans,f[i][0]+a[i].t+a[i].f);
	printf("%d\n",ans);
	return 0;
}
