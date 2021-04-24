#include <iostream>

typedef int Int;

const Int mod=998244353;

int main()
{
	Int n,k;
	std::cin>>n>>k;
	Int *x=new Int[n],*y=new Int[n];
	for(int i=0;i<n;i++)
		std::cin>>x[i]>>y[i];
	Int *pre=new Int[n+1],*sub=new Int[n+1];
	delete[] x;
	delete[] y;
	delete[] pre;
	delete[] sub;
}
