// P-Center.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "io.h"
#include "solution.h"
int random(const int base) {
	return rand() % base;
}

int main(int argc,char* argv[])
{
	Input input;
	if (readTxtInstance("F:\\instances\\pmed34.txt", input)) 
	{
		cout << "read instance succeed\n";
	}
	Solution solution(input);
	if (solution.solve()) 
	{
		cout << "ok";
	}
	
	return 0;
}


