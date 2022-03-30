#include <cstddef>
template<typename Int,size_t size>
class tarray{
	private:
		Int a[size];
		size_t lowbit(size_t x){return x&(-x);}
	public:
		tarray(){;}
		void reset()
		{
			for(size_t i=0;i<size;i++)
				a[i]=0;
			return;
		}
		void reset(size_t r)
		{
			for(size_t i=0;i<r;i++)
				a[i]=0;
			return;
		}
		void add(size_t p,Int x)
		{
			if(p==0)
			{
				a[p]+=x;
				return;
			}
			while(p<size)
			{
				a[p]+=x;
				p+=lowbit(p);
			}
			return;
		}
		Int pre(size_t p)
		{
			if(p==0)
				return 0;
			Int ans=0;
			p--;
			while(p!=0)
			{
				ans+=a[p];
				p-=lowbit(p);
			}
			ans+=a[0];
			return ans;
		}
		Int range(size_t l,size_t r){return pre(r)-pre(l);}
		void set(size_t p,Int x){add(p,x-range(p,p+1));}
};

#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

class nod{
	public:
		int pos,a,b,c;
		bool operator<(const nod&x)const{return a==x.a?(b==x.b?c<x.c:b<x.b):a<x.a;}
		bool operator==(const nod&x)const{return a==x.a&&b==x.b&&c==x.c;}
		bool operator!=(const nod&x)const{return !(*this==x);}
};

tarray<int,200010> tr;

int n,k;
int f[100010];

void deal(vector<nod>&x,vector<nod>&y)
{
	if(x.empty()||y.empty())	return;
	int lc=x.front().c;
	for(auto i:x)	lc=min(lc,i.c);
	vector<int> op;
	int it=0;
	for(int i=0;i<y.size();i++)
	{
		while(it<x.size()&&x[it].a<=y[i].a)
		{
			tr.add(x[it].c,1);
			op.push_back(x[it].c);
			it++;
		}
		f[y[i].pos]+=tr.range(lc,y[i].c+1);
	}
	for(auto i:op) tr.add(i,-1);
	return;
}

void cdq(nod *q,int l,int r)
{
	if(l==r-1)
		return;
	vector<int>tmp;
	for(int i=l;i<r;i++)
		tmp.push_back(q[i].b);
	sort(tmp.begin(),tmp.end());
	int mid=(l+r)/2,mb=tmp[mid-l],lc=q[l].c;
	vector<nod> lf,rf;
	vector<nod> t,tl,tr;
	for(int i=l;i<r;i++)
	{
		lc=min(lc,q[i].c);
		if(q[i].b<mb)
			lf.push_back(q[i]);
		else if(q[i].b>mb)
			rf.push_back(q[i]);
		else if(q[i].b==mb)
			t.push_back(q[i]);
	}
	deal(lf,t),deal(lf,rf),deal(t,rf);deal(t,t);
	for(auto i:t)
		f[i.pos]--;
	for(int i=l;i<l+lf.size();i++)
		q[i]=lf[i-l];
	for(int i=mid;i<mid+rf.size();i++)
		q[i]=rf[i-mid];
	if(!lf.empty())cdq(q,l,l+lf.size());
	if(!rf.empty())cdq(q,mid,mid+rf.size());
	return;
}

nod quest[100010];

int ans[100010];

int main()
{
	ios::sync_with_stdio(false);
	cin>>n>>k;
	for(int i=0;i<n;i++)
	{
		cin>>quest[i].a>>quest[i].b>>quest[i].c;
		quest[i].pos=i;
	}
	sort(quest,quest+n);
	cdq(quest,0,n);
	for(int i=0;i<n;i++)
		ans[f[i]]++;
	for(int i=0;i<n;i++)
		cout<<ans[i]<<'\n';
	return 0;
}