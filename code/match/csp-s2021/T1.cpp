#include <iostream>
#include <algorithm>
#include <set>
#include <queue>
using namespace std;

int n,m1,m2;
struct plane{
	int l,r;
	bool operator <(const plane&x)const
	{
		return l==x.l?r<x.r:l<x.l;
	}
	plane(){;}
	plane(int _l,int _r)
	{
		l=_l,r=_r;
		return;
	}
};

plane p[100010];
int cnt[100010],cnt1[100010],cnt2[100010];

istream& operator >>(istream& ins,plane&x)
{
	ins>>x.l>>x.r;
	return ins;
}

void init()
{
	cin>>n>>m1>>m2;
	m2+=m1;
	for(int i=0;i<m2;i++)
		cin>>p[i];
	sort(p,p+m1);
	sort(p+m1,p+m2);
	return;
}

/*template<typename T1,typename T2>
struct pair{
	T1 first;T2 second;
	pair(const T1 &_first,const T2 &_second)
	{
		first=_first,second=_second;
		return;
	}
	pair(){;}
};*/
/*bool cmp(const pair<int,int>&x,const pair<int,int>&y)
{
	return x.first==y.first?x.second>y.second:x.first>y.first;
}*/

void wk(int l,int r)
{
	set<int>bge;
	set<pair<int,int>>q;
	for(int i=1;i<=n;i++)
		bge.insert(i);
	for(int i=l;i<r;i++)
	{
		for(auto it=q.begin();it!=q.end()&&it->first<=p[i].l;it++)
		{
			bge.insert(it->second);
		}
		q.erase(q.begin(),q.upper_bound(make_pair(p[i].l,0x7fffffff)));
		if(!bge.empty())
		{
			int b=*bge.begin();
			q.insert(make_pair(p[i].r,b));
			bge.erase(bge.begin());
			cnt[b]++;
		}
	}
	return;
}

int main()
{
	init();
	wk(0,m1);
	for(int i=0;i<=n;i++)
	{
		//bge[i]=plane(0,0);
		cnt1[i]=cnt[i];
		cnt[i]=0;
	}
	wk(m1,m2);
	for(int i=0;i<=n;i++)
	{
		//bge[i]=plane(0,0);
		cnt2[i]=cnt[i];
		//cnt[i]=0;
	}
	for(int i=1;i<=n;i++)
	{
		cnt1[i]+=cnt1[i-1];
		cnt2[i]+=cnt2[i-1];
	}
	int ans=0;
	for(int k=0;k<=n;k++)
	{
		ans=max(ans,cnt1[k]+cnt2[n-k]);
	}
	cout<<ans<<endl;
	return 0;
}