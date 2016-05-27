#include "solution.h"

Solution::Solution(const Input &problem) : instance( problem )
{
	foundPoints = 0;
	requiredPoints = instance.numberOfServerPoint;
	serverPoints = vector<int>(requiredPoints, -1);
	maxLength = 0;
}

Solution::~Solution()
{
}

int Solution::getRandomPoint(list<int> points)
{
	int i = 0, random = rand() % points.size();
	for (list<int>::iterator li = points.begin(); li != points.end(); li++)
	{
		if (i == random) {
			return (*li);
		}
		i++;
	}
	return -1;
}
void Solution::initTables() 
{
	int server = serverPoints[0];
	fTable = vector<vector<int>>(instance.numberOfPoint, vector<int>(2, server));
	dTable = vector<vector<int>>(instance.numberOfPoint, vector<int>(2, 0));
	for (int i = 0; i < instance.numberOfPoint; i++)
	{
		dTable[i][0] = instance.distance[server][i];
		if (dTable[i][0] > maxLength)
		{
			maxLength = dTable[i][0];
		}
	}
}

void Solution::updateTables(int point)
{
	for (int i = 0; i < instance.numberOfPoint; i++)
	{
		if (instance.distance[point][i] < dTable[i][0])
		{
			dTable[i][1] = dTable[i][0];
			fTable[i][1] = fTable[i][0];
			dTable[i][0] = instance.distance[point][i];
			fTable[i][0] = point;
		}
		else if (dTable[i][1] == 0 || instance.distance[point][i] < dTable[i][1])
		{
			dTable[i][1] = instance.distance[point][i];
			fTable[i][1] = point;
		}
	}
}

vector<int> Solution::findFarthestPoint() //<point, maxDistance>
{
	list<int> points;
	int maxDistance = 0;
	for (int i = 0; i < instance.numberOfPoint; i++)
	{
		if (dTable[i][0] == maxDistance) 
		{
			points.push_back(i);
		}
		else if(dTable[i][0] > maxDistance)
		{
			maxDistance = dTable[i][0];
			points.clear();
			points.push_back(i);
		}
	}
	maxLength = maxDistance;
	vector<int> result = vector<int>(2, -1);
	result[0] = getRandomPoint(points);
	result[1] = maxDistance;
	return result;
}

list<int> Solution::getNextPoints(int center, int radius)  //求解以最远用户结点为中心，距离小于最长服务边的点的集合
{
	list<int> points;
	for (int i = 0; i < instance.numberOfPoint; i++)
	{
		if (instance.distance[center][i] < radius)
		{
			points.push_back(i);
		}
	}
	return points;
}

int Solution::selectNextServer(int center, int radius)   //选择下一个服务点
{
	return getRandomPoint(getNextPoints(center, radius));
}

void Solution::addServerPoint(int point) 
{
	if (foundPoints < instance.numberOfServerPoint) 
	{
		serverPoints[foundPoints++] = point;
	}
}

void Solution::setFirstPoint() 
{
	addServerPoint(rand() % requiredPoints);
}

void Solution::createInitSln()
{
	setFirstPoint();
	initTables();
	while (foundPoints < requiredPoints)
	{
		vector<int> result = findFarthestPoint();
		if (result[0] != -1)
		{
			int next = selectNextServer(result[0], result[1]);
			if (next != -1) {
				addServerPoint(next);
				updateTables(next);
			}
		}
	}
}

bool Solution::solve() 
{
	createInitSln();
	return true;
}