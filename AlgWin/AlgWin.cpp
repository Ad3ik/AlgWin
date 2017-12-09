// AlgWin.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "EvolutionAlg.h"


int main()
{
	EvolutionAlg* evolutionAlg = new EvolutionAlg(.9, .1, 5, 500, 15, 2);
	evolutionAlg->Initialize("test.txt", 100, 100);
	std::getchar();
	return 0;
}

