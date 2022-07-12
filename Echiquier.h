//---------------------------------------------------------------------------

#ifndef EchiquierH
#define EchiquierH
//---------------------------------------------------------------------------
#include <string>
#include "Joueur.h"
#include "SNImage.h"
using namespace std;
//---------------------------------------------------------------------------
class Echiquier
{   private :
		char tabEchiquier[8][8];
		Joueur jBlancs,jNoirs;
/*POUR REGLES ET NOTATION*/
		int demiCoup;   //0 au départ, 1 après le premier coup des blancs, 2 après celui des noirs ... (modifier avant notation)
		char tabEchiquierPrecedent[8][8];
		bool grandRoqueNoirPossible,petitRoqueNoirPossible,grandRoqueBlancPossible,petitRoqueBlancPossible;
		void SauvegarderEchiquierPrecedent(char tEchiquier[8][8]); //pour la prise en passant  ET après notation
		string notation;
/*FIN POUR REGLES ET NOTATION*/
	public:
		Echiquier();
		char LireCaseEchiquier(int ligne, int colonne);
		void InitialiserEchiquier();
		string VisualiserEchiquier();
		string Les64Caracteres();
		void ChargerEchiquierComplet(char * les64Caracteres);
		void ModifierCaseEchiquier(char cPiece, int ligne, int colonne);
		bool EstUnePieceNoire(int ligne, int colonne);
		bool EstUnePieceBlanche(int ligne, int colonne);
		bool EstVide(int ligne, int colonne);
		void ChangerLeTrait();
		bool Deplacer(int idep, int jdep, int iarr, int jarr, char piecePromotion);//piecePromotion=' ' en absence de promotion
		string Trait();
/*POUR REGLES ET NOTATION*/
		int DemiCoup(){return demiCoup;};
		void GrandRoqueNoirImpossible(){grandRoqueNoirPossible=false;};
		void PetitRoqueNoirImpossible(){petitRoqueNoirPossible=false;};
		void GrandRoqueBlancImpossible(){grandRoqueBlancPossible=false;};
		void PetitRoqueBlancImpossible(){petitRoqueBlancPossible=false;};
		bool GrandRoqueNoirPossible(){return grandRoqueNoirPossible;};
		bool PetitRoqueNoirPossible(){return petitRoqueNoirPossible;};
		bool GrandRoqueBlancPossible(){return grandRoqueBlancPossible;};
		bool PetitRoqueBlancPossible(){return petitRoqueBlancPossible;};
		string Notation(){return notation;};
		char LireCaseEchiquierPrecedent(int ligne, int colonne){return tabEchiquierPrecedent[ligne][colonne];};
		string VisualiserEchiquierPrecedent();
/*FIN POUR REGLES ET NOTATION*/
/*POUR WEB*/
		void SauvegarderEchiquierBMP(char* fichier);
		//nécessite 100x100 :     cavB.bmp    cavN.bmp    dameB.bmp    dameN.bmp    fouB.bmp    fouN.bmp    pionB.bmp   pionN.bmp    roiB.bmp    roiN.bmp    tourB.bmp    tourN.bmp	vide.bmp
		//Echiquier.bmp en 800x800
/*FIN POUR WEB*/
/*POUR TIMER*/
		Joueur* JBlancs(){return &jBlancs;};
		Joueur* JNoirs(){return &jNoirs;};
/*FIN POUR tIMER*/
};

#endif
