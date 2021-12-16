#include <iostream>
#include <vector>
#include <deque>
using namespace std;

#define MP 1
#define ZP 2
#define FP 3

#define DEAD -1

#define LO 114
#define AT 514
#define ALL 233

#define LP 191
#define AP 908
#define LIK 17

#define MAXHP 4

#define NUL 0

int card_type(char card,int target_action)
{
	if(card=='Z'||card=='W'||card=='N'||card=='P'||card=='D')
		return NUL;
	if(card=='K'||card=='F')
		return AT;
	if((target_action==ALL||target_action==AT)&&card=='J')
		return LO;
	if(target_action==LO&&card=='J')
		return AT;
}

template<typename iterator>
iterator roll_add(iterator it,const iterator&begin,const iterator&end)
{
	++it;
	if(it==end)
		it=begin;
	return it;
}

deque<char> cardpool;

class pig{
	private:
		int _type,_jump,HP;
		bool _arm;
	public:
		deque<char> cards;
		template<typename C>
		pig(int __type,const C&_cards):_type(__type)
		{
			_arm=false;
			for(auto i:_cards)
				cards.push_back(i);
			_jump=NUL;
			HP=MAXHP;
			if(_type==MP)
				_jump=MP;
			return;
		}
		void put_card(char card,int target,int target_action)
		{
			if(_jump==NUL||_jump==LIK)
			{
				int typ=card_type(card,target_action);
				if(typ==ALL&&target==MP)
					_jump=LIK;
				if(typ==AT)
					if(target==MP||target==LP)
						_jump=AP;
					else
						_jump=LP;
				if(typ==LO)
					if(target==MP||target==LP)
						_jump=LP;
					else
						_jump=AP;
			}
			for(auto i=cards.begin();i!=cards.end();++i)
			{
				if(*i==card)
				{
					cards.erase(i);
					break;
				}
			}
			return;
		}
		template<typename C>
		void get_card(C&_cards)
		{
			cards.push_back(*_cards.begin());
			if(_cards.size()>1)
				_cards.pop_front();
			cards.push_back(*_cards.begin());
			if(_cards.size()>1)
				_cards.pop_front();
		}
		int type()
		{
			return _type;
		}
		int jump()
		{
			return _jump;
		}
		bool arm()
		{
			return _arm;
		}
		void throw_card(char card)
		{
			for(auto i=cards.begin();i!=cards.end();++i)
			{
				if(*i==card)
				{
					cards.erase(i);
					break;
				}
			}
			return;
		}
		bool check_card(char card)
		{
			for(auto i=cards.begin();i!=cards.end();++i)
			{
				if(*i==card)
					return true;
			}
			return false;
		}
		void hurt()
		{
			HP--;
			if(HP==0)
				check_P();
			if(HP==0)
				throw DEAD;
			return;
		}
		bool check_K()
		{
			if(check_card('D'))
			{
				throw_card('D');
				return true;
			}
			hurt();
			return false;
		}
		bool check_F(int target)
		{
			if(target==MP&&type()==ZP)
			{
				hurt();
				return false;
			}
			if(check_card('K'))
			{
				throw_card('K');
				return true;
			}
			hurt();
			return false;
		}
		bool check_P()
		{
			if(HP<MAXHP&&check_card('P'))
			{
				throw_card('P');
				HP++;
				return true;
			}
			return false;
		}
		bool put_N()
		{
			throw_card('N');
			return true;
		}
		bool put_W()
		{
			throw_card('W');
			return true;
		}
		bool check_N()
		{
			if(check_card('K'))
			{
				throw_card('K');
				return true;
			}
			hurt();
			return false;
		}
		bool check_W()
		{
			if(check_card('D'))
			{
				throw_card('D');
				return true;
			}
			hurt();
			return false;
		}
		bool put_Z()
		{
			if(check_card('Z'))
			{
				throw_card('Z');
				_arm=true;
				return true;
			}
			return false;
		}
		bool check_K(int target)
		{
			if(check_card('K'))
			{
				if(type()==MP&&(target==AP||target==LIK))
				{
					put_card('K',target,NUL);
					return true;
				}
				if(type()==ZP&&target==AP)
				{
					put_card('K',target,NUL);
					return true;
				}
				if(type()==AP&&(target==LP||target==MP))
				{
					put_card('K',target,NUL);
					return true;
				}
			}
			return false;
		}
};