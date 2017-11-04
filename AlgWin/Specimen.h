#pragma once
#include <vector>

class Specimen
{
public:
	Specimen();
	~Specimen();
	void AddCityToEnd(int city);
	std::vector<int> GetSpecimenVector();
	void SetSpecimenVector(std::vector<int> specimenVector);

private:
	std::vector<int> specimenVector;
	int speciemanEvaluateValue;
};

