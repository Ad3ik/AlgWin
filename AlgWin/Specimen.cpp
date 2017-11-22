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

void Specimen::SetSpecimenEvaluateValue(double value)
{
	this->speciemanEvaluateValue = value;
}

double Specimen::GetSpecimentEvaluateValue()
{
	return this->speciemanEvaluateValue;
}

void Specimen::SetSpecimenVectorValue(int index, int value)
{
	this->specimenVector[index] = value;
}

int Specimen::GetLastCity()
{
	return this->specimenVector.back();
}
