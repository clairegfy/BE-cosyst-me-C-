#ifndef _KAMIKAZE_H_
#define _KAMIKAZE_H_

#include "Comportement.h"

class Kamikaze : public Comportement
{
public :
    void action( Bestiole* b, std::vector<Bestiole*>& voisins ) override;
    Comportement* clone() const override { return new Kamikaze(*this); }
};

#endif