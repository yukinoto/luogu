#include <iostream>
#include <algorithm>
#include <cmath>
#include <iomanip>
using namespace std;

int n;
pair<int,int> d[100010];

void init(istream&ins)
{
	ins>>n;
	for(int i=0;i<n;i++)
	{
		long double x,y;
		ins>>x>>y;
		if(x>0)	x+=0.005;else	x-=0.005;
		if(y>0)	y+=0.005;else	y-=0.005;
		d[i].first=(x)*100,d[i].second=(y)*100;
	}
	sort(d,d+n);
}

long long calc(const pair<int,int>&x,const pair<int,int>&y)
{
	return (long long)x.first*y.second-(long long)x.second*y.first;
}
long long dist(const pair<int,int>&x,const pair<int,int>&y)
{
	return (long long)x.first*y.first+(long long)x.second*y.second;
}

pair<int,int> operator-(const pair<int,int>&x,const pair<int,int>&y)
{
	return make_pair(x.first-y.first,x.second-y.second);
}

pair<int,int> stk[100010];
int top=0;

void slov(ostream&ous)
{
	for(int i=0;i<n;i++)
	{
		while(top>=2&&calc(stk[top-1]-stk[top-2],d[i]-stk[top-1])<0)
			--top;
		stk[top++]=d[i];
	}
	long double ans=0;
	for(int i=1;i<top;i++)
		ans+=sqrt((long double)dist(stk[i]-stk[i-1],stk[i]-stk[i-1])/10000);
	top=0;
	for(int i=0;i<n;i++)
	{
		while(top>=2&&calc(stk[top-1]-stk[top-2],d[i]-stk[top-1])>0)
			--top;
		stk[top++]=d[i];
	}
	for(int i=1;i<top;i++)
		ans+=sqrt((long double)dist(stk[i]-stk[i-1],stk[i]-stk[i-1])/10000);
	ous<<fixed<<setprecision(2)<<ans<<endl;
}

int main()
{
	init(cin);
	slov(cout);
	return 0;
}