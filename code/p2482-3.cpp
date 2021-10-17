#include <iostream>
#include <sstream>
#include <iomanip>
#include <vector>
#include <string>
using namespace std;

class CardPool{
	private:
		stringstream pool;
		char pre;
	public:
		void init()
		{
			char x[4010];
			cin.getline(x,4010);
			pool.str(x);
			return;
		}
		char get()
		{
			if(pool.str().length())
				return pre;
			pool>>pre;
			return pre;
		}
};

class Card{
	private:
		vector<char>a;
	public:
		class iterator{
			public:
				decltype(a.begin()) it;
				iterator& operator ++()
				{
					++it;
					return *this;
				}
				iterator operator ++(int)
				{
					iterator x=*this;
					++it;
					return x;
				}
				iterator(decltype(it) _it)
				{
					it=_it;
					return;
				}
				bool operator ==(const iterator& x)const
				{
					return it==x.it;
				}
		};
		void init()
		{
			for(int i=0;i<4;i++)
			{
				char x;
				cin>>x;
				a.push_back(x);
			}
			return;
		}
		auto begin()
		{
			iterator x(a.begin());
			return x;
		}
		auto end()
		{
			iterator x(a.end());
			return x;
		}
		void erase(const iterator& p)
		{
			a.erase(p.it);
			return;
		}
};

class Pig{
	private:
		Card card;
		char type,jump;//'N'/'M'/'Z'/'F'/'L'
	public:
		void init()
		{
			char x;
			cin>>type>>x;
			card.init();
			if(type=='M')
				jump='M';
			else
				jump='N';
		}
		void Lo(Pig &target)
		{
			if(this->type=='M')
				return;
			if(target.jump=='Z'||target.jump=='M')
				this->jump='Z';
			if(target.jump=='F')
				this->jump='F';
			return;
		}
		void At(Pig &target)
		{
			if(this->type=='M')
				return;
			if(target.jump=='Z'||target.jump=='M')
				this->jump='F';
			if(target.jump=='F')
				this->jump='Z';
			return;
		}
		bool MP_Lo(Pig &target)
		{
			if(target.jump=='Z')
				return true;
			return false;
		}
		bool MP_At(Pig &target)
		{
			if(target.jump=='F'||target.jump=='L')
				return true;
			return false;
		}
		bool ZP_Lo(Pig &target)
		{
			if(target.jump=='M'||target.jump=='Z')
				return true;
			return false;
		}
		bool ZP_At(Pig &target)
		{
			if(target.jump=='F')
				return true;
			return false;
		}
		bool FP_Lo(Pig &target)
		{
			if(target.jump=='F')
				return true;
			return false;
		}
		bool FP_At(Pig &target)
		{
			if(target.jump=='M'||target.jump=='Z')
				return true;
			return false;
		}
};
