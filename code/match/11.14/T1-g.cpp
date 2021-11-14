#include <iostream>
#include <random>
using namespace std;

mt19937 rnd(time(0));

int main(int argc,char**argv)
{
	int n=atoi(argv[1]),m=atoi(argv[2]);
	cout<<n<<' '<<m<<endl;
	for(int i=0;i<n;i++)
		cout<<rnd()%100000<<' '<<rnd()%100000<<endl;
	for(int i=0;i<m;i++)
	{
		int f=rnd()%3;
		if(f==0)
		{
			cout<<"m "<<rnd()%1000000<<' '<<rnd()%1000000<<endl;
		}
		if(f==1)
			cout<<"x\n";
		if(f==2)
			cout<<"y\n";
	}
	cout.flush();
	return 0;
}