//---------------------------------------------------------------------------

#pragma hdrstop

#include "ReglesEtNotation.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)
bool ReglesEtNotation::DeplacementPossible(int idepart,int jdepart, int iarrivee, int jarrivee, bool cEstUnDeplacement,Echiquier *cetEchiquier)   //cEstUnDeplacement=false pour un test de deplacement
{   DeplacementCavalier monCavalier;
	DeplacementPion monPion;
	DeplacementFou monFou;
	DeplacementTour maTour;
	DeplacementDame maDame;
	DeplacementRoi monRoi;
	if(cEstUnDeplacement)
	{		cEstUnePriseEnPassant=false;
			cEstUnGrandRoque=false;
			cEstUnPetitRoque=false;
	}
	//cout<<cetEchiquier->VisualiserEchiquier();
	char piece=cetEchiquier->LireCaseEchiquier(idepart,jdepart);
	switch (piece)
	{	case 'C':
		case 'c': 	monCavalier.CalculerPositionArrivee(idepart,jdepart,cetEchiquier);
					return monCavalier.ValiderPositionArrivee(iarrivee,jarrivee);
					break;
		case 'F':
		case 'f': 	monFou.CalculerPositionArrivee(idepart,jdepart,cetEchiquier);
					return monFou.ValiderPositionArrivee(iarrivee,jarrivee);
					break;
		case 'T':
		case 't': 	maTour.CalculerPositionArrivee(idepart,jdepart,cetEchiquier);
					if(maTour.ValiderPositionArrivee(iarrivee,jarrivee))
					{   if(cEstUnDeplacement)
						{   if(piece=='t')
							{	if(jdepart==0) 	cetEchiquier->GrandRoqueNoirImpossible();
								if(jdepart==7)	cetEchiquier->PetitRoqueNoirImpossible();
							}
							else
							{	if(jdepart==0)	cetEchiquier->GrandRoqueBlancImpossible();
								if(jdepart==7)	cetEchiquier->PetitRoqueBlancImpossible();
							}
						}
						return true;
					}
					break;
		case 'P':
		case 'p': 	monPion.CalculerPositionArrivee(idepart,jdepart,cetEchiquier);
					if(monPion.ValiderPositionArrivee(iarrivee,jarrivee))
					{
						//test de la prise en passant :
						if(jdepart!=jarrivee && cetEchiquier->LireCaseEchiquier(iarrivee,jarrivee)==' ')
						{   bool autorisation=false;
							if(piece=='P'
							   &&cetEchiquier->LireCaseEchiquier(iarrivee+1,jarrivee)=='p'
							   &&cetEchiquier->LireCaseEchiquierPrecedent(iarrivee-1,jarrivee)=='p'
							   &&cetEchiquier->LireCaseEchiquier(iarrivee-1,jarrivee)==' ')
							{  autorisation=true;
							   if(cEstUnDeplacement) cEstUnePriseEnPassant=autorisation;
							}
							if(piece=='p'
							   &&cetEchiquier->LireCaseEchiquier(iarrivee-1,jarrivee)=='P'
							   &&cetEchiquier->LireCaseEchiquierPrecedent(iarrivee+1,jarrivee)=='P'
							   &&cetEchiquier->LireCaseEchiquier(iarrivee+1,jarrivee)==' ')
							{  autorisation=true;
							   if(cEstUnDeplacement) cEstUnePriseEnPassant=autorisation;
							}
							if(!autorisation) return false;
						}
						return true;
					}
					break;
		case 'D':
		case 'd': 	maDame.CalculerPositionArrivee(idepart,jdepart,cetEchiquier);
					return maDame.ValiderPositionArrivee(iarrivee,jarrivee);
					break;
		case 'R':
		case 'r': 	monRoi.CalculerPositionArrivee(idepart,jdepart,cetEchiquier);
					if(monRoi.ValiderPositionArrivee(iarrivee,jarrivee))
					{   //test du roque :
						bool autorisation=false;
						if(abs(jarrivee-jdepart)>1)
						{   if(jarrivee<jdepart) //grand roque
							{   if(cetEchiquier->GrandRoqueNoirPossible() && idepart==0)
									autorisation=true;
								else
								if(cetEchiquier->GrandRoqueBlancPossible() && idepart==7)
									autorisation=true;
								if(cEstUnDeplacement) cEstUnGrandRoque=autorisation;
							}
							else
							{   if(cetEchiquier->PetitRoqueNoirPossible() && idepart==0)
									autorisation=true;
								else
								if(cetEchiquier->PetitRoqueBlancPossible() && idepart==7)
									autorisation=true;
								if(cEstUnDeplacement) cEstUnPetitRoque=autorisation;
							}
							if(!autorisation) return false;
						}
						if(cEstUnDeplacement)
						{	if(piece=='r')
							{	cetEchiquier->GrandRoqueNoirImpossible();
								cetEchiquier->PetitRoqueNoirImpossible();
							}
							else
							{	cetEchiquier->GrandRoqueBlancImpossible();
								cetEchiquier->PetitRoqueBlancImpossible();
							}
						}
						return true;
					}
					break;
	}
	return false;
}
bool ReglesEtNotation::CaseEnEchec(int ligne,int colonne,bool noirs,Echiquier *cetEchiquier)
{   bool enEchecs=false,cEstUnPion=false;
	char piece=cetEchiquier->LireCaseEchiquier(ligne,colonne);
	cetEchiquier->ModifierCaseEchiquier(' ',ligne,colonne);//on enlève la pièce de la case à tester
	for(int i=0;i<8;i++)
		for(int j=0;j<8;j++)
			if((cetEchiquier->EstUnePieceNoire(i,j)&&noirs==0) || (cetEchiquier->EstUnePieceBlanche(i,j)&&noirs==1))
			{   cEstUnPion=(cetEchiquier->LireCaseEchiquier(i,j)=='p' || cetEchiquier->LireCaseEchiquier(i,j)=='P');
				if(cEstUnPion) //on met un pion adverse pour tester l'attaque
					cetEchiquier->ModifierCaseEchiquier('P'+32*(noirs),ligne,colonne);
				if(DeplacementPossible(i,j, ligne, colonne, false,cetEchiquier))
				{   if(cEstUnPion)
					{    if(j!=colonne) enEchecs=true;
					}
					else
					if(cetEchiquier->LireCaseEchiquier(i,j)=='r' || cetEchiquier->LireCaseEchiquier(i,j)=='R')
					{    if(abs(j-colonne)!=2) enEchecs=true;
					}
					else
					enEchecs=true;
				}
				cetEchiquier->ModifierCaseEchiquier(' ',ligne,colonne);//on enlève à nouveau la pièce
			}
	cetEchiquier->ModifierCaseEchiquier(piece,ligne,colonne);
	return enEchecs;
}
bool ReglesEtNotation::RoiEnEchec(bool noirs,Echiquier *cetEchiquier)
{   int iR,jR;
	for(int i=0;i<8;i++)
		for(int j=0;j<8;j++)
			if(cetEchiquier->LireCaseEchiquier(i,j)==('R'+noirs*32))
			{iR=i;jR=j;}
	return CaseEnEchec(iR,jR,noirs,cetEchiquier);
}
string ReglesEtNotation::EnregistrerNotation(int idep, int jdep, int iarr, int jarr, char piecePromotion,Echiquier *cetEchiquier)
{   stringstream coup("");
	string notation;
	bool noirs=false;
	char piece;
	if(cetEchiquier->DemiCoup()%2)
		coup<<(cetEchiquier->DemiCoup()+1)/2<<" : ";
	else
		coup<<cetEchiquier->Notation()<<' ';
	if(cEstUnPetitRoque)
	{	coup<<"0-0";
		notation=coup.str();
		return notation;
	}
	if(cEstUnGrandRoque)
	{	coup<<"0-0-0";
		notation=coup.str();
		return notation;
	}
	piece=cetEchiquier->LireCaseEchiquierPrecedent(idep,jdep);
	//if(piece>'a') {piece-=32; noirs=true;}
	noirs = piece>'a';
	piece-=noirs*32;
	if(piece!='P') coup<<piece;
	coup<<(char)('a'+jdep)<<(char)('8'-idep);
	if(cetEchiquier->LireCaseEchiquierPrecedent(iarr,jarr)!=' ' || cEstUnePriseEnPassant){
		coup<<'x';
	}
	else{
		coup<<'-';
	}
	coup<<(char)('a'+jarr)<<(char)('8'-iarr);
	if((iarr==0 && cetEchiquier->LireCaseEchiquierPrecedent(idep,jdep)=='P')
	  ||(iarr==7 && cetEchiquier->LireCaseEchiquierPrecedent(idep,jdep)=='p'))
	{   if(piecePromotion>'a') piecePromotion-=32;
		coup<<"="<<piecePromotion;
	}
	if(RoiEnEchec(!noirs,cetEchiquier)) coup<<"+";//échec au roi
	notation=coup.str();
	return notation;
}
