// AlgWin.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "EvolutionAlg.h"


int main()
{
	EvolutionAlg* evolutionAlg = new EvolutionAlg(.2, .1, 10, 10);
	evolutionAlg->Initialize("test.txt",20);
	std::getchar();
    return 0;
}

