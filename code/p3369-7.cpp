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
				node(const T&value,node *fa){this->value=value,this->fa=fa;}
		};
		node *root;
		void rotate(node *,bool);
		void splay(node *);
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

#undef DEBUG