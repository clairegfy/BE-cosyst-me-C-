#ifndef _BESTIOLESFACTORY_H_
#define _BESTIOLESFACTORY_H_

#include "Bestiole.h"
#include "PopulationConfig.h"
#include "PrototypeRegistry.h"

class Milieu;

class BestiolesFactory
{
private:
    static BestiolesFactory* instance;
    PrototypeRegistry registry;

    BestiolesFactory();

public:
    static BestiolesFactory* getInstance();

    Bestiole* createGregaire();
    Bestiole* createPeureuse();
    Bestiole* createKamikaze();
    Bestiole* createMulti();

    void initialiserPrototypes();
    Bestiole* cloneBestiole( const std::string& nom );

    void peuplerMilieu( Milieu& milieu, const PopulationConfig& config );
};

#endif