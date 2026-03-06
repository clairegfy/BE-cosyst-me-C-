#include "Aquarium.h"
#include "Milieu.h"
#include "Bestiole.h"
#include "Gregaire.h"
#include "Peureuse.h"
#include "Kamikaze.h"
#include "MultiPersonnalite.h"

int main()
{
    Aquarium ecosysteme( 640, 480, 30 );

    // 5 grégaires
    for ( int i = 0; i < 5; ++i ) {
        Bestiole* b = new Bestiole();
        b->setComportement( new Gregaire() );
        ecosysteme.getMilieu().addMember( b );
    }
    // 5 peureuses
    for ( int i = 0; i < 5; ++i ) {
        Bestiole* b = new Bestiole();
        b->setComportement( new Peureuse() );
        ecosysteme.getMilieu().addMember( b );
    }
    // 5 kamikazes
    for ( int i = 0; i < 5; ++i ) {
        Bestiole* b = new Bestiole();
        b->setComportement( new Kamikaze() );
        ecosysteme.getMilieu().addMember( b );
    }
    // 5 multi-personnalités
    for ( int i = 0; i < 5; ++i ) {
        Bestiole* b = new Bestiole();
        MultiPersonnalite* mp = new MultiPersonnalite();
        mp->ajouterComportement( new Gregaire() );
        mp->ajouterComportement( new Kamikaze() );
        b->setComportement( mp );
        ecosysteme.getMilieu().addMember( b );
    }

    ecosysteme.run();
    return 0;
}
