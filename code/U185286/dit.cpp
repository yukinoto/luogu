#include <iostream>
#include <sstream>
using namespace std;

int main(int argc,char**argv)
{
	int l,r;
	stringstream cache;
	cache<<argv[1]<<' '<<argv[2];
	cache>>l>>r;
	for(int i=l;i<r;i++)
	{
		char c[50];
		sprintf(c,"mv ./%d ./%d.in\n",i,i);
		system(c);
	}
	return 0;
}
