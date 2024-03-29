#include <cstdio>
#include <cmath>
#include <vector>
#include <algorithm>
using namespace std;

class Complex{
	private:
		double real,img;
	public:
		Complex(){}
		~Complex(){}
		Complex(const double &_real,const double &_img)
		{
			real=_real,img=_img;
		}
		double abs()const
		{
			return sqrt(real*real+img*img);
		}
		Complex make_comp(const double &_real,const double &_img)const
		{
			Complex ans(_real,_img);
			return ans;
		}
		Complex operator +(const Complex &x)const
		{
			return make_comp(real+x.real,img+x.img);
		}
		Complex operator -(const Complex &x)const
		{
			return (*this)+x;
		}
		Complex operator *(const Complex &x)const
		{
			return make_comp(real*x.real-img*x.img,real*x.img+x.real*img);
		}
		Complex operator *(const int &x)const
		{
			return make_comp(real*x,img*x);
		}
		Complex operator /(const Complex &x)const
		{
			double m=x.abs();
			return make_comp((real*x.real+img*x.img)/m,(img*x.real-real*x.img)/m);
		}
		void operator +=(const Complex &x)
		{
			real+=x.real;
			img+=x.img;
		}
		void operator -=(const Complex &x)
		{
			real-=x.real;
			img-=x.img;
		}
		Complex operator /(const double &x)const
		{
			return make_comp(real/x,img/x);
		}
		void operator /=(const double &x)
		{
			real/=x;
			img/=x;
			return;
		}
		//tbd

		void input()
		{
			scanf("%lf%lf",&real,&img);
			return;
		}
		void print()const
		{
			printf("%lf+%lfi\n",real,img);
			return;
		}
		double getreal()
		{
			return real;
		}
};
Complex make_comp(const double &_real,const double &_img)
{
	Complex ans(_real,_img);
	return ans;
}
const double pi=acos(-1);

Complex w(int k,int n)
{
	return make_comp(cos(2*pi*k/n),sin(2*pi*k/n));
}

vector<Complex> fft(const vector<Complex>&fun,int n)
{
	vector<Complex> ans;
	if(n<=32)
	{
		for(int i=0;i<n;i++)
		{
			Complex x(fun[0]),id=w(i,n),nw=id;
			for(int j=1;j<n;j++)
			{
				x+=nw*fun[j];
				nw=nw*id;
			}
			ans.push_back(x);
		}
		return ans;
	}
	vector<Complex>f1,f2;
	for(int i=0;i<fun.size();i++)
	{
		if((i&1)==0)
			f1.push_back(fun[i]);
		else
			f2.push_back(fun[i]);
	}
	vector<Complex> a1(move(fft(f1,n/2))),a2(move(fft(f2,n/2)));
	for(int i=0;i<n/2;i++)
		ans.push_back(a1[i]+w(i,n)*a2[i]);
	for(int i=n/2;i<n;i++)
		ans.push_back(a1[i-n/2]+w(i,n)*a2[i-n/2]);
	return ans;
}

vector<Complex> _ifft(const vector<Complex>&fun,int n)
{
	vector<Complex> ans;
	if(n<=32)
	{
		for(int i=0;i<n;i++)
		{
			Complex x(fun[0]),id=w(-i,n),nw=id;
			for(int j=1;j<n;j++)
			{
				x+=nw*fun[j];
				nw=nw*id;
			}
			ans.push_back(x);
		}
		return ans;
	}
	vector<Complex>f1,f2;
	for(int i=0;i<fun.size();i++)
	{
		if((i&1)==0)
			f1.push_back(fun[i]);
		else
			f2.push_back(fun[i]);
	}
	vector<Complex> a1(move(_ifft(f1,n/2))),a2(move(_ifft(f2,n/2)));
	for(int i=0;i<n/2;i++)
		ans.push_back((a1[i]+w(-i,n)*a2[i]));
	for(int i=n/2;i<n;i++)
		ans.push_back((a1[i-n/2]+w(-i,n)*a2[i-n/2]));
	return ans;
}

vector<Complex> ifft(const vector<Complex>&fun,int n)
{
	vector<Complex> ans=_ifft(fun,n);
	for(int i=0;i<ans.size();i++)
		ans[i]/=n;
	return ans;
}

int main()
{
	vector<Complex> cache1,cache2,a1,a2;
	int n,m;
	scanf("%d%d",&n,&m);
	for(int i=0;i<=n;i++)
	{
		int x;
		scanf("%d",&x);
		cache1.push_back(make_comp(x,0));
	}
	for(int i=0;i<=m;i++)
	{
		int x;
		scanf("%d",&x);
		cache2.push_back(make_comp(x,0));
	}
	int b=1;
	while(b<=m+n) b<<=1;
	for(int i=n+1;i<b;i++)
		cache1.push_back(make_comp(0,0));
	for(int i=m+1;i<b;i++)
		cache2.push_back(make_comp(0,0));
	a1=fft(cache1,b),a2=fft(cache2,b);
	cache1.clear();
	for(int i=0;i<b;i++)
		cache1.push_back(a1[i]*a2[i]);
	cache2=ifft(cache1,b);
	for(int i=0;i<=m+n;i++)
		printf("%d ",int(cache2[i].getreal()+0.5));
	return 0;
}
