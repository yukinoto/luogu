#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
using namespace std;

class block{
	public:
	int l,r;
	vector<bool> data;
	int l0,l1,r0,r1,t0,t1,cnt0,cnt1;
	bool anti;
	int tag;
};

int n,m,bn;
block a[1000];

void calc(block &x)
{
	if(x.tag!=-1)
	{
		for(auto it=x.data.begin();it!=x.data.end();++it)
			(*it)=x.tag;
		x.tag=-1;
	}
	if(x.anti)
	{
		for(auto it=x.data.begin();it!=x.data.end();++it)
			(*it)=!(*it);
		x.anti=false;
	}
	x.l0=x.l1=-1;
	for(int i=0;i<x.r-x.l;i++)
	{
		if(x.data[i]&&x.l0==-1)
			x.l0=i;
		if(!x.data[i]&&x.l1==-1)
			x.l1=i;
		if(x.l0!=-1&&x.l1!=-1)
			break;
	}
	x.r0=x.r1=-1;
	for(int i=x.r-x.l-1;i>=0;i--)
	{
		if(x.data[i]&&x.r0==-1)
			x.r0=x.r-x.l-i-1;
		if(!x.data[i]&&x.r1==-1)
			x.r1=x.r-x.l-i-1;
		if(x.r0!=-1&&x.r1!=-1)
			break;
	}
	int tmp0=0,tmp1=0;
	x.t0=x.t1=0;x.cnt0=x.cnt1=0;
	for(int i=0;i<x.r-x.l;i++)
	{
		tmp0++,tmp1++;
		if(x.data[i])
		{
			tmp0=0;
			x.cnt1++;
		}
		else
		{
			tmp1=0;
			x.cnt0++;
		}
		x.t0=max(x.t0,tmp0),x.t1=max(x.t1,tmp1);
	}
	if(x.cnt0==x.r-x.l)	x.l0=x.r0=x.cnt0;
	if(x.cnt1==x.r-x.l)	x.l1=x.r1=x.cnt1;
	return;
}

void init()
{
	cin>>n>>m;
	int sep=ceil(sqrt(n));
	int i;
	for(i=0;i+sep<=n;i+=sep)
	{
		int p=i/sep;
		a[p].tag=-1,a[p].anti=false;
		a[p].l=i,a[p].r=i+sep;
		for(int j=i;j<i+sep;j++)
		{
			bool x;
			cin>>x;
			a[p].data.emplace_back(x);
		}
		calc(a[p]);
	}
	int p=i/sep+1;
	a[p].tag=-1,a[p].anti=false;
	a[p].l=i,a[p].r=n;
	for(;i<n;i++)
	{
		bool x;
		cin>>x;
		a[p].data.emplace_back(x);
	}
	calc(a[p]);
	bn=p+1;
	return;
}

void set(int l,int r,bool x)
{
	for(int i=0;i<bn;i++)
	{
		if(l>=a[i].r||r<=a[i].l)
			continue;
		if(l<=a[i].l&&r>=a[i].r)
		{
			a[i].tag=x;
			a[i].anti=false;
			if(x)
			{
				a[i].cnt1=a[i].l1=a[i].r1=a[i].t1=a[i].r-a[i].l;
				a[i].cnt0=a[i].l0=a[i].r0=a[i].t0=0;
			}
			else
			{
				a[i].cnt1=a[i].l1=a[i].r1=a[i].t1=0;
				a[i].cnt0=a[i].l0=a[i].r0=a[i].t0=a[i].r-a[i].l;
			}
		}
		else
		{
			calc(a[i]);
			for(int j=max(l,a[i].l);j<min(r,a[i].r);j++)
				a[i].data[j-a[i].l]=x;
			calc(a[i]);
		}
	}
	return;
}

void anti(int l,int r)
{
	for(int i=0;i<bn;i++)
	{
		if(l>=a[i].r||r<=a[i].l)
			continue;
		if(l<=a[i].l&&r>=a[i].r)
		{
			if(a[i].tag!=-1)
			{
				a[i].tag^=1;
			}
			else
			{
				a[i].anti=!a[i].anti;
			}
			swap(a[i].cnt0,a[i].cnt1),swap(a[i].l0,a[i].l1),
			swap(a[i].r0,a[i].r1),swap(a[i].t0,a[i].t1);
		}
		else
		{
			calc(a[i]);
			for(int j=max(l,a[i].l);j<min(r,a[i].r);j++)
				a[i].data[j-a[i].l]=!a[i].data[j-a[i].l];
			calc(a[i]);
		}
	}
}

int quest(int l,int r)
{
	int ans=0;
	for(int i=0;i<bn;i++)
	{
		if(l>=a[i].r||r<=a[i].l)
			continue;
		if(l<=a[i].l&&r>=a[i].r)
		{
			ans+=a[i].cnt1;
		}
		else
		{
			calc(a[i]);
			for(int j=max(l,a[i].l);j<min(r,a[i].r);j++)
				if(a[i].data[j-a[i].l])
					ans++;
		}
	}
	return ans;
}

int questl(int l,int r)
{
	int bef=0,ans=0;
	for(int i=0;i<bn;i++)
	{
		if(l>=a[i].r||r<=a[i].l)
			continue;
		if(l<=a[i].l&&r>=a[i].r)
		{
			bef+=a[i].l1;
			ans=max(ans,bef);
			ans=max(ans,a[i].t1);
			if(a[i].l1!=a[i].r-a[i].l)
				bef=a[i].r1;
			ans=max(ans,bef);
		}
		else
		{
			calc(a[i]);
			for(int j=max(l,a[i].l);j<min(r,a[i].r);j++)
			{
				if(a[i].data[j-a[i].l])
				{
					bef++;
					ans=max(ans,bef);
				}
				else
					bef=0;
			}
		}
	}
	return ans;
}

int main()
{
	init();
	for(int i=0;i<m;i++)
	{
		int op,l,r;
		cin>>op>>l>>r;
		r++;
		if(l<0||r>n)
			throw -1;
		switch(op){
			case 0:
				set(l,r,0);
				break;
			case 1:
				set(l,r,1);
				break;
			case 2:
				anti(l,r);
				break;
			case 3:
				cout<<quest(l,r)<<endl;
				break;
			case 4:
				cout<<questl(l,r)<<endl;
				break;
		}
	}
	return 0;
}