#include <iostream>
#include <random>
using namespace std;

mt19937_64 rnd(time(0));
int main(int argc,char**argv)
{
	int n=atoi(argv[1]),m=atoi(argv[2]);
	cout<<n<<endl;
	for(int i=1;i<n;i++)
		cout<<rnd()%1000000000000ll<<' ';
	cout<<rnd()<<endl;
	cout<<m<<endl;
	for(int i=0;i<m;i++)
		cout<<rnd()%2<<' '<<rnd()%n+1<<' '<<rnd()%n+1<<endl;
	return 0;
}