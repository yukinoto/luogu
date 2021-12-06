#include <iostream>
#include <algorithm>
#include <utility>
#include <cmath>
using namespace std;

#define ll long long

pair<ll,ll> node[400010];

ll calc(const pair<ll,ll>&a,const pair<ll,ll>&b)
{
    return (a.first-b.first)*(a.first-b.first)+(a.second-b.second)*(a.second-b.second);
}

bool cmp(const pair<ll,ll>&a,const pair<ll,ll>&b)
{
    return a.second==b.second?a.first<b.first:a.second<b.second;
}

ll sol(int l,int r)
{
    if(l>=r-1)
        return 0x3fffffffffffffffll;
    sort(node+l,node+r);
    int mid=(l+r)/2;
    ll d=sol(l,mid);
    d=min(d,sol(mid,r));
    sort(node+l,node+r);
    long long x=sqrt(d);
    auto pl=lower_bound(node+l,node+r,make_pair(node[mid].first-x,0ll)),
    pr=upper_bound(node+l,node+r,make_pair(node[mid].first+x,0x7fffffffffffffffll));
    sort(pl,pr,cmp);
    for(auto i=pl;i!=pr;i++)
    {
        for(auto j=i-1;j!=pl-1;j--)
        {
            if(i->second-j->second>=x)
                break;
            long long tmp=calc(*i,*j);
            if(tmp<d)
            {
                d=tmp;
                x=sqrt(d);
            }
        }
    }
    return d;
}

int main()
{
    int n;
    cin>>n;
    for(int i=0;i<n;i++)
        cin>>node[i].first>>node[i].second;
    cout<<sol(0,n)<<endl;
    return 0;
}