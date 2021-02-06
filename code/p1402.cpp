#include <stdio.h>
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
		T end()
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
	for(int k=1;k<=n;k++)
		for(int i=1;i<=p;i++)
		{
			scanf("%d",&x);
			if(x==1)
				mp[i].push_back(k);
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



int main()
{
	init();
}
