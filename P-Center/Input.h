#ifndef INPUT_H
#define INPUT_H
#include <vector>
using namespace std;

class Input
{
public:
	int numberOfPoint;
	int numberOfServerPoint;
	int numberOfEdge;
	vector<vector<int>> distance;
public:
	Input();
	~Input();
	void setCount(int point ,int edge, int server);
	void initDistance();
	void setDistance(int pointA, int pointB, int length);
	void floyd();
};
#endif
