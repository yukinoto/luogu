#include <iostream>
#include <string>
#include <iterator>
using namespace std;

#define ui unsigned
class xds{
	private:
	class node{
		private:
		ui value,tag;
		node *lc,*rc;
		void pushtag(int l,int r)
		{
			if(lc==nullptr)
			{
				tag=0;
				return;
			}
			int mid=(l+r)/2;
			lc->value+=(mid-l)*tag;
			rc->value+=(r-mid)*tag;
			lc->tag+=tag,rc->tag+=tag;
			return;
		}
		public:
		node(int l,int r)
		{
			if(l==r-1)
			{
				lc=rc=nullptr;
				value=tag=0;
				return;
			}
			int mid=(l+r)/2;
			lc=new node(l,mid),rc=new node(mid,r);
			value=tag=0;
			return;
		}
		~node()
		{
			delete lc,rc;
		}
		void add(int l,int r,int left,int right,ui x)
		{
			if(left>=r||right<=l)
				return;
			if(left<=l&&right>=r)
			{
				tag+=x;
				value+=(r-l)*x;
				return;
			}
			pushtag(l,r);
			int mid=(l+r)/2;
			lc->add(l,mid,left,right,x);
			rc->add(mid,r,left,right,x);
			value=lc->value+rc->value;
		}
		ui quest(int l,int r,int left,int right)
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
	node *root;
	int l,r;
	public:
	xds(int _l,int _r):l(_l),r(_r)
	{
		root=new node(l,r);
	}
	~xds()
	{
		delete root;
	}
	void add(int left,int right,ui x)
	{
		if(right<=left)
			return;
		root->add(l,r,left,right,x);
	}
	ui quest(int left,int right)
	{
		if(right<=left)
			return 0;
		return root->quest(l,r,left,right);
	}
};
#undef ui

void kmp(const string &x,int *k)
{
	int l=x.size();
	for(int i=0;i<l;i++)
		k[i]=0;
	for(int i=1;i<l;i++)
	{
		int j=k[i-1];
		while(j!=0&&x[j]!=x[i])
			j=k[j-1];
		if(x[j]==x[i])
			k[i]=j+1;
	}
}

int main()
{
	int l1,l2;
	cin>>l1>>l2;
	string s1,s2;
	cin>>s1>>s2;
	int k[l1*2+1];
	xds tr(0,l1);
	string x=s2+"#"+s1;
	kmp(x,k);
	unsigned ans=0;
	for(int i=0;i<l1-l2+1;i++)
	{
		if(k[i+l2*2]==l2)
			tr.add(i,i+1,1);
	}
	for(int i=0;i<l1;i++)
	{
		for(int l=0;i-l>=0&&i+l<l1;l++)
		{
			if(s1[i+l]!=s1[i-l])
				break;
			if(tr.quest(i-l,i+l-l2+2)!=0)
				ans++;
		}
	}
	cout<<ans<<endl;
	return 0;
}