//---------------------------------------------------------------------------

#pragma hdrstop

#include "Echiquier.h"
#include "ReglesEtNotation.h"
#include <sstream>
//---------------------------------------------------------------------------
#pragma package(smart_init)

Echiquier::Echiquier()
{   InitialiserEchiquier();
}
void Echiquier::InitialiserEchiquier()
{   tabEchiquier[0][0] = 't';
	tabEchiquier[0][1] = 'c';
	tabEchiquier[0][2] = 'f';
	tabEchiquier[0][3] = 'd';
	tabEchiquier[0][4] = 'r';
	tabEchiquier[0][5] = 'f';
	tabEchiquier[0][6] = 'c';
	tabEchiquier[0][7] = 't';
	tabEchiquier[7][0] = 'T';
	tabEchiquier[7][1] = 'C';
	tabEchiquier[7][2] = 'F';
	tabEchiquier[7][3] = 'D';
	tabEchiquier[7][4] = 'R';
	tabEchiquier[7][5] = 'F';
	tabEchiquier[7][6] = 'C';
	tabEchiquier[7][7] = 'T';
	for(int j=0; j<8 ; j++)
	{   tabEchiquier[1][j] = 'p';
		tabEchiquier[6][j] = 'P';
	}
	for(int i=2; i<=5 ; i++)
	{   for(int j=0; j<8 ; j++)
		{	tabEchiquier[i][j] = ' ';
		}
	}
	jBlancs.DonnerLeTrait();
	jNoirs.RetirerLeTrait();
/*FIN POUR REGLES ET NOTATION*/
	demiCoup=0;
	grandRoqueNoirPossible=true;
	petitRoqueNoirPossible=true;
	grandRoqueBlancPossible=true;
	petitRoqueBlancPossible=true;
	SauvegarderEchiquierPrecedent(tabEchiquier);
	notation="1:";
/*FIN POUR REGLES ET NOTATION*/
/*POUR TIMER*/
	jBlancs.Initialiser(5,0);
	jNoirs.Initialiser(5,0);
/*FIN POUR TIMER*/
}
string Echiquier::VisualiserEchiquier()
{	string str = "      ";
	for(int i= 0; i<8 ; i++)
	{	for(int j=0 ; j<8 ; j++)
		{   str = str + tabEchiquier[i][j];
		}
		str = str + "\n      ";
	}
	return str;
}

void Echiquier::ModifierCaseEchiquier(char cPiece, int ligne, int colonne)
{	tabEchiquier[ligne][colonne] = cPiece;
}

char Echiquier::LireCaseEchiquier(int ligne, int colonne)
{   return tabEchiquier[ligne][colonne];
}

bool Echiquier::EstVide(int ligne, int colonne)
{   if(tabEchiquier[ligne][colonne] ==  ' ')
	{   return true;
	}
	return false;
}

bool Echiquier::EstUnePieceNoire(int ligne, int colonne)
{   if((tabEchiquier[ligne][colonne] >= 'a') && (tabEchiquier[ligne][colonne] <= 'z'))
	{       return true;
	}
	return false;
}

bool Echiquier::EstUnePieceBlanche(int ligne, int colonne)
{   if( (tabEchiquier[ligne][colonne] >= 'A') && (tabEchiquier[ligne][colonne] <= 'Z') )
	{       return true;
	}
	return false;
}
void Echiquier::ChangerLeTrait()
{	if(jBlancs.Trait())
	{	jBlancs.RetirerLeTrait();jNoirs.DonnerLeTrait();
	}
	else
	if(jNoirs.Trait())
	{	jNoirs.RetirerLeTrait();jBlancs.DonnerLeTrait();
	}
	/*POUR REGLES ET NOTATION*/
	demiCoup++; //avant notation
	/*FIN POUR REGLES ET NOTATION*/
}
string Echiquier::Trait()
{	if(jBlancs.Trait()) return "Blancs";
	else return "Noirs";
}
bool Echiquier::Deplacer(int idep, int jdep, int iarr, int jarr, char piecePromotion)//piecePromotion=' ' en absence de promotion
{   if(idep>=0 && idep<8 && jdep>=0 && jdep<8 && iarr>=0 && iarr<8 && jarr>=0 && jarr<8)
		if(  (jBlancs.Trait() && EstUnePieceBlanche(idep,jdep) && !EstUnePieceBlanche(iarr,jarr))
		   ||(jNoirs.Trait() && EstUnePieceNoire(idep,jdep) && !EstUnePieceNoire(iarr,jarr)))
		{   /*POUR REGLES ET NOTATION*/
			ReglesEtNotation regles;
			bool roqueEnEchecs=false;
			char tabEchiquierTmp[8][8];
			//sauvegarde de la position en vue d'un retour si le roi se met en echecs
			bool grandRoqueNoirPossibleTmp,petitRoqueNoirPossibleTmp,grandRoqueBlancPossibleTmp,petitRoqueBlancPossibleTmp;
			for(int i=0;i<8;i++) for(int j=0;j<8;j++) tabEchiquierTmp[i][j]=tabEchiquier[i][j];
			grandRoqueNoirPossibleTmp=grandRoqueNoirPossible;
			petitRoqueNoirPossibleTmp=petitRoqueNoirPossible;
			grandRoqueBlancPossibleTmp=grandRoqueBlancPossible;
			petitRoqueBlancPossibleTmp=petitRoqueBlancPossible;
			/*FIN POUR REGLES ET NOTATION*/
			/*POUR REGLES ET NOTATION*/
			if(regles.DeplacementPossible(idep,jdep,iarr,jarr,true,this))
			/*FIN POUR REGLES ET NOTATION*/
			{	char piece=LireCaseEchiquier(idep,jdep);
				//promotion
				if((piece=='P' && iarr==0)||(piece=='p' && iarr==7))
				{   if(piecePromotion>'a') piecePromotion-=32;
					if(jNoirs.Trait()) piecePromotion+=32;
					ModifierCaseEchiquier(piecePromotion,iarr,jarr);
				}
				else
				{   //prise en passant
					if((piece=='P'||piece=='p') && jarr!=jdep && EstVide(iarr,jarr))
						ModifierCaseEchiquier(' ',iarr-(piece=='p')+(piece=='P'),jarr);
					//déplacement normal
					ModifierCaseEchiquier(piece,iarr,jarr);
				}
				//déplacement normal
				ModifierCaseEchiquier(' ',idep,jdep);
				//roque
				if((piece=='R'||piece=='r') && abs(jarr-jdep)==2)
					if(jarr==6)
					{	ModifierCaseEchiquier('T'+piece-'R',iarr,jarr-1);
						ModifierCaseEchiquier(' ',iarr,jarr+1);
						/*POUR REGLES ET NOTATION*/
						//test du cases du roque en échecs
						if(regles.CaseEnEchec(iarr,jarr-1,piece=='r',this)
						 ||regles.CaseEnEchec(iarr,jarr-2,piece=='r',this))
							roqueEnEchecs=true;
						/*FIN POUR REGLES ET NOTATION*/
					}
					else
					{	ModifierCaseEchiquier('T'+piece-'R',iarr,jarr+1);
						ModifierCaseEchiquier(' ',iarr,jarr-2);
						/*POUR REGLES ET NOTATION*/
						//test du cases du roque en échecs
						if(regles.CaseEnEchec(iarr,jarr+1,piece=='r',this)
						 ||regles.CaseEnEchec(iarr,jarr+2,piece=='r',this))
							roqueEnEchecs=true;
						/*FIN POUR REGLES ET NOTATION*/
					}
				/*POUR REGLES ET NOTATION*/
				//roi en echecs
				if(regles.RoiEnEchec(piece>='a',this) || roqueEnEchecs)
				{   //annulation du déplacement car le roi se met en echecs
					for(int i=0;i<8;i++) for(int j=0;j<8;j++) tabEchiquier[i][j]=tabEchiquierTmp[i][j];
					grandRoqueNoirPossible=grandRoqueNoirPossibleTmp;
					petitRoqueNoirPossible=petitRoqueNoirPossibleTmp;
					grandRoqueBlancPossible=grandRoqueBlancPossibleTmp;
					petitRoqueBlancPossible=petitRoqueBlancPossibleTmp;
					return false;
				}
				/*FIN POUR REGLES ET NOTATION*/
				//coup validé
				ChangerLeTrait();
				/*POUR REGLES ET NOTATION*/
				notation=regles.EnregistrerNotation(idep, jdep, iarr, jarr, piecePromotion,this);
				SauvegarderEchiquierPrecedent(tabEchiquierTmp); //après notation
				/*FIN POUR REGLES ET NOTATION*/
				return true;
			}
		}
	return false;
}
string Echiquier::Les64Caracteres()
{   string str = "";
	for(int i= 0; i<8 ; i++)
	{	for(int j=0 ; j<8 ; j++)
		{   str = str + tabEchiquier[i][j];
		}
	}
	/*POUR REGLES ET NOTATION*/
	str=str+notation;
	/*FIN POUR REGLES ET NOTATION*/
	return str;
}
void Echiquier::ChargerEchiquierComplet(char * les64Caracteres)
{   int k=0;
	char tabEchiquierTmp[8][8];
	for(int i=0;i<8;i++) for(int j=0;j<8;j++) tabEchiquierTmp[i][j]=tabEchiquier[i][j];
	for(int i=0; i<8 ; i++)
		for(int j=0 ; j<8 ; j++)
			tabEchiquier[i][j]=les64Caracteres[k++];
	/*POUR REGLES ET NOTATION*/
	notation=les64Caracteres+64;
	/*FIN POUR REGLES ET NOTATION*/
	SauvegarderEchiquierPrecedent(tabEchiquierTmp); //après notation
}
/*POUR REGLES ET NOTATION*/
void Echiquier::SauvegarderEchiquierPrecedent(char tEchiquier[8][8])
{   for(int i=0;i<8;i++)
		for(int j=0;j<8;j++)
			tabEchiquierPrecedent[i][j]=tEchiquier[i][j];
}
string Echiquier::VisualiserEchiquierPrecedent()
{	string str = "      ";
	for(int i= 0; i<8 ; i++)
	{	for(int j=0 ; j<8 ; j++)
		{   str = str + tabEchiquierPrecedent[i][j];
		}
		str = str + "\n      ";
	}
	return str;
}
/*FIN POUR REGLES ET NOTATION*/
/*POUR WEB*/
void Echiquier::SauvegarderEchiquierBMP(char* fichier)
	//nécessite 100x100 :     cavB.bmp    cavN.bmp    dameB.bmp    dameN.bmp    fouB.bmp    fouN.bmp    pionB.bmp   pionN.bmp    roiB.bmp    roiN.bmp    tourB.bmp    tourN.bmp	vide.bmp
	//Echiquier.bmp en 800x800
{   SNImage cavB,cavN,fouB,fouN,pionB,pionN,roiB,roiN,dameB,dameN,tourB,tourN;
	SNImage position;
	cavB.Charger("Images\\cavB.bmp");
	int largeurPiece=cavB.Largeur();
	cavN.Charger("Images\\cavN.bmp");
	fouB.Charger("Images\\fouB.bmp");
	fouN.Charger("Images\\fouN.bmp");
	pionB.Charger("Images\\pionB.bmp");
	pionN.Charger("Images\\pionN.bmp");
	roiB.Charger("Images\\roiB.bmp");
	roiN.Charger("Images\\roiN.bmp");
	dameB.Charger("Images\\dameB.bmp");
	dameN.Charger("Images\\dameN.bmp");
	tourB.Charger("Images\\tourB.bmp");
	tourN.Charger("Images\\tourN.bmp");
	Pixel blanc={255,255,255},gris={200,200,200};
	position.Charger("Images\\Echiquier.bmp");
	for(int ligne=0;ligne<8;ligne++)
		for(int colonne=0;colonne<8;colonne++)
			for(int i=0;i<largeurPiece;i++)
				for(int j=0;j<largeurPiece;j++)
				{   Pixel couleur=cavB.image[0][0];//couleur de transparence : 1er pixel en haut à gauche
					if(tabEchiquier[ligne][colonne]=='C')
						couleur=cavB.image[i][j];
					if(tabEchiquier[ligne][colonne]=='c')
						couleur=cavN.image[i][j];
					if(tabEchiquier[ligne][colonne]=='F')
						couleur=fouB.image[i][j];
					if(tabEchiquier[ligne][colonne]=='f')
						couleur=fouN.image[i][j];
					if(tabEchiquier[ligne][colonne]=='P')
						couleur=pionB.image[i][j];
					if(tabEchiquier[ligne][colonne]=='p')
						couleur=pionN.image[i][j];
					if(tabEchiquier[ligne][colonne]=='R')
						couleur=roiB.image[i][j];
					if(tabEchiquier[ligne][colonne]=='r')
						couleur=roiN.image[i][j];
					if(tabEchiquier[ligne][colonne]=='D')
						couleur=dameB.image[i][j];
					if(tabEchiquier[ligne][colonne]=='d')
						couleur=dameN.image[i][j];
					if(tabEchiquier[ligne][colonne]=='T')
						couleur=tourB.image[i][j];
					if(tabEchiquier[ligne][colonne]=='t')
						couleur=tourN.image[i][j];
					if(couleur.rouge==cavB.image[0][0].rouge && couleur.vert==cavB.image[0][0].vert && couleur.bleu==cavB.image[0][0].bleu)
					{	if((ligne+colonne)%2)
							position.image[ligne*largeurPiece+i][colonne*largeurPiece+j]=gris;
						else
							position.image[ligne*largeurPiece+i][colonne*largeurPiece+j]=blanc;
					}
					else position.image[ligne*largeurPiece+i][colonne*largeurPiece+j]=couleur;
				}
	position.Sauvegarder(fichier);
}
/*FIN POUR WEB*/

