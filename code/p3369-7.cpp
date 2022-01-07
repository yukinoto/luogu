#define DEBUG

#define LEFT true
#define RIGHT false
typedef int size_t;

template<typename T>
class Splay{
	private:
		class node{
			public:
				T value;
				node *fa,*lc,*rc;
				size_t size,cnt;
				node(){;}
				~node(){delete lc,delete rc;}
				node(const T&value,node *fa){this->value=value,this->fa=fa;this->lc=this->rc=nullptr;}
		};
		node *root;
		node* find(const T&)const;
		void rotate(node *,bool);
		void splay(node *);
		void update(node *);
		void pushup(node *);
		void erase(node *);
	public:
		Splay():root(nullptr){;}
		~Splay(){delete root;}
		class iterator;
		iterator insert(const T&);
		void erase(const iterator&);
};

template<typename T>
class Splay<T>::iterator{
	private:
		node *pt;
	public:
		iterator(node *x):pt(x){;}
		iterator& operator ++();
		iterator& operator --();
		const T& operator*();
		friend Splay<T>::iterator Splay<T>::insert(const T&);
		friend Splay<T>::iterator Splay<T>::erase(node *);
};

template<typename T>
typename Splay<T>::iterator& Splay<T>::iterator::operator++()
{
	if(pt->rc!=nullptr)
	{
		pt=pt->rc;
		while(pt->lc!=nullptr)
			pt=pt->lc;
		return *this;
	}
	while(pt->fa!=nullptr&&pt->fa->rc==pt)
		pt=pt->fa;
	pt=pt->fa;
	return *this;
}

template<typename T>
typename Splay<T>::iterator& Splay<T>::iterator::operator--()
{
	if(pt->lc!=nullptr)
	{
		pt=pt->lc;
		while(pt->rc!=nullptr)
			pt=pt->rc;
		return *this;
	}
	while(pt->fa!=nullptr&&pt->fa->lc==pt)
		pt=pt->fa;
	pt=pt->fa;
	return *this;
}

template<typename T>
const T& Splay<T>::iterator::operator*()
{
	return *pt;
}

template<typename T>
void Splay<T>::update(node *pt)
{
	auto gs=[this](node *pt){if(pt==nullptr)return 0;return pt->size;};
	pt->size=gs(pt->lc)+gs(pt->rc)+pt->cnt;
	return;
}

template<typename T>
void Splay<T>::pushup(node *pt)
{
	update(pt);
	if(pt->fa!=nullptr)
		pushup(pt->fa);
	return;
}

//undone! size not maintained!
template<typename T>
void Splay<T>::rotate(node *pt,bool dir)
{
	if (dir==LEFT)
	{
		node *l=pt->lc;
		l->fa=pt->fa;
		pt->lc=l->rc;
		l->rc=pt;
		pt->fa=l;
		if(pt->lc!=nullptr)
			pt->lc->fa=pt;
		if(l->fa!=nullptr)
		{
			if(l->fa->lc==pt)
				l->fa->lc=l;
			else
				l->fa->rc=l;
		}
	}
	else
	{
		node *r=pt->rc;
		r->fa=pt->fa;
		pt->rc=r->lc;
		r->lc=pt;
		pt->fa=r;
		if(pt->rc!=nullptr)
			pt-rc->fa=pt;
		if(r->fa!=nullptr)
		{
			if(r->fa->lc==pt)
				r->fa->lc=r;
			else
				r->fa->rc=r;
		}
	}
	return;
}

template<typename T>
void Splay<T>::splay(node *pt)
{
	auto f=[this](node *pt)->void{if(pt->fa->lc==pt)rotate(pt->fa,LEFT)else rotate(pt->fa,RIGHT);};
	auto dt=[](node *pt)->bool{if(pt->fa->lc==pt)return LEFT;else return RIGHT;};
	while(pt->fa!=nullptr)
	{
		if(pt->fa->fa==nullptr||dt(pt)!=dt(pt->fa))
			f(pt);
		else
			f(pt->fa);
	}
	return;
}

template<typename T>
typename Splay<T>::node* Splay<T>::find(const T&value)const
{
	auto pt=root;
	while(pt->value!=value)
	{
		if(pt->value>value)
		{
			if(pt->lc==nullptr)
				return pt;
			pt=pt->lc;
		}
		else
		{
			if(pt->rc==nullptr)
				return pt;
			pt=pt->rc;
		}
	}
	return pt;
}

template<typename T>
typename Splay<T>::iterator Splay<T>::insert(const T&value)
{
	if(root==nullptr)
	{
		root=new node(value,nullptr);
		root->size=root->cnt=1;
		return iterator(root);
	}
	auto pt=find(value);
	if(pt->value==value)
	{
		pt->cnt++;
		pushup(pt);
		return iterator(pt);
	}
	if(pt->value>value)
	{
		pt->lc=new node(value,pt);
		pt->lc->cnt=pt->lc->size=1;
		pushup(pt);
		return iterator(pt->lc);
	}
	else
	{
		pt->rc=new node(value,pt);
		pt->rc->cnt=pt->rc->size=1;
		pushup(pt);
		return iterator(pt->rc);
	}
}

template<typename T>
void Splay<T>::erase(node *pt)
{
	if(pt->cnt>1)
	{
		pt->cnt--;
		pushup(pt);
		return;
	}
	if(pt->lc==nullptr&&pt->rc==nullptr)
	{
		if(pt->fa==nullptr)
			root=nullptr;
		else
			(pt->fa->lc==pt?pt->fa->lc:pt->fa->rc)=nullptr;
		delete pt;
		return;
	}
	//tbd
}

#undef DEBUG