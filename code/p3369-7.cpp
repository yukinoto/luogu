#define DEBUG

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
				node(const T&value,node *fa):this->value(value),this->fa(fa){;}
		};
		node *root;
		void rotate(node *);
		void splay(node *);
		void pushup(node *);
		void erase(node *);
	public:
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
		friend iterator insert(const T&);
		friend iterator erase(node *);
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

