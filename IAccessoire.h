#ifndef _IACCESSOIRE_H_
#define _IACCESSOIRE_H_

class IAccessoire
{
public:
    virtual double modifierVitesse(double vitesseBase) const { return vitesseBase; }
    virtual double getBonusCamouflage() const { return 0.0; }
    virtual double getBonusProtection() const { return 0.0; }
    virtual IAccessoire* clone() const = 0;
    virtual ~IAccessoire() {}
};

#endif