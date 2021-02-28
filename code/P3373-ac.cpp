#include <stdio.h>

long long mod;

template <typename inte>
class tree{
	private:
		class node{
			private:
				inte num,jiatag,chengtag;
				int l,r;
				node *lc,*rc;
			public:
				node(const inte *base,int left,int right)
				{
					num=0,jiatag=0,chengtag=1;
					l=left,r=right;
					lc=rc=nullptr;
					if(left>=right-1)
					{
						num=base[left];
						return;
					}
					int mid=(left+right)/2;
					if(mid>left)
					{
						lc=new node(base,left,mid);
						num+=lc->num;
					}
					if(right>mid)
					{
						rc=new node(base,mid,right);
						num+=rc->num;
					}
					return;
				}
				~node()
				{
					delete lc,rc;
					return;
				}
				void pushTag()
				{
					if(jiatag==0&&chengtag==1)
						return;
					auto f=[this](decltype(lc) ptr)
					{
						if(ptr==nullptr) return;
						ptr->num=ptr->num*chengtag%mod;
						ptr->num=ptr->num+jiatag*(ptr->r-ptr->l);
						ptr->chengtag=ptr->chengtag*chengtag%mod;
						ptr->jiatag=ptr->jiatag*chengtag%mod;
						ptr->jiatag=(ptr->jiatag+jiatag)%mod;
						return;
					};
					f(lc);f(rc);
					jiatag=0,chengtag=1;
					return;
				}
				inte quest(int left,int right)
				{
					if(left>=r||right<=l)
						return 0;
					pushTag();
					if(l>=left&&r<=right)
						return num;
					inte ans=0;
					if(lc!=nullptr)
						ans+=lc->quest(left,right);
					if(rc!=nullptr)
						ans+=rc->quest(left,right);
					return ans%mod;;
				}
				void add(int left,int right,inte x)
				{
					if(left>=r||right<=l)
						return;
					pushTag();
					if(left<=l&&right>=r)
					{
						jiatag+=x;
						num+=x*(r-l);
						jiatag%=mod;
						num%=mod;
						return;
					}
					if(lc!=nullptr)
						lc->add(left,right,x);
					if(rc!=nullptr)
						rc->add(left,right,x);
					if(lc!=nullptr&&rc!=nullptr)
						num=(lc->num+rc->num)%mod;
				}
				void ch(int left,int right,inte x)
				{
					if(left>=r||right<=l)
						return;
					pushTag();
					if(left<=l&&right>=r)
					{
						chengtag*=x;
						jiatag*=x;
						num*=x;
						chengtag%=mod;
						jiatag%=mod;
						num%=mod;
						return;
					}
					if(lc!=nullptr)
						lc->ch(left,right,x);
					if(rc!=nullptr)
						rc->ch(left,right,x);
					if(lc!=nullptr&&rc!=nullptr)
					{
						num=(lc->num+rc->num)%mod;
						return;
					}
					/*if(lc!=nullptr)
					{
						num=lc->num;
						return;
					}
					if(rc!=nullptr)
					{
						num=rc->num;
						return;
					}*/
					return;
				}

		};
		node *root;
	public:
		tree(const inte *base,int left,int right)
		{
			root=new node(base,left,right);
			return;
		}
		~tree()
		{
			delete root;
			return;
		}
		inte quest(int left,int right)
		{
			return root->quest(left,right);
		}
		void add(int left,int right,inte x)
		{
			root->add(left,right,x%mod);
			return;
		}
		void ch(int left,int right,inte x)
		{
			root->ch(left,right,x%mod);
			return;
		}
};

void fre()
{
	freopen("P3373_1.in","r",stdin);
	freopen("mas.out","w",stdout);
}

int main()
{
	//fre();
	int n,m;
	scanf("%d%d%lld",&n,&m,&mod);
	long long *a=new long long [n];
	for(int i=0;i<n;++i)
		scanf("%lld",a+i);
	auto* tr=new tree<long long>(a,0,n);
	delete[] a;
	for(int i=0;i<m;++i)
	{
		static int f;
		scanf("%d",&f);
		if(f==1)
		{
			int l,r;
			long long x;
			scanf("%d%d%lld",&l,&r,&x);
			tr->ch(l-1,r,x);
		}else if(f==2)
		{
			int l,r;
			long long x;
			scanf("%d%d%lld",&l,&r,&x);
			tr->add(l-1,r,x);
		}else if(f==3)
		{
			int l,r;
			scanf("%d%d",&l,&r);
			printf("%lld\n",tr->quest(l-1,r));
		}
	}
	delete tr;
	return 0;
}

