//rbt

#define DEBUG

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
			size_t size;
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
#ifdef DEBUG
		void checkRBT();
		int checkNODE(node*x);
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
		iterator nth_element(size_t rank);
		size_t get_rank(const T &x);
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
	size=0;
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
		if(checkb(x->fa->lc==x?x->fa->rc:x->fa->lc))
		{
			x->fa->col=BLACK;
			rotate(x->fa->fa,(x->fa->fa->lc==x->fa)?LEFT:RIGHT);
#ifdef DEBUG
	if(this->root->col==RED)
		throw -1;
#endif
			if(x->fa->lc==x)
				if(x->fa->rc!=nullptr)
					x->fa->rc->col=RED;
			else
				if(x->fa->rc!=nullptr)
					x->fa->lc->col=RED;
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
			if(x->fa->col==BLACK)
			{
				if(x->fa->lc==x)
				{
					rotate(x->fa->rc,LEFT);
					rotate(x->fa,RIGHT);
					x->fa->fa->col=BLACK;
#ifdef DEBUG
	if(this->root->col==RED)
		throw -1;
#endif
				}
				else
				{
					rotate(x->fa->lc,RIGHT);
					rotate(x->fa,LEFT);
					x->fa->fa->col=BLACK;
#ifdef DEBUG
	if(this->root->col==RED)
		throw -1;
#endif
				}
			}
			else
			{
				if(x->fa->lc==x)
					rotate(x->fa,RIGHT);
				else
					rotate(x->fa,LEFT);
#ifdef DEBUG
	if(this->root->col==RED)
		throw -1;
#endif
			}
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
		return iterator(root);
	}
	node* now=find(x);
	if(now->value==x)
	{
		return iterator(now);
	}
	if(now->value<x)
	{
		now->rc=new node(now,x,RED);
		SolveDoubleRed(now=now->rc);
	}
	else
	{
		now->lc=new node(now,x,RED);
		SolveDoubleRed(now=now->lc);
	}
	return iterator(now);
}

template<typename T>
void rbt<T>::erase(node *x)
{
	node *now=x->fa;
	if(x->lc==nullptr&&x->rc==nullptr)
	{
		if(now==nullptr)
		{
			root=nullptr;
			return;
		}
		else
			if(x->fa->lc==x)
				x->fa->lc=nullptr;
			else
				x->fa->rc=nullptr;
		delete x;
		SolveDoubleBlack(now);
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
		x->rc->col=BLACK;
		x->rc=nullptr;
		delete x;
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
		x->lc->col=BLACK;
		x->lc=nullptr;
		delete x;
		return;
	}
	iterator it(x);
	++it;
	swap(it.pt->value,x->value);
	erase(it.pt);
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
void rbt<T>::checkRBT()
{
	if(root==nullptr)
		return;
	if(root->col==RED)
		throw -1;
	checkNODE(root);
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