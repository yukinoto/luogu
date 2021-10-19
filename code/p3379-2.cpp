#include <iostream>
#include <vector>
#include <cstring>
#include <algorithm>
using namespace std;

class tr{
	private:
		class node{
			public:
				int fa;
				int son,top,size,dep;
				vector<int>sons;
				void init(int root,int _fa,vector<int>&sns,bool *tb)
				{
					fa=_fa;
					tb[root]=true;
					for(int i:sns)
					{
						if(!tb[i])
							sons.push_back(i);
					}
					son=dep=top=0;
					size=1;
					return;
				}
		};
		node *a;
		void build(int root,int fa,vector<int>*mp,bool*tb)
		{
			static int cnt=0;
			tb[root]=true;
			a[root].init(root,fa,mp[root],tb);
			a[root].dep=a[fa].dep+1;
			for(int i:a[root].sons)
			{
				build(i,root,mp,tb);
				if(a[root].son==0||a[a[root].son].size<a[i].size)
					a[root].son=i;
				a[root].size+=a[i].size;
			}
			return;
		}
		void dfs(int root,int top)
		{
			a[root].top=top;
			if(a[root].son!=0)
				dfs(a[root].son,top);
			for(int i:a[root].sons)
				if(i!=a[root].son)
					dfs(i,i);
			return;
		}
	public:
		void init(int n,int root,vector<int>*mp)
		{
			bool *tb=new bool[n+1];
			a=new node[n+1];
			memset(tb,false,sizeof(tb));
			build(root,root,mp,tb);
			dfs(root,root);
			delete[]tb;
		}
		int quest(int x,int y)
		{
			while(a[x].top!=a[y].top)
			{
				if(a[a[x].top].dep<a[a[y].top].dep)
					swap(x,y);
				x=a[a[x].top].fa;
			}
			if(a[x].dep<a[y].dep)
				swap(x,y);
			return y;
		}
		~tr()
		{
			delete[]a;
		}
};

int n,m;

tr t;

void init()
{
	cin.sync_with_stdio(false),cout.sync_with_stdio(false);
	int s;
	cin>>n>>m>>s;
	vector<int>*mp=new vector<int>[n+1];
	for(int i=1;i<n;i++)
	{
		int x,y;
		cin>>x>>y;
		mp[x].push_back(y);
		mp[y].push_back(x);
	}
	t.init(n,s,mp);
	return;
}

void work()
{
	for(int i=0;i<m;i++)
	{
		int x,y;
		cin>>x>>y;
		cout<<t.quest(x,y)<<endl;
	}
	return;
}

int main()
{
	init();
	work();
	return 0;
}
