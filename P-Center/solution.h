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
	int getRandomPoint(list<int> points); //�ڼ��������ѡ��һ��Ԫ��
	void addServerPoint(int point);
	void swapPoints(vector<int> pair);  //�����������
	void setFirstPoint();
	void initTables();
	void updateTables(int point, int flag);
	void findSubPoint(int point);        //Ѱ�Ҵν���
	vector<int> findFarthestPoint();     //Ѱ��������
	list<int> getNextPoints(int center, int radius); //�Խ��Ϊ���ģ�Ѱ�Ҿ���С��radius�ĵ�
	int selectNextServer(int center, int radius);
	void createInitSln();
	void optimizeSln();
	list<vector<int>> findPair();        //Ѱ�ҿ��Ż���Ľ�������
	vector<int> selectProperPair(list<vector<int>> pairs); //�ڿɽ���������ѡ��һ��
	bool writeFile(int time);
public:
	int maxLength;
	int time;  //��������
	FTable fTable;
	DTable dTable;
	const Input &instance;
	vector<int> serverPoints;  //the index of points
	int calculateMaxEdge();
	bool solve();
};
#endif