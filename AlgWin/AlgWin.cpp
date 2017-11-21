// AlgWin.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "EvolutionAlg.h"


int main()
{
	EvolutionAlg* evolutionAlg = new EvolutionAlg(.5, .15, 100, 10, 1);
	evolutionAlg->Initialize("test.txt",200, 10);
	std::getchar();
    return 0;
}

