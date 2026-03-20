#include "Nageoires.h"

Nageoires::Nageoires(double f)
{
    facteur = f;
}

double Nageoires::modifierVitesse(double vitesseBase) const
{
    return vitesseBase * facteur;
}

double Nageoires::getBonusCamouflage() const
{
    return 0.0;
}

double Nageoires::getBonusProtection() const
{
    return 0.0;
}
