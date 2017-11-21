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
	population->SetSelectedPopulationList({});
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
	//population->SetPopulationLList({});
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
	//while (populationList.size() < population->GetPopulationCount())
	//{
		//int randomSpecimenNumber = rand() % population->GetSelectedPopulationCount();
		//int randomSpecimenNumber2 = rand() % population->GetSelectedPopulationCount();
	std::random_shuffle(populationList.begin(), populationList.end());
	for (size_t m = 0; m < populationList.size(); m += 2)
	{
		Specimen* specimenFirst = populationList[m];
		Specimen* specimenSecond = populationList[m + 1];
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
				if (!geneFinding) {
					firstSpecimenGene = firstSpecimentVector[i];
					secondSpecimenGene = secondSpecimentVector[i];
				}
				geneFinding = false;

				for (size_t j = crossOverSpot; j < firstSpecimentVector.size() / 2 + crossOverSpot; j++)
				{
					if (firstSpecimentVector[j] == secondSpecimenGene) {
						shouldCopy = false;
						break;
					}
					if (firstSpecimenGene == secondSpecimentVector[j]) {
						firstSpecimenGene = firstSpecimentVector[j];
						geneFinding = true;
					}
				}
			} while (geneFinding);
			if (shouldCopy)
			{
				for (size_t k = 0; k < firstSpecimentVector.size(); k++)
				{

					if (firstSpecimenGene == secondSpecimentVector[k])
					{
						newSpecimen->SetSpecimenVectorValue(k, secondSpecimenGene);

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
		//population->AddSpecimen(newSpecimen);
		populationList[m] = newSpecimen;


		Specimen* specimenFirst2 = populationList[m + 1];
		Specimen* specimenSecond2 = populationList[m];
		std::vector<int> firstSpecimentVector2 = specimenFirst2->GetSpecimenVector();
		std::vector<int> secondSpecimentVector2 = specimenSecond2->GetSpecimenVector();
		Specimen* newSpecimen2 = new Specimen();
		int crossOverSpot2 = rand() % (specimenFirst2->GetSpecimenVector().size() / 2 + 1);
		for (size_t i = 0; i < specimenFirst2->GetSpecimenVector().size(); i++)
		{
			newSpecimen2->AddCityToEnd(-1);
		}
		for (size_t i = crossOverSpot2; i < firstSpecimentVector2.size() / 2 + crossOverSpot2; i++)
		{
			newSpecimen2->SetSpecimenVectorValue(i, firstSpecimentVector2[i]);

		}
		for (size_t i = crossOverSpot2; i < firstSpecimentVector2.size() / 2 + crossOverSpot2; i++)
		{
			int firstSpecimenGene;
			int secondSpecimenGene;
			bool geneFinding = false;
			bool shouldCopy = true;
			do
			{
				if (!geneFinding) {
					firstSpecimenGene = firstSpecimentVector2[i];
					secondSpecimenGene = secondSpecimentVector2[i];
				}
				geneFinding = false;

				for (size_t j = crossOverSpot2; j < firstSpecimentVector2.size() / 2 + crossOverSpot2; j++)
				{
					if (firstSpecimentVector2[j] == secondSpecimenGene) {
						shouldCopy = false;
						break;
					}
					if (firstSpecimenGene == secondSpecimentVector2[j]) {
						firstSpecimenGene = firstSpecimentVector2[j];
						geneFinding = true;
					}
				}
			} while (geneFinding);
			if (shouldCopy)
			{
				for (size_t k = 0; k < firstSpecimentVector2.size(); k++)
				{

					if (firstSpecimenGene == secondSpecimentVector2[k])
					{
						newSpecimen2->SetSpecimenVectorValue(k, secondSpecimenGene);

					}
				}
			}


		}
		std::vector<int> newSpecimentVector2 = newSpecimen2->GetSpecimenVector();
		for (size_t i = 0; i < firstSpecimentVector2.size(); i++)
		{
			if (newSpecimentVector2[i] == -1) {
				newSpecimen2->SetSpecimenVectorValue(i, secondSpecimentVector2[i]);
			}
		}
		populationList[m + 1] = newSpecimen2;
	}
	//}
	population->SetPopulationLList(populationList);
}


void EvolutionAlg::CrossoverOX(Population * population)
{
	std::vector<Specimen*> populationList = population->GetPopulationList();
	srand(time(NULL));
	std::random_shuffle(populationList.begin(), populationList.end());
	for (size_t m = 0; m < populationList.size(); m += 2)
	{
		double randomCrossOverRate = (double)rand() / RAND_MAX;
		Specimen* specimenFirst = populationList[m];
		Specimen* specimenSecond = populationList[m + 1];
		Specimen* newSpecimen = new Specimen();
		int crossOverSpot = rand() % (specimenFirst->GetSpecimenVector().size() / 2 + 1);
		if (randomCrossOverRate < this->crossoverRate) {
			Specimen* specimenFirst = populationList[m];
			Specimen* specimenSecond = populationList[m + 1];
			std::vector<int> firstSpecimentVector = specimenFirst->GetSpecimenVector();
			std::vector<int> secondSpecimentVector = specimenSecond->GetSpecimenVector();


			for (size_t i = 0; i < specimenFirst->GetSpecimenVector().size(); i++)
			{
				newSpecimen->AddCityToEnd(-1);
			}
			int firstIndexAfterCrossOverSpot = 0;
			for (size_t i = crossOverSpot; i < firstSpecimentVector.size() / 2 + crossOverSpot; i++)
			{
				newSpecimen->SetSpecimenVectorValue(i, firstSpecimentVector[i]);
				firstIndexAfterCrossOverSpot = i;

			}

			// ->
			for (size_t i = firstIndexAfterCrossOverSpot + 1; i < firstSpecimentVector.size() - firstSpecimentVector.size() / 2 + firstIndexAfterCrossOverSpot + 1; i++)
			{
				for (size_t j = firstIndexAfterCrossOverSpot + 1; j < firstSpecimentVector.size() + firstIndexAfterCrossOverSpot + 1; j++)
				{
					bool geneWasUsed = false;
					for (size_t k = crossOverSpot; k < firstSpecimentVector.size() + crossOverSpot; k++)
					{
						if (secondSpecimentVector[j%firstSpecimentVector.size()] == newSpecimen->GetSpecimenVector()[k%firstSpecimentVector.size()])
						{
							geneWasUsed = true;
						}
					}
					if (!geneWasUsed)
					{
						newSpecimen->SetSpecimenVectorValue(i%firstSpecimentVector.size(), secondSpecimentVector[j%firstSpecimentVector.size()]);
						break;
					}
				}

			}
		}
		Specimen* newSpecimen2 = new Specimen();
		double randomCrossOverRate2 = (double)rand() / RAND_MAX;
		if (randomCrossOverRate2 < this->crossoverRate) {
			Specimen* specimenFirst2 = populationList[m + 1];
			Specimen* specimenSecond2 = populationList[m];
			std::vector<int> firstSpecimentVector2 = specimenFirst2->GetSpecimenVector();
			std::vector<int> secondSpecimentVector2 = specimenSecond2->GetSpecimenVector();

			//int crossOverSpot2 = rand() % (specimenFirst2->GetSpecimenVector().size() / 2 + 1);
			for (size_t i = 0; i < specimenFirst2->GetSpecimenVector().size(); i++)
			{
				newSpecimen2->AddCityToEnd(-1);
			}
			int firstIndexAfterCrossOverSpot2 = 0;
			for (size_t i = crossOverSpot; i < firstSpecimentVector2.size() / 2 + crossOverSpot; i++)
			{
				newSpecimen2->SetSpecimenVectorValue(i, firstSpecimentVector2[i]);
				firstIndexAfterCrossOverSpot2 = i;

			}

			// ->
			for (size_t i = firstIndexAfterCrossOverSpot2 + 1; i < firstSpecimentVector2.size() - firstSpecimentVector2.size() / 2 + firstIndexAfterCrossOverSpot2 + 1; i++)
			{
				for (size_t j = firstIndexAfterCrossOverSpot2 + 1; j < firstSpecimentVector2.size() + firstIndexAfterCrossOverSpot2 + 1; j++)
				{
					bool geneWasUsed = false;
					for (size_t k = crossOverSpot; k < firstSpecimentVector2.size() + crossOverSpot; k++)
					{
						if (secondSpecimentVector2[j%firstSpecimentVector2.size()] == newSpecimen2->GetSpecimenVector()[k%firstSpecimentVector2.size()])
						{
							geneWasUsed = true;
						}
					}
					if (!geneWasUsed)
					{
						newSpecimen2->SetSpecimenVectorValue(i%firstSpecimentVector2.size(), secondSpecimentVector2[j%firstSpecimentVector2.size()]);
						break;
					}
				}

			}
		}
		if (randomCrossOverRate < this->crossoverRate) {
			populationList[m] = newSpecimen;
		}
		if (randomCrossOverRate2 < this->crossoverRate) {
			populationList[m + 1] = newSpecimen2;
		}
	}
	population->SetPopulationLList(populationList);

}

void EvolutionAlg::CrossoverEX(Population * population)
{

}




void EvolutionAlg::Mutation(Population* population)
{

	srand(time(NULL));
	for (size_t i = 0; i < population->GetPopulationList().size(); i++)
	{
		double randomMutationRate = (double)rand() / RAND_MAX;

		if (randomMutationRate < this->mutationRate) {
			Specimen* mutatedSpecimen = population->GetPopulationList()[i];
			int firstMutatedGene = rand() % mutatedSpecimen->GetSpecimenVector().size();
			int secondMutatedGene = rand() % mutatedSpecimen->GetSpecimenVector().size();
			int tmpMutatedGene = mutatedSpecimen->GetSpecimenVector()[firstMutatedGene];
			mutatedSpecimen->SetSpecimenVectorValue(firstMutatedGene, mutatedSpecimen->GetSpecimenVector()[secondMutatedGene]);
			mutatedSpecimen->SetSpecimenVectorValue(secondMutatedGene, tmpMutatedGene);
		}
	}




}

void EvolutionAlg::StartAlgotitm()
{
	while (GetGenerationsCount() < this->maxIterations && this->population->GetBestValueGenerationsCount() < generationsWithNoChangeBestSpecimenValue) {
		IncreaseGenerationCount();
		Evaluate(this->population);
		Selection(this->population);
		Crossover(this->population);
		Mutation(this->population);
		if (population->GetSelectedPopulationList()[0]->GetSpecimentEvaluateValue() == population->GetBestSpecimenEvaluateValue())
		{
			population->SetBestValueGenerationsCount(population->GetBestValueGenerationsCount() + 1);
		}
		else
		{
			population->SetBestSpecimenEvaluateValue(population->GetSelectedPopulationList()[0]->GetSpecimentEvaluateValue());
			population->SetBestValueGenerationsCount(1);
		}

	}
	if (true) {
		int a = 6;
	}

}
