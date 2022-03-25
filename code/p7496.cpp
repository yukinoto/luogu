#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <utility>
using namespace std;

long long mod1=998244353,mod2=1000000007;

vector<pair<int,int>>st;

int main()
{
	int n;
	cin>>n;
	string x,y;
	cin>>x>>y;
	for(int i=0;i<n;i++)
	{
		long long hush1=0,hush2=0;
		int it=0;
		for(int j=i;j<n;j++,it++)
		{
			hush1=((hush1<<5)+(y[j]-'a')+1);
			hush2=((hush2<<5)+(y[j]-'a')+1);
			if(hush1>=mod1)  hush1%=mod1;
			if(hush2>=mod2)  hush2%=mod2;
			while(x[it]!=y[j]&&it<n)
				it++;
			if(it==n)
				break;
			st.emplace_back(hush1,hush2);
		}
	}
	sort(st.begin(),st.end());
	long long ans=1;
	pair<int,int>bef=*st.begin();
	for(auto i:st)
	{
		if(i!=bef)
		{
			ans++;
			bef=i;
		}
	}
	cout<<ans<<endl;
	return 0;
}