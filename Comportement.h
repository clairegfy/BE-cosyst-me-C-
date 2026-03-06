#ifndef _COMPORTEMENT_H_
#define _COMPORTEMENT_H_

#include <stdlib.h>
#include <vector>

class Bestiole;

class Comportement {
public:
    virtual void action( Bestiole* b, std::vector<Bestiole*>& voisins ) = 0;
    virtual Comportement* clone() const = 0;
    virtual ~Comportement() {}
};

#endif