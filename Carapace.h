#ifndef _CARAPACE_H_
#define _CARAPACE_H_

#include "IAccessoire.h"

class Carapace : public IAccessoire
{
private:
    double protection;
    double ralentissement;

public:
    Carapace(double p, double r);

    double getBonusProtection() const override;
    double modifierVitesse(double vitesseBase) const override;
    double getBonusCamouflage() const override;

    IAccessoire* clone() const override { return new Carapace(*this); }
};

#endif