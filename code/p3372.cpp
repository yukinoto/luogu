#include <stdio.h>

inline int min(const int &x,const int &y)
{
	return x>y?y:x;
}
inline int max(const int &x,const int &y)
{
	return x>y?x:y;
}

namespace xds{
	struct node{
		bool exs;
		int l,r;
		long long sum,sumtag;	
	};
	struct node st[800010];
	void mkt(long long a[],int l,int r,int root)
	{
		if(l>=r)
			return;
		st[root].exs=true;
		if(l==r-1)
		{
			st[root].sum=a[l];
			st[root].l=l;
			st[root].r=r;
			return;
		}
		int lc=root<<1,rc=(root<<1)|1,mid=(l+r)/2;
		st[root].l=l;st[root].r=r;
		mkt(a,l,mid,lc);mkt(a,mid,r,rc);
		st[root].sum=st[lc].sum+st[rc].sum;
		return;
	}
	void add(int l,int r,long long x,int root)
	{
		if(!st[root].exs||l>=st[root].r||r<=st[root].l)
			return;
		if(l<=st[root].l&&r>=st[root].r)
		{
			st[root].sum+=x*(st[root].r-st[root].l);
			st[root].sumtag+=x;
			return;
		}
		if(l>=st[root].l&&r<=st[root].r)
			st[root].sum+=(r-l)*x;
		else
			st[root].sum+=(min(st[root].r,r)-max(st[root].l,l))*x;
		add(l,r,x,root<<1);
		add(l,r,x,(root<<1)|1);
		return;
	}
	long long dosum(int l,int r,int root)
	{
		if(l>=st[root].r||r<=st[root].l||st[root].l>=st[root].r||!st[root].exs)
			return 0;
		if(st[root].sumtag!=0)
		{
			st[root<<1].sumtag+=st[root].sumtag;
			st[(root<<1)|1].sumtag+=st[root].sumtag;
			st[root<<1].sum+=(st[root<<1].r-st[root<<1].l)*st[root].sumtag;
			st[(root<<1)|1].sum+=(st[(root<<1)|1].r-st[(root<<1)|1].l)*st[root].sumtag;
			st[root].sumtag=0;
		}
		if(l<=st[root].l&&r>=st[root].r)
			return st[root].sum;
		return dosum(l,r,root<<1)
		+dosum(l,r,(root<<1)|1);
	}
}

int n,m;
long long a[100010];
int main()
{
	//freopen("p3372.in","r",stdin);
	//freopen("p3372.out","w",stdout);
	scanf("%d%d",&n,&m);
	for(int i=0;i<n;i++)
		scanf("%lld",a+i);
	xds::mkt(a,0,n,1);
	for(int i=0;i<m;i++)
	{
		int f;
		scanf("%d",&f);
		if(f==1)
		{
			int x,y,k;
			scanf("%d%d%d",&x,&y,&k);
			xds::add(x-1,y,k,1);
		}
		else
		{
			int x,y;
			scanf("%d%d",&x,&y);
			printf("%lld\n",xds::dosum(x-1,y,1));
		}
	}
	return 0;
}
