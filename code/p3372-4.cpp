#include <stdio.h>

#define nulltag 0
#define jia 1
#define cheng 2

template <typename inte>
class tree{
	private:
		class node{
			private:
				inte num,tag;
				int tagType,l,r;
				node *lc,*rc;
			public:
				node(const inte *base,int left,int right)
				{
					num=0,tag=0,tagType=0;
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
					if(tagType==nulltag)
						return;
					if(tagType==jia)
					{
						if(lc!=nullptr)
						{
							lc->pushTag();
							lc->tagType=jia;
							lc->tag=tag;
							lc->num+=(lc->r-lc->l)*lc->tag;
						}
						if(rc!=nullptr)
						{
							rc->pushTag();
							rc->tagType=jia;
							rc->tag=tag;
							rc->num+=(rc->r-rc->l)*rc->tag;
						}
					}
					if(tagType==cheng)
					{
						if(lc!=nullptr)
						{
							lc->pushTag();
							lc->tagType=cheng;
							lc->tag=tag;
							lc->num*=lc->tag;
						}
						if(rc!=nullptr)
						{
							rc->pushTag();
							rc->tagType=cheng;
							rc->tag=tag;
							rc->num*=rc->tag;
						}
					}
					tagType=nulltag;
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
						ans+=lc->quest();
					if(rc!=nullptr)
						ans+=rc->quest();
				}
				void add(int left,int right,inte x)
				{
					if(left>=r||right<=l)
						return;
					if(tagType!=jia)
					{
						pushTag();
						tagType=jia;
						tag=0;
					}
					if(left>=l&&right<=r)
					{
						tag+=x;
						num+=x*(r-l);
						return;
					}
					num=0;
					if(lc!=nullptr)
					{
						lc->add(left,right,x);
						num+=lc->num;
					}
					if(rc!=nullptr)
					{
						rc->add(left,right,x);
						num+=rc->num;
					}
				}
				void ch(int left,int right,inte x)
				{
					if(left>=r||right<=l)
						return;
					if(tagType!=cheng)
					{
						pushTag();
						tagType=cheng;
						tag=1;
					}
					if(left>=l&&right<=r)
					{
						tag*=x;
						num*=x;
						return;
					}
					num=0;
					if(lc!=nullptr)
					{
						lc->ch(left,right,x);
						num+=lc->num;
					}
					if(rc!=nullptr)
					{
						rc->ch(left,right,x);
						num+=rc->num;
					}
				}

		};
		node *root;
	public:
		tree(const inte *base,left,right)
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
			root->add(left,right,x);
			return;
		}
		void ch(int left,int right,inte x)
		{
			root->ch(left,right,x);
			return;
		}
};

int main()
{
	int n,m,p;
	scanf("%d%d%*d",&n,&m);
	long long *a=new long long [n];
	for(int i=0;i<n;++i)
		scanf("%lld",a+i);
	auto* tr=new tree<long long>(a,0,n);
	for(int i=0;i<m;++i)
	{
		static int f;
		scanf("%d",&f);
		if(f==1)
		{
			int l,r,x;
			scanf("%d%d%d",&l,&r,&x);
			tr->ch(l,r,x);
		}else if(f==2)
		{
			int l,r,x;
			scanf("%d%d%d",&l,&r,&x);
			tr->add(l,r,x);
		}else if(f==3)
		{
			int l,r;
			scanf("%d%d",&l,&r);
			printf("%d\n",tr->quest(l,r));
		}
	}
	delete tr;
	delete[] a;
	return;
}