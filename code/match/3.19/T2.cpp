#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
using namespace std;

class vec{
	public:
		long long x,y;
		vec(){;}
		vec(long long _x,long long _y){x=_x,y=_y;}
		bool operator <(const vec&o)const{return x==o.x?y<o.y:x<o.x;}
		vec operator -(const vec&o)const{return vec(x-o.x,y-o.y);}
		vec operator +(const vec&o)const{return vec(x+o.x,y+o.x);}
};

long long dc(const vec&x,const vec&y){return x.x*y.x+x.y*y.y;}
long long cc(const vec&x,const vec&y){return x.x*y.y-x.y*y.x;}

vector<vec> tb(vector<vec>&nodes)
{
	vector<vec> up,down;
	sort(nodes.begin(),nodes.end());
	for(auto i:nodes)
	{
		while(up.size()>=2&&cc(i-up.back(),up.back()-*(up.end()-2))>0)
			up.pop_back();
		while(down.size()>=2&&cc(i-down.back(),down.back()-*(down.end()-2))<0)
			down.pop_back();
		up.push_back(i),down.push_back(i);
	}
	up.pop_back(),up.erase(up.begin());
	for(auto i=up.rbegin();i!=up.rend();i++)
		down.push_back(*i);
	return down;
}

bool cp(const vector<vec>&nodes)
{
	auto f=[&nodes](decltype(nodes.begin()) it)
	{
		it++;
		if(it==nodes.end())
			it=nodes.begin();
		return it;
	};
	auto it=nodes.begin()++;
	for(auto i=nodes.begin();i!=nodes.end();i++)
	{
		while(cc(*f(i)-*i,*f(it)-*it)<0)
			it=f(it);
		if(cc(*f(i)-*i,*f(it)-*it)==0&&it!=i)
			return true;
	}
	return false;
}

const double pi=acos(-1);

double arg(const vec&o)
{
	double x=o.x*1.0/sqrt(double(dc(o,o))),y=o.y*1.0/sqrt(double(dc(o,o)));
	double ans=acos(x);
	if(asin(y)<0)
		ans+=pi;
	return ans;
}

void work()
{
	int n;
	cin>>n;
	vector<vec> nodes;
	for(int i=0;i<n;i++)
	{
		long long x,y;
		cin>>x>>y;
		nodes.emplace_back(x,y);
	}
	if(n<3)
	{
		cout<<0<<endl;
		return;
	}
	if(n==3)
	{
		cout<<3<<endl;
		return;
	}
	auto ch=tb(nodes);
	if(ch.size()<n)
	{
		cout<<3<<endl;
		return;
	}
	if(cp(ch))
	{
		cout<<4<<endl;
		return;
	}
	return;
}

int main()
{
	int t;
	cin>>t;
	for(int i=0;i<t;i++)
		work();
	return 0;
}