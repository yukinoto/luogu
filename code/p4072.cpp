#include <iostream>
#include <algorithm>
#include <cstdlib>
using namespace std;

typedef int Int;

Int n,m;
Int *p,**f;
const Int inf=0x3fffffff;

void del()
{
	delete[]p;
	delete[]f[0];
	delete[]f[1];
	delete[]f;
	return;
}

void init()
{
	cin.sync_with_stdio(false);
	cout.sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);
	cin>>n>>m;
	p=new Int[n];
	f=new Int*[2];
	f[0]=new Int[n],f[1]=new Int[n];
	cin>>p[0];
	for(int i=1;i<n;i++)
	{
		Int x;
		cin>>x;
		p[i]=p[i-1]+x;
		f[1][i]=inf;
	}
	f[1][0]=inf;
	atexit(del);
	return;
}

template<typename T>
class queue{
	private:
		T a[3001];
	public:
		int first,last;
		queue()
		{
			first=last=0;
		}
		void push(const T &x)
		{
			a[last++]=x;
		}
		void popback()
		{
			last--;
		}
		void popfront()
		{
			first++;
		}
		void clear()
		{
			first=last=0;
		}
		bool empty()
		{
			return first>=last;
		}
		int size()
		{
			return last-first;
		}
		T&operator [](int p)
		{
			return a[p];
		}
};

struct pt{
	Int x,y;
};

pt mkpt(Int _x,Int _y)
{
	pt ans;
	ans.x=_x,ans.y=_y;
	return ans;
}

queue<pt> q;

void insert(pt x)
{
	while(q.size()>1)
	{
		if((long long)(q[q.last-1].y-q[q.last-2].y)*(q[q.last-1].x-x.x)<(long long)(q[q.last-1].y-x.y)*(q[q.last-1].x-q[q.last-2].x))
			q.popback();
		else
			break;
	}
	q.push(x);
	return;
}

int e;
Int fnd(int s)
{
	auto f=[&](pt x)
	{
		return x.y-2*p[s]*x.x;
	};
	while(e+1<q.last&&f(q[e+1])<f(q[e]))
		e++;
	return f(q[e]);
}

void work()
{
	for(int j=0;j<n;j++)
		f[0][j]=p[j]*p[j];
	for(int i=1;i<m;i++)
	{
		q.clear();
		e=0;
		insert(mkpt(p[i-1],f[(i&1)^1][i-1]+p[i-1]*p[i-1]));
		for(int j=i;j<n;j++)
		{
			f[i&1][j]=fnd(j)+p[j]*p[j];
			insert(mkpt(p[j],f[(i&1)^1][j]+p[j]*p[j]));
		}
	}
	cout<<f[(m&1)^1][n-1]*m-p[n-1]*p[n-1]<<endl;
	return;
}

int main()
{
	init();
	work();
	return 0;
}
