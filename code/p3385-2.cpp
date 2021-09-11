#include <iostream>
#include <vector>
#include <utility>
#include <queue>
#include <array>
using namespace std;

void work();

int main()
{
	int t;
	cin>>t;
	for(int i=0;i<t;i++)
		work();
	return 0;
}

void work()
{
	int n,m;
	cin>>n>>m;
	vector<pair<int,long long> >edge[2010];
	for(int i=0;i<m;i++)
	{
		long long u,v,w;
		cin>>u>>v>>w;
		if(w>=0)
		{
			edge[u].push_back(make_pair(v,w));
			edge[v].push_back(make_pair(u,w));
		}
		else
			edge[u].push_back(make_pair(v,w));
	}
	queue<int>q;
	array<bool,2010>isk;
	array<int,2010>k;
	array<long long,2010>dis;
	isk.fill(false),k.fill(0);dis.fill(0x3ffffffffffll);
	q.push(1),isk[1]=true,k[1]++;
	dis[1]=0;
	while(!q.empty())
	{
		int p=q.front();q.pop();
		isk[p]=false;
		for(int i=0;i<edge[p].size();i++)
			if(dis[p]+edge[p][i].second<dis[edge[p][i].first])
			{
				dis[edge[p][i].first]=edge[p][i].second+dis[p];
				if(isk[edge[p][i].first]==false)
				{
					isk[edge[p][i].first]=true;
					q.push(edge[p][i].first);
					k[edge[p][i].first]++;
					if(k[edge[p][i].first]>n)
					{
						cout<<"YES"<<endl;
						return;
					}
				}
			}
	}
	cout<<"NO"<<endl;
	return;
}