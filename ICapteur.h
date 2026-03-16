#ifndef _ICAPTEUR_H_
#define _ICAPTEUR_H_

class Bestiole;

class ICapteur
{
public:
    virtual bool detecte(const Bestiole& self, const Bestiole& other) const = 0;
    virtual ICapteur* clone() const = 0;
    virtual ~ICapteur() {}
};

#endif