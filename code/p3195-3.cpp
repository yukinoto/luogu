#include <cstdlib>
#include <iostream>
#include <algorithm>
using namespace std;

long long n,l;
long long *c,*p,*s,*f;

void del()
{
	delete[]c,p,s,f;
}

void init()
{
	cin>>n>>l;
	++l;
	c=new long long[n];
	p=new long long[n];
	s=new long long[n];
	f=new long long[n];
	for(int i=0;i<n;i++)
	{
		cin>>c[i];
		if(i==0)
		{
			p[i]=c[i];
			s[i]=p[i]+i;
		}
		else
		{
			p[i]=p[i-1]+c[i];
			s[i]=p[i]+i;
		}
		f[i]=0x3fffffffffffffffull;
	}
	atexit(del);
	return;
}

template<typename T>
class queue
{
	private:
		T x[50010];
	public:
		int first,last;
		queue()
		{
			first=last=0;
		}
		T front()
		{
			return x[first];
		}
		T end()
		{
			return x[last];
		}
		bool empty()
		{
			return first==last;
		}
		void pop()
		{
			if(first>=last)
				throw "fuckccf";
			first++;
			return;
		}
		void popback()
		{
			if(first>=last)
				throw "fuckccf";
			last--;
			return;
		}
		void push(const T &a)
		{
			x[last++]=a;
			return;
		}
		T& operator[](int p)
		{
			return x[p];
		}
};

struct pt{long long x,y;};
queue<pt> q;
pt makept(long long _x,long long _y)
{
	pt a;
	a.x=_x,a.y=_y;
	return a;
}

int e=0;

long long fnd(int s)
{
	auto f=[&](int i){return q[i].y+q[i].x*2*(l-s);};
	while(e!=q.last-1&&f(e+1)<f(e))
		e++;
	return f(e);
}

int main()
{
	init();
	for(int i=0;i<n;i++)
	{
		if(i>0)
		{
			f[i]=fnd(s[i]);
			f[i]+=(s[i]-l)*(s[i]-l);
		}
		f[i]=min(f[i],(s[i]-l+1)*(s[i]-l+1));
		long long x=s[i],y=f[i]+s[i]*s[i];
		while(q.last-q.first>1)
		{
			pt a=q[q.last-2],b=q[q.last-1];
			if(double(a.y-b.y)/(a.x-b.x)>=double(b.y-y)/(b.x-x))
			{
				q.popback();
				if(e==q.last)
					e--;
			}
			else
				break;
		}
		q.push(makept(x,y));
	}
	cout<<f[n-1]<<endl;
	return 0;
}