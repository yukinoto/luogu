#include <iostream>
#include <vector>
#include <set>
#include <algorithm>
using namespace std;

int n,m;
vector<int> edge[5010];
bool taken[5010];
struct node{
	vector<int>sons;
	int fa;
};
node tr[5010];

namespace part{
	void build(int root)
	{
		for(auto i:edge[root])
		{
			if(i!=tr[root].fa)
			{
				tr[i].fa=root;
				tr[root].sons.push_back(i);
				build(i);
			}
		}
		return;
	}
	void init()
	{
		cin>>n>>m;
		for(int i=0;i<m;i++)
		{
			int x,y;
			cin>>x>>y;
			edge[x].push_back(y);
			edge[y].push_back(x);
		}
		tr[1].fa=-1;
		build(1);
	}
	void work(int root)
	{
		cout<<root<<' ';
		sort(tr[root].sons.begin(),tr[root].sons.end());
		for(auto i:tr[root].sons)
		{
			work(i);
		}
		return;
	}
	void main()
	{
		init();
		work(1);
		return;
	}
}

int main()
{
	part::main();
	return 0;
}