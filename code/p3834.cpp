#include <iostream>
#include <algorithm>
#include <vector>
#include <map>
using namespace std;

int tog(int l1,int r1,int l2,int r2)
{
	int l=max(l1,l2),r=min(r1,r2);
	if(r>l)
		return r-l;
	return 0;
}

class tree{
	private:
		class node{
			public:
				int value;
				int l,r;
				node *lc,*rc;
				int version;
				node(int left,int right)
				{
					lc=rc=nullptr;
					l=left,r=right;
					value=version=0;
					if(r-l<=1)
						return;
					int mid=(l+r)/2;
					if(l<mid)
						lc=new node(l,mid);
					if(r>mid)
						rc=new node(mid,r);
					return;
				}
				node(const node *from,int left,int right,int val,int ver)//add
				{
					value=from->value;
					l=from->l,r=from->r;
					version=ver;
					int mid=(l+r)/2;
					int len1=tog(left,right,l,mid),len2=tog(left,right,mid,r);
					value+=(len1+len2)*val;
					if(r-l<=1)
					{
						lc=rc=nullptr;
						return;
					}
					if(len1>0)
						lc=new node(from->lc,left,right,val,ver);
					else
						lc=from->lc;
					if(len2>0)
						rc=new node(from->rc,left,right,val,ver);
					else
						rc=from->rc;
				}
				~node()
				{
					if(lc!=nullptr&&lc->version==version)
						delete lc;
					if(rc!=nullptr&&rc->version==version)
						delete rc;
					return;
				}
		};
		vector<node*>root;
	public:
		tree(int left,int right)
		{
			root.push_back(new node(left,right));
			return;
		}
		void add(int left,int right,int value,int ver)
		{
			root.push_back(new node(root[ver],left,right,value,root.size()));
			return;
		}
		int quest(int v1,int v2,int th)
		{
			if(v2<v1)
				swap(v1,v2);
			node *r1=root[v1],*r2=root[v2];
			int cnt=r2->value-r1->value;
			while(r2->r-r2->l>1)
			{
				if(cnt-(r2->rc->value-r1->rc->value)>=th)
				{
					cnt-=r2->rc->value-r1->rc->value;
					r1=r1->lc,r2=r2->lc;
				}
				else
					r1=r1->rc,r2=r2->rc;
			}
			return r1->l;
		}
		~tree()
		{
			for(auto it=root.rbegin();it!=root.rend();it++)
				delete *it;
			return;
		}
};

int a[200010],b[200010];
map<int,int> mp1,mp2;

int main()
{
	int n,m;
	cin>>n>>m;
	for(int i=0;i<n;i++)
	{
		cin>>a[i];
		b[i]=a[i];
	}
	sort(b,b+n);
	for(int i=0;i<n;i++)
	{
		mp1.insert(make_pair(i,b[i]));
		mp2.insert(make_pair(b[i],i));
	}
	tree T(0,n);
	for(int i=0;i<n;i++)
		T.add(mp2[b[i]],mp2[b[i]]+1,1,i);
	for(int i=0;i<m;i++)
	{
		int l,r,k;
		cin>>l>>r>>k;
		cout<<mp1[T.quest(l-1,r,k)]<<endl;
	}
	return 0;
}