#include "leftistheap.hpp"
#include <iostream>
using namespace std;

int main()
{
	const int a[]={1,2};
	leftistheap<int> x((const int *)a,(const int *)a+1),y((const int *)a+1,(const int *)a+2);
	y.merge(x);
	cout<<y.top()<<endl;
	return 0;
}