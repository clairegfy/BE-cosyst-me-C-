#ifndef _MILIEU_H_
#define _MILIEU_H_


#include "UImg.h"
#include "Bestiole.h"
#include <iostream>
#include <vector>
#include <cmath>

using namespace std;


class Milieu : public UImg
{

private :
   static const T          white[];

   int                     width, height;
   std::vector<Bestiole*> listeBestioles;
   static const double SEUIL_COLLISION;

public :
   Milieu( int _width, int _height );
   ~Milieu( void );

   int getWidth( void ) const { return width; };
   int getHeight( void ) const { return height; };

   void step( void );

   void addMember( Bestiole* b );
   void removeMember( Bestiole* b );  //Ajouté pour supprimer une bestiole du milieu
   int nbVoisins( Bestiole* b );
   std::vector<Bestiole*>& getBestioles(){ return listeBestioles; }; //Ajouté pour récupérer la liste des bestioles du milieu

};


#endif
