#include <iostream>
#include <cstdlib>
using namespace std;

int randint()
{
	return (rand()<<16)|rand();
}

template <typename T>
class treap{
	private:
		class node{
			public:
				T value;
				int key,cnt,size;
				node *lc,*rc,*fa;
				~node()
				{
					delete lc;
					delete rc;
					return;
				}
				//node(){;}
				node(const T &x)
				{
					value=x;
					key=randint();
					cnt=1;
					lc=rc=fa=nullptr;
					size=1;
					return;
				}
				void reset()
				{
					size=cnt;
					if(lc!=nullptr)
						size+=lc->size;
					if(rc!=nullptr)
						size+=rc->size;
					return;
				}
				void update()
				{
					reset();
					if(fa!=nullptr)
						fa->update();
					return;
				}
		};
		node *root;
	public:
		node * fnd(const T &x)
		{
			node *p=root;
			while(p->value!=x)
			{
				if(x>p->value)
				{
					if(p->lc==nullptr)
						break;
					p=p->lc;
				}
				if(x<p->value)
				{
					if(p->rc==nullptr)
						break;
					p=p->rc;
				}
			}
			return p;
		}
		void roll_right_up(node *p)
		{
			node *r=p->rc;
			r->fa=p->fa;
			p->fa=r;
			p->rc=r->lc;
			p->rc->fa=p;
			r->lc=p;
			p->reset();
			r->reset();
		}
		void roll_left_up(node *p)
		{
			node *l=p->lc;
			l->fa=p->fa;
			p->fa=l;
			p->lc=l->rc;
			p->lc->fa=p;
			l->rc=p;
			p->reset();
			l->reset();
		}
		void fall(node *p)
		{
			while(true)
			{
				if(p->lc==p->rc&&p->lc==nullptr)
					return;
				if(p->lc==nullptr||p->rc->key<p->lc->key)
					roll_right_up(p);
				if(p->rc==nullptr||p->rc->key>p->lc->key)
					roll_left_up(p);
			}
			return;
		}
		void rise(node *p)
		{
			while(p->fa!=nullptr&&p->key<p->fa->key)
			{
				if(p->fa->lc==p)
					roll_left_up(p->fa);
				if(p->fa->rc==p)
					roll_right_up(p->fa);
			}
			return;
		}
		void insert(const T &x)
		{
			node *p=fnd(x);
			if(x==p->value)
			{
				p->cnt++;
				p->update();
				return;
			}
			node *np=new node(x);
			if(x>p->value)
				p->rc=np;
			if(x<p->value)
				p->lc=np;
			np->fa=p;
			np->update();
			rise(np);
			return;
		}
		void erase(const T &x)
		{
			node *p=fnd(x);
			if(x!=p->value)
				return;
			if(p->cnt>1)
			{
				p->cnt--;
				p->update();
			}
			else
			{
				p->key=0x7fffffff;
				fall(p);
				p->cnt=0;
				p->update();
				if(p->fa->lc==p)
					p->fa->lc=nullptr;
				if(p->fa->rc==p)
					p->fa->rc=nullptr;
				delete p;
			}
			return;
		}
		int rank(const T &x)const
		{
			node *p=root;
			int cnt=0;
			while(p->value!=x)
			{
				if(p->value>x)
					p=p->rc;
				if(p->value<x)
				{
					cnt+=p->lc->size;
					cnt+=p->cnt;
					p=p->rc;
				}
			}
			return cnt+1;
		}
		T bef(const T &x)const
		{
			node *p=fnd(x);
			if(p->lc!=nullptr)
			{
				p=p->lc;
				while(p->rc!=nullptr)
					p=p->rc;
				return p;
			}
			return p->fa;
		}
		T aft(const T &x)const
		{
			node *p=fnd(x);
			if(p->rc!=nullptr)
			{
				p=p->rc;
				while(p->lc!=nullptr)
					p=p->lc;
				return p;
			}
			return p->fa;
		}
		~treap()
		{
			delete root;
			return;
		}
};

int main()
{
	int n;
	cin>>n;
	treap<int> t;
	for(int i=0;i<n;i++)
	{
		int f,x;
		cin>>f>>x;;
		if(f==1)
			t.insert(x);
		if(f==2)
			t.erase(x);
		if(f==3)
			cout<<t.rank(x)<<endl;
		if(f==4)
			cout<<t.bef(x)<<endl;
		
	}
}