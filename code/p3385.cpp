#include <iostream>
#include <array>
#include <queue>
using namespace std;

array< array<long long,2010>,2010 >mp;

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
	mp[0].fill(0x7ffffffffffffffll);
	mp.fill(mp[0]);
	cin>>n>>m;
	for(int i=0;i<m;i++)
	{
		long long u,v,w;
		cin>>u>>v>>w;
		if(w>=0)
		{
			if(mp[u][v]==0)
				mp[u][v]=w;
			else
				mp[u][v]=min(mp[u][v],w);
			if(mp[v][u]==0)
				mp[v][u]=w;
			else
				mp[v][u]=min(mp[v][u],w);
		}
		else
			mp[u][v]=min(mp[u][v],w);
	}
	queue<int> q;
	array<long long,2010> k,d;
	array<bool,2010> isk;
	isk.fill(false);k.fill(0);d.fill(0x7ffffffffffffffll);
	q.push(1);isk[1]=true;k[1]++;d[1]=0;
	while(!q.empty())
	{
		int p=q.front();
		q.pop();isk[p]=false;
		for(int i=1;i<=n;i++)
			if(mp[p][i]!=0x7ffffffffffffffll)
				if(mp[p][i]+d[p]<d[i])
				{
					d[i]=mp[p][i]+d[p];
					if(!isk[i])
					{
						q.push(i);
						k[i]++;
						isk[i]=true;
					}
					if(k[i]>=n)
					{
						cout<<"YES"<<endl;
						return;
					}
				}
	}
	cout<<"NO"<<endl;
	return;
}