//rbt

//#define DEBUG
#define SIZE
#define MULTIBLE

#ifdef SIZE
#ifndef MULTIBLE
#define NODE_SIZE(X) 1
#else
#define NODE_SIZE(X) ((X)->count)
#endif
#endif

#include <algorithm>
using std::swap;

#define RED false
#define BLACK true

#define LEFT false
#define RIGHT true

template<typename T>
class rbt{
	private:
		struct node{
			node *fa,*lc,*rc;
			T value;
#ifdef SIZE
			size_t size;
#endif
#ifdef MUTIBLE
			size_t count;
#endif
			bool col;
			node();
			node(node *_fa,const T&_value,bool _col);
			~node();
		};
		node *root;
		node* find(const T&value);
		void rotate(node *x,bool direct);
		void SolveDoubleRed(node* x);
		void SolveDoubleBlack(node* x);
		void erase(node *x);
#ifdef SIZE
		void pushup(node *x);
#endif
#ifdef DEBUG
		void checkRBT()const;
		size_t checkNODE(node*x)const;
#endif
	public:
		class iterator;
		rbt();
		~rbt();
		iterator begin();
		iterator end();
		size_t size();
		iterator insert(const T &x);
		void erase(const T &x);
		void erase(const iterator&it);
		iterator lowwer_bound(const T &x);
		iterator upper_bound(const T &x);
#ifdef SIZE
		iterator nth_element(size_t rank);
		size_t get_rank(const T &x);
#endif
};

template<typename T>
class rbt<T>::iterator{
	private:
		node *pt;
	public:
		iterator& operator ++();
		iterator& operator --();
		const T& operator *();
		bool operator ==(const iterator&)const;
		bool operator !=(const iterator&)const;
		iterator(){;}
		iterator(node* _pt):pt(_pt){;}
		friend void rbt<T>::erase(node*);
		friend void rbt<T>::erase(const iterator&);
};

template<typename T>
typename rbt<T>::iterator& rbt<T>::iterator::operator ++()
{
	if(pt->rc==nullptr)
	{
		while(true)
		{
			if(pt->fa==nullptr)
			{
				pt=nullptr;
				return *this;
			}
			if(pt->fa->lc==pt)
			{
				pt=pt->fa;
				return *this;
			}
			pt=pt->fa;
		}
	}
	pt=pt->rc;
	while(pt->lc!=nullptr)
		pt=pt->lc;
	return *this;
}

template<typename T>
typename rbt<T>::iterator& rbt<T>::iterator::operator --()
{
	if(pt->lc==nullptr)
	{
		while(true)
		{
			if(pt->fa==nullptr)
			{
				pt=nullptr;
				return *this;
			}
			if(pt->fa->rc==pt)
			{
				pt=pt->fa;
				return *this;
			}
			pt=pt->fa;
		}
	}
	pt=pt->lc;
	while(pt->rc!=nullptr)
		pt=pt->rc;
	return *this;
}

template<typename T>
const T& rbt<T>::iterator::operator*()
{
	return pt->value;
}

template<typename T>
bool rbt<T>::iterator::operator==(const iterator&it)const
{
	return pt==it.pt;
}

template<typename T>
bool rbt<T>::iterator::operator!=(const iterator&it)const
{
	return pt!=it.pt;
}

template<typename T>
rbt<T>::node::node()
{
	lc=rc=fa=nullptr;
#ifdef SIZE
	size=0;
#endif
	return;
}

template<typename T>
rbt<T>::node::node(node* _fa,const T&_value,bool _col):fa(_fa),value(_value),col(_col)
{
	node();
	return;
}

template<typename T>
rbt<T>::node::~node()
{
	delete lc,rc;
	return;
}

template<typename T>
rbt<T>::rbt()
{
	root=nullptr;
	return;
}

template<typename T>
rbt<T>::~rbt()
{
	delete root;
	return;
}

template<typename T>
typename rbt<T>::node* rbt<T>::find(const T&value)
{
	if(root==nullptr)
		return nullptr;
	node* now=root;
	while(now->value!=value)
	{
		if(now->value>value)
			if(now->lc!=nullptr)
				now=now->lc;
			else
				return now;
		else
			if(now->rc!=nullptr)
				now=now->rc;
			else
				return now;
	}
	return now;
}

template<typename T>
void rbt<T>::rotate(node* x,bool direct)
{
	node* fa=x->fa;
#ifdef SIZE
	auto f=[](node *pt){return pt==nullptr?0:pt->size;};
#endif
	if(direct==LEFT)
	{
		node *l=x->lc;
		if(l==nullptr)
			return;
		l->fa=fa;
		x->lc=l->rc;
		l->rc=x;
		x->fa=l;
		if(x->lc!=nullptr)
			x->lc->fa=x;
		if(fa!=nullptr)
			if(fa->lc==x)
				fa->lc=l;
			else
				fa->rc=l;
		else
			root=l;
#ifdef SIZE
		x->size=f(x->lc)+f(x->rc)+NODE_SIZE(x);
		l->size=f(l->lc)+f(l->rc)+NODE_SIZE(l);
#endif
	}
	if(direct==RIGHT)
	{
		node*r=x->rc;
		if(r==nullptr)
			return;
		r->fa=fa;
		x->rc=r->lc;
		r->lc=x;
		x->fa=r;
		if(x->rc!=nullptr)
			x->rc->fa=x;
		if(fa!=nullptr)
			if(fa->rc==x)
				fa->rc=r;
			else
				fa->lc=r;
		else
			root=r;
#ifdef SIZE
		x->size=f(x->lc)+f(x->rc)+NODE_SIZE(x);
		r->size=f(r->lc)+f(r->rc)+NODE_SIZE(r);
#endif
	}
	return;
}

template<typename T>
void rbt<T>::SolveDoubleRed(node *x)
{
	if(x->fa==nullptr)
	{
		x->col=BLACK;
		return;
	}
	auto checkb=[](node *pt){return pt==nullptr||pt->col==BLACK;};
	if(x->col==BLACK||(checkb(x->fa)&&checkb(x->lc)&&checkb(x->rc)))
		return;
	if(x->fa->col==RED)
	{
		if(checkb(x->fa->fa->lc==x->fa?x->fa->fa->rc:x->fa->fa->lc))
		{
			if((x->fa->fa->lc==x->fa?1:0)!=(x->fa->lc==x?1:0))
			{
				auto tmp=x->fa;
				rotate(x->fa,x->fa->lc==x?LEFT:RIGHT);
				x=tmp;
			}
			x->fa->fa->col=RED;
			x->fa->col=BLACK;
			rotate(x->fa->fa,(x->fa->fa->lc==x->fa)?LEFT:RIGHT);
#ifdef DEBUG
	if(this->root->col==RED)
		throw -1;
#endif
			return;
		}
		else
		{
			x->fa->fa->col=RED;
			if(x->fa->fa->lc!=nullptr)
				x->fa->fa->lc->col=BLACK;
			if(x->fa->fa->rc!=nullptr)
				x->fa->fa->rc->col=BLACK;
			SolveDoubleRed(x->fa->fa);
			return;
		}
	}
}

template<typename T>
void rbt<T>::SolveDoubleBlack(node *x)
{
	if(x->fa==nullptr)
	{
		x->col=BLACK;
		return;
	}
	if((x->fa->lc==x?x->fa->rc:x->fa->lc)==nullptr)
	{
		SolveDoubleBlack(x->fa);
		return;
	}
	if((x->fa->lc==x?x->fa->rc:x->fa->lc)->col==RED)
	{
		rotate(x->fa,x->fa->lc==x?RIGHT:LEFT);
		x->fa->col=RED;
		x->fa->fa->col=BLACK;
		SolveDoubleBlack(x);
		return;
	}
	if((x->fa->lc==x?x->fa->rc:x->fa->lc)->col==BLACK)
	{
		auto cheb=[](node *pt){return pt==nullptr||pt->col==BLACK;};
		if(cheb((x->fa->lc==x?x->fa->rc:x->fa->lc)->lc)&&cheb((x->fa->lc==x?x->fa->rc:x->fa->lc)->rc))
		{
			if(x->fa->col==BLACK)
			{
				(x->fa->lc==x?x->fa->rc:x->fa->lc)->col=RED;
				SolveDoubleBlack(x->fa);
				return;
			}
			else
			{
				(x->fa->lc==x?x->fa->rc:x->fa->lc)->col=RED;
				x->fa->col=BLACK;
				return;
			}
		}
		else
		{
			auto c=(x->fa->lc==x?x->fa->rc:x->fa->lc)->lc;
			if(c==nullptr||c->col==BLACK)
				c=(x->fa->lc==x?x->fa->rc:x->fa->lc)->rc;
			if((c->fa->fa->lc==c->fa?1:0)!=(c->fa->lc==c?1:0))
			{
				if((c->fa->lc==c?c->fa->rc:c->fa->lc)!=nullptr&&(c->fa->lc==c?c->fa->rc:c->fa->lc)->col==RED)
				{
					c=(c->fa->lc==c?c->fa->rc:c->fa->lc);
				}
				else
				{
					c->fa->col=RED;
					c->col=BLACK;
					rotate(c->fa,(c->fa->lc==c?LEFT:RIGHT));
					if(c->lc!=nullptr&&c->lc->col==RED)
						c=c->lc;
					else
						c=c->rc;
				}
			}
			auto co=x->fa->col;
			rotate(x->fa,c->fa==x->fa->lc?LEFT:RIGHT);
			x->fa->col=c->col=BLACK;
			x->fa->fa->col=co;
			return;
		}
	}
}

template<typename T>
typename rbt<T>::iterator rbt<T>::begin()
{
	if(root==nullptr)
		return iterator(nullptr);
	node *now=root;
	while (now->lc!=nullptr)
	{
		now=now->lc;
	}
	return iterator(now);
}

template<typename T>
typename rbt<T>::iterator rbt<T>::end()
{
	return iterator(nullptr);
}

template<typename T>
typename rbt<T>::iterator rbt<T>::insert(const T &x)
{
	if(root==nullptr)
	{
		root=new node(nullptr,x,BLACK);
#ifdef DEBUG
		checkRBT();
#endif
#ifdef SIZE
		root->size=1;
#endif
		return iterator(root);
	}
	node* now=find(x);
	if(now->value==x)
	{
#ifdef MULTIBLE
		now->count++;
		pushup(now->fa);
#endif
#ifdef DEBUG
		checkRBT();
#endif
		return iterator(now);
	}
	if(now->value<x)
	{
		now->rc=new node(now,x,RED);
#ifdef SIZE
		now->rc->size=1;
		pushup(now);
#endif
		SolveDoubleRed(now=now->rc);
	}
	else
	{
		now->lc=new node(now,x,RED);
#ifdef SIZE
		now->lc->size=1;
		pushup(now);
#endif
		SolveDoubleRed(now=now->lc);
	}
#ifdef DEBUG
	checkRBT();
#endif
	return iterator(now);
}

template<typename T>
void rbt<T>::erase(node *x)
{
#ifdef MULTIBLE
	if(NODE_SIZE(x)>1)
		x->count--;
		pushup(x->fa);
		return;
#endif
	node *now=x->fa;
	if(x->lc==nullptr&&x->rc==nullptr)
	{
		if(x->col==BLACK)
			SolveDoubleBlack(x);
		if(now==nullptr)
		{
			delete root;
			root=nullptr;
#ifdef DEBUG
			checkRBT();
#endif
			return;
		}
		else
			if(x->fa->lc==x)
				x->fa->lc=nullptr;
			else
				x->fa->rc=nullptr;
#ifdef SIZE
		x->size=0;
		pushup(x->fa);
#endif
		delete x;
#ifdef DEBUG
		checkRBT();
#endif
		return;
	}
	if(x->lc==nullptr)
	{
		if(now==nullptr)
			root=x->rc;
		else
			if(x==now->lc)
				now->lc=x->rc;
			else
				now->rc=x->rc;
		x->rc->fa=now;
#ifdef SIZE
		pushup(x->fa);
#endif
		if(x->rc->col==RED)
			x->rc->col=x->col;
		else
			if(x->rc->col==BLACK&&x->col==BLACK)
				SolveDoubleBlack(x->rc);
		x->rc=nullptr;
		delete x;
#ifdef DEBUG
		checkRBT();
#endif
		return;
	}
	if(x->rc==nullptr)
	{
		if(now==nullptr)
			root=x->lc;
		else
			if(x==now->lc)
				now->lc=x->lc;
			else
				now->rc=x->lc;
		x->lc->fa=now;
#ifdef SIZE
		pushup(x->fa);
#endif
		if(x->lc->col==RED)
			x->lc->col=x->col;
		else
			if(x->lc->col==BLACK&&x->col==BLACK)
				SolveDoubleBlack(x->lc);
		x->lc=nullptr;
		delete x;
#ifdef DEBUG
		checkRBT();
#endif
		return;
	}
	iterator it(x);
	++it;
	swap(it.pt->value,x->value);
	erase(it.pt);
#ifdef DEBUG
	checkRBT();
#endif
	return;
}

template<typename T>
void rbt<T>::erase(const iterator &it)
{
	erase(it.pt);
	return;
}

template<typename T>
void rbt<T>::erase(const T&x)
{
	node *now=find(x);
	if(now==nullptr)
		return;
	if(now->value==x)
		erase(now);
	return;
}

//tbd

#ifdef DEBUG
template<typename T>
void rbt<T>::checkRBT()const
{
	if(root==nullptr)
		return;
	if(root->col==RED)
		throw -1;
	checkNODE(root);
	return;
}

template<typename T>
size_t rbt<T>::checkNODE(node *x)const
{
	if(x==nullptr)
		return 0;
	size_t black_height=checkNODE(x->lc);
	if(black_height!=checkNODE(x->rc))
		throw -1;
	if(x->col==BLACK)
		return black_height+1;
	return black_height;
}
#endif

#ifdef SIZE
template<typename T>
void rbt<T>::pushup(node *x)
{
	if(x==nullptr)
		return;
	auto f=[](node *pt){return pt==nullptr?0:pt->size;};
	while(x->fa!=nullptr)
	{
		x->size=f(x->lc)+f(x->rc)+NODE_SIZE(x);
		x=x->fa;
	}
	x->size=f(x->lc)+f(x->rc)+NODE_SIZE(x);
	return;
}
#endif

#undef LEFT
#undef RIGHT

#undef RED
#undef BLACK

#include <iostream>
using namespace std;

int main()
{
	int n;
	cin>>n;
	rbt<int> tr;
	for(int i=1;i<=n;i++)
	{
		int f,x;
		cin>>f>>x;
		if(f==1)
			tr.insert(x);
		else
			tr.erase(x);
		for(auto it=tr.begin();it!=tr.end();++it)
			cout<<*it<<' ';
		cout<<endl;
	}
}