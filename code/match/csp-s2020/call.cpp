#include <stdio.h>
#include <vector>
using namespace std;

int n,m;
long long a[100010];
struct fun{
	int type,p,v;
	vector<int> nxt;
};
fun cj[100010];

void f(int t)
{
	if(cj[t].type==1)
	{
		a[cj[t].p]=(a[cj[t].p]+cj[t].v)%998244353;
		return;
	}
	if(cj[t].type==2)
	{
		for(int i=1;i<=n;i++)
			a[i]=a[i]*cj[t].v%998244353;
		return;
	}
	if(cj[t].type==3)
		for(vector<int>::iterator it=cj[t].nxt.begin();it!=cj[t].nxt.end();it++)
			f(*it);
	return;
}

int main()
{
	freopen("call.in","r",stdin);
	freopen("call.out","w",stdout);
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
		scanf("%lld",a+i);
	scanf("%d",&m);
	for(int i=1;i<=m;i++)
	{
		scanf("%d",&cj[i].type);
		if(cj[i].type==1)
			scanf("%d%d",&cj[i].p,&cj[i].v);
		if(cj[i].type==2)
			scanf("%d",&cj[i].v);
		if(cj[i].type==3)
		{
			int c;
			scanf("%d",&c);
			for(int j=1;j<=c;j++)
			{
				int x;
				scanf("%d",&x);
				cj[i].nxt.push_back(x);
			}
		}
	}
	int q;
	scanf("%d",&q);
	for(int i=1;i<=q;i++)
	{
		int x;
		scanf("%d",&x);
		f(x);
	}
	for(int i=1;i<n;i++)
		printf("%lld ",a[i]);
	printf("%lld\n",a[n]);
	return 0;
}
