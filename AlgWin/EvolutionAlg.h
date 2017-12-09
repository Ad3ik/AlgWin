#pragma once
#include "Population.h"
#include "PopulationInitializer.h"

#include <iostream>
#include <string>
#include <algorithm>
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include <random>

class EvolutionAlg
{
public:
	EvolutionAlg();
	EvolutionAlg(double crossoverRate, double mutationRate, double bestSpecimanSelectionMultiplication, int maxIterations, int generationsWithNoChangeBestSpecimenValue, int crossOverType);
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
	double bestSpecimanSelectionMultiplication;
	int maxIterations;
	int generationsCount;
	int generationsWithNoChangeBestSpecimenValue;
	int crossOverType;
	

	void Evaluate(Population* population);
	void Selection(Population* population);
	void Crossover(Population* population);
	void CrossoverPMX(Population* population);
	void CrossoverOX(Population* population);
	void CrossoverEX(Population* population);
	void Mutation(Population* population);
	void StartAlgotitm();
};

