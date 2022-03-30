#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

class quest{
	public:
		int x,cnt,op;
		long long ans;
		bool operator <(const quest&o)const{return x==o.x?op<o.op:x<o.x;}
};

void cdq(quest *q,int l,int r)
{
	if(l==r-1)
		return;
	long long sum=0;
	int mid=(l+r)/2;
	vector<quest> lf,rf;
	for(int i=l;i<r;i++)
		if(q[i].cnt<mid)
		{
			if(q[i].op==1)
				sum+=q[i].ans;
			lf.push_back(q[i]);
		}
		else
		{
			if(q[i].op==2)
				q[i].ans+=sum;
			rf.push_back(q[i]);
		}
	for(int i=l;i<mid;i++)
		q[i]=lf[i-l];
	for(int i=mid;i<r;i++)
		q[i]=rf[i-mid];
	cdq(q,l,mid),cdq(q,mid,r);
}

quest q[2000010];
long long pre[500010];

int main()
{
	ios::sync_with_stdio(false);
	int n,m;
	cin>>n>>m;
	for(int i=1;i<=n;i++)
	{
		cin>>pre[i];
		pre[i]+=pre[i-1];
	}
	int top=0;
	for(int i=0;i<m;i++)
	{
		int op,x,y;
		cin>>op>>x>>y;
		if(op==1)
		{
			q[top].op=1;
			q[top].ans=y,q[top].x=x;
			q[top].cnt=top;
			top++;
		}
		if(op==2)
		{
			q[top].op=2;
			q[top].cnt=top,q[top].x=x-1;
			top++;
			q[top].op=2;
			q[top].cnt=top,q[top].x=y;
			top++;
		}
	}
	sort(q,q+top);
	cdq(q,0,top);
	for(int i=0;i<top;i++)
		if(q[i].op==2)
		{
			cout<<q[i+1].ans-q[i].ans+pre[q[i+1].x]-pre[q[i].x]<<'\n';
			i++;
		}
	return 0;
}