#include <iostream>
#include <vector>
#include <queue>
using namespace std;

struct edg{
	int from,to;
	int t1,t2;
	edg(int _from,int _to,int _t1,int _t2)
	{
		from=_from,to=_to,t1=_t1,t2=_t2;
	}
};

/*struct nd{
	int f,t;
	int w;
	bool operator<(const nd&x)const
	{
		return w<x.w;
	}
};*/

int n,k,m;
vector<edg> edge;

void init()
{
	cin>>n>>k>>m;
	for(int i=0;i<m;i++)
	{
		int x,y,t1,t2;
		cin>>x>>y>>t2>>t1;
		edge.push_back(edg(x,y,t1,t2));
	}
	return;
}

class bc{
	private:
		int a[10001];
		int fa(int x)
		{
			if(a[x]==x)
				return x;
			return a[x]=fa(a[x]);
		}
	public:
		bc()
		{
			for(int i=0;i<=10000;i++)
				a[i]=i;
		}
		bool is(int x,int y)
		{
			return fa(x)==fa(y);
		}
		void merge(int x,int y)
		{
			int v=fa(x),w=fa(y);
			if(v!=w)
				a[v]=w;
			return;
		}
};

bool check(int mx)
{
	bc st;
	int cnt=0;
	for(auto i:edge)
	{
		if(!st.is(i.from,i.to)&&i.t2<=mx)
		{
			cnt++;
			st.merge(i.from,i.to);
		}
	}
	for(auto i:edge)
	{
		if(!st.is(i.from,i.to)&&i.t1<=mx)
			st.merge(i.from,i.to);
	}
	if(cnt<k)
		return false;
	for(int i=2;i<=n;i++)
		if(!st.is(1,i))
			return false;
	return true;
}

int fnd(int l,int r)
{
	if(l==r-1)
		return l;
	int mid=(l+r)/2;
	if(check(mid))
		return fnd(l,mid);
	return fnd(mid,r);
}

int main()
{
	init();
	cout<<fnd(0,1000001)+1<<endl;
	return 0;
}