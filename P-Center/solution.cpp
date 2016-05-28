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

bool Solution::initTabusList()
{
	tabusList = vector<vector<int>>(2, vector<int>(instance.numberOfPoint, 0));
	return true;
}

int Solution::calculateMaxEdge()
{
	maxLength = 0;
	for (int i = 0; i < instance.numberOfPoint; i++)
	{
		if (dTable[i][0] > maxLength)
		{
			maxLength = dTable[i][0];
		}
	}
	return maxLength;
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
	}
}

void Solution::updateTables(int point, int flag)
{
	if (flag == ADD_FLAG)
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
	else if(flag == DELETE_FLAG)
	{
		for (int i = 0; i < instance.numberOfPoint; i++)
		{
			if (fTable[i][0] == point)
			{
				fTable[i][0] = fTable[i][1];
				dTable[i][0] = dTable[i][1];
				dTable[i][1] = 0;
				findSubPoint(i);
			}
			else if (fTable[i][1] == point)
			{
				dTable[i][1] = 0;

			}
		}
	}
	
}

void Solution::findSubPoint(int point)
{
	for (int i = 0; i < foundPoints; i++)
	{
		if (serverPoints[i] != fTable[point][0])
		{
			if (dTable[point][1] == 0 || instance.distance[point][serverPoints[i]] < dTable[point][1])
			{
				dTable[i][1] = instance.distance[point][serverPoints[i]];
				fTable[i][1] = serverPoints[i];
			}
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

list<vector<int>> Solution::findPair()     //寻找交换结点对
{
	vector<int> result = findFarthestPoint();
	list<vector<int>> pairs;
	int maxCost = maxLength;
	if (result[0] != -1)
	{
		list<int>  nextList = getNextPoints(result[0], result[1]);
		for (list<int>::iterator li = nextList.begin(); li != nextList.end(); li++)
		{
			vector<int> mf = vector<int>(foundPoints, 0);
			for (int i = 0; i < foundPoints; i++)
			{
				int point = serverPoints[i];
				for (int j = 0; j < instance.numberOfPoint; j++)
				{
					if (fTable[j][0] == point)
					{
						if (min(dTable[j][1], instance.distance[(*li)][j]) > mf[i])
						{
							mf[i] = min(dTable[j][1], instance.distance[(*li)][j]);
						}
					}
				}		
			}
			for (int i = 0; i < foundPoints; i++)
			{
				if (mf[i] == maxCost)
				{
					vector<int> v = vector<int>(2, -1);
					v[0] = (*li);
					v[1] = serverPoints[i];
					pairs.push_back(v);
				}
				else if(mf[i] < maxCost)
				{
					vector<int> v = vector<int>(2, -1);
					v[0] = (*li);
					v[1] = serverPoints[i];
					pairs.clear();
					pairs.push_back(v);
					maxCost = mf[i];
				}
			}
		}
	}
	return pairs;
}

vector<int> Solution::selectProperPair(list<vector<int>> pairs)
{
	return (*pairs.begin());
}

void Solution::addServerPoint(int point) 
{
	if (foundPoints < instance.numberOfServerPoint) 
	{
		serverPoints[foundPoints++] = point;
	}
}

void Solution::swapPoints(vector<int> pair)
{
	int addPoint = pair[0];
	int deletePoint = pair[1];
	for (int i = 0; i < foundPoints; i++)
	{
		if (serverPoints[i] == deletePoint) {
			serverPoints[i] = addPoint;
			updateTables(addPoint, ADD_FLAG);
			updateTables(deletePoint, DELETE_FLAG);
			break;
		}
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
				updateTables(next, ADD_FLAG);
			}
		}
	}
}

void Solution::optimizeSln()
{
	time = 0;
	while (true)
	{
		++time;
		list<vector<int>> pairs = findPair();
		if (pairs.size() == 0)
		{
			break;
		}
		swapPoints(selectProperPair(pairs));
		calculateMaxEdge();
		writeFile(time);
	}
}

bool Solution::solve() 
{
	createInitSln();
	calculateMaxEdge();
	writeFile(time);
	optimizeSln();
	return true;
}

bool Solution::writeFile(int time)
{
	stringstream fileName;
	fileName << "F:\\tables\\table" << time << ".csv";

	ofstream outFile(fileName.str());
	if (!outFile.is_open()) {
		return false;
	}

	outFile << "server points\n";
	for (int i = 0; i < serverPoints.size(); ++i) {
		outFile << serverPoints[i] + 1 << ",";
		if ((i + 1) % 10 == 0)
		{
			outFile << "\n";
		}
	}
	outFile << "\nmax length:" << maxLength;
	outFile << "\n,ftable,,,dtable\n";
	outFile << "point,f0,f1,,d0,d1\n";
	for (int i = 0; i < instance.numberOfPoint; ++i) {
		outFile << i + 1 << "," << fTable[i][0] + 1 << "," << fTable[i][1] + 1
			<< ",," << dTable[i][0] << "," << dTable[i][1] << "\n";
	}
	outFile.close();
	return true;
}