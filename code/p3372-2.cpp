#include <stdio.h>
#include <algorithm>
using namespace std;

int n,m,num[100010];

#define a num
typedef long long tpe;
class tree{
	protected:
		int l,r;
		class node{
			protected:
				node *ls,*rs;
				int l,r;//[)
				tpe sum,tag;
			public:
				node(int left,int right)
				{
					l=left,r=right;
					if(l==r-1)
					{
						ls=rs=nullptr;
						sum=a[l];
						tag=0;
						return;
					}
					int mid=(l+r)/2;
					if(mid>l)
						ls=new node(left,mid);
					else
						ls=nullptr;
					if(r>mid)
						rs=new node(mid,right);
					else
						rs=nullptr;
					sum=ls->sum+rs->sum;
					tag=0;
					return;
				}
				~node()
				{
					if(ls!=nullptr)
						delete ls;
					if(rs!=nullptr)
						delete rs;
					return;
				}
				void pushdown()
				{
					if(ls!=nullptr)
					{
						ls->tag+=this->tag;
						ls->sum+=(ls->r-ls->l)*this->tag;
					}
					if(rs!=nullptr)
					{
						rs->tag+=this->tag;
						rs->sum+=(rs->r-rs->l)*this->tag;
					}
					this->tag=0;
				}
				void add(int left,int right,int x)
				{
					if(left>=r||right<=l)
						return;
					if(left<=l&&right>=r)
					{
						this->tag+=x;
						this->sum+=(r-l)*x;
						return;
					}
					if(tag!=0)
						this->pushdown();
					this->sum=0;
					if(ls!=nullptr)
					{
						ls->add(left,right,x);
						this->sum+=ls->sum;
					}
					if(rs!=nullptr)
					{
						rs->add(left,right,x);
						this->sum+=rs->sum;
					}
					return;
				}
				tpe quest(int left,int right)
				{
					if(left>=r||right<=l)
						return 0;
					if(left<=l&&right>=r)
						return this->sum;
					if(this->tag!=0)
						this->pushdown();
					tpe ans=0;
					if(ls!=nullptr)
						ans+=ls->quest(left,right);
					if(rs!=nullptr)
						ans+=rs->quest(left,right);
					return ans;
				}
		};
		node *root;
	public:
		tree()
		{
			//flexible
			l=0,r=n;
			root=new node(l,r);
		}
		~tree()
		{
			delete root;
			return;
		}
		void add(int left,int right,int x)
		{
			root->add(left,right,x);
			return;
		}
		tpe quest(int left,int right)
		{
			return root->quest(left,right);
		}
};

int main()
{
	scanf("%d%d",&n,&m);
	for(int i=0;i<n;i++)
		scanf("%d",num+i);
	tree *tr=new tree();
	for(int i=0;i<m;i++)
	{
		static int f;
		scanf("%d",&f);
		if(f==1)
		{
			static int l,r,x;
			scanf("%d%d%d",&l,&r,&x);
			tr->add(l-1,r,x);
		}
		if(f==2)
		{
			static int l,r;
			scanf("%d%d",&l,&r);
			printf("%lld\n",tr->quest(l-1,r));
		}
	}
	return 0;
}
