template <typename T>
inline T max(const T &a,const T &b)
{
	return a>b?a:b;
}
template <typename T>
inline T min(const T &a,const T &b)
{
	return a<b?a:b;
}
template <typename tpe,typename stpe>
class tree{
	protected:
		int l,r;
		class node{
			protected:
				tpe *a;
				node *ls,*rs;
				int l,r;//[)
				stpe sum,tag;
			public:
				node(int left,int right,tpe *data)
				{
					a=data;
					l=left,r=right;
					if(l==r-1)
					{
						ls=rs=nullptr;
						sum=a[l];
						tag=0;
						return;
					}
					int mid=(l+r)/2;
					if(mid>l)
						ls=new node(left,mid,a);
					else
						ls=nullptr;
					if(r>mid)
						rs=new node(mid,right,a);
					else
						rs=nullptr;
					sum=ls->sum+rs->sum;
					tag=0;
					return;
				}
				~node()
				{
					if(ls!=nullptr)
						delete ls;
					if(rs!=nullptr)
						delete rs;
					return;
				}
				void pushdown()
				{
					if(ls!=nullptr)
					{
						ls->tag+=this->tag;
						ls->sum+=(ls->r-ls->l)*this->tag;
					}
					if(rs!=nullptr)
					{
						rs->tag+=this->tag;
						rs->sum+=(rs->r-rs->l)*this->tag;
					}
					this->tag=0;
				}
				void add(int left,int right,int x)
				{
					if(left>=r||right<=l)
						return;
					if(left<=l&&right>=r)
					{
						this->tag+=x;
						this->sum+=(r-l)*x;
						return;
					}
					if(tag!=0)
						this->pushdown();
					this->sum=0;
					if(ls!=nullptr)
					{
						ls->add(left,right,x);
						this->sum+=ls->sum;
					}
					if(rs!=nullptr)
					{
						rs->add(left,right,x);
						this->sum+=rs->sum;
					}
					return;
				}
				stpe quest(int left,int right)
				{
					if(left>=r||right<=l)
						return 0;
					if(left<=l&&right>=r)
						return this->sum;
					if(this->tag!=0)
						this->pushdown();
					stpe ans=0;
					if(ls!=nullptr)
						ans+=ls->quest(left,right);
					if(rs!=nullptr)
						ans+=rs->quest(left,right);
					return ans;
				}
		};
		node *root;
	public:
		tree(tpe *data,int pl,int pr)
		{
			//flexible
			l=pl,r=pr;
			root=new node(l,r,data);
		}
		~tree()
		{
			delete root;
			return;
		}
		void add(int left,int right,tpe x)
		{
			root->add(left,right,x);
			return;
		}
		stpe quest(int left,int right)
		{
			return root->quest(left,right);
		}
};
/*class long_int{
	protected:
		class num{
			public:
				int n;
				num *nxt;
				~num()
				{
					if(nxt!=nullptr)
						delete nxt;
					return;
				}
		};
		num *head,*last;
		bool opr;
	public:
		long_int()
		{
			opr=true;
			last=head=new num;
			head->n=0;
			head->nxt=nullptr;
		}
		template<typename T>
		long_int(T x)
		{
			if(x<0)
			{
				x=-x;
				opr=false;
			}
			else
				opr=true;
			while (x!=0)
			{
				if(last==nullptr)
				{
					head=last=new num;
					last->n=x%10;
					x/=10;
					last->nxt=nullptr;
				}
				else
				{
					last->nxt=new num;
					last=last->nxt;
					last->n=x%10;
					x/=10;
					last->nxt=nullptr;
				}
			}
		}
		~long_int()
		{
			delete head;
			return;
		}
		long_int opo(long_int x)
		{
			x.opr=!x.opr;
			return x;
		}
		long_int operator +(long_int x)
		{
			long_int ans;
			if(!this->opr&&!x.opr)
			{
				ans=opo(*this)+opo(x);
				return opo(ans);
			}
			if(!this->opr)
				return x + (*this);
			if(!x.opr)return;
			num *pt1,*pt2;
			while(pt1!=nullptr&&pt2!=nullptr)
		}
};*/