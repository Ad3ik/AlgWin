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

void EvolutionAlg::Initialize(std::string filePath, int populationCount, int selectedPopulationCount)
{
	this->population = new Population(populationCount,  selectedPopulationCount);
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



void EvolutionAlg::Evaluate(Population* population)
{
	for (auto &Specimen : population->GetPopulationList())
	{
		std::vector<int> specimenVector = Specimen->GetSpecimenVector();
		double specimenEvaluateValue = 0;
		for (size_t i = 0; i < specimenVector.size()-1; i++)
		{
			specimenEvaluateValue = specimenEvaluateValue + population->GetDistanceMatrix()[specimenVector[i]][specimenVector[i+1]];

		}
		Specimen->SetSpecimenEvaluateValue(specimenEvaluateValue);
	}
	
}

void EvolutionAlg::Selection(Population* population)
{
	std::vector<Specimen*> populationList = population->GetPopulationList();
	for (size_t i = 0; i < population->GetSelectedPopulationCount(); i++)
	{
		double bestSpecimenEvaluateValue = INFINITY;
		Specimen* bestSpecimen = new Specimen();
		for (auto &Specimen : populationList)
		{
			if (Specimen->GetSpecimentEvaluateValue()<bestSpecimenEvaluateValue)
			{
				bestSpecimenEvaluateValue = Specimen->GetSpecimentEvaluateValue();
				bestSpecimen = Specimen;
			}
		}
		population->AddSelectedSpecimen(bestSpecimen);
		populationList.erase(std::remove(populationList.begin(), populationList.end(), bestSpecimen), populationList.end());
	}
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
		Evaluate(this->population);
		Selection(this->population);
	}
	int a = 5;

}
