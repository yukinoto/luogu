#include <iostream>
#include <cstdlib>
using namespace std;

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
					key=rand();
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
				else if(x<p->value)
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
			if(p->fa!=nullptr)
			{
				if(p->fa->lc==p)
					p->fa->lc=r;
				else if(p->fa->rc==p)
					p->fa->rc=r;
			}
			else
				root=r;
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
			if(p->fa!=nullptr)
			{
				if(p->fa->lc==p)
					p->fa->lc=l;
				else if(p->fa->rc==p)
					p->fa->rc=l;
			}
			else
				root=l;
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
				if(p->lc==nullptr&&p->rc==nullptr)
					return;
				if(p->lc==nullptr)
					roll_right_up(p);
				else if(p->rc==nullptr)
					roll_left_up(p);
				else if(p->lc->key<p->rc->key)
					roll_left_up(p);
				else
					roll_right_up(p);
			}
			return;
		}
		void rise(node *p)
		{
			while(p->fa!=nullptr)
			{
				if(p->key>=p->fa->key)
					break;
				if(p->fa->lc==p)
					roll_left_up(p->fa);
				else if(p->fa->rc==p)
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
				else if(p->fa->rc==p)
					p->fa->rc=nullptr;
				delete p;
			}
			return;
		}
		int rank(const T &x)
		{
			node *p=root;
			int cnt=0;
			//insert(x);
			if(p->lc!=nullptr)
				cnt+=p->lc->size;
			while(p->value!=x)
			{
				if(x<p->value)
				{
					if(p->lc==nullptr)
						break;
					p=p->lc;
					cnt-=p->cnt;
					if(p->rc!=nullptr)
						cnt-=p->rc->size;
				}
				else
				{
					cnt+=p->cnt;
					if(p->rc==nullptr)
						break;
					p=p->rc;
					if(p->lc!=nullptr)
						cnt+=p->lc->size;
				}
			}
			//erase(x);
			return cnt;
		}
		T nst(int n)
		{
			n++;
			node *p=root;
			int cnt;
			if(p->lc==nullptr)
				cnt=0;
			else
				cnt=p->lc->size;
			while(cnt+1>n||cnt+p->cnt<n)
			{
				if(cnt+1>n)
				{
					p=p->lc;
					cnt-=p->cnt;
					if(p->rc!=nullptr)
						cnt-=p->rc->size;
				}
				else
				{
					cnt+=p->cnt;
					p=p->rc;
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
					if(p->fa->rc==p)
						return p->fa->value;
					else
					{
						while(p->fa->rc!=p)
							p=p->fa;
						p=p->fa;
						return p->value;
					}
				else
					p=p->lc;
				while(p->rc!=nullptr)
					p=p->rc;
				return p->value;
			}
			return p->value;
		}
		T aft(const T &x)
		{
			const node *p=fnd(x);
			if(p->value>x)
				return p->value;
			if(p->value<=x)
			{
				if(p->rc==nullptr)
					if(p->fa->lc==p)
						return p->fa->value;
					else
					{
						while(p->fa->lc!=p)
							p=p->fa;
						p=p->fa;
						return p->value;
					}
				else
					p=p->rc;
				while(p->lc!=nullptr)
					p=p->lc;
				return p->value;
			}
			return p->value;
		}
		treap(T inf)
		{
			root=nullptr;
			insert(inf);
			insert(-inf);
			return;
		}
		~treap()
		{
			delete root;
			return;
		}
};


int main()
{
#ifndef ONLINE_JUDGE
	//freopen("P3369_3.in","r",stdin);
#endif
	int n,m;
	cin>>n>>m;
	treap<int> t(0x7fffffff);
	for(int i=0;i<n;i++)
	{
		int x;
		cin>>x;
		t.insert(x);
	}
	int bef=0,ans=0;
	for(int i=0;i<m;i++)
	{
		int f,x;
		cin>>f>>x;;
		if(f==1)
			t.insert(x^bef);
		if(f==2)
			t.erase(x^bef);
		if(f==3)
			bef=t.rank(x^bef);
		if(f==4)
			bef=t.nst(x^bef);
		if(f==5)
			bef=t.bef(x^bef);
		if(f==6)
			bef=t.aft(x^bef);
		if(f>=3)
			ans^=bef;
	}
	cout<<ans<<endl;
	return 0;
}