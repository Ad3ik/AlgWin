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
	for (auto &Specimen : population->GetSelectedPopulationList())
	{
		std::vector<int> specimenVector = Specimen->GetSpecimenVector();
		double specimenEvaluateValue = 0;
		if (specimenVector.size() > 0) {
			for (size_t i = 0; i < specimenVector.size() - 1; i++)
			{
				specimenEvaluateValue = specimenEvaluateValue + population->GetDistanceMatrix()[specimenVector[i]][specimenVector[i + 1]];

			}
			Specimen->SetSpecimenEvaluateValue(specimenEvaluateValue);
		}
	}

}

void EvolutionAlg::Selection(Population* population)
{
	/*population->SetSelectedPopulationList({});
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
	}*/
	std::vector<Specimen*> populationList = population->GetPopulationList();
	std::vector<Specimen*> selectedPopulationList = population->GetSelectedPopulationList();
	for (size_t i = 0; i < selectedPopulationList.size(); i += 2)
	{
		if (selectedPopulationList[i]->GetSpecimenVector().size() != 0) {
			std::vector<Specimen*> specimenV = {};
			specimenV.push_back(populationList[i]);
			specimenV.push_back(populationList[i + 1]);
			specimenV.push_back(selectedPopulationList[i]);
			specimenV.push_back(selectedPopulationList[i + 1]);
			Specimen* bestSpecimen = NULL;
			double bestEvaluatedValue = INFINITY;
			for (size_t j = 0; j < specimenV.size(); j++)
			{
				if (specimenV[j]->GetSpecimentEvaluateValue() < bestEvaluatedValue)
				{
					bestEvaluatedValue = specimenV[j]->GetSpecimentEvaluateValue();
					bestSpecimen = specimenV[j];

				}

			}
			specimenV.erase(std::remove(specimenV.begin(), specimenV.end(), bestSpecimen), specimenV.end());

			Specimen* bestSpecimen2 = NULL;
			bestEvaluatedValue = INFINITY;
			for (size_t j = 0; j < specimenV.size(); j++)
			{
				if (specimenV[j]->GetSpecimentEvaluateValue() < bestEvaluatedValue)
				{
					bestEvaluatedValue = specimenV[j]->GetSpecimentEvaluateValue();
					bestSpecimen2 = specimenV[j];

				}

			}
			populationList[i] = bestSpecimen;
			populationList[i + 1] = bestSpecimen2;

		}
	}
	population->SetPopulationLList(populationList);

	double bestSpecimenEvaluateValue = INFINITY;
	for (auto &Specimen : populationList)
	{
		if (Specimen->GetSpecimentEvaluateValue() < bestSpecimenEvaluateValue)
		{
			bestSpecimenEvaluateValue = Specimen->GetSpecimentEvaluateValue();
		}
	}
	if (bestSpecimenEvaluateValue < population->bestSpecimenEvaluateOveralValue && bestSpecimenEvaluateValue != 0) {
		population->bestSpecimenEvaluateOveralValue = bestSpecimenEvaluateValue;
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
		double randomCrossOverRate = (double)rand() / RAND_MAX;
		if (randomCrossOverRate < this->crossoverRate) {
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
			//populationList[m] = newSpecimen;


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
			std::vector<Specimen*> vec = population->GetSelectedPopulationList();
			vec[m] = newSpecimen;
			population->SetSelectedPopulationList(vec);

			vec = population->GetSelectedPopulationList();
			vec[m + 1] = newSpecimen2;
			population->SetSelectedPopulationList(vec);
			//populationList[m + 1] = newSpecimen2;
		}
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
			//Specimen* specimenFirst = populationList[m];
			//Specimen* specimenSecond = populationList[m + 1];
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
		//double randomCrossOverRate2 = (double)rand() / RAND_MAX;
		if (randomCrossOverRate < this->crossoverRate) {
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
			std::vector<Specimen*> vec = population->GetSelectedPopulationList();
			vec[m] = newSpecimen;
			population->SetSelectedPopulationList(vec);
			//populationList[m] = newSpecimen;
		}
		if (randomCrossOverRate < this->crossoverRate) {
			std::vector<Specimen*> vec = population->GetSelectedPopulationList();
			vec[m + 1] = newSpecimen2;
			population->SetSelectedPopulationList(vec);
			//populationList[m + 1] = newSpecimen2;
		}
	}
	population->SetPopulationLList(populationList);

}

void EvolutionAlg::CrossoverEX(Population * population)
{
	std::vector<Specimen*> populationList = population->GetPopulationList();
	srand(time(NULL));
	std::random_shuffle(populationList.begin(), populationList.end());
	for (size_t m = 0; m < populationList.size(); m += 2) {
		double randomCrossOverRate = (double)rand() / RAND_MAX;
		Specimen* specimenFirst = populationList[m];
		Specimen* specimenSecond = populationList[m + 1];
		Specimen* newSpecimen = new Specimen();
		Specimen* newSpecimen2 = new Specimen();
		if (randomCrossOverRate < this->crossoverRate) {
			std::vector<int> firstSpecimentVector = specimenFirst->GetSpecimenVector();
			std::vector<int> secondSpecimentVector = specimenSecond->GetSpecimenVector();
			std::vector<std::vector<int>> edgeTable = {};
			for (size_t i = 0; i < firstSpecimentVector.size(); i++)
			{
				std::vector<int> edgeHelpVector = {};
				for (size_t j = 0; j < firstSpecimentVector.size(); j++)
				{
					if (i == firstSpecimentVector[j])
					{
						edgeHelpVector.push_back(firstSpecimentVector[(j - 1) % firstSpecimentVector.size()]);
						edgeHelpVector.push_back(firstSpecimentVector[(j + 1) % firstSpecimentVector.size()]);
					}
					if (i == secondSpecimentVector[j])
					{
						edgeHelpVector.push_back(secondSpecimentVector[(j - 1) % secondSpecimentVector.size()]);
						edgeHelpVector.push_back(secondSpecimentVector[(j + 1) % secondSpecimentVector.size()]);
					}
				}
				edgeTable.push_back(edgeHelpVector);
			}
			int randomVertex = rand() % (firstSpecimentVector.size());
			newSpecimen->AddCityToEnd(randomVertex);
			for (size_t i = 0; i < edgeTable.size(); i++)
			{
				edgeTable[i].erase(std::remove(edgeTable[i].begin(), edgeTable[i].end(), newSpecimen->GetLastCity()), edgeTable[i].end());
			}

			while (newSpecimen->GetSpecimenVector().size()<firstSpecimentVector.size())
			{


				int nextCityHelper = -1;
				int nextCityRepeatCounter = 0;
				for (size_t i = 0; i < edgeTable[newSpecimen->GetLastCity()].size(); i++) // ten for znajduje kolejne miasto 
				{
					if (count(edgeTable[newSpecimen->GetLastCity()].begin(), edgeTable[newSpecimen->GetLastCity()].end(), edgeTable[newSpecimen->GetLastCity()][i]) > 1) {
						//znalaz³o dwa takie same wyst¹pienia krawêdzi
						nextCityHelper = edgeTable[newSpecimen->GetLastCity()][i];
						nextCityRepeatCounter = 2;
					}
					else
					{//nie by³o 2 wiec szukamy 1
						int minSizeHelper = 5;
						int minSizeIndexHelper = -1;
						for (size_t j = 0; j < edgeTable[newSpecimen->GetLastCity()].size(); j++)
						{
							if (edgeTable[j].size() < minSizeHelper)
							{
								minSizeHelper = edgeTable[j].size();
								minSizeIndexHelper = j;
							}

						}
						if (minSizeIndexHelper >= 0)//wybieramy najkrótsza liste z 1 do wyboru
						{
							nextCityHelper = edgeTable[newSpecimen->GetLastCity()][minSizeIndexHelper];
							nextCityRepeatCounter = 1;
						}

						if (nextCityHelper < 0) {//jeœli nie znalaz³o 2 ani 1 bo nie ma ¿adnych do wyboru w liœcie s¹siadów obecnego wierzcho³ka
							//w tej sytuacji musimy jakis losowy nie u¿yty wierzcho³ek znaleŸæ
							std::vector<int> ramainingCities = {};
							for (size_t k = 0; k < firstSpecimentVector.size(); k++)
							{
								if (std::find(newSpecimen->GetSpecimenVector().begin(), newSpecimen->GetSpecimenVector().end(), k) != newSpecimen->GetSpecimenVector().end()) {

								}
								else
								{
									ramainingCities.push_back(k);
								}
							}
							int randomCities = rand() % ramainingCities.size();
							nextCityHelper = ramainingCities[randomCities];
						}
					}
				}
				if (edgeTable[newSpecimen->GetLastCity()].size() == 0) {
					std::vector<int> ramainingCities = {};
					for (size_t k = 0; k < firstSpecimentVector.size(); k++)
					{//sprawdzic czy k jest w newSpeciman, jesli nie ma to dodac k do ramainingCities
						bool itemFound = false;
						for (size_t x = 0; x < newSpecimen->GetSpecimenVector().size(); x++)
						{
							if (k == newSpecimen->GetSpecimenVector()[x]) {
								itemFound = true;
							}
						}
						if (!itemFound) {
							ramainingCities.push_back(k);
						}
					}
					int randomCities = rand() % ramainingCities.size();
					nextCityHelper = ramainingCities[randomCities];
				}
				newSpecimen->AddCityToEnd(nextCityHelper);
				for (size_t i = 0; i < edgeTable.size(); i++)
				{
					edgeTable[i].erase(std::remove(edgeTable[i].begin(), edgeTable[i].end(), newSpecimen->GetLastCity()), edgeTable[i].end());
				}

			}


			randomVertex = rand() % (firstSpecimentVector.size());
			newSpecimen2->AddCityToEnd(randomVertex);
			for (size_t i = 0; i < edgeTable.size(); i++)
			{
				edgeTable[i].erase(std::remove(edgeTable[i].begin(), edgeTable[i].end(), newSpecimen2->GetLastCity()), edgeTable[i].end());
			}

			while (newSpecimen2->GetSpecimenVector().size()<firstSpecimentVector.size())
			{


				int nextCityHelper = -1;
				int nextCityRepeatCounter = 0;
				for (size_t i = 0; i < edgeTable[newSpecimen2->GetLastCity()].size(); i++) // ten for znajduje kolejne miasto 
				{
					if (count(edgeTable[newSpecimen2->GetLastCity()].begin(), edgeTable[newSpecimen2->GetLastCity()].end(), edgeTable[newSpecimen2->GetLastCity()][i]) > 1) {
						//znalaz³o dwa takie same wyst¹pienia krawêdzi
						nextCityHelper = edgeTable[newSpecimen2->GetLastCity()][i];
						nextCityRepeatCounter = 2;
					}
					else
					{//nie by³o 2 wiec szukamy 1
						int minSizeHelper = 5;
						int minSizeIndexHelper = -1;
						for (size_t j = 0; j < edgeTable[newSpecimen2->GetLastCity()].size(); j++)
						{
							if (edgeTable[j].size() < minSizeHelper)
							{
								minSizeHelper = edgeTable[j].size();
								minSizeIndexHelper = j;
							}

						}
						if (minSizeIndexHelper >= 0)//wybieramy najkrótsza liste z 1 do wyboru
						{
							nextCityHelper = edgeTable[newSpecimen2->GetLastCity()][minSizeIndexHelper];
							nextCityRepeatCounter = 1;
						}

						if (nextCityHelper < 0) {//jeœli nie znalaz³o 2 ani 1 bo nie ma ¿adnych do wyboru w liœcie s¹siadów obecnego wierzcho³ka
												 //w tej sytuacji musimy jakis losowy nie u¿yty wierzcho³ek znaleŸæ
							std::vector<int> ramainingCities = {};
							for (size_t k = 0; k < firstSpecimentVector.size(); k++)
							{
								if (std::find(newSpecimen2->GetSpecimenVector().begin(), newSpecimen2->GetSpecimenVector().end(), k) != newSpecimen2->GetSpecimenVector().end()) {

								}
								else
								{
									ramainingCities.push_back(k);
								}
							}
							int randomCities = rand() % ramainingCities.size();
							nextCityHelper = ramainingCities[randomCities];
						}
					}
				}
				if (edgeTable[newSpecimen2->GetLastCity()].size() == 0) {
					std::vector<int> ramainingCities = {};
					for (size_t k = 0; k < firstSpecimentVector.size(); k++)
					{//sprawdzic czy k jest w newSpeciman, jesli nie ma to dodac k do ramainingCities
						bool itemFound = false;
						for (size_t x = 0; x < newSpecimen2->GetSpecimenVector().size(); x++)
						{
							if (k == newSpecimen2->GetSpecimenVector()[x]) {
								itemFound = true;
							}
						}
						if (!itemFound) {
							ramainingCities.push_back(k);
						}
					}
					int randomCities = rand() % ramainingCities.size();
					nextCityHelper = ramainingCities[randomCities];
				}
				newSpecimen2->AddCityToEnd(nextCityHelper);
				for (size_t i = 0; i < edgeTable.size(); i++)
				{
					edgeTable[i].erase(std::remove(edgeTable[i].begin(), edgeTable[i].end(), newSpecimen2->GetLastCity()), edgeTable[i].end());
				}

			}

			std::vector<Specimen*> vec = population->GetSelectedPopulationList();
			vec[m] = newSpecimen;
			population->SetSelectedPopulationList(vec);

			vec = population->GetSelectedPopulationList();
			vec[m + 1] = newSpecimen2;
			population->SetSelectedPopulationList(vec);
			
		}
	}
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
			/*if (population->GetSelectedPopulationList()[0]->GetSpecimentEvaluateValue()<population->bestSpecimenEvaluateOveralValue &&
				population->GetSelectedPopulationList()[0]->GetSpecimentEvaluateValue() != 0) {
				population->bestSpecimenEvaluateOveralValue = population->GetSelectedPopulationList()[0]->GetSpecimentEvaluateValue();
			}*/
			population->SetBestSpecimenEvaluateValue(population->GetSelectedPopulationList()[0]->GetSpecimentEvaluateValue());
			population->SetBestValueGenerationsCount(1);
		}

	}
	if (true) {
		int a = 6;
	}

}
