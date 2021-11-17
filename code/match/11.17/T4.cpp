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
		bool ln,rn;
		void pushtag(int l,int r)
		{
			if(lc==nullptr)
				return;
			int mid=(l+r)/2;
			if(!ln)
			{
				lc=new node(*lc);
				ln=true;
			}
			if(!rn)
			{
				rc=new node(*rc);
				rn=true;
			}
			lc->value+=(mid-l)*tag;
			lc->tag+=tag;
			rc->value+=(r-mid)*tag;
			rc->tag+=tag;
			tag=0;
			return;
		}
		public:
		node(int l,int r)
		{
			if(l==r-1)
			{
				lc=rc=nullptr;
				value=tag=0;
				ln=rn=false;
			}
			else
			{
				int mid=(l+r)/2;
				lc=new node(l,mid),rc=new node(mid,r);
				value=tag=0;
				ln=rn=true;
			}
		}
		~node()
		{
			if(ln)
				delete lc;
			if(rn)
				delete rc;
		}
		node *add_gen(int l,int r,int left,int right,int x)
		{
			if(left>=r||right<=l)
			{
				return nullptr;
			}
			if(left<=l&&right>=r)
			{
				node *ans=new node(*this);
				ans->value+=(r-l)*x;
				ans->tag+=x;
				ans->ln=ans->rn=false;
				return ans;
			}
			int mid=(l+r)/2;
			node *ans=new node(*this);
			ans->ln=ans->rn=false;
			ans->pushtag(l,r);
			node *pl=nullptr,*pr=nullptr;
			if(ans->ln)
				ans->lc->add(l,mid,left,right,x);
			else
				pl=ans->lc->add_gen(mid,r,left,right,x);
			if(ans->rn)
				ans->rc->add(mid,r,left,right,x);
			else
				pr=ans->rc->add_gen(mid,r,left,right,x);
			if(pl!=nullptr)
			{
				ans->lc=pl;
				ans->ln=true;
			}
			if(pr!=nullptr)
			{
				ans->rc=pr;
				ans->rn=true;
			}
			ans->value=ans->lc->value+ans->rc->value;
			return ans;
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
			int mid=(l+r)/2;
			pushtag(l,r);
			lc->add(l,mid,left,right,x);
			rc->add(mid,r,left,right,x);
			value=lc->value+rc->value;
			return;
		}
		int quest(int l,int r,int left,int right)
		{
			if(left>=r||right<=l)
				return 0;
			if(left<=l&&right>=r)
				return value;
			int mid=(l+r)/2;
			pushtag(l,r);
			return lc->quest(l,mid,left,right)+rc->quest(mid,r,left,right);
		}
	};
	vector<node*>root;
	int l,r;
	public:
	zxs(int _l,int _r):l(_l),r(_r)
	{
		root.push_back(new node(l,r));
		return;
	}
	~zxs()
	{
		for_each(root.begin(),root.end(),[](node*pt){delete pt;});
		return;
	}
	void add(int left,int right,int x,int version)
	{
		root[version]->add(l,r,left,right,x);
		return;
	}
	void add_gen(int left,int right,int x,int version)
	{
		root.push_back(root[version]->add_gen(l,r,left,right,x));
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
	zxs tr(0,n+1);
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
			cout<<tr.quest(c,c+1,r)-tr.quest(c,c+1,l)<<endl;
		}
		if(f==2)
		{
			int x;
			cin>>x;
			tr.add(a[x],a[x]+1,-1,x);
			tr.add(a[x],a[x]+1,1,x+1);
			tr.add(a[x+1],a[x+1]+1,-1,x+1);
			tr.add(a[x+1],a[x+1]+1,1,x);
			swap(a[x],a[x+1]);
		}
	}
	return 0;
}