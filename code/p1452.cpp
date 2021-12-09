#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

class node{
	public:
		int x,y;
		node(){;}
		node(int _x,int _y):x(_x),y(_y){;}
		long long operator*(const node&o)const
		{
			return (long long)x*o.x+(long long)y*o.y;
		}
		node operator -(const node&o)const
		{
			return node(x-o.x,y-o.y);
		}
		node operator +(const node&o)const
		{
			return node(x+o.x,y+o.y);
		}
		bool operator<(const node&o)const
		{
			return x==o.x?y<o.y:x<o.x;
		}
		friend istream& operator>>(istream&,node&);
};

istream& operator>>(istream&ins,node&o)
{
	return ins>>o.x>>o.y;
}

bool cmp(const node&a,const node&b)
{
	return a.y==b.y?a.x<b.x:a.y<b.y;
}

long long xj(const node&x,const node&y)
{
	return (long long)x.x*y.y-(long long)x.y*y.x;
}

int n;
node nd[50010];

void init()
{
	cin>>n;
	for(int i=0;i<n;i++)
		cin>>nd[i];
	return;
}

vector<node> tb;

node stk[50010];
int top=0;

void gtb()
{
	sort(nd,nd+n);
	for(int i=0;i<n;i++)
	{
		while(top>=2&&xj(stk[top-1]-stk[top-2],nd[i]-stk[top-1])>0)
			--top;
		stk[top++]=nd[i];
	}
	for(int i=0;i<top;i++)
		tb.push_back(nd[i]);
	top=0;
	for(int i=0;i<n;i++)
	{
		while(top>=2&&xj(stk[top-1]-stk[top-2],nd[i]-stk[top-1])<0)
			--top;
		stk[top++]=nd[i];
	}
	for(int i=top-1;i>0;i--)
		tb.push_back(nd[i]);
	return;
}

#define f vector<node>::iterator
f roll_add(const f &it,const f&beg,const f&ed)
{
	f ans=it+1;
	if(ans==ed)
		ans=beg;
	return ans;
}
#undef f

long long dist(const node&x,const node&y)
{
	return (x-y)*(x-y);
}

long long kk()
{
	long long ans=0;
	auto it=tb.begin();
	for(auto i:tb)
	{
		while(dist(*roll_add(it,tb.begin(),tb.end()),i)>=dist(*it,i))
			it=roll_add(it,tb.begin(),tb.end());
		ans=max(ans,dist(*it,i));
	}
	return ans;
}

int main()
{
	init();
	gtb();
	cout<<kk()<<endl;
	return 0;
}