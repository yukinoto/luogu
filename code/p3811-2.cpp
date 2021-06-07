#include <iostream>
using namespace std;

long long n,p;
long long anti[3000010];
int main()
{
	cin>>n>>p;
	anti[1]=1;
	for(int i=2;i<=n;i++)
		anti[i]=(-p/i*anti[p%i]%p+p)%p;
	for(int i=1;i<n;i++)
		cout<<anti[i]<<'\n';
	cout<<anti[n]<<endl;
	return 0;
}
