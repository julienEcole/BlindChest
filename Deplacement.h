//---------------------------------------------------------------------------

#ifndef DeplacementH
#define DeplacementH
//---------------------------------------------------------------------------
#include "Echiquier.h"
class Echiquier;
class Deplacement
{       protected:
                int tabPositionArrivee[2][63];
                int nbPositionArrivee;
        public:
				Deplacement(){};
                bool ValiderPositionArrivee(int iarr,int jarr);
};
class DeplacementCavalier : public Deplacement
{       public:
				DeplacementCavalier(){};
				void CalculerPositionArrivee(int idep,int jdep,Echiquier *PE);
};
class DeplacementFou : public Deplacement
{       public:
				DeplacementFou(){};
                void CalculerPositionArrivee(int idep,int jdep,Echiquier *PE);
};
class DeplacementDame : public Deplacement
{       public:
				DeplacementDame(){};
                void CalculerPositionArrivee(int idep,int jdep,Echiquier *PE);
};
class DeplacementRoi : public Deplacement
{       public:
				DeplacementRoi(){};
                void CalculerPositionArrivee(int idep,int jdep,Echiquier *PE);
};
class DeplacementTour : public Deplacement
{       public:
				DeplacementTour(){};
                void CalculerPositionArrivee(int idep,int jdep,Echiquier *PE);
};
class DeplacementPion : public Deplacement
{       public:
                DeplacementPion(){};
                void CalculerPositionArrivee(int idep,int jdep,Echiquier *PE);
};
#endif
