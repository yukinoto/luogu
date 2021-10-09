#include <iostream>
#include <vector>
#include <stack>
using namespace std;

int n,m;
vector<int> mp[10010];

void init()
{
	cin>>n>>m;
	for(int i=0;i<m;i++)
	{
		int f,t;
		cin>>f>>t;
		mp[f].push_back(t);
	}
	return;
}

int main()
{
}