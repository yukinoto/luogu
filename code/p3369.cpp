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
					node *_fa=fa,*_lc=lc,*_rc=rc,*_lc_rc=lc->rc,*_rc_lc=rc->lc;
					if(type==LEFT_UP)
					{
						fa=_lc,lc=_lc_rc,_lc->rc=this,_lc->fa=_fa;
					}
					if(type=RIGHT_UP)
					{
						fa=_rc,rc=_rc_lc,_rc->lc=this,_rc->fa=_fa;
					}
					resetsons(fa);
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
				*node get(const T &x)const
				{
					if(num==x)
						return this;
					if(num>x)
					{
						if(lc==nullptr)
							return nullptr;
						return lc->get();
					}
					else
					{
						if(rc==nullptr)
							return nullptr;
						return rc->get();
					}
				}
				node(const T &x,const node *_fa)
				{
					fa=_fa;
					num=x;
					key=getRand();
					lc=rc=nullptr;
					rnk=1;
				}
				~node(){delete lc;delete rc;}
				void add(const T &x)
				{
					if(x==num)
					{
						node *_lc=lc;
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
};
