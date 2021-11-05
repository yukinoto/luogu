#include <iostream>
#include <string>
using namespace std;

int k[2000010];

int main()
{
	string a,b;
	cin>>a>>b;
	string x=b+"*"+a;
	/*cin>>x;*/
	k[0]=-1;
	for(int i=1;i<x.length();i++)
	{
		int j=k[i-1];
		while(j>=0&&x[j+1]!=x[i])
			j=k[j];
		k[i]=j+1;
		if(k[i]==0&&x[0]!=x[i])
			k[i]=-1;
	}
	/*cout<<x<<endl;
	for(int i=0;i<x.length();i++)
		cout<<k[i]<<' ';
	cout<<endl;*/
	for(int i=b.length()+1;i<x.length();i++)
	{
		if(k[i]==b.length()-1)
			cout<<i-b.length()*2+1<<endl;
	}
	for(int i=0;i<b.length();i++)
		cout<<k[i]+1<<' ';
	cout<<endl;
	return 0;
}