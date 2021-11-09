#include <iostream>
#include <algorithm>
using namespace std;

class matrix{
	public:
		long long a11,a12,a21,a22;
		matrix(){;}
		matrix(long long _a11,long long _a12,long long _a21,long long _a22)
		{a11=_a11,a12=_a12,a21=_a21,a22=_a22;}

};

const long long inf=0x3fffffffffffffffll;

typedef matrix T;
T op(const T x,const T y)
{
	return T
	(max(max(x.a11,y.a11),max(x.a12,y.a21)),max(max(x.a11,y.a12),max(x.a12,y.a22)),
	max(max(x.a21,y.a11),max(x.a22,y.a21)),max(max(x.a21,y.a12),max(x.a22,y.a22)));
}
T pop(const T x,const T y,size_t n)
{
	return op(x,y);
}
T id=matrix(-inf,-inf,-inf,-inf);

class xds{
	private:
		class node{
			public:
				node *lc,*rc;
				T num,tag;
				node(size_t l,size_t r,const T* a)
				{
					if(l==r-1)
					{
						lc=rc=nullptr;
						num=a[l];
						tag=id;
						return;
					}
					else
					{
						size_t mid=(l+r)/2;
						lc=new node(l,mid,a);
						rc=new node(mid,r,a);
						tag=id;
						num=op(lc->num,rc->num);
						return;
					}
				}
				~node()
				{
					delete lc,rc;
				}
				void pushdown(size_t l,size_t r)
				{
					if(lc==nullptr)
					{
						tag=id;
						return;
					}
					size_t mid=(l+r)/2;
					lc->tag=op(lc->tag,tag),rc->tag=op(rc->tag,tag);
					lc->num=pop(lc->num,tag,mid-l),rc->num=pop(rc->num,tag,r-mid);
					tag=id;
					return;
				}
				void add(size_t l,size_t r,size_t left,size_t right,const T&x)
				{
					if(left>=r||right<=l)
						return;
					if(left<=l&&right>=r)
					{
						tag=op(tag,x);
						num=pop(num,x,r-l);
						return;
					}
					pushdown(l,r);
					size_t mid=(l+r)/2;
					lc->add(l,mid,left,right,x);
					rc->add(mid,r,left,right,x);
					num=op(lc->num,rc->num);
					return;
				}
				T quest(size_t l,size_t r,size_t left,size_t right)
				{
					if(left>=r||right<=l)
						return id;
					if(left<=l&&right>=r)
						return num;
					pushdown(l,r);
					size_t mid=(l+r)/2;
					return op(lc->quest(l,mid,left,right),rc->quest(mid,r,left,right));
				}
		};
		node *root;
		size_t l,r;
	public:
		xds(size_t _l,size_t _r,T *a)
		{
			l=_l,r=_r;
			root=new node(l,r,a);
		}
		~xds()
		{
			delete root;
		}
		void add(size_t left,size_t right,const T&x)
		{
			root->add(l,r,left,right,x);
			return;
		}
		T quest(size_t left,size_t right)
		{
			return root->quest(l,r,left,right);
		}
};

//test
/*int main()
{
	size_t n,m;
	cin>>n>>m;
	long long *a=new long long[n];
	for(int i=0;i<n;i++)
		cin>>a[i];
	xds tr(0,n,a);
	for(int i=0;i<m;i++)
	{
		int f;
		cin>>f;
		size_t l,r;
		cin>>l>>r;
		--l;
		if(f==1)
		{
			long long x;
			cin>>x;
			tr.add(l,r,x);
		}
		else
			cout<<tr.quest(l,r)<<endl;
	}
	return 0;
}*/

class tre{
	private:
};