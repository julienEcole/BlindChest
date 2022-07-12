#include"SNImage.h"
SNImage::SNImage()
{   signature=0;largeur=0;hauteur=0;tailleFichier=0;debutImage=0;tailleImage=0;
	tailleEntete=0;format=0;resoLarg=0;resoHaut=0;dimensionMax=0;
}
SNImage::~SNImage()
{   //libération de la mémoire
	if(dimensionMax)
	{	for(int i=0;i<dimensionMax;i++)
			delete []image[i];
		delete []image;
	}
}
void SNImage::Charger(string nomFichier)
{	ifstream entree;
	long i,j;char k; long h;
	unsigned long dimensionMaxPrecedente=dimensionMax;
	entree.open(nomFichier.c_str(),fstream::binary);
	//lecture entête image:
	entree.read((char*)&signature,2*sizeof(char));//signature (BM)=424D
	entree.read((char*)&tailleFichier,sizeof(long));
	entree.read((char*)&zero,sizeof(long));
	entree.read((char*)&debutImage,sizeof(long));
	entree.read((char*)&tailleEntete,sizeof(long));
	entree.read((char*)&largeur,sizeof(long));
	entree.read((char*)&hauteur,sizeof(long));
	entree.read((char*)&format,sizeof(long));
	entree.read((char*)&zero,sizeof(long));
	entree.read((char*)&tailleImage,sizeof(long));
	entree.read((char*)&resoLarg,sizeof(long));
	entree.read((char*)&resoHaut,sizeof(long));
	entree.read((char*)&zero,sizeof(long));
	entree.read((char*)&zero,sizeof(long));
	//calcul de k
	k=(4-(largeur*3)%4)%4;
	//remplissage tableau 2 dimensions
	i=hauteur-1;j=0;//i indice des lignes
	if(signature!=0x4D42) cout<<"Vous devez choisir un bitmap .bmp";
	else   if(format!=0x180001) cout<<"Vous devez choisir un bitmap 24 bits";
	else
	{   //libération éventuelle de la mémoire occupée par l'ancienne image
		if(dimensionMaxPrecedente)
		{	for(h=0;h<dimensionMaxPrecedente;h++)
				delete []image[h];
			delete []image;
		}
		if(hauteur>largeur) dimensionMax=hauteur;
		else dimensionMax=largeur;
		//réservation de la mémoire
		image=new Pixel*[dimensionMax];//i
		for(h=0;h<dimensionMax;h++)
			image[h]=new Pixel[dimensionMax];//j
		while(!entree.eof())
		{	entree.read((char*)&image[i][j].bleu,sizeof(char));
			entree.read((char*)&image[i][j].vert,sizeof(char));
			entree.read((char*)&image[i][j].rouge,sizeof(char));
			j++;
			if(j==largeur)
			{  	entree.seekg(k,ios_base::cur);
				j=0;i--;
			}
		}
	}
	entree.close();
}
void SNImage::Sauvegarder(string nomFichier)
{   ofstream sortie; int i,j; char k,z=0,n;
	sortie.open(nomFichier.c_str(),fstream::binary);
	k=(4-(largeur*3)%4)%4;
	sortie.write((char*)&signature,2*sizeof(char));
	sortie.write((char*)&tailleFichier,sizeof(long));
	sortie.write((char*)&zero,sizeof(long));
	sortie.write((char*)&debutImage,sizeof(long));
	sortie.write((char*)&tailleEntete,sizeof(long));
	sortie.write((char*)&largeur,sizeof(long));
	sortie.write((char*)&hauteur,sizeof(long));
	sortie.write((char*)&format,sizeof(long));
	sortie.write((char*)&zero,sizeof(long));
	sortie.write((char*)&tailleImage,sizeof(long));
	sortie.write((char*)&resoLarg,sizeof(long));
	sortie.write((char*)&resoHaut,sizeof(long));
	sortie.write((char*)&zero,sizeof(long));
	sortie.write((char*)&zero,sizeof(long));
	for(i=hauteur-1;i>=0;i--)
	{	for(j=0;j<largeur;j++)
		{   sortie.write((char*)&image[i][j].bleu,sizeof(char));
			sortie.write((char*)&image[i][j].vert,sizeof(char));
			sortie.write((char*)&image[i][j].rouge,sizeof(char));
		}
		//pixels de remplissage
		for(n=0;n<k;n++)
			sortie.write((char*)&z,sizeof(char));
	}
	 sortie.close();
}
void SNImage::Tourner90Droite()
{	int i,j;
	Pixel **temp;
	temp=new Pixel*[dimensionMax];//la hauteur de temp est la largeur de image
	for(i=0;i<dimensionMax;i++)
		temp[i]=new Pixel[dimensionMax];
	unsigned long htemp;
	for(i=0;i<hauteur;i++)
	{	for(j=0;j<largeur;j++)
		{	temp[j][(hauteur-1)-i]=image[i][j];
		}
	}
	htemp=hauteur;hauteur=largeur;largeur=htemp;
	for(i=0;i<hauteur;i++)
	{	for(j=0;j<largeur;j++)
		{	image[i][j]=temp[i][j];
		}
	}
	for(i=0;i<dimensionMax;i++)
		delete []temp[i];
	delete []temp;
}
void SNImage::Tourner180()
{   Tourner90Droite();
	Tourner90Droite();
}
void SNImage::Tourner90Gauche()
{   Tourner90Droite();
	Tourner180();
}
void SNImage::Negatif()
{	int i,j;
	for(i=0;i<hauteur;i++)
	{	for(j=0;j<largeur;j++)
		{	image[i][j].bleu=~(image[i][j].bleu);
			image[i][j].vert=~(image[i][j].vert);
			image[i][j].rouge=~(image[i][j].rouge);
		}
	}
}
void SNImage::RetournerHorizontal()
{	int i,j;
	Pixel temp;
	for(i=0;i<hauteur;i++)
	{	for(j=0;j<largeur/2;j++)
		{	temp=image[i][(largeur-1)-j];image[i][(largeur-1)-j]=image[i][j];image[i][j]=temp;
		}
	}
}
void SNImage::RetournerVertical()
{	int i,j;
	Pixel temp;
	for(i=0;i<hauteur/2;i++)
	{	for(j=0;j<largeur;j++)
		{	temp=image[(hauteur-1)-i][j];image[(hauteur-1)-i][j]=image[i][j];image[i][j]=temp;
		}
	}
}
void SNImage::NiveauDeGris()
{	int i,j;
	unsigned char rouge,vert,bleu,gris;
	for(i=0;i<hauteur;i++)
	{	for(j=0;j<largeur;j++)
		{	bleu=image[i][j].bleu;
			vert=image[i][j].vert;
			rouge=image[i][j].rouge;
			image[i][j].bleu=(bleu+vert+rouge)/3;
			image[i][j].vert=(bleu+vert+rouge)/3;
			image[i][j].rouge=(bleu+vert+rouge)/3;
		}
	}
}
void SNImage::Eclaircir(int niveau)
{	int i,j;
	for(i=0;i<hauteur;i++)
	{	for(j=0;j<largeur;j++)
		{	if((int)(image[i][j].bleu)+niveau<256) image[i][j].bleu=image[i][j].bleu+niveau; else image[i][j].bleu=255;
			if((int)(image[i][j].vert)+niveau<256) image[i][j].vert=image[i][j].vert+niveau; else image[i][j].vert=255;
			if((int)(image[i][j].rouge)+niveau<256) image[i][j].rouge=image[i][j].rouge+niveau; else image[i][j].rouge=255;
		}
	}
}
void SNImage::Assombrir(int niveau)
{	int i,j;
	for(i=0;i<hauteur;i++)
	{	for(j=0;j<largeur;j++)
		{	if((int)(image[i][j].bleu)-niveau>=0) image[i][j].bleu=image[i][j].bleu-niveau; else image[i][j].bleu=0;
			if((int)(image[i][j].vert)-niveau>=0) image[i][j].vert=image[i][j].vert-niveau; else image[i][j].vert=0;
			if((int)(image[i][j].rouge)-niveau>=0) image[i][j].rouge=image[i][j].rouge-niveau; else image[i][j].rouge=0;
		}
	}
}
void SNImage::SeuillerNoirBlanc(int niveau)
{	int i,j;
	NiveauDeGris();
	for(i=0;i<hauteur;i++)
	{	for(j=0;j<largeur;j++)
		{	if(image[i][j].bleu<niveau)
			{	image[i][j].bleu=0; image[i][j].vert=0; image[i][j].rouge=0;
			}
			else
			{	image[i][j].bleu=255; image[i][j].vert=255; image[i][j].rouge=255;
			}
		}
	}
}
void SNImage::Colorier(Coordonnee coord,int l,int h,Pixel couleur)
{   if((coord.ligne+h<=hauteur)&&(coord.colonne+l<=largeur))
	for(int i=coord.ligne;i<coord.ligne+h;i++)
	{	for(int j=coord.colonne;j<coord.colonne+l;j++)
		{	if(i>=0 && i<hauteur && j>=0 && j<largeur)
			{	image[i][j].bleu=couleur.bleu;
				image[i][j].vert=couleur.vert;
				image[i][j].rouge=couleur.rouge;
			}
		}
	}

}
void SNImage::Detourer(int largeurGauche,int largeurDroite,int largeurHaut,int largeurBas,Pixel couleur)
{   Coordonnee coor;
	coor.ligne=0;coor.colonne=0;
	Colorier(coor,largeurGauche,hauteur,couleur);
	Colorier(coor,largeur,largeurHaut,couleur);
	coor.ligne=0;coor.colonne=largeur-largeurDroite;
	Colorier(coor,largeurDroite,hauteur,couleur);
	coor.ligne=hauteur-largeurBas;coor.colonne=0;
	Colorier(coor,largeur,largeurBas,couleur);

}
void SNImage::Recadrer(Coordonnee coord,int l,int h)
{   if((coord.ligne+h<=hauteur)&&(coord.colonne+l<=largeur))
	{   for(int i=0;i<h;i++)
		{	for(int j=0;j<l;j++)
			{	image[i][j]=image[i+coord.ligne][j+coord.colonne];
			}
		}
		largeur=l;hauteur=h;
		int k=(4-(largeur*3)%4)%4;
		tailleImage=(largeur+k)*(hauteur)*3;
		tailleFichier=tailleImage+debutImage;
	}
}
Coordonnee SNImage::RechercherZone(int l,int h,Pixel couleur)
{   Coordonnee coord={-1,-1};
	int i,j,m,n;
	bool zoneTrouve;
	for(int i=0;i<hauteur;i++)
	{	for(int j=0;j<largeur;j++)
		{   if(image[i][j].bleu==couleur.bleu && image[i][j].vert==couleur.vert && image[i][j].rouge==couleur.rouge)
			{   zoneTrouve=true;
				for(int m=0;m<h;m++)
				{   for(int n=0;n<l;n++)
					{	if(image[i+m][j+n].bleu!=couleur.bleu || image[i+m][j+n].vert!=couleur.vert || image[i+m][j+n].rouge!=couleur.rouge)
							zoneTrouve=false;
					}
				}
				if(zoneTrouve)
				{   coord.ligne=i;
					coord.colonne=j;
					i=hauteur;
					j=largeur;
				}
			}
		}
	}
	return coord;
}

void SNImage::DessinerCroix(Coordonnee coord,int taille,int epaisseur,Pixel couleur)
{       Coordonnee debut;
		debut.ligne=coord.ligne-taille/2;debut.colonne=coord.colonne-epaisseur/2;
		if(debut.ligne<0) debut.ligne=0;
		if(debut.colonne<0) debut.colonne=0;
		Colorier(debut,epaisseur,taille,couleur);
		debut.ligne=coord.ligne-epaisseur/2;debut.colonne=coord.colonne-taille/2;
		if(debut.ligne<0) debut.ligne=0;
		if(debut.colonne<0) debut.colonne=0;
		Colorier(debut,taille,epaisseur,couleur);
}
void SNImage::DessinerCarre(Coordonnee coord,int taille,int epaisseur,Pixel couleur)
{       Coordonnee debut=coord;
		debut.ligne-=epaisseur/2;
		debut.colonne-=epaisseur/2;
		Colorier(debut,epaisseur,taille,couleur);//f ou e
		Colorier(debut,taille,epaisseur,couleur);//a
		debut.colonne+=taille;
		Colorier(debut,epaisseur,taille,couleur);//b ou c
		debut=coord;
		debut.ligne-=epaisseur/2;
		debut.colonne-=epaisseur/2;
		debut.ligne+=taille;
		Colorier(debut,taille+epaisseur,epaisseur,couleur);//g ou d
}
void SNImage::Dessiner11Segments(Coordonnee coord,int taille,int epaisseur,Pixel couleur,string message)
{       int ligneDepart=coord.ligne;
		for(int i=0;i<message.length();i++)
		{       coord.ligne=ligneDepart;
				switch (message.c_str()[i])
				{       case '0':
								ChangerCouleurSegment(coord,taille,epaisseur,couleur,'a');
								ChangerCouleurSegment(coord,taille,epaisseur,couleur,'b');
								ChangerCouleurSegment(coord,taille,epaisseur,couleur,'c');
								ChangerCouleurSegment(coord,taille,epaisseur,couleur,'d');
								ChangerCouleurSegment(coord,taille,epaisseur,couleur,'e');
								ChangerCouleurSegment(coord,taille,epaisseur,couleur,'f');
								ChangerCouleurSegment(coord,taille,epaisseur,couleur,'i');
								ChangerCouleurSegment(coord,taille,epaisseur,couleur,'j');

								break;
						case '1':
								ChangerCouleurSegment(coord,taille,epaisseur,couleur,'b');
								ChangerCouleurSegment(coord,taille,epaisseur,couleur,'c');
								ChangerCouleurSegment(coord,taille,epaisseur,couleur,'i');
								break;
						case '2':
								ChangerCouleurSegment(coord,taille,epaisseur,couleur,'a');
								ChangerCouleurSegment(coord,taille,epaisseur,couleur,'b');
								ChangerCouleurSegment(coord,taille,epaisseur,couleur,'d');
								ChangerCouleurSegment(coord,taille,epaisseur,couleur,'e');
								ChangerCouleurSegment(coord,taille,epaisseur,couleur,'g');
								break;
						case '3':
								ChangerCouleurSegment(coord,taille,epaisseur,couleur,'a');
								ChangerCouleurSegment(coord,taille,epaisseur,couleur,'b');
								ChangerCouleurSegment(coord,taille,epaisseur,couleur,'c');
								ChangerCouleurSegment(coord,taille,epaisseur,couleur,'d');
								ChangerCouleurSegment(coord,taille,epaisseur,couleur,'g');
								break;
						case '4':
								ChangerCouleurSegment(coord,taille,epaisseur,couleur,'b');
								ChangerCouleurSegment(coord,taille,epaisseur,couleur,'c');
								ChangerCouleurSegment(coord,taille,epaisseur,couleur,'f');
								ChangerCouleurSegment(coord,taille,epaisseur,couleur,'g');
								break;
						case '5':
								ChangerCouleurSegment(coord,taille,epaisseur,couleur,'a');
								ChangerCouleurSegment(coord,taille,epaisseur,couleur,'c');
								ChangerCouleurSegment(coord,taille,epaisseur,couleur,'d');
								ChangerCouleurSegment(coord,taille,epaisseur,couleur,'f');
								ChangerCouleurSegment(coord,taille,epaisseur,couleur,'g');
								break;
						case '6':
								ChangerCouleurSegment(coord,taille,epaisseur,couleur,'a');
								ChangerCouleurSegment(coord,taille,epaisseur,couleur,'c');
								ChangerCouleurSegment(coord,taille,epaisseur,couleur,'d');
								ChangerCouleurSegment(coord,taille,epaisseur,couleur,'e');
								ChangerCouleurSegment(coord,taille,epaisseur,couleur,'f');
								ChangerCouleurSegment(coord,taille,epaisseur,couleur,'g');
								break;
						case '7':
								ChangerCouleurSegment(coord,taille,epaisseur,couleur,'a');
								ChangerCouleurSegment(coord,taille,epaisseur,couleur,'i');
								ChangerCouleurSegment(coord,taille,epaisseur,couleur,'j');
								break;
						case '8':
								ChangerCouleurSegment(coord,taille,epaisseur,couleur,'a');
								ChangerCouleurSegment(coord,taille,epaisseur,couleur,'b');
								ChangerCouleurSegment(coord,taille,epaisseur,couleur,'c');
								ChangerCouleurSegment(coord,taille,epaisseur,couleur,'d');
								ChangerCouleurSegment(coord,taille,epaisseur,couleur,'e');
								ChangerCouleurSegment(coord,taille,epaisseur,couleur,'f');
								ChangerCouleurSegment(coord,taille,epaisseur,couleur,'g');
								break;
						case '9':
								ChangerCouleurSegment(coord,taille,epaisseur,couleur,'a');
								ChangerCouleurSegment(coord,taille,epaisseur,couleur,'b');
								ChangerCouleurSegment(coord,taille,epaisseur,couleur,'c');
								ChangerCouleurSegment(coord,taille,epaisseur,couleur,'d');
								ChangerCouleurSegment(coord,taille,epaisseur,couleur,'f');
								ChangerCouleurSegment(coord,taille,epaisseur,couleur,'g');
								break;
						case 'A':
								ChangerCouleurSegment(coord,taille,epaisseur,couleur,'a');
								ChangerCouleurSegment(coord,taille,epaisseur,couleur,'b');
								ChangerCouleurSegment(coord,taille,epaisseur,couleur,'c');
								ChangerCouleurSegment(coord,taille,epaisseur,couleur,'e');
								ChangerCouleurSegment(coord,taille,epaisseur,couleur,'f');
								ChangerCouleurSegment(coord,taille,epaisseur,couleur,'g');
								break;
						case 'a':
								ChangerCouleurSegment(coord,taille,epaisseur,couleur,'g');
								ChangerCouleurSegment(coord,taille,epaisseur,couleur,'j');
								ChangerCouleurSegment(coord,taille,epaisseur,couleur,'c');
								ChangerCouleurSegment(coord,taille,epaisseur,couleur,'d');
								break;
						case 'B':
								ChangerCouleurSegment(coord,taille,epaisseur,couleur,'a');
								ChangerCouleurSegment(coord,taille,epaisseur,couleur,'d');
								ChangerCouleurSegment(coord,taille,epaisseur,couleur,'e');
								ChangerCouleurSegment(coord,taille,epaisseur,couleur,'f');
								ChangerCouleurSegment(coord,taille,epaisseur,couleur,'i');
								ChangerCouleurSegment(coord,taille,epaisseur,couleur,'k');
								break;
						case 'b':
								ChangerCouleurSegment(coord,taille,epaisseur,couleur,'d');
								ChangerCouleurSegment(coord,taille,epaisseur,couleur,'c');
								ChangerCouleurSegment(coord,taille,epaisseur,couleur,'e');
								ChangerCouleurSegment(coord,taille,epaisseur,couleur,'f');
								ChangerCouleurSegment(coord,taille,epaisseur,couleur,'g');
								break;
						case 'C':
								ChangerCouleurSegment(coord,taille,epaisseur,couleur,'f');
								ChangerCouleurSegment(coord,taille,epaisseur,couleur,'e');
								ChangerCouleurSegment(coord,taille,epaisseur,couleur,'a');
								ChangerCouleurSegment(coord,taille,epaisseur,couleur,'d');
								break;
						case 'c':
								ChangerCouleurSegment(coord,taille,epaisseur,couleur,'d');
								ChangerCouleurSegment(coord,taille,epaisseur,couleur,'e');
								ChangerCouleurSegment(coord,taille,epaisseur,couleur,'g');
								break;
						case 'D':
								ChangerCouleurSegment(coord,taille,epaisseur,couleur,'d');
								ChangerCouleurSegment(coord,taille,epaisseur,couleur,'e');
								ChangerCouleurSegment(coord,taille,epaisseur,couleur,'f');
								ChangerCouleurSegment(coord,taille,epaisseur,couleur,'h');
								ChangerCouleurSegment(coord,taille,epaisseur,couleur,'k');
								break;
						case 'd':
								ChangerCouleurSegment(coord,taille,epaisseur,couleur,'b');
								ChangerCouleurSegment(coord,taille,epaisseur,couleur,'c');
								ChangerCouleurSegment(coord,taille,epaisseur,couleur,'e');
								ChangerCouleurSegment(coord,taille,epaisseur,couleur,'d');
								ChangerCouleurSegment(coord,taille,epaisseur,couleur,'g');
								break;
						case 'E':
								ChangerCouleurSegment(coord,taille,epaisseur,couleur,'a');
								ChangerCouleurSegment(coord,taille,epaisseur,couleur,'f');
								ChangerCouleurSegment(coord,taille,epaisseur,couleur,'e');
								ChangerCouleurSegment(coord,taille,epaisseur,couleur,'d');
								ChangerCouleurSegment(coord,taille,epaisseur,couleur,'g');
								break;
						case 'e':
								ChangerCouleurSegment(coord,taille,epaisseur,couleur,'g');
								ChangerCouleurSegment(coord,taille,epaisseur,couleur,'j');
								ChangerCouleurSegment(coord,taille,epaisseur,couleur,'e');
								ChangerCouleurSegment(coord,taille,epaisseur,couleur,'d');
								break;
						case 'F':
								ChangerCouleurSegment(coord,taille,epaisseur,couleur,'a');
								ChangerCouleurSegment(coord,taille,epaisseur,couleur,'f');
								ChangerCouleurSegment(coord,taille,epaisseur,couleur,'e');
								ChangerCouleurSegment(coord,taille,epaisseur,couleur,'g');
								break;
						case 'f':
								ChangerCouleurSegment(coord,taille,epaisseur,couleur,'b');
								ChangerCouleurSegment(coord,taille,epaisseur,couleur,'i');
								ChangerCouleurSegment(coord,taille,epaisseur,couleur,'j');
								ChangerCouleurSegment(coord,taille,epaisseur,couleur,'g');
								ChangerCouleurSegment(coord,taille,epaisseur,couleur,'e');
								break;
						case 'G':
								ChangerCouleurSegment(coord,taille,epaisseur,couleur,'a');
								ChangerCouleurSegment(coord,taille,epaisseur,couleur,'k');
								ChangerCouleurSegment(coord,taille,epaisseur,couleur,'d');
								ChangerCouleurSegment(coord,taille,epaisseur,couleur,'e');
								ChangerCouleurSegment(coord,taille,epaisseur,couleur,'f');
								break;
						case 'g':
								ChangerCouleurSegment(coord,taille,epaisseur,couleur,'a');
								ChangerCouleurSegment(coord,taille,epaisseur,couleur,'i');
								ChangerCouleurSegment(coord,taille,epaisseur,couleur,'h');
								ChangerCouleurSegment(coord,taille,epaisseur,couleur,'j');
								ChangerCouleurSegment(coord,taille,epaisseur,couleur,'e');
								break;
						case 'H':
								ChangerCouleurSegment(coord,taille,epaisseur,couleur,'b');
								ChangerCouleurSegment(coord,taille,epaisseur,couleur,'c');
								ChangerCouleurSegment(coord,taille,epaisseur,couleur,'e');
								ChangerCouleurSegment(coord,taille,epaisseur,couleur,'f');
								ChangerCouleurSegment(coord,taille,epaisseur,couleur,'g');
								break;
						case 'h':
								ChangerCouleurSegment(coord,taille,epaisseur,couleur,'c');
								ChangerCouleurSegment(coord,taille,epaisseur,couleur,'e');
								ChangerCouleurSegment(coord,taille,epaisseur,couleur,'f');
								ChangerCouleurSegment(coord,taille,epaisseur,couleur,'g');
								break;
						case 'I':
								ChangerCouleurSegment(coord,taille,epaisseur,couleur,'l');
								break;
						case 'i':
								ChangerCouleurSegment(coord,taille,epaisseur,couleur,'c');
								break;
						case 'J':
								ChangerCouleurSegment(coord,taille,epaisseur,couleur,'b');
								ChangerCouleurSegment(coord,taille,epaisseur,couleur,'c');
								ChangerCouleurSegment(coord,taille,epaisseur,couleur,'d');
								break;
						case 'j':
								ChangerCouleurSegment(coord,taille,epaisseur,couleur,'g');
								ChangerCouleurSegment(coord,taille,epaisseur,couleur,'e');
								ChangerCouleurSegment(coord,taille,epaisseur,couleur,'i');
								ChangerCouleurSegment(coord,taille,epaisseur,couleur,'j');
								break;
						case 'K':
								ChangerCouleurSegment(coord,taille,epaisseur,couleur,'i');
								ChangerCouleurSegment(coord,taille,epaisseur,couleur,'e');
								ChangerCouleurSegment(coord,taille,epaisseur,couleur,'f');
								ChangerCouleurSegment(coord,taille,epaisseur,couleur,'k');
								break;
						case 'k':
								ChangerCouleurSegment(coord,taille,epaisseur,couleur,'k');
								ChangerCouleurSegment(coord,taille,epaisseur,couleur,'e');
								ChangerCouleurSegment(coord,taille,epaisseur,couleur,'f');
								ChangerCouleurSegment(coord,taille,epaisseur,couleur,'g');
								break;
						case 'L':
								ChangerCouleurSegment(coord,taille,epaisseur,couleur,'d');
								ChangerCouleurSegment(coord,taille,epaisseur,couleur,'e');
								ChangerCouleurSegment(coord,taille,epaisseur,couleur,'f');
								break;
						case 'l':
								ChangerCouleurSegment(coord,taille,epaisseur,couleur,'i');
								ChangerCouleurSegment(coord,taille,epaisseur,couleur,'j');
								ChangerCouleurSegment(coord,taille,epaisseur,couleur,'d');
								break;

						case 'M':
								ChangerCouleurSegment(coord,taille,epaisseur,couleur,'i');
								ChangerCouleurSegment(coord,taille,epaisseur,couleur,'h');
								ChangerCouleurSegment(coord,taille,epaisseur,couleur,'b');
								ChangerCouleurSegment(coord,taille,epaisseur,couleur,'c');
								ChangerCouleurSegment(coord,taille,epaisseur,couleur,'e');
								ChangerCouleurSegment(coord,taille,epaisseur,couleur,'f');
								break;
						case 'm':
								ChangerCouleurSegment(coord,taille,epaisseur,couleur,'c');
								ChangerCouleurSegment(coord,taille,epaisseur,couleur,'e');
								ChangerCouleurSegment(coord,taille,epaisseur,couleur,'g');
								break;
						case 'N':
								ChangerCouleurSegment(coord,taille,epaisseur,couleur,'k');
								ChangerCouleurSegment(coord,taille,epaisseur,couleur,'h');
								ChangerCouleurSegment(coord,taille,epaisseur,couleur,'b');
								ChangerCouleurSegment(coord,taille,epaisseur,couleur,'c');
								ChangerCouleurSegment(coord,taille,epaisseur,couleur,'e');
								ChangerCouleurSegment(coord,taille,epaisseur,couleur,'f');
								break;
						case 'n':
								ChangerCouleurSegment(coord,taille,epaisseur,couleur,'j');
								ChangerCouleurSegment(coord,taille,epaisseur,couleur,'k');
								ChangerCouleurSegment(coord,taille,epaisseur,couleur,'c');
								break;
						case 'O':
								ChangerCouleurSegment(coord,taille,epaisseur,couleur,'b');
								ChangerCouleurSegment(coord,taille,epaisseur,couleur,'c');
								ChangerCouleurSegment(coord,taille,epaisseur,couleur,'d');
								ChangerCouleurSegment(coord,taille,epaisseur,couleur,'e');
								ChangerCouleurSegment(coord,taille,epaisseur,couleur,'a');
								ChangerCouleurSegment(coord,taille,epaisseur,couleur,'f');
								break;
						case 'o':
								ChangerCouleurSegment(coord,taille,epaisseur,couleur,'c');
								ChangerCouleurSegment(coord,taille,epaisseur,couleur,'d');
								ChangerCouleurSegment(coord,taille,epaisseur,couleur,'e');
								ChangerCouleurSegment(coord,taille,epaisseur,couleur,'g');
								break;
						case 'P':
								ChangerCouleurSegment(coord,taille,epaisseur,couleur,'a');
								ChangerCouleurSegment(coord,taille,epaisseur,couleur,'b');
								ChangerCouleurSegment(coord,taille,epaisseur,couleur,'e');
								ChangerCouleurSegment(coord,taille,epaisseur,couleur,'f');
								ChangerCouleurSegment(coord,taille,epaisseur,couleur,'g');
								break;
						case 'p':
								ChangerCouleurSegment(coord,taille,epaisseur,couleur,'b');
								ChangerCouleurSegment(coord,taille,epaisseur,couleur,'g');
								ChangerCouleurSegment(coord,taille,epaisseur,couleur,'i');
								ChangerCouleurSegment(coord,taille,epaisseur,couleur,'j');
								break;
						case 'Q':
								ChangerCouleurSegment(coord,taille,epaisseur,couleur,'b');
								ChangerCouleurSegment(coord,taille,epaisseur,couleur,'c');
								ChangerCouleurSegment(coord,taille,epaisseur,couleur,'d');
								ChangerCouleurSegment(coord,taille,epaisseur,couleur,'e');
								ChangerCouleurSegment(coord,taille,epaisseur,couleur,'a');
								ChangerCouleurSegment(coord,taille,epaisseur,couleur,'f');
								ChangerCouleurSegment(coord,taille,epaisseur,couleur,'k');
								break;
						case 'q':
								ChangerCouleurSegment(coord,taille,epaisseur,couleur,'h');
								ChangerCouleurSegment(coord,taille,epaisseur,couleur,'k');
								ChangerCouleurSegment(coord,taille,epaisseur,couleur,'f');
								ChangerCouleurSegment(coord,taille,epaisseur,couleur,'g');
								break;
						case 'R':
								ChangerCouleurSegment(coord,taille,epaisseur,couleur,'a');
								ChangerCouleurSegment(coord,taille,epaisseur,couleur,'b');
								ChangerCouleurSegment(coord,taille,epaisseur,couleur,'e');
								ChangerCouleurSegment(coord,taille,epaisseur,couleur,'f');
								ChangerCouleurSegment(coord,taille,epaisseur,couleur,'g');
								ChangerCouleurSegment(coord,taille,epaisseur,couleur,'k');
								break;
						case 'r':
								ChangerCouleurSegment(coord,taille,epaisseur,couleur,'e');
								ChangerCouleurSegment(coord,taille,epaisseur,couleur,'g');
								break;
						case 'S':
								ChangerCouleurSegment(coord,taille,epaisseur,couleur,'a');
								ChangerCouleurSegment(coord,taille,epaisseur,couleur,'c');
								ChangerCouleurSegment(coord,taille,epaisseur,couleur,'d');
								ChangerCouleurSegment(coord,taille,epaisseur,couleur,'f');
								ChangerCouleurSegment(coord,taille,epaisseur,couleur,'g');
								break;
						case 's':
								ChangerCouleurSegment(coord,taille,epaisseur,couleur,'k');
								ChangerCouleurSegment(coord,taille,epaisseur,couleur,'d');
								ChangerCouleurSegment(coord,taille,epaisseur,couleur,'g');
								break;
						case 'T':
								ChangerCouleurSegment(coord,taille,epaisseur,couleur,'a');
								ChangerCouleurSegment(coord,taille,epaisseur,couleur,'l');
								break;
						case 't':
								ChangerCouleurSegment(coord,taille,epaisseur,couleur,'i');
								ChangerCouleurSegment(coord,taille,epaisseur,couleur,'j');
								ChangerCouleurSegment(coord,taille,epaisseur,couleur,'g');
								break;
						case 'U':
								ChangerCouleurSegment(coord,taille,epaisseur,couleur,'b');
								ChangerCouleurSegment(coord,taille,epaisseur,couleur,'c');
								ChangerCouleurSegment(coord,taille,epaisseur,couleur,'d');
								ChangerCouleurSegment(coord,taille,epaisseur,couleur,'e');
								ChangerCouleurSegment(coord,taille,epaisseur,couleur,'f');
								break;
						case 'u':
								ChangerCouleurSegment(coord,taille,epaisseur,couleur,'c');
								ChangerCouleurSegment(coord,taille,epaisseur,couleur,'d');
								ChangerCouleurSegment(coord,taille,epaisseur,couleur,'e');
								break;
						case 'V':
								ChangerCouleurSegment(coord,taille,epaisseur,couleur,'f');
								ChangerCouleurSegment(coord,taille,epaisseur,couleur,'e');
								ChangerCouleurSegment(coord,taille,epaisseur,couleur,'j');
								ChangerCouleurSegment(coord,taille,epaisseur,couleur,'i');
								break;
						case 'v':
								ChangerCouleurSegment(coord,taille,epaisseur,couleur,'e');
								ChangerCouleurSegment(coord,taille,epaisseur,couleur,'j');
								break;
						case 'W':
								ChangerCouleurSegment(coord,taille,epaisseur,couleur,'b');
								ChangerCouleurSegment(coord,taille,epaisseur,couleur,'c');
								ChangerCouleurSegment(coord,taille,epaisseur,couleur,'e');
								ChangerCouleurSegment(coord,taille,epaisseur,couleur,'f');
								ChangerCouleurSegment(coord,taille,epaisseur,couleur,'j');
								ChangerCouleurSegment(coord,taille,epaisseur,couleur,'k');
								break;
						case 'w':
								ChangerCouleurSegment(coord,taille,epaisseur,couleur,'c');
								ChangerCouleurSegment(coord,taille,epaisseur,couleur,'e');
								ChangerCouleurSegment(coord,taille,epaisseur,couleur,'j');
								ChangerCouleurSegment(coord,taille,epaisseur,couleur,'k');
								break;
						case 'X':
								ChangerCouleurSegment(coord,taille,epaisseur,couleur,'h');
								ChangerCouleurSegment(coord,taille,epaisseur,couleur,'i');
								ChangerCouleurSegment(coord,taille,epaisseur,couleur,'j');
								ChangerCouleurSegment(coord,taille,epaisseur,couleur,'k');
								break;
						case 'x':
								ChangerCouleurSegment(coord,taille,epaisseur,couleur,'g');
								ChangerCouleurSegment(coord,taille,epaisseur,couleur,'j');
								ChangerCouleurSegment(coord,taille,epaisseur,couleur,'k');
								break;
						case 'Y':
								ChangerCouleurSegment(coord,taille,epaisseur,couleur,'h');
								ChangerCouleurSegment(coord,taille,epaisseur,couleur,'i');
								ChangerCouleurSegment(coord,taille,epaisseur,couleur,'j');
								break;
						case 'y':
								ChangerCouleurSegment(coord,taille,epaisseur,couleur,'e');
								ChangerCouleurSegment(coord,taille,epaisseur,couleur,'g');
								ChangerCouleurSegment(coord,taille,epaisseur,couleur,'i');
								ChangerCouleurSegment(coord,taille,epaisseur,couleur,'j');
								ChangerCouleurSegment(coord,taille,epaisseur,couleur,'h');
								break;
						case 'Z':
								ChangerCouleurSegment(coord,taille,epaisseur,couleur,'d');
								ChangerCouleurSegment(coord,taille,epaisseur,couleur,'a');
								ChangerCouleurSegment(coord,taille,epaisseur,couleur,'i');
								ChangerCouleurSegment(coord,taille,epaisseur,couleur,'j');
								break;
						case 'z':
								ChangerCouleurSegment(coord,taille,epaisseur,couleur,'d');
								ChangerCouleurSegment(coord,taille,epaisseur,couleur,'g');
								ChangerCouleurSegment(coord,taille,epaisseur,couleur,'j');
								break;
						case '-':
								ChangerCouleurSegment(coord,taille,epaisseur,couleur,'g');
								break;
						case '\\':
								ChangerCouleurSegment(coord,taille,epaisseur,couleur,'h');
								ChangerCouleurSegment(coord,taille,epaisseur,couleur,'k');
								break;
						case '/':
								ChangerCouleurSegment(coord,taille,epaisseur,couleur,'i');
								ChangerCouleurSegment(coord,taille,epaisseur,couleur,'j');
								break;
				}
				coord.colonne+=2*(taille/2);
				coord.ligne=ligneDepart;
		}
}
void SNImage::Dessiner7Segments(Coordonnee coord,int taille,int epaisseur,Pixel couleur,string message)
{       int ligneDepart=coord.ligne;
		for(int i=0;i<message.length();i++)
		{       coord.ligne=ligneDepart;
				switch (message.c_str()[i])
				{       case '0':
						case 'D':
						case 'O':
								ChangerCouleurSegment(coord,taille,epaisseur,couleur,'a');
								ChangerCouleurSegment(coord,taille,epaisseur,couleur,'b');
								ChangerCouleurSegment(coord,taille,epaisseur,couleur,'c');
								ChangerCouleurSegment(coord,taille,epaisseur,couleur,'d');
								ChangerCouleurSegment(coord,taille,epaisseur,couleur,'e');
                                ChangerCouleurSegment(coord,taille,epaisseur,couleur,'f');
								break;
						case '1':
						case 'I':
						case 'l':
								ChangerCouleurSegment(coord,taille,epaisseur,couleur,'b');
								ChangerCouleurSegment(coord,taille,epaisseur,couleur,'c');
								break;
						case '2':
						case 'Z':
						case 'z':
								ChangerCouleurSegment(coord,taille,epaisseur,couleur,'a');
								ChangerCouleurSegment(coord,taille,epaisseur,couleur,'b');
								ChangerCouleurSegment(coord,taille,epaisseur,couleur,'d');
                                ChangerCouleurSegment(coord,taille,epaisseur,couleur,'e');
								ChangerCouleurSegment(coord,taille,epaisseur,couleur,'g');
                                break;
						case '3':
								ChangerCouleurSegment(coord,taille,epaisseur,couleur,'a');
								ChangerCouleurSegment(coord,taille,epaisseur,couleur,'b');
								ChangerCouleurSegment(coord,taille,epaisseur,couleur,'c');
								ChangerCouleurSegment(coord,taille,epaisseur,couleur,'d');
								ChangerCouleurSegment(coord,taille,epaisseur,couleur,'g');
								break;
						case '4':
						case 'Y':
								ChangerCouleurSegment(coord,taille,epaisseur,couleur,'b');
								ChangerCouleurSegment(coord,taille,epaisseur,couleur,'c');
								ChangerCouleurSegment(coord,taille,epaisseur,couleur,'f');
								ChangerCouleurSegment(coord,taille,epaisseur,couleur,'g');
								break;
						case '5':
								ChangerCouleurSegment(coord,taille,epaisseur,couleur,'a');
								ChangerCouleurSegment(coord,taille,epaisseur,couleur,'c');
								ChangerCouleurSegment(coord,taille,epaisseur,couleur,'d');
								ChangerCouleurSegment(coord,taille,epaisseur,couleur,'f');
								ChangerCouleurSegment(coord,taille,epaisseur,couleur,'g');
								break;
                        case '6':
								ChangerCouleurSegment(coord,taille,epaisseur,couleur,'a');
								ChangerCouleurSegment(coord,taille,epaisseur,couleur,'c');
								ChangerCouleurSegment(coord,taille,epaisseur,couleur,'d');
								ChangerCouleurSegment(coord,taille,epaisseur,couleur,'e');
                                ChangerCouleurSegment(coord,taille,epaisseur,couleur,'f');
                                ChangerCouleurSegment(coord,taille,epaisseur,couleur,'g');
                                break;
                        case '7':
								ChangerCouleurSegment(coord,taille,epaisseur,couleur,'a');
                                ChangerCouleurSegment(coord,taille,epaisseur,couleur,'b');
                                ChangerCouleurSegment(coord,taille,epaisseur,couleur,'c');
								break;
						case '8':
						case 'B':
								ChangerCouleurSegment(coord,taille,epaisseur,couleur,'a');
								ChangerCouleurSegment(coord,taille,epaisseur,couleur,'b');
								ChangerCouleurSegment(coord,taille,epaisseur,couleur,'c');
								ChangerCouleurSegment(coord,taille,epaisseur,couleur,'d');
								ChangerCouleurSegment(coord,taille,epaisseur,couleur,'e');
								ChangerCouleurSegment(coord,taille,epaisseur,couleur,'f');
								ChangerCouleurSegment(coord,taille,epaisseur,couleur,'g');
								break;
						case '9':
						case 'g':
								ChangerCouleurSegment(coord,taille,epaisseur,couleur,'a');
								ChangerCouleurSegment(coord,taille,epaisseur,couleur,'b');
								ChangerCouleurSegment(coord,taille,epaisseur,couleur,'c');
								ChangerCouleurSegment(coord,taille,epaisseur,couleur,'d');
								ChangerCouleurSegment(coord,taille,epaisseur,couleur,'f');
												ChangerCouleurSegment(coord,taille,epaisseur,couleur,'g');
								break;
						case 'A':
								ChangerCouleurSegment(coord,taille,epaisseur,couleur,'a');
								ChangerCouleurSegment(coord,taille,epaisseur,couleur,'b');
								ChangerCouleurSegment(coord,taille,epaisseur,couleur,'c');
								ChangerCouleurSegment(coord,taille,epaisseur,couleur,'e');
								ChangerCouleurSegment(coord,taille,epaisseur,couleur,'f');
								ChangerCouleurSegment(coord,taille,epaisseur,couleur,'g');
								break;
						case 'b':
								ChangerCouleurSegment(coord,taille,epaisseur,couleur,'e');
								ChangerCouleurSegment(coord,taille,epaisseur,couleur,'d');
								ChangerCouleurSegment(coord,taille,epaisseur,couleur,'c');
								ChangerCouleurSegment(coord,taille,epaisseur,couleur,'f');
								ChangerCouleurSegment(coord,taille,epaisseur,couleur,'g');
								break;
						case 'C':
								ChangerCouleurSegment(coord,taille,epaisseur,couleur,'f');
								ChangerCouleurSegment(coord,taille,epaisseur,couleur,'e');
								ChangerCouleurSegment(coord,taille,epaisseur,couleur,'a');
								ChangerCouleurSegment(coord,taille,epaisseur,couleur,'d');
								break;
						case 'c':
								ChangerCouleurSegment(coord,taille,epaisseur,couleur,'d');
								ChangerCouleurSegment(coord,taille,epaisseur,couleur,'e');
								ChangerCouleurSegment(coord,taille,epaisseur,couleur,'g');
								break;
						case 'd':
								ChangerCouleurSegment(coord,taille,epaisseur,couleur,'b');
								ChangerCouleurSegment(coord,taille,epaisseur,couleur,'c');
								ChangerCouleurSegment(coord,taille,epaisseur,couleur,'e');
								ChangerCouleurSegment(coord,taille,epaisseur,couleur,'d');
								ChangerCouleurSegment(coord,taille,epaisseur,couleur,'g');
								break;
						case 'E':
								ChangerCouleurSegment(coord,taille,epaisseur,couleur,'a');
								ChangerCouleurSegment(coord,taille,epaisseur,couleur,'f');
								ChangerCouleurSegment(coord,taille,epaisseur,couleur,'e');
								ChangerCouleurSegment(coord,taille,epaisseur,couleur,'d');
								ChangerCouleurSegment(coord,taille,epaisseur,couleur,'g');
								break;
						case 'e':
								ChangerCouleurSegment(coord,taille,epaisseur,couleur,'a');
								ChangerCouleurSegment(coord,taille,epaisseur,couleur,'d');
								ChangerCouleurSegment(coord,taille,epaisseur,couleur,'f');
								ChangerCouleurSegment(coord,taille,epaisseur,couleur,'e');
								ChangerCouleurSegment(coord,taille,epaisseur,couleur,'b');
								ChangerCouleurSegment(coord,taille,epaisseur,couleur,'g');
								break;
						case 'F':
						case 'f':
								ChangerCouleurSegment(coord,taille,epaisseur,couleur,'a');
								ChangerCouleurSegment(coord,taille,epaisseur,couleur,'f');
								ChangerCouleurSegment(coord,taille,epaisseur,couleur,'e');
								ChangerCouleurSegment(coord,taille,epaisseur,couleur,'g');
								break;
						case 'G':
								ChangerCouleurSegment(coord,taille,epaisseur,couleur,'a');
								ChangerCouleurSegment(coord,taille,epaisseur,couleur,'c');
								ChangerCouleurSegment(coord,taille,epaisseur,couleur,'d');
								ChangerCouleurSegment(coord,taille,epaisseur,couleur,'e');
								ChangerCouleurSegment(coord,taille,epaisseur,couleur,'f');
								break;
						case 'H':
						case 'h':
								ChangerCouleurSegment(coord,taille,epaisseur,couleur,'b');
								ChangerCouleurSegment(coord,taille,epaisseur,couleur,'c');
								ChangerCouleurSegment(coord,taille,epaisseur,couleur,'e');
								ChangerCouleurSegment(coord,taille,epaisseur,couleur,'f');
								ChangerCouleurSegment(coord,taille,epaisseur,couleur,'g');
								break;
						case 'i':
								ChangerCouleurSegment(coord,taille,epaisseur,couleur,'c');
								break;
						case 'J':
								ChangerCouleurSegment(coord,taille,epaisseur,couleur,'b');
								ChangerCouleurSegment(coord,taille,epaisseur,couleur,'c');
								ChangerCouleurSegment(coord,taille,epaisseur,couleur,'d');
						case 'j':
								ChangerCouleurSegment(coord,taille,epaisseur,couleur,'c');
								ChangerCouleurSegment(coord,taille,epaisseur,couleur,'d');
								break;
						case 'k':
						case 'K':
								ChangerCouleurSegment(coord,taille,epaisseur,couleur,'d');
								ChangerCouleurSegment(coord,taille,epaisseur,couleur,'e');
								ChangerCouleurSegment(coord,taille,epaisseur,couleur,'f');
								ChangerCouleurSegment(coord,taille,epaisseur,couleur,'g');
								break;
						case 'L':
								ChangerCouleurSegment(coord,taille,epaisseur,couleur,'d');
								ChangerCouleurSegment(coord,taille,epaisseur,couleur,'e');
								ChangerCouleurSegment(coord,taille,epaisseur,couleur,'f');
								break;
						case 'M':
						case 'm':
								ChangerCouleurSegment(coord,taille,epaisseur,couleur,'a');
								ChangerCouleurSegment(coord,taille,epaisseur,couleur,'b');
								ChangerCouleurSegment(coord,taille,epaisseur,couleur,'c');
								ChangerCouleurSegment(coord,taille,epaisseur,couleur,'e');
								ChangerCouleurSegment(coord,taille,epaisseur,couleur,'f');
								break;
						case 'N':
						case 'n':
								ChangerCouleurSegment(coord,taille,epaisseur,couleur,'c');
								ChangerCouleurSegment(coord,taille,epaisseur,couleur,'e');
								ChangerCouleurSegment(coord,taille,epaisseur,couleur,'g');
								break;

						case 'o':
						case 'a':
								ChangerCouleurSegment(coord,taille,epaisseur,couleur,'c');
								ChangerCouleurSegment(coord,taille,epaisseur,couleur,'d');
								ChangerCouleurSegment(coord,taille,epaisseur,couleur,'e');
								ChangerCouleurSegment(coord,taille,epaisseur,couleur,'g');
								break;
						case 'P':
						case 'p':
								ChangerCouleurSegment(coord,taille,epaisseur,couleur,'a');
								ChangerCouleurSegment(coord,taille,epaisseur,couleur,'b');
								ChangerCouleurSegment(coord,taille,epaisseur,couleur,'e');
								ChangerCouleurSegment(coord,taille,epaisseur,couleur,'f');
								ChangerCouleurSegment(coord,taille,epaisseur,couleur,'g');
								break;
						case 'Q':
						case 'q':
								ChangerCouleurSegment(coord,taille,epaisseur,couleur,'a');
								ChangerCouleurSegment(coord,taille,epaisseur,couleur,'b');
								ChangerCouleurSegment(coord,taille,epaisseur,couleur,'c');
								ChangerCouleurSegment(coord,taille,epaisseur,couleur,'f');
								ChangerCouleurSegment(coord,taille,epaisseur,couleur,'g');
								break;
						case 'R':
						case 'r':
								ChangerCouleurSegment(coord,taille,epaisseur,couleur,'e');
								ChangerCouleurSegment(coord,taille,epaisseur,couleur,'g');
								break;
						case 'S':
						case 's':
								ChangerCouleurSegment(coord,taille,epaisseur,couleur,'a');
								ChangerCouleurSegment(coord,taille,epaisseur,couleur,'c');
								ChangerCouleurSegment(coord,taille,epaisseur,couleur,'d');
								ChangerCouleurSegment(coord,taille,epaisseur,couleur,'f');
								ChangerCouleurSegment(coord,taille,epaisseur,couleur,'g');
								break;
						case 'T':
						case 't':
								ChangerCouleurSegment(coord,taille,epaisseur,couleur,'d');
								ChangerCouleurSegment(coord,taille,epaisseur,couleur,'e');
								ChangerCouleurSegment(coord,taille,epaisseur,couleur,'f');
								ChangerCouleurSegment(coord,taille,epaisseur,couleur,'g');
								break;
						case 'U':
								ChangerCouleurSegment(coord,taille,epaisseur,couleur,'b');
								ChangerCouleurSegment(coord,taille,epaisseur,couleur,'c');
								ChangerCouleurSegment(coord,taille,epaisseur,couleur,'d');
								ChangerCouleurSegment(coord,taille,epaisseur,couleur,'e');
								ChangerCouleurSegment(coord,taille,epaisseur,couleur,'f');
								break;
						case 'u':
								ChangerCouleurSegment(coord,taille,epaisseur,couleur,'c');
								ChangerCouleurSegment(coord,taille,epaisseur,couleur,'d');
								ChangerCouleurSegment(coord,taille,epaisseur,couleur,'e');
								break;
						case 'V':
						case 'W':
								ChangerCouleurSegment(coord,taille,epaisseur,couleur,'b');
								ChangerCouleurSegment(coord,taille,epaisseur,couleur,'c');
								ChangerCouleurSegment(coord,taille,epaisseur,couleur,'d');
								ChangerCouleurSegment(coord,taille,epaisseur,couleur,'e');
								ChangerCouleurSegment(coord,taille,epaisseur,couleur,'f');
								break;
						case 'v':
						case 'w':
								ChangerCouleurSegment(coord,taille,epaisseur,couleur,'c');
								ChangerCouleurSegment(coord,taille,epaisseur,couleur,'d');
								ChangerCouleurSegment(coord,taille,epaisseur,couleur,'e');
								break;
						case 'x':
								ChangerCouleurSegment(coord,taille,epaisseur,couleur,'g');
								ChangerCouleurSegment(coord,taille,epaisseur,couleur,'d');
								break;
						case 'X':
								ChangerCouleurSegment(coord,taille,epaisseur,couleur,'d');
								ChangerCouleurSegment(coord,taille,epaisseur,couleur,'a');
								break;
						case 'y':
								ChangerCouleurSegment(coord,taille,epaisseur,couleur,'b');
								ChangerCouleurSegment(coord,taille,epaisseur,couleur,'c');
								ChangerCouleurSegment(coord,taille,epaisseur,couleur,'d');
								ChangerCouleurSegment(coord,taille,epaisseur,couleur,'f');
								ChangerCouleurSegment(coord,taille,epaisseur,couleur,'g');
								break;
				}
				coord.colonne+=2*(taille/2);
				coord.ligne=ligneDepart;
		}
}

void SNImage::ChangerCouleurSegment(Coordonnee coord,int taille,int epaisseur,Pixel couleur,char segment)//segment='a' 'b' 'c' 'd' 'e' 'f'
{       Coordonnee debut,fin;
		switch (segment)
		{       case 'a':
						debut=coord; debut.ligne-=epaisseur/2; debut.colonne-=epaisseur/2; Colorier(debut,taille/2+epaisseur,epaisseur,couleur); break;
				case 'b':
						debut=coord; debut.ligne-=epaisseur/2; debut.colonne-=epaisseur/2; debut.colonne+=taille/2; Colorier(debut,epaisseur,taille/2+epaisseur,couleur); break;
				case 'f':
						debut=coord; debut.ligne-=epaisseur/2; debut.colonne-=epaisseur/2; Colorier(debut,epaisseur,taille/2+epaisseur,couleur); break;
				case 'g':
						debut=coord; debut.ligne-=epaisseur/2; debut.colonne-=epaisseur/2; debut.ligne+=taille/2; Colorier(debut,taille/2+epaisseur,epaisseur,couleur); break;
				case 'c':
						debut=coord; debut.ligne-=epaisseur/2-taille/2; debut.colonne-=epaisseur/2; debut.colonne+=taille/2; Colorier(debut,epaisseur,taille/2+epaisseur,couleur); break;
				case 'e':
						debut=coord; debut.ligne-=epaisseur/2-taille/2; debut.colonne-=epaisseur/2; Colorier(debut,epaisseur,taille/2+epaisseur,couleur); break;
				case 'd':
						debut=coord; debut.ligne-=epaisseur/2-taille/2; debut.colonne-=epaisseur/2; debut.ligne+=taille/2; Colorier(debut,taille/2+epaisseur,epaisseur,couleur); break;
				case 'h':    //10h
						debut=coord; fin=coord;
						debut.colonne=debut.colonne+taille/4-epaisseur/2;
						debut.ligne=debut.ligne+taille/2;
						fin.colonne=fin.colonne+taille/2-epaisseur/2;
						fin.ligne=fin.ligne-epaisseur/2;
						fin.colonne-=taille/2;
						TracerDiagonale(debut,fin,epaisseur,couleur);
						break;
				case 'i':    //2h
						debut=coord; fin=coord;
						debut.colonne=debut.colonne+taille/4-epaisseur/2;
						debut.ligne=debut.ligne+taille/2;//-2;     //-2???
						fin.colonne=fin.colonne+taille/2-epaisseur/2;
						fin.ligne=fin.ligne-epaisseur/2;
						TracerDiagonale(debut,fin,epaisseur,couleur);
//						DessineCroix(debut,30,1,c1);
//						DessineCroix(fin,30,1,c2);
						break;
				case 'j':    //8h
						debut=coord; fin=coord;
						debut.colonne=debut.colonne+taille/4-epaisseur/2;
						debut.ligne=debut.ligne+taille/2;
						fin.colonne=fin.colonne+taille/2-epaisseur/2;
						fin.ligne=fin.ligne-epaisseur/2;
						fin.colonne-=taille/2;
						fin.ligne+=taille+epaisseur-2;           //-2???
						TracerDiagonale(debut,fin,epaisseur,couleur);
						break;
				case 'k':    //4h
						debut=coord; fin=coord;
						debut.colonne=debut.colonne+taille/4-epaisseur/2;
						debut.ligne=debut.ligne+taille/2;
						fin.colonne=fin.colonne+taille/2-epaisseur/2;
						fin.ligne=fin.ligne-epaisseur/2;
						fin.ligne+=taille+epaisseur;
						TracerDiagonale(debut,fin,epaisseur,couleur);
						break;
				case 'l':    //12h+6h
						debut=coord; debut.ligne-=epaisseur/2; debut.colonne-=epaisseur/2; debut.colonne+=taille/4;
						Colorier(debut,epaisseur,taille+epaisseur,couleur); break;
		}
}
void SNImage::TracerDiagonaleUnPixel(Coordonnee debut,Coordonnee fin, Pixel couleur)
{//   Pixel r={0,0,255},b={255,0,0},v={0,255,0},bl={255,255,255},n={0,0,0};
	if(debut.ligne>fin.ligne)
	{   Coordonnee temp=fin;
		fin=debut;
		debut=temp;
	}
//	DessinerCroix(debut,5,1,r);    DessinerCroix(fin,5,1,v);
	float h=abs(debut.ligne-fin.ligne);
	float l=abs(debut.colonne-fin.colonne);
	//cout<<"h="<<h<<" l="<<l<<endl;
	if(l==0) Colorier(debut,1,h,couleur);
	else
	{	if(h==0)
		{	if(debut.colonne<=fin.colonne) Colorier(debut,l,1,couleur);
			else
			{   Coordonnee d;
				d.ligne=debut.ligne;
				d.colonne=debut.colonne-l;
				Colorier(d,l,1,couleur);
			}
		}
		else
		{       if(debut.colonne<=fin.colonne)
				{   if (l>=h)
					{   float i = debut.ligne;
						float r = l/h;
						for (int j = debut.colonne; j <= fin.colonne; j++)
						{   //if(i<=fin.ligne)
							if(i>=0 && i<hauteur && j>=0 && j<largeur)
								image[(int)i][j] = couleur;
							i+=1/r;
						}
					}
					else
					{   float j = debut.colonne;
						float r = h/l;
						for (int i = debut.ligne; i <= fin.ligne; i++)
						{   //if(j<=fin.colonne)
							if(i>=0 && i<hauteur && j>=0 && j<largeur)
								image[i][(int)j] = couleur;
							j+=1/r;
						}
					}
				}
				else
				{   if (l>=h)
					{   float i = debut.ligne;
						float r = l/h;
						for (int j = debut.colonne; j >= fin.colonne; j--)
						{   //if(i<=fin.ligne)
							if(i>=0 && i<hauteur && j>=0 && j<largeur)
								image[(int)i][j] = couleur;
							i+=1/r;
						}
					}
					else
					{   float j = debut.colonne;
						float r = h/l;
						for (int i = debut.ligne; i <= fin.ligne; i++)
						{   //if(j>=fin.colonne)
							if(i>=0 && i<hauteur && j>=0 && j<largeur)
								image[i][(int)j] = couleur;
							j-=1/r;
						}
					}
				}
		}
	}
}
void SNImage::TracerDiagonale(int debutX, int debutY, int finX, int finY, int epaisseur, int couleur)
{   Coordonnee debut={debutY,debutX},fin={finY,finX};
	Pixel couleurPix;
	couleurPix.bleu=(couleur>>16)&255;
	couleurPix.vert=(couleur>>8)&255;
	couleurPix.rouge=couleur&255;
	TracerDiagonale(debut,fin, epaisseur, couleurPix);
}

void SNImage::TracerDiagonale(Coordonnee debut,Coordonnee fin, int epaisseur, Pixel couleur)
{	Coordonnee CDebut=debut,CFin=fin;
	int h=abs(CDebut.ligne-CFin.ligne);
	int l=abs(CDebut.colonne-CFin.colonne);
	if(l>h)
	{	CDebut.ligne-=epaisseur/2;
		CFin.ligne-=epaisseur/2;
		for(int k=0;k<epaisseur;k++)
		{	TracerDiagonaleUnPixel(CDebut,CFin,couleur);
			CDebut.ligne++;
			CFin.ligne++;
		}
	}
	else
	{   CDebut.colonne-=epaisseur/2;
		CFin.colonne-=epaisseur/2;
		for(int k=0;k<epaisseur;k++)
		{	TracerDiagonaleUnPixel(CDebut,CFin,couleur);
			CDebut.colonne++;
			CFin.colonne++;
		}
	}
}
void SNImage::TracerCercleUnPixel(Coordonnee centre, int rayon, Pixel couleur)
{   for(int angle=0; angle<3600; angle++)
	{	int i=rayon*sin(angle*M_PI/1800)+centre.ligne;
		int j=rayon*cos(angle*M_PI/1800)+centre.colonne;
		if(i>=0 && i<hauteur && j>=0 && j<largeur) image[i][j]=couleur;
	}
}
void SNImage::TracerCercle(int centreX, int centreY, int rayon, int epaisseur, int couleur)
{   Coordonnee centre={centreY,centreX};
	Pixel couleurPix;
	couleurPix.bleu=(couleur>>16)&255;
	couleurPix.vert=(couleur>>8)&255;
	couleurPix.rouge=couleur&255;
	TracerCercle(centre, rayon, epaisseur, couleurPix);
}
void SNImage::TracerCercle(Coordonnee centre, int rayon, int epaisseur, Pixel couleur)
{   int Rmax=rayon+epaisseur/2;
	for(int k=0;k<epaisseur;k++)
	{	TracerCercleUnPixel(centre, Rmax--, couleur);
	}
}
void SNImage::Dessiner7Segments(int x, int y,int taille,int epaisseur,int couleur,string message)
{   Coordonnee coord={y,x};
	Pixel couleurPix;
	couleurPix.bleu=(couleur>>16)&255;
	couleurPix.vert=(couleur>>8)&255;
	couleurPix.rouge=couleur&255;
	Dessiner7Segments(coord, taille, epaisseur, couleurPix, message);
}
void SNImage::Dessiner11Segments(int x, int y,int taille,int epaisseur,int couleur,string message)
{   Coordonnee coord={y,x};
	Pixel couleurPix;
	couleurPix.bleu=(couleur>>16)&255;
	couleurPix.vert=(couleur>>8)&255;
	couleurPix.rouge=couleur&255;
	Dessiner11Segments(coord, taille, epaisseur, couleurPix, message);
}
