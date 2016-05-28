#ifndef SOLUTION_H
#define SOLUTION_H
#include "input.h"
#include <string>
#include <sstream>
#include <iostream>
#include <fstream>
#include <list>
#include <algorithm>
class  Solution
{
public:
	Solution(const Input &input);
	~Solution();
	typedef vector<vector<int>> FTable;
	typedef vector<vector<int>> DTable;
	typedef vector<vector<int>> TabusList;

private:
	const int ADD_FLAG = 1;
	const int DELETE_FLAG = 1;
	int foundPoints;
	int requiredPoints;
	TabusList tabusList;

	bool initTabusList();
	int getRandomPoint(list<int> points); //在集合中随机选择一个元素
	void addServerPoint(int point);
	void swapPoints(vector<int> pair);  //交换两个结点
	void setFirstPoint();
	void initTables();
	void updateTables(int point, int flag);
	void findSubPoint(int point);        //寻找次近点
	vector<int> findFarthestPoint();     //寻找最长服务边
	list<int> getNextPoints(int center, int radius); //以结点为中心，寻找距离小于radius的点
	int selectNextServer(int center, int radius);
	void createInitSln();
	void optimizeSln();
	list<vector<int>> findPair();        //寻找可优化解的交换结点对
	vector<int> selectProperPair(list<vector<int>> pairs); //在可交换结点对中选择一对
	bool writeFile(int time);
public:
	int maxLength;
	int time;  //迭代次数
	FTable fTable;
	DTable dTable;
	const Input &instance;
	vector<int> serverPoints;  //the index of points
	int calculateMaxEdge();
	bool solve();
};
#endif