#pragma once
#include "Population.h"
#include "StringHelper.h"
#include <ctime>       
#include <cstdlib> 
#include <algorithm>
#include <string>
#include <iostream>
#include <fstream>
class PopulationInitializer
{
public:
	PopulationInitializer();
	PopulationInitializer(Population* population);
	~PopulationInitializer();
	void InitializeRandomPopulation();
	void InitializePopulationFromFile(std::string filePath);
private:
	Population* population;
};

