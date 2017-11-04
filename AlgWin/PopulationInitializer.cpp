#include "stdafx.h"
#include "PopulationInitializer.h"
using namespace std;


PopulationInitializer::PopulationInitializer()
{
}

PopulationInitializer::PopulationInitializer(Population* population)
{
	this->population = population;
}


PopulationInitializer::~PopulationInitializer()
{
}

void PopulationInitializer::InitializeRandomPopulation()
{
}

void PopulationInitializer::InitializePopulationFromFile(std::string filePath)
{
	string line;
	ifstream myfile(filePath);
	if (myfile.is_open())
	{

		getline(myfile, line);
		int cityCount = std::stoi(line);
		vector<int> speciemenVector;
		for (size_t i = 0; i < cityCount; i++)
		{
			speciemenVector.push_back(i);
		}
		for (size_t i = 0; i < population->GetPopulationCount(); i++)
		{
			std::random_shuffle(speciemenVector.begin(), speciemenVector.end());
			Specimen* specimen = new Specimen();
			specimen->SetSpecimenVector(speciemenVector);
			this->population->AddSpecimen(specimen);
		}
		std::vector<std::vector<int>> distanceMatrix;
		
		for (size_t i = 0; i < cityCount; i++)
		{
			std::vector<int> distanceVector;
			getline(myfile, line);
			
			istringstream iss(line);
			vector<string> tokens;
			copy(istream_iterator<string>(iss),
				istream_iterator<string>(),
				back_inserter(tokens));
			for (int i = 0; i < tokens.size(); i++)
			{
				int num = atoi(tokens.at(i).c_str());
				distanceVector.push_back(num);
			}
			distanceMatrix.push_back(distanceVector);
		}
		population->SetDistanceMatrix(distanceMatrix);
		myfile.close();
	}

	else cout << "Unable to open file";
}
