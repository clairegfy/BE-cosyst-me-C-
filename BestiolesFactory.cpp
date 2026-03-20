#include "BestiolesFactory.h"
#include "Gregaire.h"
#include "Peureuse.h"
#include "Kamikaze.h"
#include "MultiPersonnalite.h"
#include "Yeux.h"
#include "Oreilles.h"
#include "Nageoires.h"
#include "Carapace.h"
#include "Camouflage.h"

// La factory crée des bestioles complètement configurées
// (comportement + capteurs + accessoires)
// -> intégration des patterns Factory + Decorator

BestiolesFactory* BestiolesFactory::instance = nullptr;

BestiolesFactory::BestiolesFactory()
{
}

BestiolesFactory* BestiolesFactory::getInstance()
{
    if ( instance == nullptr )
        instance = new BestiolesFactory();

    return instance;
}

Bestiole* BestiolesFactory::createGregaire()
{
    Bestiole* b = new Bestiole();
    b->setComportement( new Gregaire() );

    b->ajouterCapteur( new Yeux( 1.5, 60.0, 1.0 ) );
    b->ajouterAccessoire( new Nageoires( 1.3 ) );

    return b;
}

Bestiole* BestiolesFactory::createPeureuse()
{
    Bestiole* b = new Bestiole();
    b->setComportement( new Peureuse() );

    b->ajouterCapteur( new Oreilles( 50.0, 1.0 ) );
    b->ajouterAccessoire( new Camouflage( 0.5 ) );

    return b;
}

Bestiole* BestiolesFactory::createKamikaze()
{
    Bestiole* b = new Bestiole();
    b->setComportement( new Kamikaze() );

    b->ajouterCapteur( new Yeux( 1.2, 70.0, 1.0 ) );
    b->ajouterAccessoire( new Carapace( 0.3, 0.8 ) );

    return b;
}

Bestiole* BestiolesFactory::createMulti()
{
    Bestiole* b = new Bestiole();

    MultiPersonnalite* mp = new MultiPersonnalite();
    mp->ajouterComportement( new Gregaire() );
    mp->ajouterComportement( new Kamikaze() );

    b->setComportement( mp );

    b->ajouterCapteur( new Yeux( 1.5, 60.0, 1.0 ) );
    b->ajouterCapteur( new Oreilles( 40.0, 1.0 ) );

    return b;
}

std::vector<Bestiole*> BestiolesFactory::creerPopulation( const PopulationConfig& config )
{
    std::vector<Bestiole*> population;

    for ( int i = 0; i < config.getNbGregaires(); ++i )
        population.push_back( createGregaire() );

    for ( int i = 0; i < config.getNbPeureuses(); ++i )
        population.push_back( createPeureuse() );

    for ( int i = 0; i < config.getNbKamikazes(); ++i )
        population.push_back( createKamikaze() );

    for ( int i = 0; i < config.getNbMulti(); ++i )
        population.push_back( createMulti() );

    return population;
}