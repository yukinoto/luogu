#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

vector<int> mp[300001];

int main()
{
	ios::sync_with_stdio(false);
	int n,m;
	cin>>n>>m;
	int a[n+1];
	for(int i=1;i<=n;i++)
	{
		cin>>a[i];
		mp[a[i]].push_back(i);
	}
	for(int i=0;i<m;i++)
	{
		int f;
		cin>>f;
		if(f==1)
		{
			int l,r,c;
			cin>>l>>r>>c;
			auto ie=upper_bound(mp[c].begin(),mp[c].end(),r),ib=lower_bound(mp[c].begin(),mp[c].end(),l);
			cout<<ie-ib<<endl;
		}
		if(f==2)
		{
			int x;
			cin>>x;
			if(a[x]!=a[x+1])
			{
				auto ia=lower_bound(mp[a[x]].begin(),mp[a[x]].end(),x),ib=lower_bound(mp[a[x+1]].begin(),mp[a[x+1]].end(),x+1);
				swap(*ia,*ib);
				swap(a[x],a[x+1]);
			}
		}
	}
	return 0;
}