#include "stdafx.h"
#include "Population.h"


Population::Population()
{
	this->populationCount = 20;
}

Population::Population(int populationCount)
{
	this->populationCount = populationCount;
}


Population::~Population()
{
}

void Population::AddSpecimen(Specimen * specimen)
{
	this->populationList.push_back(specimen);
}

int Population::GetPopulationCount()
{
	return this->populationCount;
}

void Population::SetDistanceMatrix(std::vector<std::vector<int>> distanceMatrix)
{
	this->distanceMatrix = distanceMatrix;
}

int Population::GetBestValueGenerationsCount()
{
	return this->bestValueGenerationsCount;
}


