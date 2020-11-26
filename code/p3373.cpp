#include <stdio.h>

int n,m,mod;
namespace xds{
	struct node{
		int l,r;
		int sum,tag;
		bool type;
	};
	node tr[400010];
	int a[100010];
	void mkt(int l,int r,int root)
	{
		if(l>=r)
			return;
		tr[root].l=l;
		tr[root].r=r;
		if(l==r-1)
		{
			tr[root].sum=a[l];
			return;
		}
		int mid=(l+r)/2;
		mkt(l,mid,root<<1);
		mkt(mid,r,(root<<1)|1);
		tr[root].sum=tr[root<<1].sum+tr[(root<<1)|1].sum;
		return;
	}
	void pshstg(int);
	void pshctg(int);
	void add(int l,int r,int x,int root)
	{
		if(l>=r)
			return;
		if(tr[root].l>=r||tr[root].r<=l)
			return;
		if(tr[root].l>=l&&tr[root].r<=r)
		{
			pshctg(root);
			tr[root].type=false;
			tr[root].tag+=x;
			return;
		}
		pshctg(root);
		add(l,r,x,root<<1);
		add(l,r,x,(root<<1)|1);
		return;
	}
	void c(int l,int r,int x,int root)
	{
		if(l>=r)
			return;
		if(tr[root].l>=r||tr[root].r<=l)
			return;
		if(tr[root].l>=l&&tr[root].r<=r)
		{
			pshstg(root);
			tr[root].type=true;
			tr[root].tag*=x;
			return;
		}
		pshstg(root);
		c(l,r,x,root<<1);
		c(l,r,x,(root<<1)|1);
		return;
	}
	int opts(int l,int r,int root)
	{
		if(l>=r||tr[root].l>=r||tr[root].r<=l)
			return 0;
		if(tr[root].l>=l&&tr[root].r<=r)
		{
			if(tr[root].type)
				return tr[root].sum*tr[root].tag;
			else
				return tr[root].sum+tr[root].tag*(tr[root].r-tr[root].l);
		}
		return opts(l,r,root<<1)
		+opts(l,r,(root<<1)|1);
	}
	void pshstg(int root)
	{
		if(tr[root].type||tr[root].tag==0)
			return;
		int lc=root<<1,rc=(root<<1)|1;
		tr[root].sum+=tr[root].tag*(tr[root].r-tr[root].l);
		if(tr[lc].type)
		{
			pshctg(lc);
			tr[lc].type=false;
		}
		if(tr[rc].type)
		{
			pshctg(rc);
			tr[rc].type=false;
		}
		tr[lc].tag=tr[rc].tag=tr[root].tag;
		tr[root].tag=0;
		return;
	}
	void pshctg(int root)
	{
		if(!tr[root].type||tr[root].tag==0||tr[root].tag==1)
			return;
		int lc=root<<1,rc=(root<<1)|1;
		tr[root].sum*=tr[root].tag;
		if(!tr[lc].type)
		{
			pshstg(lc);
			tr[lc].type=true;
		}
		if(!tr[rc].type)
		{
			pshstg(rc);
			tr[rc].type=true;
		}
		tr[lc].tag=tr[rc].tag=tr[root].tag;
		tr[root].tag=1;
		return;
	}
}
inline void init()
{
	scanf("%d%d%d",&n,&m,&mod);
	for(int i=0;i<n;i++)
		scanf("%d",a+i);
	xds::mkt(0,n,1);
	return 0;
}

inline void work()
{
	int f;
	scanf("%d",&f);
	switch (f)
	{
	case 1:
		int x,y,k;
		scanf("%d%d%d",&x,&y,&k);
		xds::c(x,y,k,1);
		break;
	case 2:
		int x,y,k;
		scanf("%d%d%d",&x,&y,&k);
		xds::add(x,y,k,1);
		break;
	case 3:
		int x,y;
		scanf("%d%d",&x,&y);
		printf("%d\n",xds::opts(x,y,1));
	default:
		break;
	}
}

int main()
{
}
