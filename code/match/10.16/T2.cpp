#include <iostream>
using namespace std;

typedef int Int;

int main()
{
	Int n,d;
	cin>>n>>d;
	Int p=n/2*2;
	Int q=n*2-p;
	if(d>=p+q/2)
		cout<<-1<<endl;
	else
	{
		for(int i=1;i<=q/2;i++)
			cout<<2*i-1<<' ';
		for(int i=1;i<=p/2;i++)
			cout<<2*i<<' '<<2*i<<' ';
		for(int i=1;i<=q/2;i++)
			cout<<2*i-1<<' ';
	}
	cout<<endl;
	return 0;
}
