#include <stdio.h>
#include <vector>
using namespace std;

namespace func{
	void init();
	void mkt(vector<int>*,int);
	void swap(int&,int&);
}
namespace map{
	int n,m;
	struct edge{
		int v1,v2;
	};
	edge e[300000];
	struct node{
		int father[20],deepth,t;
		vector<int>son;
	};
	node tr[300000];
	struct player{
		int from,to;
	};
	player py[300000];
}
namespace lca{
	void pre_dfs(int);
	int father(int,int);
	int skip(int,int);
	int lca(int,int);
}
namespace work{
	int ans[300000];
	vector<int>* fuck_ccf(int);
}

int main()
{
	func::init();
	vector<int>* pt=work::fuck_ccf(1);
	delete pt;
}

namespace func{
	void init()
	{
		scanf("%d%d",&map::n,&map::m);
		vector<int> *mp=new vector<int>[300000];
		for(int i=1;i<map::n;i++)
		{
			int x,y;
			scanf("%d%d",&x,&y);
			mp[x].push_back(y);
			mp[y].push_back(x);
		}
		mkt(mp,1);
		for(int i=1;i<=map::n;i++)
			scanf("%d",&map::tr[i].t);
		for(int i=1;i<=map::m;i++)
			scanf("%d%d",&map::py[i].from,&map::py[i].to);
		lca::pre_dfs(1);
		delete[] mp;
	}
	void mkt(vector<int>*mp,int root)
	{
		for(vector<int>::iterator it=mp[root].begin();it!=mp[root].end();it++)
		{
			map::tr[root].son.push_back(*it);
			map::tr[*it].father[0]=root;
			mkt(mp,*it);
		}
		return;
	}
	void swap(int &a,int &b)
	{
		int t=a;
		a=b;
		b=t;
		return;
	}
}

namespace lca{
	void pre_dfs(int root)
	{
		for(vector<int>::iterator it=map::tr[root].son.begin();it!=map::tr[root].son.end();it++)
		{
			map::tr[*it].deepth=map::tr[root].deepth+1;
			pre_dfs(*it);
		}
		return;
	}
	int father(int root,int times)
	{
		if(map::tr[root].father[times]!=0)
			return map::tr[root].father[times];
		if((1<<times)>map::tr[root].deepth)
			return 0;
		return map::tr[root].father[times]=father(father(root,times-1),times-1);
	}
	int skip(int root,int step)
	{
		for(int i=0;step!=0;i++)
		{
			if((step&1)==1)
				root=father(root,i);
			step<<=1;
		}
		return root;
	}
	int lca(int l,int r)
	{
		if(map::tr[l].deepth<map::tr[r].deepth)
			func::swap(l,r);
		l=skip(l,map::tr[l].deepth-map::tr[r].deepth);
		for(int i=19;i>=0;i--)
			if(father(l,i)!=father(r,i))
			{
				l=father(l,i);
				r=father(r,i);
			}
		return father(l,0);
	}
}

namespace work{
	vector<int>* fuck_ccf(int root)
	{
		
	}
}
