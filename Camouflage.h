#ifndef _CAMOUFLAGE_H_
#define _CAMOUFLAGE_H_

#include "IAccessoire.h"

class Camouflage : public IAccessoire
{
private:
    double psi;

public:
    Camouflage(double p);

    double getBonusCamouflage() const override;
    double modifierVitesse(double vitesseBase) const override;
    double getBonusProtection() const override;
    IAccessoire* clone() const override { return new Camouflage(*this); }
};

#endif