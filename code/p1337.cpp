#include <iostream>
#include <cmath>
#include <iomanip>
using namespace std;

template<typename T>
T get(istream& ins)
{
	T ans;
	ins>>ans;
	return ans;
}

class vec{
	public:
		long double x,y;
		vec(){;}
		vec(long double x,long double y){this->x=x,this->y=y;}
		vec& operator*=(const long double &x){this->x*=x,this->y*=x;return *this;}
		vec operator*(const long double &x){return vec(this->x*x,this->y*x);}
		long double operator*(const vec &x){return this->x*x.x+this->y*x.y;}
		vec& operator+=(const vec &x){this->x+=x.x,this->y+=x.y;return *this;}
		vec operator+(const vec &x){return vec(this->x+x.x,this->y+x.y);}
		vec& operator-=(const vec &x){this->x-=x.x,this->y-=x.y;return *this;}
		vec operator-(const vec &x){return vec(this->x-x.x,this->y-x.y);}
};

class pla{
	public:
		long double x,y,f;
		pla(){;}
		pla(long double x,long double y,long double f){this->x=x,this->y=y,this->f=f;}
		void get(istream& ins){ins>>x>>y>>f;}
};

pla a[1010];

vec calc(const vec&p,const pla&x)
{
	long double m=sqrt((x.x-p.x)*(x.x-p.x)+(x.y-p.y)*(x.y-p.y));
	if(m<=0)
		return vec(0,0);
	return vec((x.x-p.x)*x.f/m,(x.y-p.y)*x.f/m);
}

const long double dt=0.993,lim=0.0001;
long double T=500;
int main()
{
	int n;
	cin>>n;
	for(int i=0;i<n;i++)
		a[i].get(cin);
	vec np(0,0);
	for(;T>lim;T*=dt)
	{
		vec dir(0,0);
		for(int i=0;i<n;i++)
			dir+=calc(np,a[i]);
		np+=dir*(1/sqrt(dir*dir))*T;
	}
	cout<<fixed<<setprecision(3)<<np.x<<' '<<np.y<<endl;
	return 0;
}