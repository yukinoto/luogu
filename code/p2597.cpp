#include <iostream>
#include <vector>
#include <queue>
#include <cstring>
using namespace std;

namespace tree{
	int n;
	int f[65535][17],deepth[65535];
	vector<int>sons[65535];
	int fa(int root,int b)
	{
		if(f[root][b]!=-1)
			return f[root][b];
		return f[root][b]=fa(fa(root,b-1),b-1);
	}
	int skip(int root,int step)
	{
		int x=16;
		while(x>=0)
		{
			if((1<<x)<=step)
			{
				root=fa(root,x);
				step-=(1<<x);
			}
			x--;
		}
		return root;
	}
	int lca(int a,int b)
	{
		if(deepth[a]>deepth[b])
			a^=b^=a^=b;
		b=skip(b,deepth[b]-deepth[a]);
		if(a==b)
			return a;
		for(int i=16;i>=0;i--)
		{
			if((1<<i)<=deepth[a]&&fa(a,i)!=fa(b,i))
			{
				a=fa(a,i),b=fa(b,i);
			}
		}
		return fa(a,0);
	}
	void link(int root,int father)
	{
		f[root][0]=father;
		deepth[root]=deepth[father]+1;
		sons[father].push_back(root);
	}
	int s[65535];
	int size(int root)
	{
		if(s[root]!=0)
			return s[root];
		if(sons[root].size()==0)
			return s[root]=1;
		for(int i=0;i<sons[root].size();i++)
			s[root]+=size(sons[root][i]);
		return ++s[root];
	}
}

namespace mp{
	int n;
	vector<int>mp[65535];
	int idg[65535];
}
;
namespace anti{
	int n;
	vector<int>mp[65535];
}

void init()
{
	memset(tree::f,-1,sizeof(tree::f));
	cin>>mp::n;
	anti::n=tree::n=mp::n;
	for(int i=1;i<=mp::n;i++)
	{
		int x;
		cin>>x;
		while(x!=0)
		{
			mp::mp[x].push_back(i);
			mp::idg[i]++;
			anti::mp[i].push_back(x);
			cin>>x;
		}
	}
	return;
}

void build()
{
	queue<int> q;
	for(int i=1;i<=mp::n;i++)
	{
		if(mp::idg[i]==0)
			q.push(i);
	}
	while(!q.empty())
	{
		int p=q.front();
		q.pop();
		for(auto i:mp::mp[p])
		{
			mp::idg[i]--;
			if(mp::idg[i]==0)
				q.push(i);
		}
		int dm;
		if(anti::mp[p].size()==0)
			dm=0;
		else if(anti::mp[p].size()==1)
			dm=anti::mp[p][0];
		else
		{
			dm=tree::lca(anti::mp[p][0],anti::mp[p][1]);
			for(int i=2;i<anti::mp[p].size();i++)
				dm=tree::lca(dm,anti::mp[p][i]);
		}
		tree::link(p,dm);
	}
}

void output()
{
	for(int i=1;i<=mp::n;i++)
		cout<<tree::size(i)-1<<endl;
	return;
}

int main()
{
	init();
	build();
	output();
	return 0;
}
