#include "io.h"
bool readTxtInstance(const string &instancePath, Input &input) 
{
	string buf;
	int point, server, edge;
	
	ifstream inst(instancePath);

	if (!inst.is_open()) 
	{
		return false;
	}
	inst >> point;
	inst >> edge;
	inst >> server;
	input.setCount(point, edge, server);
	input.initDistance();

	for (int i = 0; i < edge; i++)
	{
		int pointA, pointB, distance;
		inst >> pointA;
		inst >> pointB;
		inst >> distance;
		input.setDistance(pointA, pointB, distance);
	}
	input.floyd();
	return true;
}

bool writeFile(const Solution &sln)
{
	ofstream outFile("F:\\table.csv");
	if (!outFile.is_open()) {
		return false;
	}
	for (int i = 0; i < sln.serverPoints.size(); ++i) {
		outFile << sln.serverPoints[i] << ",";
	}
	outFile << "\n" << sln.maxLength;
	outFile << "\n,ftable,,,dtable\n";
	outFile << "point,f0,f1,,d0,d1\n";
	for (int i = 0; i < sln.instance.numberOfPoint; ++i) {
		outFile << i << "," << sln.fTable[i][0] << "," << sln.fTable[i][1] 
			<< ",," << sln.dTable[i][0] << "," << sln.dTable[i][1] << "\n";
	}
	outFile.close();
	return true;
}