#ifndef _BESTIOLESFACTORY_H_
#define _BESTIOLESFACTORY_H_

#include "Bestiole.h"
#include "PopulationConfig.h"
#include <vector>

class BestiolesFactory
{
private:
    static BestiolesFactory* instance;

    BestiolesFactory();

public:
    static BestiolesFactory* getInstance();

    Bestiole* createGregaire();
    Bestiole* createPeureuse();
    Bestiole* createKamikaze();
    Bestiole* createMulti();

    std::vector<Bestiole*> creerPopulation( const PopulationConfig& config );
};

#endif