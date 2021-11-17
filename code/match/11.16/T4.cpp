#include <iostream>
#include <set>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

int n,m,k,t,md;
vector<int> mp[1000001];
int dis[1000001];

void init()
{
	cin>>n>>m>>k>>t;
	for(int i=1;i<=m;i++)
	{
		int x,y;
		cin>>x>>y;
		mp[y].push_back(x);
	}
	queue<int> q;
	q.push(t);
	dis[t]=1;
	while(!q.empty())
	{
		int p=q.front();q.pop();
		for(auto i:mp[p])
		{
			if(dis[i]==0)
			{
				dis[i]=dis[p]+1;
				q.push(i);
				md=max(md,dis[p]);
			}
		}
	}
	return;
}

bool tkn[1000001];

void work()
{
	set<int> st,ro;
	for(int i=1;i<=md+k+1;i++)
		st.insert(i);
	for(int i=0;i<k;i++)
	{
		int p;
		cin>>p;
		if(!tkn[p])
		{
			int tm=*st.lower_bound(dis[p]);
			st.erase(tm),ro.insert(tm);
			tkn[p]=true;
		}
		else
		{
			int tm=(*st.lower_bound(dis[p]))-1;
			ro.erase(tm),st.insert(tm);
			tkn[p]=false;
		}
		cout<<*(--ro.end())<<endl;
	}
	return;
}

int main()
{
	init();
	work();
	return 0;
}