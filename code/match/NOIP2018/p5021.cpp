#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>
#include <set>
using namespace std;

int n,m;
int mi=0x7fffffff,ma;
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
				tr[i.first].fa=make_pair(root,i.second);
				build(i.first);
			}
		}
		return;
	}
}

void init()
{
	cin>>n>>m;
	for(int i=1;i<n;i++)
	{
		int a,b,l;
		cin>>a>>b>>l;
		bdt::edge[a].push_back(make_pair(b,l));
		bdt::edge[b].push_back(make_pair(a,l));
		ma+=l;
		mi=min(mi,l);
	}
	tr[1].fa=make_pair(-1,0);
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
	multiset<int>lth;
	for(auto i:tr[root].sons)
	{
		auto x=cst(i.first,l);
		ans+=x.first;
		if(x.second!=0)
			lth.insert(x.second);
	}
	vector<int>asq;
	while(lth.size()>1)
	{
		decltype(lth.begin()) i;
		for(i=lth.begin();i!=lth.end();i++)
		{
			auto it=lth.lower_bound(l-*i);
			if(it==i)
				it++;
			if(it==lth.end())
			{
				asq.push_back(*i);
			}
			else
			{
				ans++;
				int tmp=*it;
				lth.erase(lth.begin(),++i);
				lth.erase(lth.find(tmp));
				break;
			}
		}
		if(i==lth.end())
			lth.clear();
	}
	while(!lth.empty())
	{
		asq.push_back(*lth.begin());
		lth.erase(lth.begin());
	}
	int ap=0;
	for(int i:asq)
		ap=max(ap,i);
	if(ap+tr[root].fa.second>=l)
		return make_pair(ans+1,0);
	else
		return make_pair(ans,ap+tr[root].fa.second);
}

int check(int l)
{
	return cst(1,l).first;
}

int work(int left,int right)
{
	if(left==right-1)
		return left;
	int mid=(left+right)/2;
	if(check(mid)>=m)
		return work(mid,right);
	else
		return work(left,mid);
}

int main()
{
	init();
	cout<<work(mi,ma+2)<<endl;
	return 0;
}