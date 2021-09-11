#include <iostream>
#include <sstream>
#include <map>
#include <vector>
using namespace std;

map<string,double> chem;

void reset()
{
	chem.insert(make_pair("H",1));
	chem.insert(make_pair("C",12));
	chem.insert(make_pair("N",14));
	chem.insert(make_pair("O",16));
	chem.insert(make_pair("F",19));
	chem.insert(make_pair("Na",23));
	chem.insert(make_pair("Mg",24));
	chem.insert(make_pair("Al",27));
	chem.insert(make_pair("Si",28));
	chem.insert(make_pair("P",31));
	chem.insert(make_pair("S",32));
	chem.insert(make_pair("Cl",35.5));
	chem.insert(make_pair("K",39));
	chem.insert(make_pair("Ca",40));
	chem.insert(make_pair("Mn",55));
	chem.insert(make_pair("Fe",56));
	chem.insert(make_pair("Cu",64));
	chem.insert(make_pair("Zn",65));
	chem.insert(make_pair("Ag",108));
	chem.insert(make_pair("I",127));
	chem.insert(make_pair("Ba",137));
	chem.insert(make_pair("Hf",178.5));
	chem.insert(make_pair("Pt",195));
	chem.insert(make_pair("Au",197));
	chem.insert(make_pair("Hg",201));

}

stringstream ist;

int checknxt()
{
	char x;
	ist>>x;
	ist.putback(x);
	if(x>='A'&&x<='Z')
		return 0;
	if(x=='_')
		return 1;
	if(x=='(')
		return 2;
	if(x=='~')
		return 3;
	if(x==')')
		return 4;
	if(x=='~')
		return 5;
	return -1;
}

string getchem()
{
	char x;
	stringstream ans;
	ist>>x;
	ans<<x;
	ist>>x;
	if(x>='a'&&x<='z')
		ans<<x;
	else
		ist.putback(x);
	return ans.str();
}

int getnum()
{
	char x;
	int ans;
	ist>>x;
	if(x=='~')
	{
		if(checknxt()==0)
			ans=1;
		else
			ist>>ans;
	}
	if(x=='_')
		ist>>x>>ans>>x;
	return ans;
}

class block{
	public:
		vector<block> b;
		int num;
		double g;
		char cache;
		void init()
		{
			num=1;g=0;
			while(true)
			{
				int st=checknxt();
				if(st==2)
				{
					ist>>cache;
					block x;
					x.init();
					b.push_back(x);
					g+=x.g*x.num;
				}
				if(st==0)
				{
					string x=getchem();
					int n=1;
					if(checknxt()==1)
						n=getnum();
					g+=chem[x]*n;
				}
				if(st==4)
				{
					ist>>cache;
					if(checknxt()==1)
						num=getnum();
					return;
				}
				if(st==-1)
					return;
				if(st==3)
				{
					block x;
					int n=getnum();
					x.init();
					x.num=n;
					g+=x.g*x.num;
					b.push_back(x);
				}
			}
		}
};

int main()
{
	reset();
	string cache;
	cin>>cache;
	ist<<cache<<',';
	block x;
	x.init();
	cout<<x.g*x.num<<endl;
	return 0;
}