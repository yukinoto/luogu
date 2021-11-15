#include <iostream>
#include <utility>
#include <string>
using namespace std;

class xds{
	private:
	class node{
		private:
		int value,tag;
		node *lc,*rc;
		void pushtag(int l,int r)
		{
			if(lc==nullptr)
			{
				tag=0;
				return;
			}
			int mid=(l+r)/2;
			lc->tag+=tag,rc->tag+=tag;
			lc->value+=tag*(mid-l),rc->value+=tag*(r-mid);
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
			}
			else
			{
				int mid=(l+r)/2;
				lc=new node(l,mid),rc=new node(mid,r);
				value=tag=0;
			}
			return;
		}
		void add(int l,int r,int left,int right,int x)
		{
			if(left>=r||right<=l)
				return;
			if(left<=l&&right>=r)
			{
				value+=x*(r-l);
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
		~node()
		{
			delete lc,rc;
		}
	};
	node *root;
	int l,r;
	public:
	xds(int _l,int _r)
	{
		l=_l,r=_r;
		root=new node(l,r);
	}
	~xds()
	{
		delete root;
	}
	void add(int left,int right,int x)
	{
		if(left>=right)
			return;
		root->add(l,r,left,right,x);
	}
	int quest(int left,int right)
	{
		if(left>=right)
			return 0;
		return root->quest(l,r,left,right);
	}
};

const int inf=1000002;

pair<int,int> grg(int a,int b,int c)
{
	if(a==0)
	{
		if(b>c)
			return make_pair(-inf,inf);
		else
			return make_pair(inf,-inf);
	}
	if(a>0)
	{
		if((c-b)%a==0)
			return make_pair((c-b)/a+1,inf);
		if(c>b)
			return make_pair((c-b)/a+1,inf);
		else
			return make_pair((c-b)/a,inf);
	}
	else
	{
		if((c-b)%a==0)
			return make_pair(-inf,(c-b)/a);
		if(c>b)
			return make_pair(-inf,(c-b)/a);
		else
			return make_pair(-inf,(c-b)/a+1);
	}
}

int n,top=1;
pair<int,int> rng[100001];
bool jd[100001];
xds t(-inf,inf);

int main()
{
	cin>>n;
	for(int i=1;i<=n;i++)
	{
		string f;
		cin>>f;
		if(f=="Add")
		{
			int a,b,c;
			cin>>a>>b>>c;
			rng[top]=grg(a,b,c);
			t.add(rng[top].first,rng[top].second,1);
			jd[top]=true;
			++top;
		}
		if(f=="Del")
		{
			int p;
			cin>>p;
			if(jd[p])
			{
				t.add(rng[p].first,rng[p].second,-1);
				jd[p]=false;
			}
		}
		if(f=="Query")
		{
			int k;
			cin>>k;
			cout<<t.quest(k,k+1)<<'\n';
		}
	}
	cout.flush();
	return 0;
}