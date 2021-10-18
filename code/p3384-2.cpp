#include <iostream>
#include <algorithm>
using namespace std;

long long p;

template <typename T>
class xds{
	private:
		class node{
			private:
				T num,tag;
				node *lc,*rc;
				node(int l,int r,T *a)
				{
					tag=0;
					if(r==l+1)
					{
						lc=rc=nullptr;
						num=a[l]%p;
						return;
					}
					int mid=(l+r)/2;
					lc=new node(l,mid,a);
					rc=new node(r,mid,a);
					num=lc->num+rc->num%p;
					return;
				}
				~node()
				{
					if(lc!=nullptr)
						delete lc;
					if(rc!=nullptr)
						delete rc;
					return;
				}
				void add(int l,int r,int left,int right,const T &x)
				{
					if(min(right,r)<=max(left,l))
						return;
					if(l>=left&&r<=right)
					{
						tag=(tag+x)%p;
						num=(num+x*(r-l))%p;
						return;
					}
					int mid=(l+r)/2;
					lc->add(l,mid,left,right,x);
					rc->add(mid,r,left,right,x);
					num=(num+(min(r,right)-max(l,left)*x))%p;
					return;
				}
				void getTag(int l,int r,T _tag)
				{
					num=(num+_tag*(r-l))%p;
					tag=(tag+_tag)%p;
					return;
				}
				void pushTag(int l,int r)
				{
					if(lc!=nullptr)
					{
						int mid=(l+r)/2;
						lc->getTag(l,mid,tag);
						rc->getTag(mid,r,tag);
					}
					tag=0;
					return;
				}
				T quest(int l,int r,int left,int right)const
				{
					if(min(right,r)<=max(left,l))
						return 0;
					if(l>=left&&r<=right)
					{
						return num;
					}
					int mid=(l+r)/2;
					pushTag(l,r);
					return (lc->quest(l,mid,left,right)+rc->quest(mid,r,left,right))%p;
				}
		};
		node *root;
		int l,r;
		xds(int left,int right,T *a)
		{
			l=left,r=right;
			root=new node(l,r,a);
			return;
		}
		~xds()
		{
			delete root;
		}
		void add(int left,int right,T x)
		{
			root->add(l,r,left,right,x);
			return;
		}
		T quest(int left,int right)const
		{
			return root->quest(l,r,left,right);
		}
};
