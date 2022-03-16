#include <iostream>
using namespace std;

template<typename Int>
class xds{
	private:
		class node{
			public:
				node *lc,*rc;
				Int value,tag;
				virtual ~node(){delete lc,delete rc;}
				node(){lc=rc=nullptr;}
				node(const Int&value){lc=rc=nullptr;this->value=value;tag=0;}
		};
		node *root;
		size_t ln,rn;
		xds(){;}
		static node* build(size_t left,size_t right,Int *a)
		{
			if(right==left+1)
				return new node(a[left]);
			size_t mid=(left+right)/2;
			node *pt=new node;
			pt->lc=build(left,mid,a),pt->rc=build(mid,right,a);
			pt->tag=0,pt->value=pt->lc->value+pt->rc->value;
			return pt;
		}
		static void pushtag(size_t left,size_t right,node *pt)
		{
			if(pt->lc==nullptr)
				return;
			size_t mid=(left+right)/2;
			lc->tag+=pt->tag,rc->tag+=pt->tag;
			lc->value+=pt->tag*(mid-left),rc->value+=pt->tag*(right-mid);
			pt->tag=0;
			return;
		}
		static void add(size_t left,size_t right,size_t l,size_t r,Int x,node* pt)
		{
			if(l<=left&&r>=right)
			{
				pt->value+=(right-left)*x;
				pt->tag+=x;
				return;
			}
			if(l>=right||r<=left)
				return;
			pushtag(left,right,pt);
			size_t mid=(left+right)/2;
			add(left,mid,l,r,x,pt->lc),add(mid,right,l,r,x,pt->rc);
			pt->value=pt->lc->value+pt->rc->value;
			return;
		}
		static Int quest(size_t left,size_t right,size_t l,size_t r,node* pt)
		{
			if(l<=left&&r>=right)
				return pt->value;
			if(l>=right||r<=left)
				return 0;
			pushtag(left,right,pt);
			size_t mid=(left+right)/2;
			return quest(left,mid,l,r,pt->lc)+quest(mid,right,l,r,pt->rc);
		}
	public:
		xds(size_t left,size_t right,Int *a)
		{
			ln=left,rn=right;
			root=build(left,right,a);
			return;
		}
		void add(size_t l,size_t r,Int x)
		{
			add(ln,rn,l,r,x,root);
		}
		Int quest(size_t l,size_t r)
		{
			return quest(ln,rn,l,r,root);
		}
};