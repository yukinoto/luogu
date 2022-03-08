#include <stddef.h>
#include <algorithm>

template<typename Int>
class leftistheap{
	protected:
		class node;
		node* root;
		size_t siz;
		leftistheap(const Int &x);
		static node* merge(node* x,node* y);
	public:
		leftistheap();
		template<typename Iterator>
		leftistheap(const Iterator &begin,const Iterator &end);
		virtual ~leftistheap();
		void merge(leftistheap &x);
		void push(const Int &x);
		Int top()const;
		void pop();
		size_t size()const;
};


template<typename Int>
class leftistheap<Int>::node{
	public:
		Int value;
		node *lc,*rc;
		size_t dist;
		node();
		node(const Int &x);
		virtual ~node();
};

template<typename Int>
leftistheap<Int>::node::node()
{
	lc=rc=nullptr;
	dist=0;
	return;
}

template<typename Int>
leftistheap<Int>::node::node(const Int &x)
{
	lc=rc=nullptr;
	dist=0;
	value=x;
	return;
}

template<typename Int>
leftistheap<Int>::node::~node()
{
	delete lc;delete rc;
	return;
}


template<typename Int>
leftistheap<Int>::leftistheap(const Int &x)
{
	root=new leftistheap<Int>::node(x);
	siz=1;
	return;
}

template<typename Int>
leftistheap<Int>::leftistheap()
{
	root=nullptr;
	siz=0;
	return;
}

template<typename Int>
template<typename Iterator>
leftistheap<Int>::leftistheap(const Iterator&begin,const Iterator&end)
{
	auto i=begin;
	root=new node(*i);
	root->lc=root->rc=nullptr,siz=1;
	++i;
	leftistheap<Int> tmp;
	for(;i!=end;++i)
		merge(tmp=leftistheap<Int>(*i));
	return;
}

template<typename Int>
class leftistheap<Int>::node* leftistheap<Int>::merge(class leftistheap<Int>::node *x,class leftistheap<Int>::node *y)
{
	if(x==nullptr)
		return y;
	if(y==nullptr)
		return x;
	if(y->value<x->value)
		std::swap(x,y);
	x->rc=merge(x->rc,y);
	if(x->lc==nullptr||(x->rc!=nullptr&&(x->lc->dist<x->rc->dist)))
	{
		std::swap(x->lc,x->rc);
		if(x->rc!=nullptr)
			x->dist=x->rc->dist+1;
		else
			x->dist=0;
	}
	return x;
}

template<typename Int>
void leftistheap<Int>::merge(leftistheap &x)
{
	siz+=x.siz;
	root=merge(root,x.root);
	x.root=nullptr;
	return;
}

template<typename Int>
leftistheap<Int>::~leftistheap()
{
	delete root;
	return;
}

template<typename Int>
void leftistheap<Int>::push(const Int &x)
{
	leftistheap<Int> tmp(x);
	merge(tmp);
	return;
}

template<typename Int>
Int leftistheap<Int>::top()const
{
	return root->value;
}

template<typename Int>
void leftistheap<Int>::pop()
{
	siz--;
	node *pt1=root->lc,*pt2=root->rc;
	root->lc=root->rc=nullptr;
	delete root;
	root=merge(pt1,pt2);
	return;
}

template<typename Int>
size_t leftistheap<Int>::size()const
{
	return siz;
}