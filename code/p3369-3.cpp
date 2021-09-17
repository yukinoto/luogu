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
		treap()
		{
			root=nullptr;
			return;
		}
		node *fnd(const T &x)
		{
			node *p=root;
			while(p->value!=x)
			{
				if(x>p->value)
				{
					if(p->rc==nullptr)
						break;
					p=p->rc;
				}
				if(x<p->value)
				{
					if(p->lc==nullptr)
						break;
					p=p->lc;
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
			if(p->rc!=nullptr)
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
			if(p->lc!=nullptr)
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
			if(root==nullptr)
			{
				root=new node(x);
				return;
			}
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
			if(p->lc!=nullptr)
				cnt+=lc->size;
			while(p->value!=x)
			{
				if(x>p->value)
				{
					p=p->lc;
					cnt-=1;
					if(p->rc!=nullptr)
						cnt-=p->rc->size;
				}
				else
				{
					p=p->rc;
					cnt+=1;
					if(p->lc!=nullptr)
						cnt+=p->lc->size;
				}
			}
			return cnt+1;
		}
		T nst(const int n)
		{
			node *p=root;
			int cnt;
			if(p->lc==nullptr)
				cnt=0;
			else
				cnt=p->lc->size;
			while(cnt+1!=n)
			{
				if(cnt+1>n)
				{
					p=p->lc;
					cnt-=1;
					if(p->rc!=nullptr)
						cnt-=p->rc->size;
				}
				else
				{
					p=p->rc;
					cnt+=1;
					if(p->lc!=nullptr)
						cnt+=p->lc->size;
				}
			}
			return p->value;
		}
		T bef(const T &x)
		{
			const node *p=fnd(x);
			if(p->value<x)
				return p->value;
			if(p->value>=x)
			{
				if(p->lc==nullptr)
					return p->fa->value;
				p=p->lc;
				while(p->rc!=nullptr)
					p=p->rc;
				return p->value;
			}
		}
		T aft(const T &x)
		{
			const node *p=fnd(x);
			if(p->value>x)
				return p->value;
			if(p->value<=x)
			{
				if(p->rc==nullptr)
					return p->fa->value;
				p=p->rc;
				while(p->lc!=nullptr)
					p=p->lc;
				return p->value;
			}
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
			cout<<t.nst(x)<<endl;
		if(f==5)
			cout<<t.bef(x)<<endl;
		if(f==6)
			cout<<t.aft(x)<<endl;
	}
	return 0;
}