#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <cstdlib>
#include <set>
using namespace std;

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

struct pt{
	int to;
	long long w;
	pt(){;}
	pt(int _to,long long _w)
	:to(_to),w(_w){;}
};

struct node{
	pt fa;
	vector<pt> sons;
	pt wf[17];
};

node tr[50001];

void build(int root,vector<pt> *edge)
{
	queue<int>q;
	q.push(root);
	tr[root].fa=(pt(root,0));
	//tr[root].wf[0]=tr[root].fa;
	while(!q.empty())
	{
		int p=q.front();q.pop();
		for(auto i:edge[p])
		{
			if(i.to!=tr[p].fa.to)
			{
				q.push(i.to);
				tr[i.to].fa=pt(p,i.w);
				tr[p].sons.push_back(i);
				//tr[i.to].wf[0]=tr[i.to].fa;
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

pt jr(int root,int sep)
{
	if(tr[root].wf[sep].to!=-1)
		return tr[root].wf[sep];
	pt a=jr(root,sep-1),b=jr(a.to,sep-1);
	return tr[root].wf[sep]=pt(b.to,a.w+b.w);
}

pt rolup(int root,long long w)
{
	for(int i=16;i>=0;i--)
	{
		pt x=jr(root,i);
		if(x.to!=1&&x.w<=w)
			root=x.to,w-=x.w;
	}
	return pt(root,w);
}

int dfn[50001]/*,rnk[50001]*/,siz[50001];
int dep[50001];
void dfs1(int root)
{
	static int cnt=0;
	dep[root]=dep[tr[root].fa.to]+1;
	if(tr[root].sons.empty())
	{
		dfn[root]=++cnt;
		//rnk[cnt]=root;
		siz[root]=1;
		return;
	}
	dfn[root]=0x7fffffff;
	for(auto i:tr[root].sons)
	{
		dfs1(i.to);
		siz[root]+=siz[i.to];
		dfn[root]=min(dfn[root],dfn[i.to]);
	}
	return;
}

bool cmp1(const pt&a,const pt&b)
{
	if(dep[a.to]!=dep[b.to])
		return dep[a.to]>dep[b.to];
	return a.w==b.w?a.to<b.to:a.w<b.w;
}
bool cmp2(const pt&a,const pt&b)
{
	return a.w==b.w?a.to<b.to:a.w<b.w;
}
bool cmp3(const pt&a,const pt&b)
{
	return a.w-tr[a.to].fa.w>b.w-tr[b.to].fa.w;
}
xds *ctr;
void del()
{
	delete ctr;
}
int arm[50001];
void init()
{
	cin>>n;
	vector<pt> edge[n+1];
	for(int i=1;i<n;i++)
	{
		int u,v;long long w;
		cin>>u>>v>>w;
		edge[u].push_back(pt(v,w));
		edge[v].push_back(pt(u,w));
	}
	build(1,edge);
	dfs1(1);
	ctr=new xds(1,n+1);
	atexit(del);
	cin>>m;
	for(int i=0;i<m;i++)
		cin>>arm[i];
	sort(tr[1].sons.begin(),tr[1].sons.end(),cmp2);
	return;
}


void sett(int root,bool x)
{
	ctr->set(dfn[root],dfn[root]+siz[root],x);
	return;
}

bool questt(int root)
{
	return ctr->quest(dfn[root],dfn[root]+siz[root]);
}

bool check(long long w)
{
	sett(1,false);
	vector<pt> p;
	for(int i=0;i<m;i++)
		p.push_back(rolup(arm[i],w));
	sort(p.begin(),p.end(),cmp1);
	vector<pt> rs;
	for(auto i:p)
	{
		if(dep[i.to]>2)
			sett(i.to,true);
		else
			rs.push_back(i);
	}
	vector<pt>st;
	multiset<long long>pu;
	for(auto i:rs)
	{
		if(!questt(i.to))
		{
			sett(i.to,true);
			st.push_back(i);
		}
		else
		{
			if(i.w>tr[i.to].fa.w)
				pu.insert(i.w-tr[i.to].fa.w);
		}
	}
	sort(st.begin(),st.end(),cmp3);
	for(auto i:st)
	{
		auto it=pu.lower_bound(tr[i.to].fa.w);
		if(it!=pu.end()&&i.w-tr[i.to].fa.w>*it)
		{
			pu.erase(it);
			pu.insert(i.w-tr[i.to].fa.w);
		}
	}
	auto it=pu.begin();
	for(auto i:tr[1].sons)
	{
		if(!questt(i.to))
		{
			while(it!=pu.end()&&*it<i.w)
				++it;
			if(it==pu.end())
				break;
			sett(i.to,true);
			++it;
		}
	}
	return questt(1);
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
	if(m<tr[1].sons.size())
	{
		cout<<-1<<endl;
		return 0;
	}
	cout<<fnd(0,50000000000001ll)+1<<endl;
	return 0;
}