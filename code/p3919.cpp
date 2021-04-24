#include <stdio.h>
#include <vector>
using namespace std;

template<typename T>
inline T max(const T &a,const T &b)
{
	return a>b?a:b;
}
template<typename T>
inline T min(const T &a,const T &b)
{
	return a<b?a:b;
}

template <typename T>
class tree{
	private:
		class node{
			private:
				node *son[2];
				T sum;
			public:
				node(const int &left,const int &right,T *base)
				{
					if(left==right-1)
					{
						sum=base[left];
						for(auto &i:son)
							i=nullptr;
						return;
					}
					int mid=(left+right)>>1;
					son[0]=new node(left,mid,base);
					son[1]=new node(mid,right,base);
					return;
				}
				~node()
				{
					for(auto i:son)
						delete i;
					return;
				}
				T ask(const int &left,const int &right,const int &l,const int &r)
				{
					if(l>=right||r<=left)
						return 0;
					if(l>=left&&r<=right)
						return sum;
					T ans=0;
					if(son[0]!=nullptr)
						ans+=son[0]->ask(left,right,l,(l+r)>>1);
					if(son[1]!=nullptr)
						ans+=son[1]->ask(left,right,(l+r)>>1,r);
					return ans;
				}
				node(int left,int right,node *from,int p,T x)
				{
					for(int i=0;i<2;i++)
						son[i]=from->son[i];
					if(left==right-1&&left==p)
					{
						sum=x;
						return;
					}
					int mid=(left+right)>>1;
					if(mid>left&&p<mid)
						son[0]=new node(left,mid,son[0],p,x);
					if(right>mid&&p>=mid)
						son[1]=new node(mid,right,son[1],p,x);
					return;
				}
		};
		vector<node*> roots;
		int l,r;
	public:
		tree(int left,int right,T *base)
		{
			l=left,r=right;
			roots.push_back(new node(left,right,base));
			return;
		}
		~tree()
		{
			for(auto i:roots)
				delete i;
		}
		void change(int p,T x,int version)
		{
			roots.push_back(new node(l,r,roots[version],p,x));
			return;
		}
		T ask(int p,int version)
		{
			roots.push_back(roots[version]);
			return roots[version]->ask(p,p+1,l,r);
		}
};

void func1(int version,tree<int> *tr)
{
	static int p,x;
	scanf("%d%d",&p,&x);
	tr->change(p-1,x,version);
	return;
}

void func2(int version,tree<int> *tr)
{
	static int p;
	scanf("%d",&p);
	printf("%d\n",tr->ask(p-1,version));
	return;
}

void func(int version,tree<int> *tr)
{
	static int f;
	scanf("%d",&f);
	if(f==1)
		func1(version,tr);
	if(f==2)
		func2(version,tr);
	return;
}

int main()
{
	int n,m;
	scanf("%d%d",&n,&m);
	int *pt=new int[n];
	for(int i=0;i<n;i++)
		scanf("%d",pt+i);
	tree<int>* tr=new tree<int>(0,n,pt);
	for(int i=0;i<m;i++)
	{
		static int version;
		scanf("%d",&version);
		func(version,tr);
	}
	return 0;
}