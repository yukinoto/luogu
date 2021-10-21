#include <iostream>
#include <set>
#include <algorithm>
using namespace std;

int f[10030];
set<int>st;

int main()
{
	int l,s,t,m;
	cin>>l>>s>>t>>m;
	for(int i=0;i<m;i++)
	{
		int x;
		cin>>x;
		st.insert(x);
	}
	if(s==t)
	{
		int ans=0;
		for(auto i:st)
			if(i%s==0)
				ans++;
		cout<<ans<<endl;
		return 0;
	}
	for(int i=1;i<s;i++)
		f[i]=0x3fffffff;
	int chg=0,bef=s;
	for(int i=s;i<=l+t;i++)
	{
		f[i-chg]=0x3fffffff;
		int x;
		if(st.find(i)!=st.end())
		{
			x=1;
		}
		else
		{
			x=0;
		}
		for(int j=s;j<=t&&(i-j)>=0;j++)
			f[i-chg]=min(f[i-chg],f[i-chg-j]+x);
		if(f[i-chg]!=f[i-chg-1])
			bef=i;
		if(i-bef>=t)
		{
			auto it=st.upper_bound(i);
			if(it==st.end())
			{
				cout<<f[i-chg]<<endl;
				return 0;
			}
			int p=*it;
			if(p-i>t)
			{
				chg+=p-i-1;
				i=p-1;
			}
		}
	}
	int ans=0x7fffffff;
	for(int i=l;i<=l+t;i++)
		ans=min(ans,f[i-chg]);
	cout<<ans<<endl;
	return 0;
}
