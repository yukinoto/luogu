#include <iostream>
#include <vector>
#include <string>
#include <utility>
#include <map>
using namespace std;

int null;
const int MP=1,FP=2,ZP=3,AT=4,LO=5,NJP=6,JP=7,LIK=8,MAXBLO=4;

class card;
class pig;
class cardpool;

class card{
	protected:
		char type;
	public:
		char gettype()
		{
			return type;
		}
		friend card* initcard();
		virtual bool put(pig* from,pig* target,int &res)=0;
};

class P:public card{
	public:
		bool put(pig* from,pig* target,int &res);
};
class K:public card{
	public:
		bool put(pig* from,pig* target,int &res);
};
class D:public card{
	public:
		bool put(pig* from,pig* target,int &res);
};

card* initcard();

class pig{
	protected:
		vector<card*> cards;
		int blood,type,ifjp;
	public:
		virtual void init()=0;
		virtual void run()=0;
		virtual ~pig()
		{
			for(auto i:cards)
				delete i;
			return;
		}
		virtual bool ifAT(pig* target)=0;
		virtual bool ifLO(pig* target)=0;
		int gettype(){return type;}
		bool ifdead(){return blood<=0;}
		virtual void bleed();
		bool rct_K();
		void getcard(cardpool&);
		friend bool P::put(pig* from,pig* target,int &res);
};

class MP_P:public pig{
	protected:
		map<pig*,bool>iflik;
	public:
		void init();
		void record(const vector<pig*>&);
		void run();
		bool ifAT(pig* target);
		bool ifLO(pig* target);
		void bleed();
};

class ZP_P:public pig{
	private:
	public:
		void init();
		void run();
		bool ifAT(pig* target);
		bool ifLO(pig* target);
		void bleed();
};

class FP_P:public pig{
	private:
	public:
		void init();
		void run();
		bool ifAT(pig* target);
		bool ifLO(pig* target);
		void bleed();
};

int distance(pig* x,pig* y);

void pig::bleed()
{
	blood--;
	if(blood==0)
	{
		for(auto i=cards.begin();i!=cards.end();++i)
			if((*i)->gettype()=='P')
			{
				(*i)->put(this,this,null);
				delete (*i);
				cards.erase(i);
				break;
			}
	}
	return;
}

bool P::put(pig* from,pig* target,int &res)
{
	if(from->blood>=4)
		return false;
	from->blood++;
	res=0;
	return true;
}

bool K::put(pig* from,pig* target,int &res)
{
	if(target->ifdead()||distance(from,target)>1)
	{
		res=-1;
		return false;
	}
	else
	{
		if(target->rct_K())
		{
			res=-1;
			return true;
		}
		else
		{
			res=1;
			return true;
		}
	}
	abort();
}

bool D::put(pig* from,pig* target,int &res)
{
	res=0;
	return true;
}

bool pig::rct_K()
{
	for(auto i=cards.begin();i!=cards.end();++i)
		if((*i)->gettype()=='D')
		{
			(*i)->put(this,this,null);
			delete (*i);
			cards.erase(i);
			return true;
		}
	return false;
}

card* initcard()
{
	char cache=cin.get();
	while(isspace(cache))
		cache=cin.get();
	if(cache=='P')
	{
		card* pt=new P;
		pt->type='P';
		return pt;
	}
	if(cache=='K')
	{
		card* pt=new K;
		pt->type='K';
		return pt;
	}
	if(cache=='D')
	{
		card* pt=new D;
		pt->type='D';
		return pt;
	}
}

void MP_P::init()
{
	for(int i=0;i<4;++i)
	{
		this->cards.push_back(initcard());
	}
	this->blood=MAXBLO;
	this->type=MP;
	this->ifjp=true;
	return;
}

void MP_P::record(const vector<pig*>&x)
{
	for(auto i:x)
	{
		iflik.insert(make_pair(i,false));
	}
	return;
}

void ZP_P::init()
{
	for(int i=0;i<4;++i)
	{
		this->cards.push_back(initcard());
	}
	this->blood=MAXBLO;
	this->type=ZP;
	this->ifjp=false;
	return;
}

void FP_P::init()
{
	for(int i=0;i<4;++i)
	{
		this->cards.push_back(initcard());
	}
	this->blood=MAXBLO;
	this->type=FP;
	this->ifjp=false;
	return;
}

void MP_P::run()
{
}