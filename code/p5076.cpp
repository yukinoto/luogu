#include <cstdio>
#include <algorithm>
using namespace std;

#define LEFT 1
#define RIGHT 0
#define INF 0x7fffffff
template<typename T>
class tree{
	private:
		class node{
			private:
				T num;
				int rpt;
				mutable int size;
				node *lc,*rc,*fa;
				int get()
				{
					if(this==nullptr||fa==nullptr)
						return -1;
					if(fa->lc==this)
						return LEFT;
					return RIGHT;
				}
				T getnum()
				{
					if(this==nullptr)
						return 0;
					return num;
				}
				T getsize()
				{
					if(this==nullptr)
						return 0;
					return size;
				}
				decltype(lc) findmin()
				{
					if(lc==nullptr)
						return this;
					return lc->findmin();
				}
				decltype(lc) findmax()
				{
					if(rc==nullptr)
						return this;
					return rc->findmax();
				}
				void update()
				{
					if(this==nullptr)
						return;
					size=lc->getsize()+rc->getsize()+rpt;
					return;
				}
				void addchild(node*pt,int type)
				{
					if(pt!=nullptr)
						pt->fa=this;
					if(this!=nullptr)
						if(type==LEFT)
							lc=pt;
						else if(type==RIGHT)
							rc=pt;
					return;
				}
				void rotate()
				{
					//update();
					if(this==nullptr||fa==nullptr)
						return;
					auto f=fa,ff=fa->fa;
					int m=get(),n=fa->get();
					f->addchild(m==LEFT?rc:lc,m);
					this->addchild(fa,m^1);
					ff->addchild(this,n);
					f->update(),this->update();
				}
				decltype(lc) splay()
				{
					//update();
					if(this==nullptr)return nullptr;
					if(fa==nullptr)
						return this;
					while(fa->fa!=nullptr)
					{
						if(get()==fa->get())
							fa->rotate();
						else
							rotate();
						rotate();
						if(fa==nullptr)
							return this;
					}
					rotate();
					return this;
				}
				decltype(lc) find(const T &x)
				{
					//update();
					if(this==nullptr||num==x)
						return this;
					if(num<x)
						return rc->find(x);
					else
						return lc->find(x);
				}
				decltype(lc) nodedel()
				{
					//update();
					if(this==nullptr)
						return nullptr;
					if(rpt>1)
					{
						rpt--;
						update();
						fa->update();
						splay();
						return this;
					}
					splay();
					if(lc==nullptr&&rc==nullptr)
					{
						delete this;
						return nullptr;
					}
					if(lc==nullptr)
					{
						rc->fa=nullptr;
						auto ans=rc;
						rc=nullptr;
						delete this;
						return ans->splay();
					}
					if(rc==nullptr)
					{
						lc->fa=nullptr;
						auto ans=lc;
						lc=nullptr;
						delete this;
						return ans->splay();
					}
					auto rep=rc->findmin();
					if(rep->fa==this)
					{
						rep->fa=nullptr;
						rep->addchild(lc,LEFT);
						rep->update();
						lc=rc=nullptr;
						delete this;
						return rep->splay();
					}
					auto nr=rep->fa;
					rep->fa->addchild(rep->rc,LEFT);
					rep->fa=nullptr;
					rep->addchild(lc,LEFT),rep->addchild(rc,RIGHT);
					rep->update();
					lc=rc=nullptr;
					delete this;
					nr->update();
					nr->fa->update();
					return nr->splay();
				}
			public:
				node(const T &x,node *_fa)
				{num=x,fa=_fa,size=rpt=1;}
				~node(){delete lc,delete rc;}
				decltype(lc) add(const T &x)
				{
					//update();
					if(this->num==x)
					{
						rpt++;
						update(),fa->update();
						return splay();
					}
					if(num<=x)
					{
						if(rc==nullptr)
						{
							rc=new node(x,this);
							update();
							return rc->splay();
						}
						else
							return rc->add(x);
					}
					else
					{
						if(lc==nullptr)
						{
							lc=new node(x,this);
							update();
							return lc->splay();
						}
						else
							return lc->add(x);
					}
				}
				int checkth(const T &x,int bef)
				{
					//update();
					if(num==x)
						return bef+lc->getsize()+1;
					if(num<x)
						return rc->checkth(x,bef+rpt+lc->getsize());
					else
						return lc->checkth(x,bef);
				}
				T nth(const int &n,const int &bef)
				{
					//update();
					if(bef+lc->getsize()+rpt>=n&&bef+lc->getsize()<n)
						return num;
					if(bef+lc->getsize()<n)
						return rc->nth(n,bef+lc->getsize()+rpt);
					else
						return lc->nth(n,bef);
				}
				decltype(lc) del(const T &x)
				{
					//update();
					return find(x)->nodedel();
				}
				T getlc()
				{
					//update();
					if(lc==nullptr)
						return this->num;
					return lc->findmax()->num;
				}
				T getrc()
				{
					//update();
					if(rc==nullptr)
						return this->num;
					return rc->findmin()->num;
				}
		};
		node *root;
	public:
		tree(){root=nullptr;}
		~tree(){delete root;}
		void add(const T &x)
		{
			if(root==nullptr)
			{
				root=new node(x,nullptr);
				return;
			}
			else
				root=root->add(x);
		}
		void del(const T &x)
		{
			root=root->del(x);
		}
		int checkth(const T &x)
		{
			return root->checkth(x,0);
		}
		T nth(const int &x)
		{
			return root->nth(x,0);
		}
		T bef(const T &x)
		{
			root=root->add(x);
			T ans=root->getlc();
			root=root->del(x);
			return ans;
		}
		T nxt(const T &x)
		{
			root=root->add(x);
			T ans=root->getrc();
			root=root->del(x);
			return ans;
		}
};

void f1(tree<int> *tr)
{
	int x;
	scanf("%d",&x);
	tr->add(x);
	return;
}
void f2(tree<int> *tr)
{
	int x;
	scanf("%d",&x);
	tr->del(x);
	return;
}
void f3(tree<int> *tr)
{
	int x;
	scanf("%d",&x);
	printf("%d\n",tr->checkth(x+1));
	return;
}
void f4(tree<int> *tr)
{
	int x;
	scanf("%d",&x);
	printf("%d\n",tr->nth(x)-1);
	return;
}
void f5(tree<int> *tr)
{
	int x;
	scanf("%d",&x);
	printf("%d\n",tr->bef(x));
	return;
}
void f6(tree<int> *tr)
{
	int x;
	scanf("%d",&x);
	printf("%d\n",tr->nxt(x));
	return;
}

decltype(f1) *f[6]={f4,f3,f5,f6,f1,f6};
int main()
{
	//freopen("./code/p3369.in","r",stdin);
	int n;
	scanf("%d",&n);
	auto* tr=new tree<int>;
	tr->add(0x7fffffff),tr->add(0x80000000);
	for(int i=0;i<n;i++)
	{
		int x;
		scanf("%d",&x);
		f[x-1](tr);
	}
	delete tr;
	return 0;
}
