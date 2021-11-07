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

namespace rol{
	pair<int,int> del;
	void build(int root)
	{
		tr[root].sons.clear();
		for(auto i:edge[root])
		{
			if(i!=tr[root].fa&&del!=make_pair(root,i)&&del!=make_pair(i,root))
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
		for(int i=0;i<m;i++)
		{
			int x,y;
			cin>>x>>y;
			edge[x].push_back(y);
			edge[y].push_back(x);
		}
		tr[1].fa=-1;
	}
	int ans[5010]={0x7fffffff},fsk[5010];
	int top=0;
	void work(int root)
	{
		fsk[top++]=root;
		sort(tr[root].sons.begin(),tr[root].sons.end());
		for(auto i:tr[root].sons)
		{
			work(i);
		}
		return;
	}
	bool cmp()
	{
		for(int i=0;i<n;i++)
			if(ans[i]!=fsk[i])
				return ans[i]>fsk[i];
		return false;
	}
	void cpr()
	{
		if(cmp())
			for(int i=0;i<n;i++)
				ans[i]=fsk[i];
		return;
	}
	bool vis[5010];
	vector<pair<int,int>> eg;
	void fr(int root)
	{
		vis[root]=true;
		for(auto i:edge[root])
		{
			if(eg.empty()&&vis[i]&&i!=tr[root].fa)
			{
				eg.push_back(make_pair(root,i));
				while(root!=i)
				{
					eg.push_back(make_pair(root,tr[root].fa));
					root=tr[root].fa;
				}
				return;
			}
			if(!vis[i])
			{
				tr[i].fa=root;
				tr[root].sons.push_back(i);
				fr(i);
			}
		}
		return;
	}
	void main()
	{
		init();
		fr(1);
		for(auto i:eg)
		{
			top=0;
			del=i;
			build(1);
			work(1);
			cpr();
		}
		for(int i=0;i<n;i++)
			cout<<ans[i]<<' ';
		cout<<endl;
		return;
	}
}
int main()
{
	cin>>n>>m;
	if(m==n-1)
		part::main();
	else
		rol::main();
	return 0;
}