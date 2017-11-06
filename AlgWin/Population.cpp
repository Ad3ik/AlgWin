#include "stdafx.h"
#include "Population.h"


Population::Population()
{
	this->populationCount = 20;
	this->selectedPopulationCount = 10;
}

Population::Population(int populationCount, int selectedPopulationCount)
{
	this->populationCount = populationCount;
	this->selectedPopulationCount = selectedPopulationCount;
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

std::vector<Specimen*> Population::GetPopulationList()
{
	return this->populationList;
}

std::vector<std::vector<int>> Population::GetDistanceMatrix()
{
	return this->distanceMatrix;
}

std::vector<Specimen*> Population::GetSelectedPopulationList()
{
	return this->selectedPopulationList;
}

void Population::AddSelectedSpecimen(Specimen * specimen)
{
	this->selectedPopulationList.push_back(specimen);
}

int Population::GetSelectedPopulationCount()
{
	return this->selectedPopulationCount;
}


