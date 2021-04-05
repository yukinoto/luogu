#include <cstdio>
#include <cmath>
#include <vector>
using namespace std;

class Complex{
	private:
		double real,img;
	public:
		Complex(){}
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
		//tbd
};
Complex make_comp(const double &_real,const double &_img)const
{
	Complex ans(_real,_img);
	return ans;
}
const double pi=acos(-1);

Complex w(int k,int n)
{
	return make_comp(cos(2*pi*i/n),sin(2*pi*i/n));
}

vector<Complex>&& fft(const vector<int> &fun,int n)
{
	vector<Complex> ans;
	for(int i=0;i<n;i++)//
}
