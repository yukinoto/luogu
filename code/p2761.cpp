//gugugu
#include <iostream>
#include <string>
using namespace std;

bool link(string f,string t)
{
	if(t.size()!=f.size())
		return false;
	for(int i=0;i<f.size();i++)
	{
		if(f[i]=='0'||t[i]=='0')
			continue;
		if(f[i]!=t[i])
			return false;
	}
	return true;
}

int n,m;

void init()
{
	cin>>n>>m;

}
