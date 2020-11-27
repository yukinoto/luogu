#include <stdio.h>

int n,m,mod;

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
		int l,r;
		int sum,tag;
		int type;
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
			tr[root].sum=a[l]%mod;
			return;
		}
		int mid=(l+r)/2;
		mkt(l,mid,root<<1);
		mkt(mid,r,(root<<1)|1);
		tr[root].sum=(tr[root<<1].sum+tr[(root<<1)|1].sum)%mod;
		return;
	}
	void pshstg(int);
	void pshctg(int);
	int opts(int,int,int);
	void add(int l,int r,int x,int root)
	{
		if(l>=r)
			return;
		if(tr[root].l>=r||tr[root].r<=l)
			return;
		if(tr[root].l>=l&&tr[root].r<=r)
		{
			pshctg(root);
			tr[root].type=0;
			tr[root].tag+=x;
			tr[root].tag%=mod;
			return;
		}
		pshctg(root);
		tr[root].type=0;
		tr[root].sum+=x*(min(r,tr[root].r)-max(l,tr[root].l))%mod;
		tr[root].sum%=mod;
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
			tr[root].tag*=x;
			if(tr[root].tag==0&&x!=0&&tr[root].type==0)
				tr[root].tag=x;
			tr[root].type=1;
			tr[root].tag%=mod;
			return;
		}
		pshstg(root);
		c(l,r,x,root<<1);
		c(l,r,x,(root<<1)|1);
		tr[root].sum=(opts(tr[root].l,(tr[root].l+tr[root].r)/2,root<<1)
		+opts((tr[root].l+tr[root].r)/2,tr[root].r,(root<<1)|1))%mod;
		return;
	}
	int opts(int l,int r,int root)
	{
		if(l>=r||tr[root].l>=r||tr[root].r<=l)
			return 0;
		pshstg(root);
		pshctg(root);
		if(tr[root].l>=l&&tr[root].r<=r)
			return tr[root].sum%mod;
		return (opts(l,r,root<<1)
		+opts(l,r,(root<<1)|1))%mod;
	}
	void pshstg(int root)
	{
		if(tr[root].type||tr[root].tag==0)
			return;
		int lc=root<<1,rc=(root<<1)|1;
		tr[root].tag%=mod;
		tr[root].sum+=tr[root].tag*(tr[root].r-tr[root].l)%mod;
		tr[root].sum%=mod;
		if(tr[lc].type==1)
		{
			pshctg(lc);
			tr[lc].type=0;
		}
		if(tr[rc].type==1)
		{
			pshctg(rc);
			tr[rc].type=0;
		}
		tr[lc].tag+=tr[root].tag;
		tr[rc].tag+=tr[root].tag;
		tr[root].tag=0;
		return;
	}
	void pshctg(int root)
	{
		if(tr[root].type==0||tr[root].tag==1)
			return;
		tr[root].tag%=mod;
		int lc=root<<1,rc=(root<<1)|1;
		tr[root].sum*=tr[root].tag;
		tr[root].sum%=mod;
		if(tr[lc].type==0)
		{
			pshstg(lc);
			tr[lc].type=tr[lc].tag=1;
		}
		if(tr[rc].type==0)
		{
			pshstg(rc);
			tr[rc].type=tr[rc].tag=1;
		}
		tr[lc].tag*=tr[root].tag;
		tr[rc].tag*=tr[root].tag;
		tr[root].tag=1;
		return;
	}
}
inline void init()
{
	scanf("%d%d%d",&n,&m,&mod);
	for(int i=0;i<n;i++)
		scanf("%d",xds::a+i);
	xds::mkt(0,n,1);
	return;
}

inline void work()
{
	int f;
	scanf("%d",&f);
	switch (f)
	{
	case 1:
		{
			int x,y,k;
			scanf("%d%d%d",&x,&y,&k);
			xds::c(x-1,y,k,1);
		}
		break;
	case 2:
		{
			int x,y,k;
			scanf("%d%d%d",&x,&y,&k);
			xds::add(x-1,y,k,1);
		}
		break;
	case 3:
		{
			int x,y;
			scanf("%d%d",&x,&y);
			printf("%d\n",xds::opts(x-1,y,1));
		}
		break;
	}
}

int main()
{
	init();
	for(int i=0;i<m;i++)
		work();
	return 0;
}
