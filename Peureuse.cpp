#include "Peureuse.h"
#include "Bestiole.h"
#include <cmath>

const double Peureuse::VITESSE_FUITE      = 20.;
const double Peureuse::VITESSE_CROISIERE  = 5.;

void Peureuse::action( Bestiole* b, std::vector<Bestiole*>& voisins )
{
    if ( (int)voisins.size() >= SEUIL_PEUR )
    {
        // fuite dans la direction opposée
        b->setOrientation( b->getOrientation() + M_PI );
        b->setVitesse( VITESSE_FUITE );
        _enFuite = true;
    }
    else if ( _enFuite )
    {
        // reprend la vitesse de croisière
        b->setVitesse( VITESSE_CROISIERE );
        _enFuite = false;
    }
}