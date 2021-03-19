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
						if(rc->lc!=nullptr)
							rc->sons+=rc->lc->sons;
						if(rc->rc!=nullptr)
							rc->sons+=rc->rc->sons;
						rc->sons++;
						sons+=rc->sons;
					}
					sons++;
					if(fa!=nullptr)
						fa->resetsons();
				}
				void splay(bool type)
				{
					if(type==LEFT_UP)
					{
						if(lc==nullptr)
							return;
						if(lc->rc==nullptr)
						{
							lc->fa=fa;
							if(fa!=nullptr)
								if(fa->lc==this)
									fa->lc=lc;
								else
									fa->rc=lc;
							fa=lc;
							lc->rc=this;
							lc=nullptr;
							fa->resetsons();
							return;
						}
						else
						{
							lc->fa=fa;
							if(fa!=nullptr)
								if(fa->lc==this)
									fa->lc=lc;
								else
									fa->rc=lc;
							auto pt=lc;
							lc=pt->rc;
							pt->rc->fa=this;
							pt->rc=this;
							fa=pt;
						}
					}else if(type==RIGHT_UP)
						{
							if(rc==nullptr)
								return;
							if(rc->lc==nullptr)
							{
								rc->fa=fa;
								if(fa!=nullptr)
									if(fa->lc==this)
										fa->lc=rc;
									else
										fa->rc=rc;
								fa=rc;
								rc->lc=this;
								rc=nullptr;
								fa->resetsons();
								return;
							}
							else
							{
								rc->fa=fa;
								if(fa!=nullptr)
									if(fa->lc==this)
										fa->lc=rc;
									else
										fa->rc=rc;
								auto pt=rc;
								rc=pt->lc;
								pt->lc->fa=this;
								pt->lc=this;
								fa=pt;
							}
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
				auto checknth(const T &x,int bef)const ->int
				{
					if(num==x)
						return bef+1+(lc==nullptr?0:lc->sons);
					if(num>x)
						if(lc==nullptr)
							return -1;
						else
							return lc->checknth(x,bef);
					else
						if(rc==nullptr)
							return -1;
						else
							return rc->checknth(x,bef+1+(lc==nullptr?0:lc->sons));
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
					if(x>num)
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
				auto merge(decltype(lc) pt1,decltype(lc) pt2,decltype(lc) tf)->decltype(lc)
				{
					if(pt1==nullptr)
					{
						pt2->fa=tf;
						return pt2;
					}
					if(pt2==nullptr)
					{
						pt1->fa=tf;
						return pt1;
					}
					if(pt1->key<pt2->key)
					{
						if(pt1->num<pt2->num)
						{
							if(pt1->rc==nullptr)
							{
								pt1->rc=pt2;
								pt1->fa=tf;
								pt2->fa=pt1;
								return pt1;
							}
							else
							{
								pt1->fa=tf;
								merge(pt1->rc,pt2,pt1);
								return pt1;
							}
						}
						else
						{
							if(pt1->lc==nullptr)
							{
								pt1->lc=pt2;
								pt1->fa=tf;
								pt2->fa=pt1;
								return pt1;
							}
							else
							{
								pt1->fa=tf;
								merge(pt1->lc,pt2,pt1);
								return pt1;
							}
						}
					}
					else
					{
						if(pt2->num<pt1->num)
						{
							if(pt2->rc==nullptr)
							{
								pt2->rc=pt1;
								pt2->fa=tf;
								pt1->fa=pt2;
								return pt2;
							}
							else
							{
								pt2->fa=tf;
								merge(pt2->rc,pt1,pt2);
								return pt2;
							}
						}
						else
						{
							if(pt2->lc==nullptr)
							{
								pt2->lc=pt1;
								pt2->fa=tf;
								pt1->fa=pt2;
								return pt2;
							}
							else
							{
								pt2->fa=tf;
								merge(pt2->lc,pt1,pt2);
								return pt2;
							}
						}
					}
				}
				auto del()->decltype(lc)
				{
					key=0x80000000;
					mkHeap();
					if(lc==nullptr&&rc==nullptr)
					{
						delete this;
						return nullptr;
					}
					if(lc==nullptr)
					{
						decltype(lc) ans=rc;
						rc->fa=nullptr;
						rc=nullptr;
						delete this;
						return ans;
					}
					if(rc==nullptr)
					{
						decltype(lc) ans=lc;
						lc->fa=nullptr;
						lc=nullptr;
						delete this;
						return ans;
					}
					decltype(lc) l=lc,r=rc;
					lc=rc=nullptr;delete this;
					return merge(l,r,nullptr);
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
				bool isRoot()const{return fa==nullptr;}
				auto gtf()const ->decltype(fa){return fa;}
				T bef(const T &x)const
				{
					if(lc==nullptr&&rc==nullptr)
						return num;
					if(num<x)
						if(rc==nullptr)
							return num;
						else
							return rc->bef(x);
					else
						if(lc==nullptr)
							return 0x7fffffff;
						else
							return lc->bef(x);
				}
				T nxt(const T &x)const
				{
					if(lc==nullptr&&rc==nullptr)
						return num;
					if(num>x)
						if(lc==nullptr)
							return num;
						else
							return lc->nxt(x);
					else
						if(rc==nullptr)
							return 0x7fffffff;
						else
							return rc->nxt(x);
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
				while(!root->isRoot())
					root=root->gtf();
			}
			void del(const T &x)
			{
				(root->get(x))->del();
				return;
			}
			T nth(int n)
			{
				return root->fdnth(n,0)->get();
			}
			int checkth(const T &x)const
			{
				return root->checknth(x,0);
			}
			T bef(const T &x)const
			{
				return root->bef(x);
			}
			T nxt(const T &x)const
			{
				return root->nxt(x);
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
void f3(treap<int> *tr)
{
	int x;
	scanf("%d",&x);
	printf("%d\n",tr->checkth(x));
	return;
}
void f4(treap<int> *tr)
{
	int x;
	scanf("%d",&x);
	printf("%d\n",tr->nth(x));
	return;
}
void f5(treap<int> *tr)
{
	int x;
	scanf("%d",&x);
	printf("%d\n",tr->bef(x));
	return;
}
void f6(treap<int> *tr)
{
	int x;
	scanf("%d",&x);
	printf("%d\n",tr->nxt(x));
	return;
}

decltype(f1) *f[6]={f1,f2,f3,f4,f5,f6};
int main()
{
	freopen("./code/p3369.in","r",stdin);
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
