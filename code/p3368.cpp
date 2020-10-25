//p3374
#include <stdio.h>

int n;
int wei[2000010];

int fnd(int p)
{
	int l=1,r=n,mid=(l+r)/2,pstr=1;
	while(l+1<r)
	{
		mid=(l+r)/2;
		if(p>=mid)
		{
			l=mid;
			pstr=pstr*2+1;
			continue;
		}
		if(p<mid)
		{
			r=mid;
			pstr=pstr*2;
			continue;
		}
	}
	return pstr;
}
void set(int p,int x)
{
	wei[fnd(p)]=x;
	return;
}
void add(int l,int r,int p,int fl,int fr,int x)
{
	if(fl>=fr)
		return;
	if(fl>=l&&fr<=r)
	{
		wei[p]+=x;
		return;
	}
	if(fl>=r||fr<=l)
		return;
	int mid=(fl+fr)/2;
	add(l,r,p*2,fl,mid,x);
	add(l,r,p*2+1,mid,fr,x);
	return;
}
int read(int p)
{
	int l=1,r=n,pstr=1,mid,sum=0;
	while(l+1<r)
	{
		mid=(l+r)/2;
		sum+=wei[pstr];
		if(p<mid)
		{
			r=mid;
			pstr=pstr*2;
			continue;
		}
		if(p>=mid)
		{
			l=mid;
			pstr=pstr*2+1;
			continue;
		}
	}
	sum+=wei[pstr];
	return sum;
}
int main()
{
	int m;
	scanf("%d%d",&n,&m);
	n++;
	for(int i=1;i<n;i++)
	{
		int x;
		scanf("%d",&x);
		set(i,x);
	}
	for(int i=0;i<m;i++)
	{
		int f;
		scanf("%d",&f);
		if(f==1)
		{
			int x,y,k;
			scanf("%d%d%d",&x,&y,&k);
			add(x,y+1,1,1,n,k);
		}
		if(f==2)
		{
			int p;
			scanf("%d",&p);
			printf("%d\n",read(p));
		}
	}
	return 0;
}
