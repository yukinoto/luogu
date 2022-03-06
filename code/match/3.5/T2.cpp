#include <iostream>
#include <set>
using namespace std;

class opt{
	public:
		int time,from,to;
		opt(){;}
		opt(int time,int from,int to){this->time=time,this->from=from,this->to=to;}
		bool operator<(const opt&x)const
		{
			return time==x.time?
			(from==x.from?to<x.to:from<x.from)
			:time<x.time;
		}
};

const int MAXN=100001,MAXM=1001,MAXX=3001;

int n,m,x;
int ans[MAXM],whr[MAXM];
int bcj[MAXN],siz[MAXN],status;
bool resetflag=false;

set<opt> func;

int fa(int p)
{
	if(bcj[p]==p)
		return p;
	return bcj[p]=fa(bcj[p]);
}

void merge(int a,int b)
{
	if(fa(a)!=fa(b))
	{
		siz[fa(b)]+=siz[fa(a)];
		bcj[fa(a)]=fa(b);
	}
	return;
}

void reset()
{
	for(int i=1;i<=n;i++)
		bcj[i]=i,siz[i]=1;
	status=0;
	return;
}

void pushto(int t)
{
	if(resetflag)
	{
		resetflag=false;
		reset();
	}
	int bef=status;
	for(auto it=func.lower_bound(opt(status+1,0,0));it!=func.end()&&it->time<=t;++it)
	{
		if(it->time>bef)
		{
			for(int i=bef+1;i<=it->time;i++)
			{
				if(ans[i]<ans[i-1])
				{
					ans[i]=ans[i-1];
					whr[i]=whr[i-1];
				}
				if(ans[i]==ans[i-1]&&whr[i]>whr[i-1])
					whr[i]=whr[i-1];
				if(ans[i]>ans[i-1])
					break;
			}
			bef=it->time;
		}
		merge(it->to,it->from);
		if(siz[fa(it->from)]==ans[it->time]&&whr[it->time]>fa(it->from))
			whr[it->time]=fa(it->from);
		if(siz[fa(it->from)]>ans[it->time])
		{
			ans[it->time]=siz[fa(it->from)];
			whr[it->time]=fa(it->from);
		}
	}
	if(t>bef)
	{
		for(int i=bef+1;i<=t;i++)
		{
			if(ans[i]<ans[i-1])
			{
				ans[i]=ans[i-1];
				whr[i]=whr[i-1];
			}
			if(ans[i]==ans[i-1]&&whr[i]>whr[i-1])
				whr[i]=whr[i-1];
			if(ans[i]>ans[i-1])
				break;
		}
		bef=t;
	}
	status=t;
}

void insert(const opt&o)
{
	func.insert(o);
	if(o.time<=status)
	{
		status=o.time-1;
		resetflag=true;
	}
}

void quest(int t)
{
	if(status<t)
		pushto(t);
	if(ans[t]!=0)
		cout<<whr[t]<<' '<<ans[t]<<'\n';
	else
		cout<<"0\n";
	return;
}

int main()
{
	ios::sync_with_stdio(false);
	cin>>n>>m;
	status=0,resetflag=true;
	for(int i=1;i<=n;i++)
	{
		int c;
		cin>>c;
		for(int j=0;j<c;j++)
		{
			int p,t;
			cin>>p>>t;
			insert(opt(t+1,i,p));
		}
	}
	cin>>x;
	for(int i=0;i<x;i++)
	{
		int op;
		cin>>op;
		if(op==1)
		{
			int t;
			cin>>t;
			quest(t+1);
		}
		if(op==2)
		{
			int a,b,t;
			cin>>a>>b>>t;
			insert(opt(t+1,a,b));
		}
	}
	return 0;
}