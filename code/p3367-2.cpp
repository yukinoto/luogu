#include "unionset.hpp"
#include <iostream>
using namespace std;

int main()
{
	int n,m;
	unionset<10001> t;
	cin>>n>>m;
	for(int i=0;i<m;i++)
	{
		int op,x,y;
		cin>>op>>x>>y;
		if(op==1)
			t.merge(x,y);
		if(op==2)
			cout<<(t.if_in_same_set(x,y)?'Y':'N')<<'\n';
	}
	cout.flush();
	return 0;
}