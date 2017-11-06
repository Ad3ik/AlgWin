#pragma once
#include "Population.h"
#include "PopulationInitializer.h"

#include <iostream>
#include <string>
#include <algorithm>

class EvolutionAlg
{
public:
	EvolutionAlg();
	EvolutionAlg(double crossoverRate, double mutationRate, int maxIterations, int generationsWithNoChangeBestSpecimenValue);
	~EvolutionAlg();
	void Initialize(int citiesCount);
	void Initialize(std::string filePath, int populationCount, int selectedPopulationCount);
	int GetGenerationsCount();
	void SetGenerationsCount(int count);
	void IncreaseGenerationCount();
	


private:
	Population* population;
	double crossoverRate;
	double mutationRate;
	int maxIterations;
	int generationsCount;
	int generationsWithNoChangeBestSpecimenValue;
	

	void Evaluate(Population* population);
	void Selection(Population* population);
	void Crossover(Population population);
	void Mutation(Population population);
	void StartAlgotitm();
};

