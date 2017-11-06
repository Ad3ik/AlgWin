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
	void SetSpecimenEvaluateValue(double value);
	double GetSpecimentEvaluateValue();
	void SetSpecimenVectorValue(int index, int value);

private:
	std::vector<int> specimenVector;
	double speciemanEvaluateValue;
};

