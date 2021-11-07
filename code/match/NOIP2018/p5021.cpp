#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>
using namespace std;

int n,m;
struct node{
	vector<pair<int,int>>sons;
	pair<int,int> fa;
};
node tr[50010];
namespace bdt{
	vector<pair<int,int>>edge[50010];
	bool tkn[50010];
	void build(int root)
	{
		tkn[root]=true;
		for(auto i:edge[root])
		{
			if(!tkn[i.first])
			{
				tr[root].sons.push_back(i);
				build(i.first);
			}
		}
		return;
	}
}

void init()
{
	cin>>n>>m;
	for(int i=0;i<m;i++)
	{
		int a,b,l;
		cin>>a>>b>>l;
		bdt::edge[a].push_back(make_pair(b,l));
		bdt::edge[b].push_back(make_pair(a,l));
	}
	bdt::build(1);
	return;
}

pair<int,int> cst(int root,int l)
{
	if(tr[root].sons.empty())
	{
		if(tr[root].fa.second>=l)
			return make_pair(1,0);
		else
			return make_pair(0,tr[root].fa.second);
	}
	int ans=0;
	vector<int> lth;
	for(auto i:tr[root].sons)
	{
		auto x=cst(i.first,l);
		ans+=x.first;
		if(x.second!=0)
			lth.push_back(x.second);
	}
	sort(lth.begin(),lth.end());
	
}

int check(int l)
{}