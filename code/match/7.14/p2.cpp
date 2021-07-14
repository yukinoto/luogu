#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

const long long mod=998244353;

vector<int> posa,nega,posc,negc;
void ipt()
{
	char op=getchar();
	int v;
	while(op!='+'&&op!='*')
		op=getchar();
	cin>>v;
	if(op=='+')
	{
		if(v>0)
			posa.push_back(v);
		else if(v<0)
			nega.push_back(v);
	}
	else if(op=='*')
		if(v>0)
			posc.push_back(v);
		else if(v<0)
			negc.push_back(v);
	return;
}
int main()
{
	int n;
	cin>>n;
	for(int i=0;i<n;i++)
		ipt();
	long long ps=0,ns=0;
	for(int i=0;i<posa.size();i++)
		ps+=posa[i];
	for(int i=0;i<nega.size();i++)
		ns+=nega[i];
	sort(negc.rbegin(),negc.rend());
	if(negc.size()%2==0)
	{
		if(negc.size()==0)
		{
			long long ans=ps;
			for(int i=0;i<posc.size();i++)
				ans=ans*posc[i]%mod;
			ans+=ns;
			cout<<(ans%mod+mod)%mod<<endl;
		}
		else
		{
			long long ans=ps*negc[0]%mod;
			ans=(ans+ns)%mod;
			for(int i=0;i<posc.size();i++)
				ans=ans*posc[i]%mod;
			for(int i=1;i<negc.size();i++)
				ans=ans*negc[i]%mod;
			cout<<(ans%mod+mod)%mod;
		}
	}
	else
	{
		long long ans=ns*negc[0]%mod;
		ans=(ans+ps)%mod;
		for(int i=0;i<posc.size();i++)
				ans=ans*posc[i]%mod;
		for(int i=1;i<negc.size();i++)
			ans=ans*negc[i]%mod;
		cout<<(ans%mod+mod)%mod;
	}
	return 0;
}
