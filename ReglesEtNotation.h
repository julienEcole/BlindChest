//---------------------------------------------------------------------------

#ifndef ReglesEtNotationH
#define ReglesEtNotationH
//---------------------------------------------------------------------------
#include "Deplacement.h"
#include <string>
#include <sstream>
#include <iostream>
using namespace std;

class ReglesEtNotation
{   private :
		bool cEstUnePriseEnPassant;
		bool cEstUnGrandRoque;
		bool cEstUnPetitRoque;
	public :
		ReglesEtNotation(){};
		string EnregistrerNotation(int idep, int jdep, int iarr, int jarr, char piecePromotion,Echiquier *cetEchiquier);//piecePromotion=' ' en absence de promotion
		bool DeplacementPossible(int idepart,int jdepart, int iarrivee, int jarrivee, bool cEstUnDeplacement,Echiquier *cetEchiquier);
		//cEstUnDeplacement=false pour un test de deplacement : test du roi se mettant en échecs
		bool CaseEnEchec(int ligne,int colonne,bool noirs,Echiquier *cetEchiquier);
		bool RoiEnEchec(bool noirs,Echiquier *cetEchiquier);
};
#endif
