#include <iostream>
#include <vector>
using namespace std;

class xds{
	private:
		class node{
			public:
				int num,tag;
				node *lc,*rc;
				node(int l,int r,int *a)
				{
					if(l==r-1)
					{
						lc=rc=nullptr;
						num=a[l];
						tag=0;
					}
					else
					{
						int mid=(l+r)/2;
						lc=new node(l,mid,a);
						rc=new node(mid,r,a);
						num=lc->num+rc->num;
						tag=0;
					}
					return;
				}
				~node()
				{
					delete lc,rc;
				}
				void pushdown(int l,int r)
				{
					if(lc==nullptr)
						return;
					int mid=(l+r)/2;
					lc->tag+=tag,rc->tag+=tag;
					lc->num+=tag*(mid-l),rc->num+=tag*(r-mid);
					tag=0;
					return;
				}
			public:
				void add(int l,int r,int left,int right,int x)
				{
					if(l>=right||r<=left)
						return;
					if(l>=left&&r<=right)
					{
						num+=x*(r-l);
						tag+=x;
						return;
					}
					pushdown(l,r);
					int mid=(l+r)/2;
					lc->add(l,mid,left,right,x);
					rc->add(mid,r,left,right,x);
					num=lc->num+rc->num;
					return;
				}
				int quest(int l,int r,int left,int right)
				{
					if(l>=right||r<=left)
						return 0;
					if(l>=left&&r<=right)
						return num;
					pushdown(l,r);
					int mid=(l+r)/2;
					return lc->quest(l,mid,left,right)+rc->quest(mid,r,left,right);
				}
		};
		node *root;
		int l,r;
	public:
		xds(int _l,int _r,int *a)
		{
			l=_l,r=_r;
			root=new node(l,r,a);
		}
		void add(int left,int right,int x)
		{
			root->add(l,r,left,right,x);
		}
		int quest(int left,int right)
		{
			return root->quest(l,r,left,right);
		}
};

vector<pair<int,int>>*edges;

class tr{
	public:
		class node{
			public:
				int fa,dfn,top,son,size;
				vector<int>sons;
		};
		node *nd;
		int *rnk;
		void build(int root)
		{
			nd[root].size=1;
			int rs=root;
			for(auto i:edges[root])
			{
				if(i.first!=nd[root].fa)
				{
					nd[root].sons.push_back(i.first);
					nd[i.first].fa=root;
					build(i.first);
					nd[root].size+=nd[i.first].size;
					if(rs==root||nd[rs].size<nd[i.first].size)
						rs=i.first;
				}
			}
		}
};