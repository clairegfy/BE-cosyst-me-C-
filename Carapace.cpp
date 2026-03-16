#include "Carapace.h"

Carapace::Carapace(double p, double r)
{
    protection = p;
    ralentissement = r;
}

double Carapace::getBonusProtection() const
{
    return protection;
}

double Carapace::modifierVitesse(double vitesseBase) const
{
    return vitesseBase * ralentissement;
}