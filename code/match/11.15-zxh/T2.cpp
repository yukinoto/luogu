#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <cstdlib>
using namespace std;

struct pt{
	int to;
	long long w;
	pt(){;}
	pt(int _to,long long _w)
	{
		to=_to,w=_w;
	}
};

struct node{
	pt fa;
	vector<pt> sons;
	vector<int>leaf;
	pt wf[17];
	int dep;
};

node tr[50001];

class xds{
	private:
	class node{
		private:
		bool value;
		bool tag;
		node *lc,*rc;
		void pushtag(int l,int r)
		{
			if(!tag)
				return;
			if(l==r-1)
			{
				tag=false;
				return;
			}
			lc->value=rc->value=value;
			lc->tag=rc->tag=true;
			tag=false;
		}
		public:
		node(int l,int r)
		{
			if(l==r-1)
			{
				lc=rc=nullptr;
				value=tag=false;
				return;
			}
			int mid=(l+r)/2;
			lc=new node(l,mid),rc=new node(mid,r);
			value=tag=false;
			return;
		}
		void set(int l,int r,int left,int right,bool x)
		{
			if(l>=right||r<=left)
				return;
			if(l>=left&&r<=right)
			{
				value=x;
				tag=true;
				return;
			}
			int mid=(l+r)/2;
			pushtag(l,r);
			lc->set(l,mid,left,right,x),rc->set(mid,r,left,right,x);
			value=lc->value&&rc->value;
			return;
		}
		bool quest(int l,int r,int left,int right)
		{
			if(left>=r||right<=l)
				return true;
			if(left<=l&&right>=r)
				return value;
			int mid=(l+r)/2;
			pushtag(l,r);
			return lc->quest(l,mid,left,right)&&rc->quest(mid,r,left,right);
		}
		~node()
		{
			delete lc,rc;
		}
	};
	node *root;
	int l,r;
	public:
	xds(int _l,int _r)
	{
		l=_l,r=_r;
		root=new node(l,r);
	}
	~xds()
	{
		delete root;
	}
	void set(int left,int right,bool x)
	{
		root->set(l,r,left,right,x);
	}
	bool quest(int left,int right)
	{
		return root->quest(l,r,left,right);
	}
};

int n,m;
int arm[50001];

void build(vector<pt> *d)
{
	tr[1].fa=pt(1,0);
	queue<int>q;
	q.push(1);
	while(!q.empty())
	{
		int p=q.front();q.pop();
		for(auto i:d[p])
		{
			if(i.to!=tr[p].fa.to)
			{
				tr[p].sons.push_back(i);
				tr[i.to].fa=pt(p,i.w);
				q.push(i.to);
			}
		}
	}
	for(int i=1;i<=n;i++)
	{
		tr[i].wf[0]=tr[i].fa;
		for(int j=1;j<17;j++)
			tr[i].wf[j]=pt(-1,-1);
	}
	return;
}

xds *stp;

void del()
{
	delete stp;
}

int dfn[50001],rnk[50001],siz[50001];
void dfs1(int root)
{
	static int cnt=1;
	siz[root]=1;
	dfn[root]=1;
	rnk[1]=1;
	for(auto i:tr[root].sons)
	{
		dfn[i.to]=++cnt;
		rnk[cnt]=i.to;
		dfs1(i.to);
		siz[root]+=siz[i.to];
		for(auto j:tr[i.to].leaf)
		{
			tr[root].leaf.push_back(j);
		}
	}
	if(siz[root]==1)
		tr[root].leaf.push_back(root);
	return;
}

void init()
{
	cin>>n;
	vector<pt> d[n+1];
	for(int i=1;i<n;i++)
	{
		int u,v;long long w;
		cin>>u>>v>>w;
		d[u].push_back(pt(v,w));
		d[v].push_back(pt(u,w));
	}
	build(d);
	cin>>m;
	for(int i=0;i<m;i++)
		cin>>arm[i];
	dfs1(1);
	stp=new xds(1,n+1);
	atexit(del);
	return;
}

pt fw(int root,int sp)
{
	if(tr[root].wf[sp].to!=-1)
		return tr[root].wf[sp];
	pt a1=fw(root,sp-1),a2=fw(a1.to,sp-1);
	return tr[root].wf[sp]=pt(a2.to,a1.w+a2.w);
}

pt jp(int root,long long w)
{
	if(root==1)
		return pt(root,w);
	for(int i=16;i>=0;i--)
	{
		pt x=fw(root,i);
		if(x.w<=w&&x.to!=1)
		{
			w-=x.w;
			root=x.to;
		}
	}
	return pt(root,w);
}

void sett(int root,bool x)
{
	stp->set(rnk[root],rnk[root]+siz[root],x);
	return;
}
bool questt(int root)
{
	for(auto i:tr[root].leaf)
	{
		if(!stp->quest(rnk[i],rnk[i]+1))
			return false;
	}
	return true;
}

pt p[50001];
bool cmp1(const pt &a,const pt &b)
{
	return a.to==b.to?a.w<b.w:a.to<b.to;
}
bool cmp2(const pt &a,const pt &b)
{
	return a.w==b.w?a.to<b.to:a.w<b.w;
}
bool check(long long w)
{
	for(int i=0;i<m;i++)
		p[i]=jp(arm[i],w);
	sort(p,p+m,cmp1);
	vector<long long> che;
	stp->set(1,n+1,false);
	for(int i=0;i<m;i++)
	{
		if(!questt(p[i].to))
		{
			sett(p[i].to,true);
		}
		else
		{
			if(tr[p[i].to].fa.to==1)
			{
				che.push_back(p[i].w-tr[p[i].to].fa.w);
			}
		}
	}
	sort(tr[1].sons.begin(),tr[1].sons.end(),cmp2);
	sort(che.begin(),che.end());
	int npt=0;
	for(auto i:tr[1].sons)
	{
		if(!questt(i.to))
		{
			while(npt<che.size()&&che[npt]<i.w)
				npt++;
			if(npt==che.size())
				break;;
			sett(i.to,true);
			npt++;
		}
	}
	for(int i=1;i<=n;i++)
		if(tr[i].sons.size()==0&&!questt(i))
			return false;
	return true;
}

long long fnd(long long l,long long r)
{
	if(l==r-1)
		return l;
	long long mid=(l+r)/2;
	if(check(mid))
		return fnd(l,mid);
	return fnd(mid,r);
}

int main()
{
	init();
	//cout<<check(1)<<endl;
	if(m<tr[1].sons.size())
	{
		cout<<-1<<endl;
		return 0;
	}
	//cout<<check(8)<<endl;
	cout<<fnd(0,50000000000001ll)+1<<endl;
	return 0;
}