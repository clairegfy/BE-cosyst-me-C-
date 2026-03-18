#include "BestiolesFactory.h"
#include "Gregaire.h"
#include "Peureuse.h"
#include "Kamikaze.h"
#include "MultiPersonnalite.h"
#include "Milieu.h"

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
    return b;
}

Bestiole* BestiolesFactory::createPeureuse()
{
    Bestiole* b = new Bestiole();
    b->setComportement( new Peureuse() );
    return b;
}

Bestiole* BestiolesFactory::createKamikaze()
{
    Bestiole* b = new Bestiole();
    b->setComportement( new Kamikaze() );
    return b;
}

Bestiole* BestiolesFactory::createMulti()
{
    Bestiole* b = new Bestiole();
    MultiPersonnalite* mp = new MultiPersonnalite();
    mp->ajouterComportement( new Gregaire() );
    mp->ajouterComportement( new Kamikaze() );
    b->setComportement( mp );
    return b;
}

void BestiolesFactory::initialiserPrototypes()
{
    registry.enregistrerPrototype( "gregaire", createGregaire() );
    registry.enregistrerPrototype( "peureuse", createPeureuse() );
    registry.enregistrerPrototype( "kamikaze", createKamikaze() );
    registry.enregistrerPrototype( "multi", createMulti() );
}

Bestiole* BestiolesFactory::cloneBestiole( const std::string& nom )
{
    return registry.cloner( nom );
}

void BestiolesFactory::peuplerMilieu( Milieu& milieu, const PopulationConfig& config )
{
    for ( int i = 0; i < config.getNbGregaires(); ++i )
        milieu.addMember( createGregaire() );

    for ( int i = 0; i < config.getNbPeureuses(); ++i )
        milieu.addMember( createPeureuse() );

    for ( int i = 0; i < config.getNbKamikazes(); ++i )
        milieu.addMember( createKamikaze() );

    for ( int i = 0; i < config.getNbMulti(); ++i )
        milieu.addMember( createMulti() );
}