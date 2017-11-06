#include "stdafx.h"
#include "EvolutionAlg.h"


EvolutionAlg::EvolutionAlg()
{
}

EvolutionAlg::EvolutionAlg(double crossoverRate, double mutationRate, int maxIterations, int generationsWithNoChangeBestSpecimenValue, int crossOverType)
{
	this->crossoverRate = crossoverRate;
	this->mutationRate = mutationRate;
	this->maxIterations = maxIterations;
	this->generationsCount = 0;
	this->generationsWithNoChangeBestSpecimenValue = generationsWithNoChangeBestSpecimenValue;
	this->crossOverType = crossOverType;
}


EvolutionAlg::~EvolutionAlg()
{
}

void EvolutionAlg::Initialize(int citiesCount)
{
}

void EvolutionAlg::Initialize(std::string filePath, int populationCount, int selectedPopulationCount)
{
	this->population = new Population(populationCount, selectedPopulationCount);
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
		for (size_t i = 0; i < specimenVector.size() - 1; i++)
		{
			specimenEvaluateValue = specimenEvaluateValue + population->GetDistanceMatrix()[specimenVector[i]][specimenVector[i + 1]];

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
			if (Specimen->GetSpecimentEvaluateValue() < bestSpecimenEvaluateValue)
			{
				bestSpecimenEvaluateValue = Specimen->GetSpecimentEvaluateValue();
				bestSpecimen = Specimen;
			}
		}
		population->AddSelectedSpecimen(bestSpecimen);
		populationList.erase(std::remove(populationList.begin(), populationList.end(), bestSpecimen), populationList.end());
	}
	population->SetPopulationLList({});
}

void EvolutionAlg::Crossover(Population* population)
{
	switch (this->crossOverType)
	{
	case 0:
		CrossoverPMX(population);
		break;
	case 1:
		CrossoverOX(population);
		break;
	case 2:
		CrossoverEX(population);
		break;
	default:
		break;
	}
}

void EvolutionAlg::CrossoverPMX(Population * population)
{
	std::vector<Specimen*> populationList = population->GetPopulationList();
	srand(time(NULL));
	while (populationList.size() < population->GetPopulationCount())
	{
		int randomSpecimenNumber = rand() % population->GetSelectedPopulationCount();
		int randomSpecimenNumber2 = rand() % population->GetSelectedPopulationCount();
		Specimen* specimenFirst = population->GetSelectedPopulationList()[randomSpecimenNumber];
		Specimen* specimenSecond = population->GetSelectedPopulationList()[randomSpecimenNumber2];
		std::vector<int> firstSpecimentVector = specimenFirst->GetSpecimenVector();
		std::vector<int> secondSpecimentVector = specimenSecond->GetSpecimenVector();
		Specimen* newSpecimen = new Specimen();
		int crossOverSpot = rand() % (specimenFirst->GetSpecimenVector().size() / 2 + 1);
		for (size_t i = 0; i < specimenFirst->GetSpecimenVector().size(); i++)
		{
			newSpecimen->AddCityToEnd(-1);
		}
		for (size_t i = crossOverSpot; i < firstSpecimentVector.size() / 2 + crossOverSpot; i++)
		{
			newSpecimen->SetSpecimenVectorValue(i, firstSpecimentVector[i]);

		}
		for (size_t i = crossOverSpot; i < firstSpecimentVector.size() / 2 + crossOverSpot; i++)
		{
			int firstSpecimenGene;
			int secondSpecimenGene;
			bool geneFinding = false;
			bool shouldCopy = true;
			do
			{

				firstSpecimenGene = firstSpecimentVector[i];
				secondSpecimenGene = secondSpecimentVector[i];
				for (size_t i = crossOverSpot; i < firstSpecimentVector.size() / 2 + crossOverSpot; i++)
				{
					if (firstSpecimentVector[i] == secondSpecimenGene) {
						shouldCopy = false;
						break;
					}
					if (firstSpecimenGene == secondSpecimentVector[i]) {
						firstSpecimenGene = firstSpecimentVector[i];
						geneFinding = true;
					}
				}
			} while (geneFinding);
			if (shouldCopy)
			{
				for (size_t i = 0; i < firstSpecimentVector.size(); i++)
				{

					if (firstSpecimenGene == secondSpecimentVector[i])
					{
						newSpecimen->SetSpecimenVectorValue(i, secondSpecimenGene);

					}
				}
			}


		}
		std::vector<int> newSpecimentVector = newSpecimen->GetSpecimenVector();
		for (size_t i = 0; i < firstSpecimentVector.size(); i++)
		{
			if (newSpecimentVector[i] == -1) {
				newSpecimen->SetSpecimenVectorValue(i, secondSpecimentVector[i]);
			}
		}
		population->AddSpecimen(newSpecimen);
	}
	}
	

void EvolutionAlg::CrossoverOX(Population * population)
{
}

void EvolutionAlg::CrossoverEX(Population * population)
{

}




void EvolutionAlg::Mutation(Population population)
{
}

void EvolutionAlg::StartAlgotitm()
{
	while (GetGenerationsCount() < this->maxIterations && this->population->GetBestValueGenerationsCount() < generationsWithNoChangeBestSpecimenValue) {
		IncreaseGenerationCount();
		Evaluate(this->population);
		Selection(this->population);
		Crossover(this->population);
	}
	int a = 5;

}
