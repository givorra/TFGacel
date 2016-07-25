#include "Cube.h"

Cube::Cube()
{
	int n = 0;
	densityCube = vector<vector<vector< double> > >( n, vector<vector<double> >( n, vector<double> ( n)));
	maxDensity = 0;
	minDensity = 0;
}

Cube::Cube(int n)
{
	densityCube = vector<vector<vector< double> > >( n, vector<vector<double> >( n, vector<double> ( n)));
	for(int i = 0; i < n; i++)
		for(int j = 0; j < n; j++)
			for(int k = 0; k < n; k++)
				densityCube[i][j][k] = 0;
	maxDensity = 0;
}

double Cube::get(int i, int j, int k)
{
	return densityCube[i][j][k];
}

void Cube::set(int i, int j, int k, double v)
{
	densityCube[i][j][k] = v;
}

void Cube::setMaxDensity(double maxDensity)
{
	this->maxDensity = maxDensity;
}

double Cube::getMaxDensity()
{
	return maxDensity;
}

void Cube::setMinDensity(double minDensity)
{
	this->minDensity = minDensity;
}

double Cube::getMinDensity()
{
	return minDensity;
}

int Cube::getSideSize()
{
	return densityCube.size();
}
