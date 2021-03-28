#include <cstdio>
#include <vector>
using namespace std;

template<typename T>//[)
class xds{
	private:
		class node{
			private:
				T num,tag;
				node *lc,*rc;
				T getnum()
				{
					if(this==nullptr)
						return 0;
					return num;
				}
				void refresh()
				{
					num=lc->getnum()+rc->getnum();
					return;
				}
				void getup(const T &uptag,const int &left,const int &right)
				{
					if(this==nullptr)
						return;
					tag+=uptag;
					num+=(right-left)*uptag;
					return;
				}
				void pushdown(const int &left,const int &right)
				{
					int mid=(left+right)/2;
					lc->getup(tag,left,mid),rc->getup(tag,mid,right);
					tag=0;
					return;
				}
			public:
				node(const T *base,const int &left,const int &right)
				{
					tag=0;
					lc=rc=nullptr;
					if(left==right-1)
					{
						num=base[left];
						return;
					}
					int mid=(left+right)/2;
					if(mid>left)
						lc=new node(base,left,mid);
					if(right>mid)
						rc=new node(base,mid,right);
					refresh();
				}
				T quest(const int &l,const int &r,const int &left,const int &right)
				{
					if(this==nullptr)
						return 0;
					if(l<=left&&r>=right)
						return num;
					pushdown(left,right);
					if(l>=right||r<=left)
						return 0;
					int mid=(left+right)/2;
					return lc->quest(l,r,left,mid)+rc->quest(l,r,mid,right);
				}
				void add(const int &l,const int &r,const T &x,const int &left,const int &right)
				{
					if(this==nullptr)
						return;
					if(l<=left&&r>=right)
					{
						getup(x,left,right);
						return;
					}
					if(l>=right||r<=left)
						return;
					int mid=(left+right)/2;
					pushdown(left,right);
					lc->add(l,r,x,left,mid),rc->add(l,r,x,mid,right);
					refresh();
				}
				~node(){delete lc;delete rc;}
		};
		int l,r;
	public:
		node *root;
		xds(const T *base,const int &left,const int &right)
		{
			root=new node(base,left,right);
			l=left,r=right;
			return;
		}
		void add(const int &left,const int &right,const T &x)
		{
			root->add(left,right,x,l,r);
		}
		T quest(const int &left,const int &right)
		{
			return root->quest(left,right,l,r);
		}
		~xds(){delete root;}
};
//test
/*int main()
{
	int n,q;
	scanf("%d%d",&n,&q);
	long long *a=new long long[n];
	for(int i=0;i<n;i++)
		scanf("%lld",a+i);
	xds<long long> *tr=new xds<long long>(a,0,n);
	for(int i=0;i<q;i++)
	{
		int f;
		scanf("%d",&f);
		if(f==1)
		{
			int l,r;
			long long x;
			scanf("%d%d%lld",&l,&r,&x);
			tr->add(l-1,r,x);
		}
		else
		{
			int l,r;
			scanf("%d%d",&l,&r);
			printf("%lld\n",tr->quest(l-1,r));
		}
		
	}
	delete a;delete tr;
}*/

template<typename T>
struct node{
	T weight;
	vector<int>sons;
	int sig,heav,top,deepth,fa,size;
};

vector<node<long long> > nodes;

void dfs1(const int &p,const int &deepth,const int &fa)
{
	nodes[p].deepth=deepth,nodes[p].fa=fa,nodes[p].size=1,nodes[p].heav=-1;
	for(int i:nodes[p].sons)
	{
		dfs1(i,deepth+1,p);
		nodes[p].size+=nodes[i].size;
		if(nodes[p].heav==-1||nodes[i].size>nodes[nodes[p].heav].size)
			nodes[p].heav=nodes[i].size;
	}
	return;
}

int main(){;}