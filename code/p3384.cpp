#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
using namespace std;

long long p;

template<typename T>//[)
class xds{
	private:
		class node{
			private:
				T num,tag;
				node *lc,*rc;
				T getnum()
				{
					if(this==nullptr)
						return 0;
					return num;
				}
				void refresh()
				{
					num=(lc->getnum()+rc->getnum())%p;
					return;
				}
				void getup(const T &uptag,const int &left,const int &right)
				{
					if(this==nullptr)
						return;
					tag+=uptag;
					num+=(right-left)*uptag;
					tag%=p,num%=p;
					return;
				}
				void pushdown(const int &left,const int &right)
				{
					int mid=(left+right)/2;
					lc->getup(tag,left,mid),rc->getup(tag,mid,right);
					tag=0;
					return;
				}
			public:
				node(const T *base,const int &left,const int &right)
				{
					tag=0;
					lc=rc=nullptr;
					if(left==right-1)
					{
						num=base[left]%p;
						return;
					}
					int mid=(left+right)/2;
					if(mid>left)
						lc=new node(base,left,mid);
					if(right>mid)
						rc=new node(base,mid,right);
					refresh();
				}
				T quest(const int &l,const int &r,const int &left,const int &right)
				{
					if(this==nullptr)
						return 0;
					if(l<=left&&r>=right)
						return num;
					pushdown(left,right);
					if(l>=right||r<=left)
						return 0;
					int mid=(left+right)/2;
					return (lc->quest(l,r,left,mid)+rc->quest(l,r,mid,right))%p;
				}
				void add(const int &l,const int &r,const T &x,const int &left,const int &right)
				{
					if(this==nullptr)
						return;
					if(l<=left&&r>=right)
					{
						getup(x,left,right);
						return;
					}
					if(l>=right||r<=left)
						return;
					int mid=(left+right)/2;
					pushdown(left,right);
					lc->add(l,r,x,left,mid),rc->add(l,r,x,mid,right);
					refresh();
				}
				~node(){delete lc;delete rc;}
		};
		int l,r;
	public:
		node *root;
		xds(const T *base,const int &left,const int &right)
		{
			root=new node(base,left,right);
			l=left,r=right;
			return;
		}
		void add(const int &left,const int &right,const T &x)
		{
			root->add(left,right,x,l,r);
		}
		T quest(const int &left,const int &right)
		{
			return root->quest(left,right,l,r);
		}
		~xds(){delete root;}
};
//test
/*int main()
{
	int n,q;
	scanf("%d%d",&n,&q);
	long long *a=new long long[n];
	for(int i=0;i<n;i++)
		scanf("%lld",a+i);
	xds<long long> *tr=new xds<long long>(a,0,n);
	for(int i=0;i<q;i++)
	{
		int f;
		scanf("%d",&f);
		if(f==1)
		{
			int l,r;
			long long x;
			scanf("%d%d%lld",&l,&r,&x);
			tr->add(l-1,r,x);
		}
		else
		{
			int l,r;
			scanf("%d%d",&l,&r);
			printf("%lld\n",tr->quest(l-1,r));
		}
		
	}
	delete a;delete tr;
}*/

template<typename T>
struct node{
	T weight;
	vector<int>sons;
	int sig,heav,top,deepth,fa,size;
};

long long n,m,r;
vector<int>*to;
node<long long>*nodes;
long long int *a;
xds<long long> *xd;

void dfs1(const int &p,const int &deepth,const int &fa)
{
	nodes[p].deepth=deepth,nodes[p].fa=fa,nodes[p].size=1,nodes[p].heav=-1;
	for(int i:nodes[p].sons)
	{
		dfs1(i,deepth+1,p);
		nodes[p].size+=nodes[i].size;
		if(nodes[p].heav==-1||nodes[i].size>nodes[nodes[p].heav].size)
			nodes[p].heav=i;
	}
	return;
}

void dfs2(const int &p,const int &top)
{
	if(p==-1)
		return;
	static int cnt=0;
	nodes[p].sig=cnt++;
	a[nodes[p].sig]=nodes[p].weight;
	nodes[p].top=top;
	dfs2(nodes[p].heav,top);
	for(int i:nodes[p].sons)
		if(i!=nodes[p].heav)
			dfs2(i,i);
}

bool *taken;
void mkt(int p)
{
	for(int i:to[p])
		if(!taken[i])
		{
			taken[i]=true;
			nodes[p].sons.push_back(i);
			mkt(i);
		}
	return;
}

void buildtree()
{
	cin>>n>>m>>r>>p;
	nodes=new node<long long>[n];
	for(int i=0;i<n;i++)
		cin>>nodes[i].weight;
	to=new vector<int>[n];
	for(int i=0;i<n-1;i++)
	{
		int f,t;
		cin>>f>>t;
		to[f-1].push_back(t-1);
		to[t-1].push_back(f-1);
	}
	taken=new bool[n];
	memset(taken,false,n*sizeof(bool));
	taken[r-1]=true;
	mkt(r-1);
	delete[] taken;
	delete[] to;
	dfs1(r-1,1,r-1);
	a=new long long[n];
	dfs2(r-1,r-1);
	xd=new xds<long long>(a,0,n);
	delete[] a;
}

long long qrange(int x,int y)
{
	long long ans=0ll;
	while(nodes[x].top!=nodes[y].top)
	{
		if(x<y)	swap(x,y);
		ans+=xd->quest(nodes[nodes[x].top].sig,nodes[x].sig+1);
		x=nodes[nodes[x].top].fa;
	}
	if(x<y)	swap(x,y);
	ans+=xd->quest(nodes[y].sig,nodes[x].sig+1);
	return ans;
}
void crange(int x,int y,long long k)
{
	k%=p;
	while(nodes[x].top!=nodes[y].top)
	{
		if(x<y)	swap(x,y);
		xd->add(nodes[nodes[x].top].sig,nodes[x].sig+1,k);
		x=nodes[nodes[x].top].fa;
	}
	if(x<y)	swap(x,y);
	xd->add(nodes[y].sig,nodes[x].sig+1,k);
	return;
}
long long qsons(int r)
{
	return xd->quest(nodes[r].sig,nodes[r].sig+nodes[r].size);
}
void csons(int r,long long k)
{
	k%=p;
	xd->add(nodes[r].sig,nodes[r].sig+nodes[r].size,k);
}

int main()
{
	buildtree();
	for(int i=0;i<m;i++)
	{
		int f;
		cin>>f;
		long long x,y,z;
		switch(f){
			case 1:
				cin>>x>>y>>z;
				crange(x-1,y-1,z);
				break;
			case 2:
				cin>>x>>y;
				cout<<qrange(x-1,y-1)<<endl;
				break;
			case 3:
				cin>>x>>y;
				csons(x-1,y);
				break;
			case 4:
				cin>>x;
				cout<<qsons(x-1)<<endl;
				break;
		}
	}
	delete xd;
	return 0;
}