#include "leftistheap.hpp"
#include <iostream>
using namespace std;

int main()
{
	leftistheap<int> st;
	int n;
	cin>>n;
	for(int i=0;i<n;i++)
	{
		int op;
		cin>>op;
		if(op==1)
		{
			int x;
			cin>>x;
			st.push(x);
		}
		if(op==2)
		{
			cout<<st.top()<<'\n';
		}
		if(op==3)
		{
			st.pop();
		}
	}
	return 0;
}