
#include <iostream>  
#include <fstream>  
#include <sstream>  
using namespace std;
 
int main()
{
	int k = 1;
	//system("mkdir d:\\output");//����d���½���output�ļ���  
	//system("mkdir d:program files\\output"); 
	//����������·�������ո����޷�������Ҫ������·���ϼ�\"... \",��\"·��\"��Ҳ��������������ʽ  
	//system("mkdir \"d:program files\\output\""); ·�������ո�,������ȷ  
	system("mkdir \"output\"");//���ڵ�ǰmainĿ¼�½���output�ļ���  
 
	for (k = 1; k != 4; ++k)
	{
		stringstream ss;//���Զ�������ÿһ��ѭ�������ss��������  
		ss << "output\\" << k << ".txt";
		cout << ss.str() << endl;
		//����ÿ���ı�·����ʾ����output\k.txt,������ʵ��·����ʾ��ʽ (����output\\k.txt)  
		ofstream fout(ss.str());
		fout << "1";
		fout.close();
	}
 
	system("pause");
	return 0;
}
