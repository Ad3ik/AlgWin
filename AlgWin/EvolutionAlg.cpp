#include "stdafx.h"
#include "EvolutionAlg.h"


EvolutionAlg::EvolutionAlg()
{
}

EvolutionAlg::EvolutionAlg(double crossoverRate, double mutationRate, int maxIterations, int generationsWithNoChangeBestSpecimenValue)
{
	this->crossoverRate = crossoverRate;
	this->mutationRate = mutationRate;
	this->maxIterations = maxIterations;
	this->generationsCount = 0;
	this->generationsWithNoChangeBestSpecimenValue = generationsWithNoChangeBestSpecimenValue;
}


EvolutionAlg::~EvolutionAlg()
{
}

void EvolutionAlg::Initialize(int citiesCount)
{
}

void EvolutionAlg::Initialize(std::string filePath, int populationCount)
{
	this->population = new Population(populationCount);
	PopulationInitializer* populationInitializer = new PopulationInitializer(population);
	populationInitializer->InitializePopulationFromFile(filePath);
	SetGenerationsCount(0);
	StartAlgotitm();
}

int EvolutionAlg::GetGenerationsCount()
{
	return this->generationsCount;
}

void EvolutionAlg::SetGenerationsCount(int count)
{
	this->generationsCount = count;
}

void EvolutionAlg::IncreaseGenerationCount()
{
	this->generationsCount++;
}

void EvolutionAlg::Evaluate(Population p)
{
}

void EvolutionAlg::Selection(Population population)
{
}

void EvolutionAlg::Crossover(Population population)
{
}

void EvolutionAlg::Mutation(Population population)
{
}

void EvolutionAlg::StartAlgotitm()
{
	while (GetGenerationsCount() < this->maxIterations && this->population->GetBestValueGenerationsCount()<generationsWithNoChangeBestSpecimenValue) {
		IncreaseGenerationCount();
	}
	int a = 5;

}
