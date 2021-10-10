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
		int first,last;
	public:
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
		void push(const T &a)
		{
			x[last++]=a;
			return;
		}
		T& operator[](int p)
		{
			return &x[p];
		}
};

struct pt{int x,y;};
queue<pt> q;
int main()
{
	init();
	for(int i=0;i<n;i++)
	{
		for(int j=0;j<i;j++)
			f[i]=min(f[i],f[j]+s[j]*s[j]-2*s[j]*(s[i]-l));
		if(i>0)
			f[i]+=(s[i]-l)*(s[i]-l);
		f[i]=min(f[i],(s[i]-l+1)*(s[i]-l+1));
	}
	cout<<f[n-1]<<endl;
	return 0;
}