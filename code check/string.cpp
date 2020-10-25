#include <string.h>
#include <string>
#include <iostream>
using namespace std;

int main()
{
    string s;
    cin>>s;
    cout<<s<<endl;
    printf("%s\n",s.c_str());
    cout<<s.substr(1,3)<<endl;
    printf("%d %d %d\n",s.length(),s.size(),strlen(s.c_str()));
    return 0;
}
