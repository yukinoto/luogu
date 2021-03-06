#include <stdio.h>
#include <vector>
#include <set>
#include <algorithm>
using namespace std;

namespace data{
	class node{
		public:
			long long x,y;
			void get()
			{
				scanf("%lld%lld",&x,&y);
			}
			void set(long long _x,long long _y)
			{
				x=_x,y=_y;
			}
			bool operator < (const node &_x)const
			{
				return this->x==_x.x?this->y<_x.y:this->x<_x.x;
			}
			bool operator ==(const node &_x)const
			{
				return this->x==_x.x&&this->y==_x.y;
			}
	};
	class line{
		public:
			int type;
			node first,last;
			bool operator < (const line &_x)const
			{
				return this->first==_x.first?this->last<_x.last:this->first<_x.first;
			}
	};
	line makeline(const node &first,const node &last,int type)
	{
		line x;
		x.first=first,x.last=last,x.type=type;
		return x;
	}
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
			void add(data::line x)
			{
				root->add(x.first.x,x.last.x,x.type);
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

int main()
{
	int n,m;
	scanf("%d",&n);
	n<<=1;
	data::line *a=new data::line[n];
	auto *st=new set<long long>;
	for(int i=0;i<n;i+=2)
	{
		data::node f,s;
		f.get(),s.get();
		st->insert(f.x),st->insert(s.x);
		auto mkn=[](long long x,long long y)->data::node{data::node ans;ans.set(x,y);return ans;};
		a[i]=data::makeline(f,mkn(s.x,f.y),1);
		a[i^1]=data::makeline(mkn(f.x,s.y),s,-1);
	}
	for(auto it=st->begin();it!=st->end();++it)
	{
		tr::pt.push_back(*it);
	}
	m=st->size();
	delete st;
	for(int i=0;i<n;i++)
		a[i].first.x=sch(a[i].first.x,0,m),a[i].last.x=sch(a[i].last.x,0,m);
	tr::tree *t=new tr::tree(0,m-1);
	auto cmp=[](const data::line &a,const data::line &b)->bool const
	{
		return a.first.y<b.first.y;
	};
	sort(a,a+n,cmp);
	t->add(a[0]);
	long long ans=0l;
	for(int i=1;i<n;i++)
	{
		ans+=(a[i].first.y-a[i-1].first.y)*t->quest();
		t->add(a[i]);
	}
	printf("%lld\n",ans);
	delete[] a;
}
