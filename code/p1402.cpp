#include <stdio.h>
#include <string.h>
#include <vector>
using namespace std;

int n,q,p;
vector<int> mp[410];

template <typename T>
class queue{
	private:
		class node{
			public:
				T x;
				node *nxt;
				node(const T &_x,node *_nxt)
				{
					x=_x;
					nxt=_nxt;
				}
				node(node *nxt)
				{
					nxt=_nxt;
				}
				node()
				{
					nxt=nullptr;
				}
		};
		node *begin,*end;
	public:
		queue()
		{
			begin=end=nullptr;
		}
		inline bool empty()
		{
			return end==nullptr;
		}
		void pop()
		{
			node *pt=end->nxt;
			delete end;
			end=pt;
			return;
		}
		void push(const T &x)
		{
			begin=begin->nxt=new node(x,nullptr);
			return;
		}
		T back()
		{
			return end->x;
		}
		~queue()
		{
			while(!empty())
				pop();
			return;
		}
};

void init()
{
	int x;
	scanf("%d%d%d",&n,&p,&q);
	for(int i=1;i<=p;i++)
		mp[0].push_back(i);
	for(int i=p+n*2+1;i<=p+n*2+q;i++)
		mp[i].push_back(p+n*2+q+1);
	for(int k=1;k<=n;k++)
		for(int i=1;i<=p;i++)
		{
			scanf("%d",&x);
			if(x==1)
				mp[i].push_back(k+p);
		}
	for(int k=1;k<=n;k++)
	{
		mp[q+k].push_back(q+n+k);
		for(int i=1;i<=q;i++)
		{
			scanf("%d",&x);
			if(x==1)
				mp[q+n+k].push_back(n*2+p+i);
		}
	}
}

int deepth[410];

bool bfs()
{
	memset(deepth,0,sizeof(deepth));
	queue<int> q;
	q.push(0);
	deepth[0]=1;
	while(!q.empty())
	{
		int root=q.back();
		for(auto i:mp[root])
		{
			if(deepth[i]==0)
			{
				deepth[i]=deepth[root]+1;
				q.push(i);
			}
		}
	}
	return deepth[p+q+n*2+1]!=0;
}



int main()
{
	init();
}
