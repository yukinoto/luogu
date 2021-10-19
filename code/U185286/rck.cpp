#include <iostream>
#include <sstream>
using namespace std;

int main(int argc,char**argv)
{
	stringstream cache;
	cache<<argv[1]<<' '<<argv[2]<<' '<<argv[3]<<' '<<argv[4];
	int l,r;
	string ea,eo;
	cache>>l>>r>>eo>>ea;
	for(int i=l;i<r;i++)
	{
		char c[50];
		sprintf(c,"./checker %d.in %d.%s %d.%s",i,i,eo.c_str(),i,ea.c_str());
		system(c);
	}
	return 0;
}
