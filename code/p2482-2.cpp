#include <stdio.h>
#include <vector>
using namespace std;

#define MP 0
#define ZP 1
#define FP 2

#define P 0
#define K 1
#define D 2
#define F 3
#define N 4
#define W 5
#define J 6
#define Z 7

#define unShown 0
#define good 1
#define bad 2

bool finished=false;
int pigNum,cardPoolCardNum;
int runningPig;

char getMeaningfulChar()
{
	char x=getchar();
	while((x>'z'||x<'a')&&(x>'Z'&&x<'A')&&(x>'9'&&x<'0'))
		x=getchar();
	return x;
}

class CardPool{
	private:
		vector<char>pool;
	public:
		void set(int n)
		{
			for(int i=0;i<n;i++)
				pool.push_back(getMeaningfulChar());
			return;
		}
		char getCard()
		{
			char ans=*(pool.begin());
			pool.erase(pool.begin());
			return ans;
		}
};

struct Pig{
	bool ifAlive;
	int type,blood;
	vector<char>card;
	int shownType,viewTypeByMP;
};

CardPool cardPool;
Pig pig[15];

void initPig(int p)
{
	char x=getMeaningfulChar();
	switch (x)
	{
	case 'M':
		pig[p].type=MP;
		break;

	case 'Z':
		pig[p].type=ZP;
		break;
	
	case 'F':
		pig[p].type=FP;
		break;
	}
	getMeaningfulChar();
	for(int i=0;i<4;i++)
		pig->card.push_back(getMeaningfulChar());
	return;
}

void init()
{
	scanf("%d%d",&pigNum,&cardPoolCardNum);
	for(int i=1;i<=pigNum;i++)
		initPig(i);
	cardPool.set(cardPoolCardNum);
	return;
}

bool ifPutable(int card,int type)
{

}

void runMP();
void runZP();
void runFP();

void run()
{
	switch (pig[runningPig].type)
	{
		case MP:
			runMP();
			break;
		case ZP:
			runZP();
			break;
		case FP:
			runFP();
			break;
	}
	return;
}

void work()
{
	runningPig=1;
	while(!finished)
	{
		run();
		runningPig++;
		if(runningPig==pigNum+1)
			runningPig=1;
	}
	
}

int main()
{
	init();
	work();
	return 0;
}
