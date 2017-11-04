#include "stdafx.h"
#include "Specimen.h"


Specimen::Specimen()
{
}


Specimen::~Specimen()
{
}

void Specimen::AddCityToEnd(int city)
{
	this->specimenVector.push_back(city);
}

std::vector<int> Specimen::GetSpecimenVector()
{
	return this->specimenVector;
}

void Specimen::SetSpecimenVector(std::vector<int> specimenVector)
{
	this->specimenVector = specimenVector;
}
