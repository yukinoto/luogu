#include<vector>
using std::vector;

template<typename T>
class shipt{
	private:
		class node{
			public:
				node *lc,*rc,*fa;
				size_t size,count;
				T value;
				node():lc(nullptr),rc(nullptr),fa(nullptr),size(0),count(0){;}
				~node(){delete lc;delete rc;}
		};
		node*root;
		void rebuild(node *pt);
		node* find(const T&value);
		void erase(node *pt);
	public:
		shipt():root(nullptr){;}
		~shipt(){delete root;}
		class iterator{
			private:
				node *pt;
				iterator(const node* pt);
			public:
				~iterator();
				iterator& operator++();
				iterator& operator--();
				T& operator*();
				bool operator==(const iterator *x)const;
				friend iterator insert(const T&value);
				friend void erase(node *pt);
		};
		iterator insert(const T value);
};