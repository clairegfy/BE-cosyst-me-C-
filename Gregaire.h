#ifndef _GREGAIRE_H_
#define _GREGAIRE_H_

#include "Comportement.h"

class Gregaire : public Comportement
{
public :
    void action( Bestiole* b, std::vector<Bestiole*>& voisins ) override;
    Comportement* clone() const override { return new Gregaire(*this); }
};

#endif