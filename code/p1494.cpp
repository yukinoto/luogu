#include <iostream>
#include <algorithm>
#include <functional>
#include <cmath>
#include <utility>
using namespace std;

template<typename Int>
Int gcd(Int x,Int y)
{
	Int z;
	while(y!=0)
	{
		z=x%y;
		x=y,y=z;
	}
	return x;
}

class quest{
	public:
		int l,r,id;
		pair<long long,long long>ans;
};

int n,m;
int a[50010];
int l,r;
long long cna[50010],sn,sn2;
quest q[50010];

int blk;
bool cmp(const quest&x,const quest&y)
{
	int ax=x.l/blk,ay=y.l/blk,bx=x.r/blk,by=y.r/blk;
	return ax==ay?(bx==by?x.id<y.id:bx<by):ax<ay;
}

void init()
{
	cin>>n>>m;
	blk=ceil(sqrt(n));
	for(int i=1;i<=n;i++)
		cin>>a[i];
	for(int i=1;i<=m;i++)
	{
		cin>>q[i].l>>q[i].r;
		q[i].id=i;
	}
	l=r=1;
	sn=1,sn2=0;
	cna[a[1]]++;
}

void ist(int x)
{
	sn++;
	sn2+=2*cna[x];
	cna[x]++;
	return;
}

void ost(int x)
{
	sn--;
	cna[x]--;
	sn2-=2*cna[x];
	return;
}

void mv(int left,int right)
{
	if(left<l)
	{
		for(int i=left;i<l;i++)
			ist(a[i]);
		l=left;
	}
	if(right>r)
	{
		for(int i=right;i>r;i--)
			ist(a[i]);
		r=right;
	}
	if(left>l)
	{
		for(int i=l;i<left;i++)
			ost(a[i]);
		l=left;
	}
	if(right<r)
	{
		for(int i=r;i>right;i--)
			ost(a[i]);
		r=right;
	}
	return;
}

pair<long long,long long> gans()
{
	pair<long long,long long>ans=make_pair(sn2,sn*(sn-1));
	long long d=gcd(ans.first,ans.second);
	ans.first/=d,ans.second/=d;
	return ans;
}

void work()
{
	sort(q+1,q+m+1,cmp);
	for(int i=1;i<=n;i++)
	{
		if(q[i].l==q[i].r)
			q[i].ans=make_pair<long long,long long>(0,1);
		else
		{
			mv(q[i].l,q[i].r);
			q[i].ans=gans();
		}
	}
	sort(q+1,q+m+1,function([](const quest&x,const quest&y){return x.id<y.id;}));
	for(int i=1;i<=m;i++)
		cout<<q[i].ans.first<<'/'<<q[i].ans.second<<endl;
	return;
}

int main()
{
	init();
	work();
	return 0;
}