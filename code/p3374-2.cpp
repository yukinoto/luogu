#include <iostream>
using namespace std;

const int MAXN=500001;

int lowbit(int x)
{
	return x&(-x);
}

int n;
long long a[MAXN];

void add(int p,int x)
{
	while(p<=n)
	{
		a[p]+=x;
		p+=lowbit(p);
	}
	return;
}

long long pre(int x)
{
	long long ans=0;
	while(x>0)
	{
		ans+=a[x];
		x-=lowbit(x);
	}
	return ans;
}

long long range(int l,int r)
{
	return pre(r-1)-pre(l-1);
}

void set(int p,int x)
{
	add(p,x-range(p,p+1));
	return;
}

//#define DEBUG

int main()
{
	int m;
	cin>>n>>m;
	for(int i=1;i<=n;i++)
	{
		int x;
		cin>>x;
		set(i,x);
#ifdef DEBUG
		cerr<<range(i,i+1)<<endl;
#endif
	}
	for(int i=1;i<=m;i++)
	{
		int op;
		cin>>op;
		if(op==1)
		{
			int x,k;
			cin>>x>>k;
			add(x,k);
#ifdef DEBUG
			cerr<<range(x,x+1)<<endl;
#endif
		}
		if(op==2)
		{
			int l,r;
			cin>>l>>r;
			++r;
			cout<<range(l,r)<<'\n';
		}
	}
	cout.flush();
	return 0;
}