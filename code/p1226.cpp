#include <iostream>
using namespace std;

typedef unsigned long long Int;

Int a,n,p;

Int pow(Int a,Int n,Int p)
{
	Int ans=1;
	for(int i=63;i>=0;i--)
	{
		ans=ans*ans%p;
		if(n&(1ull<<i))
			ans=ans*a%p;
	}
	return ans;
}

int main()
{
	cin>>a>>n>>p;
	cout<<a<<"^"<<n<<" mod "<<p<<"="<<pow(a,n,p)<<endl;
	return 0;
}
