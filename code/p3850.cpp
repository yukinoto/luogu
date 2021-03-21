#include<iostream>
#include<string>
#include<vector>
using namespace std;

vector<string>init;
int main()
{
	int n;
	cin>>n;
	for(int i=0;i<n;i++)
	{
		string x;
		cin>>x;
		init.push_back(x);
	}
	int m;
	cin>>m;
	for(int i=0;i<m;i++)
	{
		string x;
		cin>>x;
		int p;
		cin>>p;
		init.insert(init.begin()+p,x);
	}
	int q;
	cin>>q;
	for(int i=0;i<q;i++)
	{
		int x;
		cin>>x;
		cout<<init[x]<<endl;
	}
	return 0;
}
