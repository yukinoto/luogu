#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>
#include <deque>
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
	ma=ma/m+2;
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
	vector<int> lth;
	for(auto i:tr[root].sons)
	{
		auto x=cst(i.first,l);
		ans+=x.first;
		if(x.second!=0)
			lth.push_back(x.second);
	}
	if(lth.size()==1)
	{
		if(lth[0]+tr[root].fa.second<l)
			return make_pair(ans,lth[0]+tr[root].fa.second);
		else
			return make_pair(ans+1,0);
	}
	sort(lth.begin(),lth.end());
	deque<int> wst;
	int fnt=0,bac=lth.size()-1;
	for(;fnt<bac;fnt++)
	{
		if(lth[fnt]+lth[bac]<l&&(wst.empty()||lth[fnt]+wst.back()<l))
		{
			wst.push_front(lth[fnt]);
		}
		else
		{
			if(lth[fnt]+lth[bac]>=l)
			{
				while(bac-1>fnt&&lth[bac-1]+lth[fnt]>=l)
					bac--;
				ans++;
				bac--;
			}
			else
			{
				ans++;
				wst.pop_back();
			}
		}
	}
	if(fnt==bac)
	{
		if(!wst.empty()&&lth[fnt]+wst.back()>=l)
		{
			ans++;
			wst.pop_back();
		}
		else
			wst.push_front(lth[fnt++]);
	}
	int ap=0;
	while(!wst.empty())
	{
		ap=max(ap,wst.back());
		wst.pop_back();
	}
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
	cout<<work(mi,ma)<<endl;
	return 0;
}