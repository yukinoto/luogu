#include "testlib.h"
#include <sstream>
#include <algorithm>
using namespace std;

const int mina=-200000,maxa=200000-1,minx=-200000,maxx=200000-1;

void gen(int l1,int r1,int l2,int r2)
{
	int n=rnd.next(l1,r1),m=rnd.next(l2,r2);
	cout<<n<<' '<<m<<endl;
	for(int i=0;i<n-1;i++)
		cout<<rnd.next(mina,maxa)<<' ';
	cout<<rnd.next(mina,maxa)<<endl;
	for(int i=0;i<m;i++)
	{
		int f=rnd.next(1,3);
		cout<<f<<' ';
		if(f==1)
		{
			int x=rnd.next(0,n),y=rnd.next(0,n);
			if(x>y)
				swap(x,y);
			cout<<x<<' '<<y<<endl;
		}
		if(f==2||f==3)
		{
			int x=rnd.next(0,n),y=rnd.next(0,n);
			if(x>y)
				swap(x,y);
			int z=rnd.next(minx,maxx);
			cout<<x<<' '<<y<<' '<<z<<endl;
		}
	}
	return;
}

int main(int argc,char**argv)//t1,t2,n in [l1,r1],m in [l2,r2]
{
	if(argc<6)
	{
		cerr<<"Error:Unenough args"<<endl;
		return -1;
	}
	registerGen(argc,argv,1);
	stringstream cache;
	cache<<argv[1]<<' '<<argv[2]<<' '<<argv[3]<<' '<<argv[4]<<' '<<argv[5]<<' '<<argv[6]<<endl;
	int t1,t2,l1,r1,l2,r2;
	cache>>t1>>t2>>l1>>r1>>l2>>r2;
	for(int i=t1;i<t2;i++)
	{
		startTest(i);
		gen(l1,r1,l2,r2);
	}
	return 0;
}
