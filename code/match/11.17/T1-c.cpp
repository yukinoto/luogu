#include <iostream>
using namespace std;

int main()
{
	int x,y;
	cin>>x>>y;
	long long a1=0,a2=0;
	for(int i=1;i<x;i++)
		a1+=(x-1)/i*i;
	for(int i=1;i<=y;i++)
		a2+=y/i*i;
	cout<<a2-a1<<endl;
	return 0;
}