#include <iostream>
#include <iomanip>
#include <set>
#include <cmath>
using namespace std;

set<pair<long long,long long>> nds;

long long ans=0x7fffffffffffffffll;

long long d(const pair<long long,long long> &x,const pair<long long,long long> &y)
{
    return (x.first-y.first)*(x.first-y.first)+(x.second-y.second)*(x.second-y.second);
}

void merge(pair<long long,long long> x)
{
    auto it1=nds.lower_bound(x);auto it2=set<pair<long long,long long>>::reverse_iterator(it1);
    while(it1!=nds.end()&&it1->first<=x.first+(long long)sqrt(ans))
    {
        if(d(*it1,x)<ans)
            ans=d(*it1,x);
        ++it1;
    }
    while(it2!=nds.rend()&&it2->first>=x.first-(long long)sqrt(ans))
    {
        if(d(*it2,x)<ans)
            ans=d(*it2,x);
        ++it2;
    }
    nds.insert(x);
    return;
}

int main()
{
    int n;
    cin>>n;
    for(int i=1;i<=n;i++)
    {
        long long x,y;
        cin>>x>>y;
        merge(make_pair(x,y));
    }
    cout<<fixed<<setprecision(4)<<sqrt(ans)<<endl;
    return 0;
}