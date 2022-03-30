const int MAXBIT=2,MAXW=(1<<MAXBIT);

class trie{
	private:
		class node{
			public:
				node *sons;
				int cnt;
				node(){cnt=0;sons=nullptr;};
				virtual ~node(){delete[] sons;}
		};
		node *root;
		bool erase(node *pt,unsigned x,int bits)
		{
			if(pt->sons==nullptr||pt->cnt==0)
				return false;
			if(bits==0)
			{
				if(pt->sons[x&(MAXW-1)].cnt>0)
				{
					pt->sons[x&(MAXW-1)].cnt--;
					pt->cnt--;
					return true;
				}
				else
					return false;
			}
			if(erase(pt->sons+((x>>bits)&(MAXW-1)),x,bits-MAXBIT))
			{
				pt->cnt--;
				return true;
			}
			return false;
		}
		unsigned fmin(node *pt,unsigned way,int bits)
		{
			if(bits==0&&pt->cnt!=0)
				return way;
			if(pt->sons==nullptr||pt->cnt==0)
				return 0xffffffff;
			for(int i=0;i<MAXW;i++)
				if(pt->sons[i].cnt>0)
					return fmin(pt->sons+i,way|(i<<(bits-MAXBIT)),bits-MAXBIT);
			return 0xffffffff;
		}
		unsigned fmax(node *pt,unsigned way,int bits)
		{
			if(bits==0&&pt->cnt!=0)
				return way;
			if(pt->sons==nullptr||pt->cnt==0)
				return 0xffffffff;
			for(int i=MAXW-1;i>=0;i--)
				if(pt->sons[i].cnt>0)
					return fmax(pt->sons+i,way|(i<<(bits-MAXBIT)),bits-MAXBIT);
			return 0xffffffff;
		}
		unsigned bef(node *pt,unsigned x,unsigned way,int bits)
		{
			if(pt->sons==nullptr||pt->cnt==0)
				return 0xffffffff;
			if((x&~((1ull<<bits)-1))==(way&~((1ull<<bits)-1)))
			{
				int tmp=(x>>(bits-MAXBIT))&(MAXW-1);
				unsigned ref=bef(pt->sons+tmp,x,way|(tmp<<(bits-MAXBIT)),bits-MAXBIT);
				if(ref!=0xffffffff)	return ref;
				for(int i=tmp-1;i>=0;i--)
				{
					ref=fmax(pt->sons+i,way|(i<<(bits-MAXBIT)),bits-MAXBIT);
					if(ref!=0xffffffff)
						return ref;
				}
				return 0xffffffff;
			}
			else
			{
				return fmax(pt,way,bits);
			}
		}
		unsigned aft(node *pt,unsigned x,unsigned way,int bits)
		{
			if(pt->sons==nullptr||pt->cnt==0)
				return 0xffffffff;
			if((x&~((1ull<<bits)-1))==(way&~((1ull<<bits)-1)))
			{
				int tmp=(x>>(bits-MAXBIT))&(MAXW-1);
				int ref=aft(pt->sons+tmp,x,way|(tmp<<(bits-MAXBIT)),bits-MAXBIT);
				if(ref!=0xffffffff)	return ref;
				for(int i=tmp+1;i<MAXW;i++)
				{
					ref=fmin(pt->sons+i,way|(i<<(bits-MAXBIT)),bits-MAXBIT);
					if(ref!=0xffffffff)
						return ref;
				}
				return 0xffffffff;
			}
			else
			{
				return fmin(pt,way,bits);
			}
		}
	public:
		trie(){root=new node;}
		virtual ~trie(){delete root;}
		void insert(unsigned x)
		{
			if(bef(x+1)==x)
				return;
			node *pt=root;
			for(int i=32-MAXBIT;i>=0;i-=MAXBIT)
			{
				if(pt->sons==nullptr)
					pt->sons=new node[MAXW];
				pt->cnt++;
				pt=pt->sons+((x>>i)&(MAXW-1));
			}
			pt->cnt++;
			return;
		}
		void erase(unsigned x)
		{
			erase(root,x,32-MAXBIT);
			return;
		}
		unsigned bef(unsigned x)
		{
			return bef(root,x,0,32);
		}
		unsigned aft(unsigned x)
		{
			return aft(root,x,0,32);
		}
};

#include <iostream>
using namespace std;
//test

/*int main()
{
	int n;
	cin>>n;
	trie tr;
	for(int i=0;i<n;i++)
	{
		int op,x;
		cin>>op>>x;
		if(op==0)
		{
			tr.insert(x);
		}
		if(op==1)
		{
			tr.erase(x);
		}
		if(op==2)
		{
			cout<<tr.bef(x)<<endl;
		}
		if(op==3)
		{
			cout<<tr.aft(x)<<endl;
		}
	}
	return 0;
}*/

#include <cstdio>
namespace GenHelper{
    unsigned z3, z4, b;
    inline unsigned rand_(){
        z3 = ((z3 & 4294967280U) << 7) ^ ((z3 << 13) ^ z3) >> 21;
        z4 = ((z4 & 4294967168U) << 13) ^ ((z4 << 3) ^ z4) >> 12;
        return (z3 ^ z4);
    }
}
inline void srand_(unsigned x){
    using namespace GenHelper;
    z3 = x ^ 0x1234598766U;
    z4 = (~x) + 51;
}
int ans;
trie tr;
inline void work(){
	int x = GenHelper::rand_() & ((1 << 30) - 1), op = (GenHelper::rand_() >> 15) & 3;
  	if(op==0)
	  tr.insert(x);
	if(op==1)
		tr.erase(x);
	if(op==2)
	{
		unsigned ref=tr.bef(x);
		if(ref!=0xffffffff)ans^=ref;
	}
	if(op==3)
	{
		unsigned ref=tr.aft(x);
		if(ref!=0xffffffff)ans^=ref;
	}
	return;
}
int n, seed;
int main(){
	cin>>n>>seed;
    srand_(seed);
    while(n --) work();
    cout<<ans<<endl;
}