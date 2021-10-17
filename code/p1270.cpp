#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>
using namespace std;

int t;
const int MAXT=6010;

/*template<typename Int>
Int getint(istream &ins)
{
	Int x;
	ins>>x;
	return x;
}*/

class node{
	public:
		int dp[MAXT];
		vector<pair<int,node*> >sons;
		int num;
		node()
		{
			for(int i=0;i<=t;i++)
				dp[i]=0;
			cin>>num;
			if(num==0)
			{
				int x;
				cin>>x;
				sons.push_back(make_pair(x*2,new node));
				cin>>x;
				sons.push_back(make_pair(x*2,new node));
			}
			if(num!=0)
			{
				for(int i=5;i<=min(num*5,t);i++)
				{
					dp[i]=dp[i-1];
					if(i%5==0)
						dp[i]++;
				}
				for(int i=num*5+1;i<=t;i++)
					dp[i]=dp[i-1];
			}
			else
			{
				for(auto it:sons)
				{
					for(int i=t-it.first;i>=0;i--)
					{
						for(int j=0;i+j+it.first<=t;j++)
						{
							dp[i+j+it.first]=max(dp[i+j+it.first],dp[i]+it.second->dp[j]);
						}
					}
				}
			}
			return;
		}
		~node()
		{
			for(auto it:sons)
				delete it.second;
			return;
		}
};

int main()
{
	cin>>t;
	int l;
	cin>>l;
	l*=2;
	node x;
	cout<<x.dp[t-l-1]<<endl;
	return 0;
}
