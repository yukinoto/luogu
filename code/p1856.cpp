#include <stdio.h>
#include <algorithm>
#include <utility>
#include <vector>
#include <set>
using namespace std;

class line{
	public:
		int x1,x2,y;
		int type;
		line(){}
		bool operator<(const line&x)
		{
			return y==x.y?(x1==x.x1?x2<x.x2:x1<x.x1):y<x.y;
		}
		line(int _x1,int _x2,int _y,int _type)
		{
			x1=_x1,x2=_x2,y=_y,type=_type;
		}
		~line(){}
};
class squ{
	public:
		int x1,x2,y1,y2;
		void get()
		{
			scanf("%d%d%d%d",&x1,&y1,&x2,&y2);
		}
};
pair<line,line> gen1(const squ &x)
{
	return make_pair(line(x.x1,x.x2,x.y1,1),line(x.x1,x.x2,x.y2,-1));
}
pair<line,line> gen2(const squ &x)
{
	return make_pair(line(x.y1,x.y2,x.x1,1),line(x.y1,x.y2,x.x2,-1));
}

namespace tr{
	vector<long long> pt;
	class tree{
		private:
			class node{
				private:
					long long l,r,len,rpt,rpttag;
					node *lc,*rc;
				public:
					node(long long left,long long right)
					{
						l=left,r=right;
						len=0;
						rpt=rpttag=0;
						if(left>=right-1)
						{
							lc=rc=nullptr;
							return;
						}
						long long mid=(left+right)/2;
						lc=new node(left,mid),rc=new node(mid,right);
						return;
					}
					~node()
					{
						delete lc,rc;
					}
					void pushtag()
					{
						if(rpttag==0)
							return;
						auto f=[this](node *ptr)
						{
							if(ptr==nullptr)
								return;
							ptr->rpt+=rpttag;
							ptr->rpttag+=rpttag;
							return;
						};
						f(lc),f(rc);
						rpttag=0;
						return;
					}
					long long quest(long long left,long long right)
					{
						if(lc==nullptr)
							return rpt==0?0:len=pt[r]-pt[l];
						if(left>=r||right<=l||(left>=right-1&&rpt==0))
							return 0;
						pushtag();
						if(left<=l&&right>=r)
						{
							if(rpt!=0)
								return len=pt[r]-pt[l];
							else
								return len=lc->quest(left,right)+rc->quest(left,right);
						}
						return len=lc->quest(left,right)+rc->quest(left,right);
					}
					void add(long long left,long long right,long long x)
					{
						if(left>=r||right<=l)
							return;
						pushtag();
						if(left<=l&&right>=r)
						{
							rpt+=x;
							rpttag+=x;
							return;
						}
						lc->add(left,right,x),rc->add(left,right,x);
						return;
					}
			};
			node *root;
		public:
			tree(long long left,long long right)
			{
				root=new node(left,right);
			}
			~tree(){delete root;}
			void add(long long left,long long right,long long x)
			{
				root->add(left,right,x);
			}
			void add(long long first,long long second,int type)
			{
				root->add(first,second,type);
			}
			long long quest()
			{
				return root->quest(0,pt.size()-1);
			}
	};
}

long long sch(long long x,long long left,long long right)
{
	if(left>=right-1)
		return left;
	if(tr::pt[(left+right)/2]>x)
		return sch(x,left,(left+right)/2);
	else
		return sch(x,(left+right)/2,right);
}

int n;
long long ans=0l;
squ *pt;

void f(decltype(gen1) gen)
{
	line x[10010];
	for(int i=0;i<n;i++)
	{
		auto ct=gen(pt[i]);
		x[i<<1]=ct.first,x[(i<<1)^1]=ct.second;
	}
	sort(x,x+(n<<1));
	set<long long>nodes;
	for(int i=0;i<(n<<1);i++)
	{
		nodes.insert(x[i].x1),
		nodes.insert(x[i].x2);
	}
	tr::pt.clear();
	for(auto it=nodes.begin();it!=nodes.end();++it)
	{
		tr::pt.push_back(*it);
	}
	for(int i=0;i<=(n<<1);i++)
	{
		x[i].x1=sch(x[i].x1,0,tr::pt.size());
		x[i].x2=sch(x[i].x2,0,tr::pt.size());
	}
	tr::tree *t=new tr::tree(0,tr::pt.size());
	long long bef=0l;
	for(int i=0;i<(n<<1);i++)
	{
		t->add(x[i].x1,x[i].x2,x[i].type);
		/*while(i<((n<<1)-1)&&x[i+1].y==x[i].y)
			t->add(x[++i].x1,x[i].x2,x[i].type);*/
		long long now=t->quest();
		ans+=abs(bef-now);
		bef=now;
	}
	delete t;
};

int main()
{
	scanf("%d",&n);
	pt=new squ[n];
	for(int i=0;i<n;i++)
		(pt+i)->get();
	f(gen1),f(gen2);
	printf("%lld",ans);
	return 0;
}
