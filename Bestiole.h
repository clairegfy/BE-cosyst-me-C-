#ifndef _BESTIOLES_H_
#define _BESTIOLES_H_


#include "UImg.h"
#include "Comportement.h"
#include <iostream>
#include <vector>
using namespace std;


class Milieu;

class Bestiole
{

private :
   static const double     AFF_SIZE;
   static const double     MAX_VITESSE;
   static const double     LIMITE_VUE;
   static const int AGE_MAX;

   static int              next;

private :
   int               identite;
   int               x, y;
   double            cumulX, cumulY;
   double            orientation;
   double            vitesse;
   int age;
   int ageMax;

   T               * couleur;
   Comportement * _comportement;

private :
   void bouge( int xLim, int yLim );

public :                                           // Forme canonique :
   Bestiole( void );                               // Constructeur par defaut
   Bestiole( const Bestiole & b );                 // Constructeur de copies
   virtual ~Bestiole( void );                              // Destructeur
                                                   // Operateur d'affectation binaire par defaut
   void action( Milieu & monMilieu );
   void draw( UImg & support );

   bool jeTeVois( const Bestiole & b ) const;

   void initCoords( int xLim, int yLim );

   int   getX() const { return x; }
   int   getY() const { return y; }
   double getOrientation() const { return orientation; }
   double getVitesse() const { return vitesse; }
   void  setOrientation( double o ) { orientation = o; }
   void  setVitesse( double v ) { vitesse = v; }
   void  setComportement( Comportement* c );
   bool estMort() const { return age >= ageMax; }

   friend bool operator==( const Bestiole & b1, const Bestiole & b2 );

};


#endif
