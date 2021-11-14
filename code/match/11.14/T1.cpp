#include <iostream>
using namespace std;

template<typename Int>
class xds{
	private:
		class node{
			private:
				Int value;
				Int adtag,tmtag;
				node *lc,*rc;
				void pushtag(size_t l,size_t r)
				{
					if(tmtag!=1)
					{
						lc->adtag*=tmtag;lc->value*=tmtag;
						rc->adtag*=tmtag;rc->value*=tmtag;
						lc->tmtag*=tmtag;rc->tmtag*=tmtag;
						tmtag=1;
					}
					if(adtag!=0)
					{
						lc->adtag+=adtag;rc->adtag+=adtag;
						size_t mid=(l+r)/2;
						lc->value+=(mid-l)*adtag;rc->value+=(r-mid)*adtag;
						adtag=0;
					}
					return;
				}
			public:
				node(size_t l,size_t r,Int *a)
				{
					if(l==r-1)
					{
						value=a[l];
						adtag=0,tmtag=1;
						lc=rc=nullptr;
						return;
					}
					size_t mid=(l+r)/2;
					lc=new node(l,mid,a);
					rc=new node(mid,r,a);
					adtag=0,tmtag=1;
					value=lc->value+rc->value;
					return;
				}
				void add(size_t l,size_t r,size_t left,size_t right,Int x)
				{
					if(left<=l&&right>=r)
					{
						value+=(r-l)*x;
						adtag+=x;
						return;
					}
					if(left>=r||right<=l)
						return;
					size_t mid=(l+r)/2;
					pushtag(l,r);
					lc->add(l,mid,left,right,x),rc->add(mid,r,left,right,x);
					value=lc->value+rc->value;
					return;
				}
				void times(size_t l,size_t r,size_t left,size_t right,Int x)
				{
					if(left<=l&&right>=r)
					{
						value*=x;
						adtag*=x;
						tmtag*=x;
						return;
					}
					if(left>=r||right<=l)
						return;
					size_t mid=(l+r)/2;
					pushtag(l,r);
					lc->times(l,mid,left,right,x),rc->times(mid,r,left,right,x);
					value=lc->value+rc->value;
					return;
				}
				Int quest(size_t l,size_t r,size_t left,size_t right)
				{
					if(left<=l&&right>=r)
						return value*(r-l);
					if(left>=r||right<=l)
						return 0;
					size_t mid=(l+r)/2;
					pushtag(l,r);
					return lc->quest(l,mid,left,right)+rc->quest(mid,r,left,right);
				}
				~node()
				{
					delete lc,rc;
				}
		};
		node *root;
		size_t l,r;
	public:
		xds(size_t _l,size_t _r,Int *a)
		{
			l=_l,r=_r;
			root=new node(l,r,a);
		}
		void add(size_t left,size_t right,Int x)
		{
			root->add(l,r,left,right,x);
		}
		void times(size_t left,size_t right,Int x)
		{
			root->times(l,r,left,right,x);
		}
		Int quest(size_t left,size_t right)
		{
			return root->quest(l,r,left,right);
		}
		~xds()
		{
			delete root;
		}
};

/*int main()
{
	int n,q;
	cin>>n>>q;
	int a[n];
	for(int i=0;i<n;i++)
		cin>>a[i];
	xds<int> tr(0,n,a);
	for(int i=0;i<q;i++)
	{
		int f,l,r;
		cin>>f>>l>>r;
		if(f==1)
		{
			cout<<tr.quest(l,r);
		}
		if(f==2)
		{
			int x;
			cin>>x;
			tr.add(l,r,x);
		}
		if(f==3)
		{
			int x;
			cin>>x;
			tr.times(l,r,x);
		}
	}
	return 0;
}*/

xds<int>*p,*q;
int x[500000],y[500000];
char f[500000];
int v1[500000],v2[500000];

int main()
{
	int n,m;
	cin>>n>>m;
	for(int i=0;i<n;i++)
	{
		cin>>x[i]>>y[i];
	}
	p=new xds<int>(0,n,x),q=new xds<int>(0,n,y);
	for(int i=0;i<m;i++)
	{
		cin>>f[i];
		if(f[i]=='m')
			cin>>v1[i]>>v2[i];
	}
	for(int i=m-1;i>=0;i--)
	{
		if(f[i]=='m')
		{
			p->add(0,n,v1[i]),q->add(0,n,v2[i]);
		}
		if(f[i]=='x')
		{
			p->times(0,n,-1);
		}
		if(f[i]=='y')
		{
			q->times(0,n,-1);
		}
	}
	for(int i=0;i<n;i++)
		cout<<p->quest(i,i+1)<<' '<<q->quest(i,i+1)<<endl;
	return 0;
}