#include <cstdio>
#include <cstdlib>

int getRand()
{
	return (rand()<<16)|rand();
}

#define LEFT_UP true
#define RIGHT_UP false
template <typename T>
class treap{
	private:
		class node{
			private:
				T num;
				int key,sons;
				node *lc,*rc,*fa;
				void resetsons()
				{
					sons=0;
					if(lc!=nullptr)
					{
						lc->sons=0;
						if(lc->lc!=nullptr)
							lc->sons+=lc->lc->sons;
						if(lc->rc!=nullptr)
							lc->sons+=lc->rc->sons;
						lc->sons++;
						sons+=lc->sons;
					}
					if(rc!=nullptr)
					{
						rc->sons=0;
						if(rc->rc!=nullptr)
							rc->sons+=rc->lc->sons;
						if(rc->rc!=nullptr)
							rc->sons+=rc->rc->sons;
						rc->sons++;
						sons+=rc->sons;
					}
					sons++;
				}
				void splay(bool type)
				{
					decltype(lc) fa_=fa,lc_=lc,rc_=rc,lc_rc_=lc->rc,rc_lc_=rc->lc;
					if(type==LEFT_UP)
					{
						fa=lc_,lc=lc_rc_,lc_->rc=this,lc_->fa=fa_;
					}
					if(type=RIGHT_UP)
					{
						fa=rc_,rc=rc_lc_,rc_->lc=this,rc_->fa=fa_;
					}
					fa->resetsons();
				}
				void mkHeap()
				{
					while(fa!=nullptr&&key<fa->key)
					{
						if(this==fa->lc)
						{
							fa->splay(LEFT_UP);
						}
						else
						{
							fa->splay(RIGHT_UP);
						}
					}
					if(key==0x7fffffff)
					{
						if(fa->lc==this)
							fa->lc=nullptr;
						else
							fa->rc=nullptr;
						delete this;
					}
					return;
				}
			public:
				T get()const{return num;}
				auto get(const T &x)->decltype(this)
				{
					if(num==x)
						return this;
					if(num>x)
					{
						if(lc==nullptr)
							return nullptr;
						return lc->get(x);
					}
					else
					{
						if(rc==nullptr)
							return nullptr;
						return rc->get(x);
					}
				}
				node(const T &x,decltype(lc) _fa)
				{
					fa=_fa;
					num=x;
					key=getRand();
					lc=rc=nullptr;
					sons=0;
				}
				~node(){delete lc;delete rc;}
				void add(const T &x)
				{
					if(x==num)
					{
						decltype(lc)_lc=lc;
						lc=new node(x,this);
						lc->lc=_lc;
						lc->mkHeap();
					}
					if(x<num)
					{
						if(rc==nullptr)
						{
							rc=new node(x,this);
							rc->mkHeap();
						}
						else
							rc->add(x);
					}
					else
					{
						if(lc==nullptr)
						{
							lc=new node(x,this);
							lc->mkHeap();
						}
						else
							lc->add(x);
					}
				}
				void del()
				{
					key=0x7fffffff;
					mkHeap();
					return;
				}
				auto fdnth(int n,int bef)->decltype(lc)
				{
					if(bef+(lc==nullptr?0:lc->sons)==n-1)
						return this;
					if(lc==nullptr)
						return rc->fdnth(n,bef+1);
					if(rc==nullptr)
						return lc->fdnth(n,bef);
					if(bef+(lc==nullptr?0:lc->sons)>n-1)
						return lc->fdnth(n,bef);
					else
						return rc->fdnth(n,bef+1+lc->sons);
				}
		};
		node *root;
		public:
			treap(){root=nullptr;}
			~treap(){delete root;}
			void add(const T &x)
			{
				if(root==nullptr)
					root=new node(x,nullptr);
				else
					root->add(x);
			}
			void del(const T &x)
			{
				root->get(x)->del();
				return;
			}
			T nth(int n)
			{
				return root->fdnth(n,0)->get();
			}
};

void f1(treap<int> *tr)
{
	int x;
	scanf("%d",&x);
	tr->add(x);
	return;
}
void f2(treap<int> *tr)
{
	int x;
	scanf("%d",&x);
	tr->del(x);
	return;
}

void f4(treap<int> *tr)
{
	int x;
	scanf("%d",&x);
	printf("%d\n",tr->nth(x));
}

decltype(f1) *f[6]={f1,f2,nullptr,f4,nullptr,nullptr};
int main()
{
	int n;
	scanf("%d",&n);
	auto* tr=new treap<int>;
	for(int i=0;i<n;i++)
	{
		int x;
		scanf("%d",&x);
		f[x-1](tr);
	}
	return 0;
}
