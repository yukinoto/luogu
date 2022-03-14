#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>
using namespace std;

int n;
vector<pair<int,int>> mp[500010];
bool tkn[500010];

int fa[500010];
vector<pair<int,int>> sons[500010];

void build(int root)
{
	tkn[root]=true;
	for(auto i:mp[root])
	{
		if(!tkn[i.first])
		{
			sons[root].emplace_back(i);
			fa[i.first]=root;
			build(i.first);
		}
	}
	return;
}

long long ans=0;

long long dfs(int root)
{
	if(sons[root].empty())
		return 0;
	vector<long long> lth;
	long long l=0;
	for(auto i:sons[root])
	{
		lth.push_back(dfs(i.first)+i.second);
		l=max(l,lth.back());
	}
	for(auto i:lth)
		ans+=l-i;
	return l;
}

int main()
{
	cin>>n;
	int s;
	cin>>s;
	for(int i=1;i<n;i++)
	{
		int a,b,t;
		cin>>a>>b>>t;
		mp[a].emplace_back(b,t),mp[b].emplace_back(a,t);
	}
	build(s);
	dfs(s);
	cout<<ans<<endl;
	return 0;
}