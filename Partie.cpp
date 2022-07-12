//---------------------------------------------------------------------------

#pragma hdrstop

#include "Partie.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
Partie::Partie()
{	InitialiserPartie();
}
void Partie::InitialiserPartie()
{	nbDemiCoup=1;
	suiteEchiquier[0].InitialiserEchiquier();
}
void Partie::SauvegarderEchiquier(Echiquier unEchiquier)
{	suiteEchiquier[nbDemiCoup++]=unEchiquier;
}
Echiquier Partie::ExtrairePosition(int demiCoup)
{	return suiteEchiquier[demiCoup];
}
Echiquier Partie::AnnulerDernierCoup()
{   int demiCoup=nbDemiCoup-2;
	nbDemiCoup--;
	if(nbDemiCoup<=0) nbDemiCoup=1;
	if(demiCoup<0) demiCoup=0;
	return suiteEchiquier[demiCoup];
}
string Partie::EditerPartie()
{   string partiePGN="";
	for(int i=2;i<nbDemiCoup;i+=2)
	{   //uniquement les notations des noirs (qui contient celle des blancs)
		partiePGN=partiePGN+suiteEchiquier[i].Notation()+"\n";
	}
	//Ajout dernier coup s'il est blanc
	if((nbDemiCoup-1)%2)
		partiePGN=partiePGN+suiteEchiquier[nbDemiCoup-1].Notation()+"\n";
	return partiePGN;
}