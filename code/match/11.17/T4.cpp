#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

class zxs{
	private:
	class node{
		private:
		int value,tag;
		node *lc,*rc;
		unsigned char tb;
		void ckl()
		{
			if(!(tb&1))
			{
				lc=new node(*lc);
				lc->tb=0;
				tb|=1;
			}
		}
		void ckr()
		{
			if(!(tb&2))
			{
				rc=new node(*rc);
				rc->tb=0;
				tb|=2;
			}
		}
		void ck()
		{
			ckl(),ckr();
		}
		void pushtag(int l,int r)
		{
			if(tag==0||lc==nullptr)
			{
				tag=0;
				return;
			}
			ck();
			int mid=(l+r)/2;
			lc->tag+=tag,rc->tag+=tag;
			lc->value+=(mid-l)*tag,rc->value+=(r-mid)*tag;
			tag=0;
			return;
		}
		public:
		node(int l,int r)
		{
			value=tag=0;
			if(l==r-1)
			{
				lc=rc=nullptr;
				tb=0;
			}
			else
			{
				int mid=(l+r)/2;
				lc=new node(l,mid),rc=new node(mid,r);
				tb=3;
			}
			return;
		}
		~node()
		{
			if(tb&1)
				delete lc;
			if(tb&2)
				delete rc;
			return;
		}
		void add(int l,int r,int left,int right,int x)
		{
			if(left>=r||right<=l)
				return;
			if(left<=l&&right>=r)
			{
				value+=(r-l)*x;
				tag+=x;
				return;
			}
			pushtag(l,r);
			int mid=(l+r)/2;
			ck();
			lc->add(l,mid,left,right,x);
			rc->add(mid,r,left,right,x);
			value=lc->value+rc->value;
			return;
		}
		node *add_gen(int l,int r,int left,int right,int x)
		{
			if(left>=r||right<=l)
				return nullptr;
			if(left<=l&&right>=r)
			{
				node *ans=new node(*this);
				ans->tb=0;
				ans->value+=(r-l)*x;
				ans->tag+=x;
				return ans;
			}
			node *ans=new node(*this);
			ans->tb=0;
			ans->pushtag(l,r);
			int mid=(l+r)/2;
			ans->ck();
			ans->lc->add(l,mid,left,right,x);
			ans->rc->add(mid,r,left,right,x);
			ans->value=ans->lc->value+ans->rc->value;
			return ans;
		}
		int quest(int l,int r,int left,int right)
		{
			if(left>=r||right<=l)
				return 0;
			if(left<=l&&right>=r)
				return value;
			pushtag(l,r);
			int mid=(l+r)/2;
			return lc->quest(l,mid,left,right)+rc->quest(mid,r,left,right);
		}
	};
	vector<node*>root;
	vector<node*>wasted;
	int l,r;
	public:
	zxs(int _l,int _r):l(_l),r(_r)
	{
		root.push_back(new node(l,r));
		return;
	}
	~zxs()
	{
		for_each(wasted.begin(),wasted.end(),[](node *pt){delete pt;});
		for_each(root.begin(),root.end(),[](node *pt){delete pt;});
		return;
	}
	void add_gen(int left,int right,int x,int version)
	{
		root.push_back(root[version]->add_gen(l,r,left,right,x));
		return;
	}
	void add(int left,int right,int x,int version)
	{
		node *ans=root[version]->add_gen(l,r,left,right,x);
		wasted.push_back(root[version]);
		root[version]=ans;
		return;
	}
	int quest(int left,int right,int version)
	{
		return root[version]->quest(l,r,left,right);
	}
};

int main()
{
	int n,m;
	cin>>n>>m;
	zxs tr(1,300001);
	int a[n+1];
	for(int i=1;i<=n;i++)
	{
		cin>>a[i];
		tr.add_gen(a[i],a[i]+1,1,i-1);
	}
	for(int i=0;i<m;i++)
	{
		int f;
		cin>>f;
		if(f==1)
		{
			int l,r,c;
			cin>>l>>r>>c;
			--l;
			int x=tr.quest(c,c+1,r),
			y=tr.quest(c,c+1,l);
			cout<<x-y<<endl;
		}
		if(f==2)
		{
			int x;
			cin>>x;
			tr.add(a[x],a[x]+1,-1,x);
			tr.add(a[x+1],a[x+1]+1,1,x);
			swap(a[x],a[x+1]);
		}
	}
	return 0;
}

//test
/*int main()
{
	int n;
	cin>>n;
	zxs tr(0,n+1);
	for(int i=1;i<=n;i++)
	{
		int x;
		cin>>x;
		tr.add_gen(x,x+1,1,i-1);
	}
	for(int i=1;i<=n;i++)
		cout<<tr.quest(i,i+1,n-1)<<endl;
	return 0;
}*/