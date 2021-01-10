#include <stdio.h>

template <typename T>
class tree{
	private:
		struct node{
			T sum;
			T tag;
			int tagtype;
			node *ls,*rs;
			int l,r;//[)
			node(T *base,int left,int right)
			{
				l=left,r=right;
				sum=tag=tagtype=0;
				if(left==right-1)
				{
					sum=base[left];
					return;
				}
				int mid=(l+r)/2;
				if(mid>l)
				{
					ls=new node(base,l,mid);
					sum+=ls->sum;
				}
				else
					ls=nullptr;
				if(r>mid)
				{
					rs=new node(base,mid,right);
					sum+=rs->sum;
				}
				else
					rs=nullptr;
				return;
			}
			~node()
			{
				delete ls,rs;
				return;
			}
			void pushdown()
			{
				if(tagtype==0)
					return;
				if(tagtype==1)
				{
					if(ls!=nullptr)
					{
						if(ls->tagtype==0)
						{
							ls->tag=0;
							ls->tagtype=1;
						}
						if(ls->tagtype!=0&&ls->tagtype!=1)
						{
							ls->pushdown();
							ls->tagtype=1;
							ls->tag=0;
						}
						ls->sum+=tag*(ls->r-ls->l);
						ls->tag+=tag;
					}
					if(rs!=nullptr)
					{
						if(rs->tagtype==0)
						{
							rs->tag=0;
							rs->tagtype=1;
						}
						if(rs->tagtype!=0&&rs->tagtype!=1)
						{
							rs->pushdown();
							rs->tagtype=1;
							rs->tag=0;
						}
						rs->sum+=tag*(rs->r-rs->l);
						rs->tag+=tag;
					}
					tagtype=tag=0;
					return;
				}
				if(tagtype==2)
				{
					if(ls!=nullptr)
					{
						if(ls->tagtype==0)
						{
							ls->tag=1;
							ls->tagtype=1;
						}
						if(ls->tagtype!=0&&ls->tagtype!=2)
						{
							ls->pushdown();
							ls->tagtype=2;
							ls->tag=1;
						}
						ls->sum*=tag*(ls->r-ls->l);
						ls->tag*=tag;
					}
					if(rs!=nullptr)
					{
						if(rs->tagtype==0)
						{
							rs->tag=1;
							rs->tagtype=1;
						}
						if(rs->tagtype!=0&&rs->tagtype!=2)
						{
							rs->pushdown();
							rs->tagtype=2;
							rs->tag=1;
						}
						rs->sum*=tag*(rs->r-rs->l);
						rs->tag*=tag;
					}
					tagtype=0;
					tag=0;
					return;
				}
			}
			void add(int left,int right,T x)
			{
				if(left>=r||right<=l)
					return;
				pushdown();
				if(left<=l&&right>=r)
				{
					sum+=(r-l)*x;
					tagtype=1;
					tag=x;
					return;
				}
				if(ls!=nullptr)
					ls->add(left,right,x);
				if(rs!=nullptr)
					rs->add(left,right,x);
				sum=ls->sum+rs->sum;
				return;
			}
			void cheng(int left,int right,T x)
			{
				if(left>=r||right<=l)
					return;
				pushdown();
				if(left<=l&&right>=r)
				{
					sum*=(r-l)*x;
					tagtype=2;
					tag=x;
					return;
				}
				if(ls!=nullptr)
					ls->cheng(left,right,x);
				if(rs!=nullptr)
					rs->cheng(left,right,x);
				sum=ls->sum+rs->sum;
				return;
			}
			T q(int left,int right)
			{
				if(left>=r||right<=l)
					return 0;
				pushdown();
				if(left<=l&&right>=r)
					return sum;
				T ans=0;
				if(ls!=nullptr)
					ans+=ls->q(left,right);
				if(rs!=nullptr)
					ans+=rs->q(left,right);
				return ans;
			}
		};
		node *root;
	public:
		tree(T *base,int l,int r)
		{
			root=new node(base,l,r);
			return;
		}
		~tree()
		{
			delete root;
			return;
		}
		T q(int left,int right)
		{
			return root->q(left,right);
		}
		void add(int left,int right,T x)
		{
			return root->add(left,right,x);
		}
		void cheng(int left,int right,T x)
		{
			return root->cheng(left,right,x);
		}
};

int main()
{
	int n,m;
	scanf("%d%d",&n,&m);
	long long *pt=new long long[n];
	for(int i=0;i<n;i++)
		scanf("%lld",pt+i);
	auto *tr=new tree<long long>(pt,0,n);
	delete pt;
	for(int i=0;i<m;i++)
	{
		static int f,l,r;
		static long long x;
		scanf("%d%d%d",&f,&l,&r);
		switch (f){
			case 1:
				scanf("%lld",&x);
				tr->cheng(l,r,x);
				break;
			case 2:
				scanf("%lld",&x);
				tr->add(l,r,x);
				break;
			case 3:
				printf("%lld\n",tr->q(l,r));
				break;
		}
	}
	return 0;
}
