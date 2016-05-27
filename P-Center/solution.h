#ifndef SOLUTION_H
#define SOLUTION_H
#include "input.h"
#include <set>
#include <list>
class  Solution
{
public:
	Solution(const Input &input);
	~Solution();
	typedef vector<vector<int>> FTable;
	typedef vector<vector<int>> DTable;

private:
	int foundPoints;
	int requiredPoints;
	
	int getRandomPoint(list<int> points);
	void addServerPoint(int point);
	void setFirstPoint();
	void initTables();
	void updateTables(int point);
	vector<int> findFarthestPoint();
	list<int> getNextPoints(int center, int radius);
	int selectNextServer(int center, int radius);
	void createInitSln();
	
public:
	int maxLength;
	FTable fTable;
	DTable dTable;
	const Input &instance;
	vector<int> serverPoints;  //the index of points
	bool solve();
};


#endif