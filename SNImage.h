#ifndef SNIMAGEH
#define SNIMAGEH
#include <windows.h>
#include <stdio.h>
#include <math.h>
#include <iostream>
#include <fstream>
#include <string>
#define TOUR 100
#define SEUILROND 100
#define ZONE 10
#define PROPORTIONCENTRE 1.30
#define AJUSTECENTRE 0
#define SEUILIMPACT 60
#define ZONEIMPACT 10
#define ZONEIMPACTCOLOREE 6
#define AJUSTETROU 2
#define PORPORTIONPOINTSDIAMETRE 19.5

using namespace std;

typedef struct {unsigned char bleu;unsigned char vert;unsigned char rouge;} Pixel;
typedef struct {int ligne; int colonne;} Coordonnee;

class SNImage
{   private:
		unsigned long dimensionMax;
		unsigned long tailleFichier,debutImage;
		unsigned long tailleImage,tailleEntete,zero,format,resoLarg,resoHaut;
		void TracerCercleUnPixel(Coordonnee centre, int rayon, Pixel couleur);
		void TracerDiagonaleUnPixel(Coordonnee debut,Coordonnee fin, Pixel couleur);
		void ChangerCouleurSegment(Coordonnee coord,int taille,int epaisseur,Pixel couleur,char segment);//segment='a' 'b' 'c' 'd' 'e' 'f'
	//protected:
	public:	//seulement pour Echiquier
		Pixel **image;
		unsigned short signature;
		unsigned long largeur,hauteur;
	public:
		SNImage();
		~SNImage();
		inline unsigned short Signature(){return signature;}
		inline unsigned long Largeur(){return largeur;}
		inline unsigned long Hauteur(){return hauteur;}
		inline unsigned long TailleFichier(){return tailleFichier;}
		inline unsigned long DebutImage(){return debutImage;}
		inline unsigned long TailleImage(){return tailleImage;}
		inline unsigned long TailleEntete(){return tailleEntete;}
		inline unsigned long Format(){return format;}
		inline unsigned long ResolutionLargeur(){return resoLarg;}
		inline unsigned long ResolutionHauteur(){return resoHaut;}
		void Charger(string nomFichier);
		void Sauvegarder(string nomFichier);
		void Tourner90Droite();
		void Tourner90Gauche();
		void Tourner180();
		void Negatif();
		void RetournerHorizontal();
		void RetournerVertical();
		void NiveauDeGris();
		void Eclaircir(int niveau);
		void Assombrir(int niveau);
		void SeuillerNoirBlanc(int niveau);
		void Colorier(Coordonnee coord,int l,int h,Pixel couleur);
		void Detourer(int largeurGauche,int largeurDroite,int largeurHaut,int largeurBas,Pixel couleur);
		void Recadrer(Coordonnee coord,int l,int h);
		Coordonnee RechercherZone(int l,int h,Pixel couleur);
		void DessinerCroix(Coordonnee coord,int taille,int epaisseur,Pixel couleur);
		void DessinerCarre(Coordonnee coord,int taille,int epaisseur,Pixel couleur);
		void Dessiner7Segments(Coordonnee coord,int taille,int epaisseur,Pixel couleur,string message);
		void Dessiner11Segments(Coordonnee coord,int taille,int epaisseur,Pixel couleur,string message);
		void Dessiner7Segments(int x, int y,int taille,int epaisseur,int couleur,string message);
		void Dessiner11Segments(int x, int y,int taille,int epaisseur,int couleur,string message);
		void TracerDiagonale(Coordonnee debut,Coordonnee fin, int epaisseur, Pixel couleur);
		void TracerDiagonale(int debutX, int debutY, int finX, int finY, int epaisseur, int couleur);
		void TracerCercle(Coordonnee centre, int rayon, int epaisseur, Pixel couleur);
		void TracerCercle(int centreX, int centreY, int rayon, int epaisseur, int couleur);
};
#endif



