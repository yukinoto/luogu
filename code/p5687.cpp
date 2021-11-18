#include <iostream>
#include <queue>
#include <vector>
#include <algorithm>
#include <iterator>
using namespace std;

int n,m;
vector<int> a,b;

int min(vector<int> x)
{
	int y=0x7fffffff;
	for(auto i:x)
		y=min(y,i);
	return y;
}

void init()
{
	cin>>n>>m;
	istream_iterator<int> it(cin);
	for(int i=0;i<n;i++)
		a.push_back(*(it++));
	copy(it,istream_iterator<int>(),back_insert_iterator<vector<int>>(b));
	if(min(a)>min(b))
	{
		swap(a,b);
		swap(n,m);
	}
	return;
}

void work()
{
	int p=0;
	for(int i=1;i<n;i++)
		if(a[i]<a[p])
			p=i;
	sort(b.begin(),b.end());
	vector<int> b_p;
	b_p.push_back(b[0]);
	for(auto it=++b.begin();it!=b.end();++it)
		b_p.push_back(b_p.back()+*it);
	int ans=a[p]*(m-1);
	for(int i=p-1;i>=0;--i)
	{
		auto it=upper_bound(b.begin(),b.end(),a[i]);
		if(it==b.begin()) it++;
		ans+=a[i]*(b.end()-it)+*(b_p.begin()+(it-b.begin()-1));
	}
	for(int i=p+1;i<n;++i)
	{
		auto it=upper_bound(b.begin(),b.end(),a[i]);
		if(it==b.begin()) it++;
		ans+=a[i]*(b.end()-it)+*(b_p.begin()+(it-b.begin()-1));
	}
	cout<<ans<<endl;
}

int main()
{
	init();
	work();
	return 0;
}