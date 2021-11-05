#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
using namespace std;

/*const int MAXL=12;
const unsigned MOD=100,BITS=2,PW[BITS]={1,10};

class bigInteger{
	private:
		unsigned int *a;
		void pushBit()
		{
			for(int i=0;i<MAXL;i++)
			{
				a[i+1]+=a[i]/MOD;
				a[i]%=MOD;
			}
			return;
		}
		void anti()
		{
			for(int i=0;i<MAXL;i++)
				a[i]=MOD-1-a[i];
			return;
		}
	public:
		bigInteger()
		{
			a=new unsigned int[MAXL+1];
			return;
		}
		~bigInteger()
		{
			delete[] a;
		}
		bigInteger(unsigned int x)
		{
            a=new unsigned int[MAXL+1];
			a[0]=x;
			for(int i=1;i<=MAXL;i++)
				a[i]=0;
			pushBit();
			return;
		}
		bigInteger(const bigInteger&x)
		{
			a=new unsigned int[MAXL+1];
			for(int i=0;i<=MAXL;i++)
				a[i]=x.a[i];
			return;
		}
		bigInteger(bigInteger &&x)
		{
			a=x.a;
			x.a=nullptr;
			return;
		}
		bigInteger& operator =(const bigInteger&x)
		{
			if(a==nullptr)
				a=new unsigned int[MAXL+1];
			for(int i=0;i<=MAXL;i++)
				a[i]=x.a[i];
			return *this;
		}
		bigInteger& operator =(bigInteger&&x)
		{
			delete[] a;
			a=x.a;
			x.a=nullptr;
			return *this;
		}
		bigInteger&& operator +(const bigInteger &x)const
		{
			static bigInteger ans;
            ans=(*this);
			for(int i=0;i<MAXL;i++)
				ans.a[i]+=x.a[i];
			ans.pushBit();
			return move(ans);
		}
		bigInteger& operator +=(const bigInteger &x)
		{
			for(int i=0;i<MAXL;i++)
				a[i]+=x.a[i];
			pushBit();
			return *this;
		}
		bigInteger&& operator *(const bigInteger &x)const
		{
			static bigInteger ans;
            ans=bigInteger(0);
			for(int i=0;i<MAXL;i++)
				for(int j=0;i+j<MAXL;j++)
					ans.a[i+j]+=a[i]*x.a[j];
			ans.pushBit();
			return move(ans);
		}
		bigInteger& operator *=(const bigInteger &x)
		{
			for(int i=MAXL-1;i>=0;i--)
			{
				int p=a[i];
				a[i]=0;
				for(int j=0;i+j<MAXL;j++)
					a[i+j]+=p*x.a[j];
			}
			pushBit();
			return *this;
		}
		bigInteger& operator +=(const unsigned int x)
		{
			a[0]+=x;
			pushBit();
			return *this;
		}
		bigInteger&& operator +(const unsigned int x)const
		{
			static bigInteger ans;
            ans=bigInteger(*this);
			return move(ans+=x);
		}
		bigInteger& operator *=(const unsigned int x)
		{
			for(int i=0;i<MAXL;i++)
				a[i]*=x;
			pushBit();
			return *this;
		}
		bigInteger&& operator *(const unsigned int x)const
		{
			static bigInteger ans;
            ans=bigInteger(*this);
			return move(ans*=x);
		}
		bigInteger& operator -=(const bigInteger&x)
		{
			bigInteger tmp(x);
			tmp.anti();
			tmp+=1;
			(*this)+=tmp;
			return *this;
		}
		bigInteger&& operator -(const bigInteger&x)const
		{
			static bigInteger ans;
            ans=bigInteger(*this);
			return move(ans-=x);
		}
		bool operator <(const bigInteger&x)const
		{
			for(int i=MAXL-1;i>=0;i--)
			{
				if(a[i]!=x.a[i])
					return a[i]<x.a[i];
			}
			return false;
		}
		bool operator ==(const bigInteger&x)const
		{
			for(int i=MAXL-1;i>=0;i--)
			{
				if(a[i]!=x.a[i])
					return false;
			}
			return true;
		}
		bool operator >=(const bigInteger&x)const
		{
			return !(*this<x);
		}
		bigInteger& operator <<=(unsigned int x)
		{
			for(int i=MAXL-1;i>=x;i--)
				a[i]=a[i-x];
			for(int i=0;i<x;i++)
				a[i]=0;
			return *this;
		}
		bigInteger& operator >>=(unsigned int x)
		{
			for(int i=0;i<MAXL-x;i++)
				a[i]=a[i+x];
			for(int i=MAXL-x;i<MAXL;i++)
				a[i]=0;
			return *this;
		}
		bigInteger&& operator <<(unsigned int x)const
		{
			static bigInteger ans;
            ans=bigInteger(*this);
			return move(ans<<=x);
		}
		bigInteger&& operator >>(unsigned int x)const
		{
			static bigInteger ans;
            ans=bigInteger(*this);
			return move(ans>>=x);
		}
		bigInteger& operator %=(const bigInteger&x)
		{
			int cnt=0;
			bigInteger tmp(x);
			while(*this>=tmp)
			{
				tmp<<=1;
				cnt++;
			}
			tmp>>=1;
			cnt--;
			while(cnt>=0)
			{
				while(*this>=tmp)
					(*this)-=tmp;
				tmp>>=1;
				cnt--;
			}
			return *this;
		}
		bigInteger&& operator %(const bigInteger&x)const
		{
			static bigInteger ans;
            ans=bigInteger(*this);
			return move(ans%=x);
		}
		bigInteger&& operator /(const bigInteger&x)const
		{
			int cnt=0;
			bigInteger tmp1(*this),tmp(x);
            static bigInteger ans;
            ans=bigInteger(0);
			while(*this>=tmp)
			{
				tmp<<=1;
				cnt++;
			}
			tmp>>=1;
			cnt--;
			while(cnt>=0)
			{
				while(tmp1>=tmp)
				{
					tmp1-=tmp;
					ans.a[cnt]++;
				}
				tmp>>=1;
				cnt--;
			}
			return move(ans);
		}
		bigInteger& operator /=(const bigInteger&x)
		{
			return *this=(*this)/x;
		}
		friend istream& operator >>(istream&,bigInteger&);
		friend ostream& operator <<(ostream&,const bigInteger&);
		operator int()const
		{
			int ans=0;
			for(int i=MAXL-1;i>=0;i--)
			{
				ans=ans*MOD+a[i];
			}
			return ans;
		}
};

istream& operator >>(istream &ins,bigInteger &x)
{
	x=move(bigInteger(0));
	char i;
	cin>>i;
	while(isspace(i))
	{
		ins.get(i);
	}
	int cnt=0;
	static int cache[MAXL*BITS];
	do
	{
		cache[cnt]=i-'0';
		cnt++;
	}while(ins.get(i)&&isdigit(i));
	reverse(cache,cache+cnt);
	for(int i=0;i<=(cnt-1)/BITS;i++)
		for(int j=min(BITS,cnt-BITS*i)-1;j>=0;j--)
		{
			x.a[i]*=10;
			x.a[i]+=cache[i*BITS+j];
		}
	return ins;
}
ostream& operator <<(ostream &ous,const bigInteger&x)
{
	static char cache[BITS*MAXL+1];
	for(int i=0;i<MAXL;i++)
	{
		for(int j=0;j<BITS;j++)
		{
			cache[i*BITS+j]=x.a[i]/PW[j]%10+'0';
		}
	}
	int p=MAXL*BITS-1;
	while(p>=0&&cache[p]=='0')
		--p;
	++p;
	reverse(cache,cache+p);
	cache[p]='\0';
	if(p!=0)
		ous<<cache;
	else
		ous<<'0';
	return ous;
}*/

//debug
/*int main()
{
	bigInteger a,b;
	cin>>a>>b;
	cout<<a+b<<endl;
	if(a>=b)
		cout<<a-b<<endl;
	else
		cout<<'-'<<b-a<<endl;
	cout<<a*b<<endl;
	cout<<a/b<<endl;
	cout<<a%b<<endl;
	return 0;
}*/

istream& operator>>(istream&ins,__int128_t &p)
{
	char x=ins.get();
	while(isspace(x))
		x=ins.get();
	p=0;
	while(isdigit(x))
	{
		p*=10;
		p+=x-'0';
	}
	return ins;
}
ostream& operator<<(ostream &ous,const __int128_t &p)
{
	char cache[32];
	int cnt=0;
	__int128_t x=p;
	while(x!=0)
	{
		cache[cnt++]=x%10+'0';
		x/=10;
	}
	reverse(cache,cache+cnt);
	cache[cnt]='\0';
	return ous<<cache;
}

template<typename Int>
Int gcd(Int x,Int y)
{
	static Int zero(0),z;
	z=x%y;
	while(z!=zero)
	{
		x=y,y=z;
		z=x%y;
	}
	return y;
}

typedef __int128_t Integer;

class Frac{
	private:
		Integer up,low;
		void chk()
		{
			Integer g=gcd(up,low);
			up/=g,low/=g;
			return;
		}
	public:
		friend istream& operator >> (istream &ins,Frac &x);
		friend ostream& operator << (ostream &ous,const Frac &x);
		Frac(const Integer &x)
		{
			up=x,low=1;
			return;
		}
		Frac(const Integer &&x)
		{
			up=move(x),low=1;
			return;
		}
		Frac(){;}
		Frac(const Frac &x)
		{
			up=x.up,low=x.low;
			return;
		}
		Frac(Frac &&x)
		{
			up=move(x.up),low=move(x.low);
			return;
		}
		Frac& operator=(const Frac&x)
		{
			up=x.up,low=x.low;
			return *this;
		}
		Frac& operator=(Frac &&x)
		{
			up=move(x.up),low=move(x.low);
			return *this;
		}
		Frac&& operator +(const Frac &x)const
		{
			static Frac ans;
			ans=Frac(up*x.low+low*up);
			ans.low=low*x.low;
			ans.chk();
			return move(ans);
		}
		Frac& operator +=(const Frac &x)
		{
			Integer tmp=low*x.up;
			this->up*=x.low,this->low*=x.low;
			this->up+=tmp;
			chk();
			return *this;
		}
		Frac& operator *=(const Integer &x)
		{
			Integer g=gcd(low,x);
			low/=g;
			up*=x/g;
			return *this;
		}
		Frac&& operator *(const Integer &x)const
		{
			Frac ans;
			ans=*this;
			return move(ans*=x);
		}
		Frac& operator *=(const Frac &x)
		{
			low*=x.low,up*=x.up;
			chk();
			return *this;
		}
		Frac&& operator *(const Frac &x)const
		{
			static Frac ans;
			ans=*this;
			return move(ans*=x);
		}
		Frac& operator /=(const Frac &x)
		{
			low*=x.up,up*=x.low;
			chk();
			return *this;
		}
		Frac&& operator /(const Frac &x)const
		{
			static Frac ans;
			ans=*this;
			return move(ans/=x);
		}
		Frac& operator /=(const Integer &x)
		{
			static Integer g;
			g=gcd(up,x);
			up/=g;
			low*=x/g;
			return *this;
		}
		Frac&& operator /(const Integer &x)const
		{
			static Frac ans;
			ans=*this;
			return move(ans/=x);
		}
};
istream& operator >>(istream &ins,Frac &x)
{
	ins>>x.up>>x.low;
	x.chk();
	return ins;
}
ostream& operator <<(ostream &ous,const Frac &x)
{
	return ous<<x.up<<' '<<x.low;
}

vector<int> toe[100010];
int idg[100010];
Frac *wt=new Frac[100010];
int n,m;

void init()
{
	cin>>n>>m;
	for(int i=1;i<=n;i++)
	{
		int p;
		cin>>p;
		for(int j=0;j<p;j++)
		{
			int x;
			cin>>x;
			toe[i].push_back(x);
			idg[x]++;
		}
	}
}

void work()
{
	queue<int>q;
	for(int i=1;i<=n;i++)
	{
		if(idg[i]==0)
		{
			wt[i]=Frac(1);
			q.push(i);
		}
		else
		{
			wt[i]=Frac(0);
		}
	}
	while(!q.empty())
	{
		int p=q.front();
		q.pop();
		if(toe[p].size()!=0)
		{
			Frac x(wt[p]/toe[p].size());
			for(auto i:toe[p])
			{
				wt[i]+=x;
				idg[i]--;
				if(idg[i]==0)
					q.push(i);
			}
		}
	}
	for(int i=1;i<=n;i++)
		if(toe[i].empty())
			cout<<wt[i]<<endl;
	return;
}

int main()
{
	ios::sync_with_stdio(false);
	init();
	work();
	delete[] wt;
	return 0;
}