#include <iostream>
#include <vector>
using namespace std;

class cardpool;
class game;
class base_pig;
class MP;
class FP;
class ZP;

class cardpool{
	private:
		vector<char> cards;
	public:
		void init(istream&ins,size_t n)
		{
			for(int i=0;i<n;i++)
			{
				char x;
				ins>>x;
				cards.push_back(x);
			}
			return;
		}
		char getcard()
		{
			char ans=*cards.begin();
			if(cards.size()>1)
				cards.erase(cards.begin());
			return ans;
		}
};

class game:public cardpool{
	private:
		vector<base_pig> pigs;
	public:
		void pig_set();
};