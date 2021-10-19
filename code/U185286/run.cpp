#include <iostream>
#include <sstream>
using namespace std;

int main(int argc,char**argv)
{
	stringstream cache;
	cache<<argv[1]<<' '<<argv[2]<<' '<<argv[3]<<' '<<argv[4];
	int l,r;
	string fn,fa;
	cache>>l>>r>>fn>>fa;
	for(int i=l;i<r;i++)
	{
		char c[50];
		sprintf(c,"./%s <%d.in >%d.%s",fn.c_str(),i,i,fa.c_str());
		system(c);
	}
	return 0;
}
