#pragma once
#include "Specimen.h"
#include <vector>

class Population
{
public:
	Population();
	Population(int populationCount);
	~Population();
	void AddSpecimen(Specimen* specimen);
	int GetPopulationCount();
	void SetDistanceMatrix(std::vector<std::vector<int>> distanceMatrix);
	int GetBestValueGenerationsCount();
private:
	int populationCount;
	std::vector<std::vector<int>> distanceMatrix;
	std::vector<Specimen*> populationList;
	int bestSpecimenEvaluateValue;
	int bestValueGenerationsCount;
};

