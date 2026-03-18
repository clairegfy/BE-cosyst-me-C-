#include "BestiolesFactory.h"
#include "Gregaire.h"
#include "Peureuse.h"
#include "Kamikaze.h"
#include "MultiPersonnalite.h"
#include "Milieu.h"
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