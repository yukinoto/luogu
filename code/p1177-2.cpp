#include "leftistheap.hpp"
#include <iostream>
using namespace std;

int main()
{
	int n;
	cin>>n;
	leftistheap<int> h;
	for(int i=0;i<n;i++)
	{
		int x;
		cin>>x;
		h.push(x);
	}
	for(int i=1;i<n;i++)
	{
		cout<<h.top()<<' ';
		h.pop();
	}
	cout<<h.top()<<endl;
	return 0;
}