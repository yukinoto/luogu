#include <iostream>
#include <string>
using namespace std;

int main()
{
    int t;
    cin>>t;
    for(int i=0;i<t;i++)
    {
        int n,m;
        cin>>n>>m;
        string x;
        cin>>x;
        int p=0,tmp=0;
        for(int i=0;i<x.size();i++)
        {
            if(x[i]=='(')
                p++;
            else
            {
                if(p>0)
                {
                    p--,tmp++;
                }
            }
        }
        if(tmp>=m)
            cout<<1<<endl;
        else
            cout<<0<<endl;
    }
}