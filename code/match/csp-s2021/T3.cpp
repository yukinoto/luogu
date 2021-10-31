#include<iostream>
#include<algorithm>
#include<queue>
#include<vector>
using namespace std;

vector<char> ans;

int t,n;
int a[1000010];

void init()
{
	cin>>n;
	for(int i=0;i<n*2;i++)
		cin>>a[i];
}

void check1(char L,char R)
{
    ans.clear();
	int li,ri,lo=0,ro=n*2-1;
	for(int i=1;i<n*2;i++)
		if(a[i]==a[0])
		{
			li=ri=i;
			break;
		}
	ans.push_back(L);
	deque<char> x;
	x.push_front(L);
	li--,ri++,lo++;
	for(int i=1;i<n;i++)
	{
		if(lo<li&&a[lo]==a[li])
		{
			ans.push_back(L);
			x.push_front(L);
			lo++;li--;
			continue;
		}
		if(lo<=li&&ro>=ri)
		{
			if(a[lo]==a[ri])
			{
				ans.push_back(L);
				x.push_front(R);
				lo++,ri++;
				continue;
			}
			if(a[ro]==a[li])
			{
				ans.push_back(R);
				x.push_front(L);
				ro--,li--;
				continue;
			}
		}
		if(ro>ri&&a[ro]==a[ri])
		{
			ans.push_back(R);
			x.push_front(R);
			ro--,ri++;
			continue;
		}
		ans.clear();
		break;
	}
	if(ans.empty())
		return;
	while(!x.empty())
	{
		ans.push_back(x.front());
		x.pop_front();
	}
	return;
}
void check2(char L,char R)
{
    ans.clear();
	int li,ri,lo=0,ro=n*2-1;
	for(int i=1;i<n*2;i++)
		if(a[i]==a[0])
		{
			li=ri=i;
			break;
		}
	ans.push_back(L);
	deque<char> x;
	x.push_front(R);
	li--,ri++,lo++;
	for(int i=1;i<n;i++)
	{
		if(ro>ri&&a[ro]==a[ri])
		{
			ans.push_back(R);
			x.push_front(R);
			ro--,ri++;
			continue;
		}
		if(lo<=li&&ro>=ri)
		{
			if(a[ro]==a[li])
			{
				ans.push_back(R);
				x.push_front(L);
				ro--,li--;
				continue;
			}
			if(a[lo]==a[ri])
			{
				ans.push_back(L);
				x.push_front(R);
				lo++,ri++;
				continue;
			}
		}
		if(lo<li&&a[lo]==a[li])
		{
			ans.push_back(L);
			x.push_front(L);
			lo++;li--;
			continue;
		}
		ans.clear();
		break;
	}
	if(ans.empty())
		return;
	while(!x.empty())
	{
		ans.push_back(x.front());
		x.pop_front();
	}
	return;
}
void print()
{
	if(ans.empty())
	{
		cout<<-1<<endl;
		return;
	}
	for(auto i:ans)
		cout<<i;
	cout<<endl;
	return;
}
void work()
{
	init();
	check1('L','R');
	if(!ans.empty())
		print();
	else
	{
		reverse(a,a+n*2);
		check2('R','L');
		print();
	}
	return;
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	cin>>t;
	for(int i=0;i<t;i++)
		work();
	return 0;
}