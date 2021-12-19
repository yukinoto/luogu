#include <iostream>
using namespace std;

int check(int a,int p)
{
	if(p<16)
		a-=10;
	if(p>20)
		a-=p-20;
	if(a<0)
		a=0;
	return a;
}

int main()
{
	int n;
	cin>>n;
	for(int i=0;i<n;i++)
	{
		int a,p;
		cin>>a>>p;
		cout<<check(a,p)<<endl;
	}
	return 0;
}