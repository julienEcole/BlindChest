//---------------------------------------------------------------------------

#ifndef PartieH
#define PartieH
#include "Echiquier.h"
//---------------------------------------------------------------------------
class Partie
{	private:
		Echiquier suiteEchiquier[500];
		int nbDemiCoup;
	public:
		Partie();
		void InitialiserPartie();
		void SauvegarderEchiquier(Echiquier unEchiquier);
		Echiquier ExtrairePosition(int demiCoup);
		Echiquier AnnulerDernierCoup();
		int NbDemiCoup(){return nbDemiCoup;};
		string EditerPartie();
};
#endif
