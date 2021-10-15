#include <cstdlib>
#include <iostream>
#include <algorithm>
using namespace std;

long long n,l;
long long *s,*f;

void del()
{
	delete[]s,f;
}

void init()
{
	cin.sync_with_stdio(false);
	cout.sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
	cin>>n>>l;
	++l;
	s=new long long[n];
	f=new long long[n];
	for(int i=0;i<n;i++)
	{
        long long x;
        cin>>x;
		if(i==0)
			s[i]=x;
		else
			s[i]=s[i-1]+1+x;
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
			//if(first>=last)
			//	throw "fuckccf";
			first++;
			return;
		}
		void popback()
		{
			//if(first>=last)
			//	throw "fuckccf";
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
			if((a.y-b.y)*(b.x-x)>=(b.y-y)*(a.x-b.x))
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