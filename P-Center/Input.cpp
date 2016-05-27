
#include "Input.h"


Input::Input()
{
}


Input::~Input()
{
}

void Input::setCount(int point, int edge, int server) 
{
	numberOfPoint = point;
	numberOfServerPoint = server;
	numberOfEdge = edge;
}

void Input::initDistance() 
{
	distance = vector<vector<int>>(numberOfPoint, vector<int>(numberOfPoint, INT_MAX));
	for (int i = 0; i < numberOfPoint; i++)
	{
		distance[i][i] = 0;
	}
}

void Input::setDistance(int pointA, int pointB, int length)
{
	distance[pointA - 1][pointB - 1] = length;
	distance[pointB - 1][pointA - 1] = length;
}

void Input::floyd() {
	for (int k = 0; k < numberOfPoint; k++)
	{
		for (int i = 0; i < numberOfPoint; i++)
		{
			for (int j = 0; j < numberOfPoint; j++)
			{
				if (distance[i][k] != INT_MAX && distance[k][j] != INT_MAX) 
				{
					if (distance[i][k] + distance[k][j] < distance[i][j]) 
					{
						distance[i][j] = distance[i][k] + distance[k][j];
						distance[j][i] = distance[i][j];
					}
				}
			}
		}
	}
}