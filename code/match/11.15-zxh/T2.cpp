#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
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
	pt wf[17];
};

node tr[50001];
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

void init()
{
	cin>>n>>m;
	vector<pt> d[n+1];
	for(int i=1;i<n;i++)
	{
		int u,v;long long w;
		cin>>u>>v>>w;
		d[u].push_back(pt(v,w));
		d[v].push_back(pt(u,w));
	}
	build(d);
	for(int i=0;i<m;i++)
		cin>>arm[i];
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

pt p[50001];
bool cmp1(const pt &a,const pt &b)
{
	return a.to==b.to?a.w<b.w:a.to<b.to;
}
bool check(long long w)
{
	for(int i=0;i<m;i++)
		p[i]=jp(arm[i],w);
	sort(p,p+m,cmp1);
	vector<pt> che;
}