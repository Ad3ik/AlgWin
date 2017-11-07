// AlgWin.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "EvolutionAlg.h"


int main()
{
	EvolutionAlg* evolutionAlg = new EvolutionAlg(.2, .15, 100000, 500, 0);
	evolutionAlg->Initialize("test.txt",20, 10);
	std::getchar();
    return 0;
}

