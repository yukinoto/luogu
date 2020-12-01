#include <stdio.h>
#include <algorithm>
using namespace std;

int n,d,k,l,r;
struct node{
	int p,w;
	bool operator <(const node &x)const{
		return this->p<x.p;
	}
};
node a[500010];
int sum[500010],s;
struct dis{
	int pl,pr,len;
	bool operator <(const dis &x)const{
		return this->len<x.len;
	}
};
dis dist[500010];
int main()
{
	scanf("%d%d%d",&n,&d,&k);
	for(int i=1;i<=n;i++)
		scanf("%d%d",&a[i].p,&a[i].w);
	sort(a+1,a+n+1);
	for(int i=1;i<=n;i++)
		for(int j=i+1;j<=n+1;j++)
			sum[j]+=a[i].w;
	for(int i=1;i<n;i++)
	{
		dist[i].pl=i;
		dist[i].pr=i+1;
		dist[i].len=a[i+1].p-a[i].p;
	}
	sort(dist+1,dist+n);
	l=1,r=n+1;
	//while(sum[r]-sum[l]>=)
}
