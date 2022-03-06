#include <iostream>
using namespace std;

const int mod=19260817;

class xds{
	private:
		class node{
			public:
				node *lc,*rc;
				int sum;
				bool tag;
				node(){lc=rc=nullptr;};
				~node(){delete lc;delete rc;}
		};
		int quest(int l,int r,int left,int right,node* pt)
		{
			if(left>=r||right<=l)
				return 0;
			if(left<=l&&right>=r)
				return pt->sum;
			int mid=(l+r)/2;
			return (quest(l,mid,left,right,pt->lc)+quest(mid,r,left,right,pt->rc))%mod;
		}
		void set(int l,int r,int left,int right,int x,node* pt)
		{
			if(left>=r||right<=l)
				return;
			if(pt->tag)
				return;
			int mid=(l+r)/2;
			if(left<=l&&right>=r)
			{
				if(l==r-1)
				{
					pt->sum-=pt->sum%x;
					if(pt->sum%60==0)
						pt->tag=true;
					return;
				}
			}
			set(l,mid,left,right,x,pt->lc),set(mid,r,left,right,x,pt->rc);
			pt->tag=pt->lc->tag&&pt->rc->tag;
			pt->sum=(pt->lc->sum+pt->rc->sum)%mod;
			return;
		}
	public:
		node* root;
		int l,r;
		xds(){root=nullptr;}
		xds(int l,int r,int* a)
		{
			this->l=l,this->r=r;
			root=build(l,r,a);
			return;
		}
		node* build(int l,int r,int *a)
		{
			node* ans=new node;
			ans->tag=false;
			if(l==r-1)
			{
				ans->sum=a[l];
				if(ans->sum%60==0)
					ans->tag=true;
				return ans;
			}
			int mid=(l+r)/2;
			ans->lc=build(l,mid,a),ans->rc=build(mid,r,a);
			ans->tag=ans->lc->tag&&ans->rc->tag;
			ans->sum=(ans->lc->sum+ans->rc->sum)%mod;
			return ans;
		}
		void set(int l,int r,int x)
		{
			set(this->l,this->r,l,r,x,root);
		}
		int quest(int l,int r)
		{
			return quest(this->l,this->r,l,r,root);
		}
		~xds(){delete root;}
};

int main()
{
	ios::sync_with_stdio(false);
	int n,m;
	cin>>n>>m;
	int *a=new int[n+1];
	for(int i=1;i<=n;i++)
		cin>>a[i];
	xds tr(1,n+1,a);
	for(int i=0;i<m;i++)
	{
		int op;
		cin>>op;
		if(op==1)
		{
			int l,r,x;
			cin>>l>>r>>x;
			r++;
			tr.set(l,r,x);
		}
		if(op==2)
		{
			int l,r;
			cin>>l>>r;
			r++;
			cout<<tr.quest(l,r)<<'\n';
		}
	}
	return 0;
}