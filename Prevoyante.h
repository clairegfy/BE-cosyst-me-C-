#ifndef _PREVOYANTE_H_
#define _PREVOYANTE_H_

#include "Comportement.h"

class Prevoyante : public Comportement
{
private :
    static const int HORIZON = 10;  // nb de pas anticipés
public :
    void action( Bestiole* b, std::vector<Bestiole*>& voisins ) override;
    Comportement* clone() const override { return new Prevoyante(*this); }
};

#endif