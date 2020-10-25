
#include <iostream>  
#include <fstream>  
#include <sstream>  
using namespace std;
 
int main()
{
	int k = 1;
	//system("mkdir d:\\output");//是在d盘下建立output文件夹  
	//system("mkdir d:program files\\output"); 
	//（创建错误）路径若带空格，则无法建立，要采用在路径上加\"... \",即\"路径\"，也就是下面这种形式  
	//system("mkdir \"d:program files\\output\""); 路径若带空格,建立正确  
	system("mkdir \"output\"");//是在当前main目录下建立output文件夹  
 
	for (k = 1; k != 4; ++k)
	{
		stringstream ss;//会自动析构，每一次循环会清空ss里面内容  
		ss << "output\\" << k << ".txt";
		cout << ss.str() << endl;
		//这里每个文本路径显示的是output\k.txt,这是真实的路径显示形式 (不是output\\k.txt)  
		ofstream fout(ss.str());
		fout << "1";
		fout.close();
	}
 
	system("pause");
	return 0;
}
