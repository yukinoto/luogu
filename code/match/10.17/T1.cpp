#include <iostream>
#include <cctype>
using namespace std;

const int inf=0x7fffffff;

#define OPEN true
#define CLOSE false

int main()
{
	int l=-inf,r=inf;
	bool lo=OPEN,ro=OPEN;
	int n;
	char x;
	cin>>n>>x;
	for(int i=0;i<n;i++)
	{
		bool flag,flag2=OPEN;
		cin>>x;
		char op;
		cin>>op;
		flag=op=='<';
		cin>>op;
		if(isdigit(op)||op=='-')
			cin.putback(op);
		else
			flag2=CLOSE;
		int num;
		cin>>num;
		if(flag)
		{
			if(r>num)
			{
				r=num;
				ro=OPEN;
			}
			if(r==num&&flag2==CLOSE)
				ro=CLOSE;
		}
		else
		{
			if(l<num)
			{
				l=num;
				lo=OPEN;
			}
			if(l==num&&flag2==CLOSE)
				lo=CLOSE;
		}
	}
	if(l>r||(l==r&&(ro==OPEN||lo==OPEN)))
	{
		cout<<"No Answer!"<<endl;
		return 0;
	}
	if(l==r&&lo==CLOSE&&ro==CLOSE)
	{
		cout<<x<<'='<<l<<endl;
		return 0;
	}
	if(l==-inf)
	{
		cout<<x<<'<';
		if(ro==CLOSE)
			cout<<'=';
		cout<<r<<endl;
		return 0;
	}
	if(r==inf)
	{
		cout<<x<<'>';
		if(lo==CLOSE)
			cout<<'=';
		cout<<l<<endl;
		return 0;
	}
	cout<<l;
	if(lo==OPEN)
		cout<<'<';
	else
		cout<<"<=";
	cout<<x;
	if(ro==OPEN)
		cout<<'<';
	else
		cout<<"<=";
	cout<<r<<endl;
	return 0;
}
