#ifndef _IACCESSOIRE_H_
#define _IACCESSOIRE_H_

class IAccessoire
{
public:
    virtual double modifierVitesse(double vitesseBase) const=0;
    virtual double getBonusCamouflage() const=0;
    virtual double getBonusProtection() const=0;
    virtual IAccessoire* clone() const=0;
    virtual ~IAccessoire() = default;
};

#endif