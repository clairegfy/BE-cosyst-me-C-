#include "Camouflage.h"

Camouflage::Camouflage(double p)
{
    psi = p;
}

double Camouflage::getBonusCamouflage() const
{
    return psi;
}