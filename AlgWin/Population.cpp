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
	this->bestValueGenerationsCount = 0;
	this->bestSpecimenEvaluateValue = INFINITY;
	this->bestSpecimenEvaluateOveralValue = 1000000;
	std::vector<Specimen*> vector = {};
	for (size_t i = 0; i < populationCount; i++)
	{
		Specimen* specimen = new Specimen();
		vector.push_back(specimen);
	}
	this->SetSelectedPopulationList(vector);
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

void Population::SetPopulationLList(std::vector<Specimen*> populationList)
{
	this->populationList= populationList;
}

void Population::SetSelectedPopulationList(std::vector<Specimen*> selectedPopulationList)
{
	this->selectedPopulationList = selectedPopulationList;
}

void Population::SetBestSpecimenEvaluateValue(double value)
{
	this->bestSpecimenEvaluateValue = value;
}

double Population::GetBestSpecimenEvaluateValue()
{
	return this->bestSpecimenEvaluateValue;
}

void Population::SetBestValueGenerationsCount(double value)
{
	this->bestValueGenerationsCount = value;
}


