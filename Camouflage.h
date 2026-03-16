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
    IAccessoire* clone() const override { return new Camouflage(*this); }
};

#endif