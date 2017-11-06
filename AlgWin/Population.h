#pragma once
#include "Specimen.h"
#include <vector>

class Population
{
public:
	Population();
	Population(int populationCount, int selectedPopulationCount);
	~Population();
	void AddSpecimen(Specimen* specimen);
	int GetPopulationCount();
	void SetDistanceMatrix(std::vector<std::vector<int>> distanceMatrix);
	int GetBestValueGenerationsCount();
	std::vector<Specimen*> GetPopulationList();
	std::vector<std::vector<int>> GetDistanceMatrix();
	std::vector<Specimen*> GetSelectedPopulationList();
	void AddSelectedSpecimen(Specimen* specimen);
	int GetSelectedPopulationCount();

	
private:
	int populationCount;
	std::vector<std::vector<int>> distanceMatrix;
	std::vector<Specimen*> populationList;
	int bestSpecimenEvaluateValue;
	int bestValueGenerationsCount;
	std::vector<Specimen*> selectedPopulationList;
	int selectedPopulationCount;

};

