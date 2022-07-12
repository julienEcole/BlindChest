#pragma hdrstop
#pragma argsused

#ifdef _WIN32
#include <tchar.h>
#else
  typedef char _TCHAR;
  #define _tmain main
#endif

#include <stdio.h>
#include <iostream>
#include "Echiquier.h"
#include "SNClientTCP.h"
#include "SNServeurTcpMonoClient.h"
int _tmain(int argc, _TCHAR* argv[])
{   int idep,jdep,iarr,jarr;
	int mode;
	bool jaiLesBlancs=true,abandon=false,coupIllegal=false;
	Echiquier monEchiquier;
	SNClientTCP modeClient;
	SNServeurTcpMonoClient modeServeur;
	//Saisie du mode
	cout<<"Partie locale (1), serveur (2), client (3) ? ";
	cin>>mode;
	//Affichage
	if(mode==2) cout<<"Mode serveur"<<endl<<endl;
	else if(mode==3) cout<<"Mode client"<<endl<<endl;
	else {mode=1; cout<<"Partie Locale"<<endl<<endl;}
	//Lancement du serveur
	if(mode==2)
	{	char message[151];
		modeServeur.Initialisation();
		modeServeur.MettreEnEcouteSurLePort(1066);
		cout<<endl<<"Ecoute sur le port 1066..."<<endl;
		modeServeur.AttendreUnNouveauClient();
		strcpy(message,"Quelle est votre couleur ?");
		modeServeur.EnvoyerUnMessage(message,strlen(message)+1);     //+1 pour 0 final
		modeServeur.RecevoirUnMessage(message, 150);
		if(message[0]=='N' || message[0]=='n')
		{   cout<<endl<<"Vous avez les blancs..."<<endl;
			jaiLesBlancs=true;
		}
		else
		{	cout<<endl<<"Vous avez les noirs..."<<endl;
			jaiLesBlancs=false;
		}
	}
	if(mode==3)
	{   char message[151],IP[20];
		cout<<"IP du serveur ? ";cin>>IP;
		modeClient.SeConnecterAUnServeur(IP,1066);
		modeClient.Recevoir(message,150);
		cout<<endl<<message<<endl;
		cin>>message;
		modeClient.Envoyer(message,strlen(message));
		if(message[0]=='N' || message[0]=='n')
		{	cout<<endl<<"Vous avez les noirs..."<<endl;
			jaiLesBlancs=false;
		}
		else
		{	cout<<endl<<"Vous avez les blancs..."<<endl;
			jaiLesBlancs=true;
		}
	}
	do
	{
	cout<<"Trait aux "<<monEchiquier.Trait()<<endl;
	cout<<monEchiquier.VisualiserEchiquier()<<endl;
//	cout<<monEchiquier.Les64Caracteres()<<endl;
//	monEchiquier.ChargerEchiquierComplet((char*)monEchiquier.Les64Caracteres().c_str());
//	cout<<monEchiquier.VisualiserEchiquier()<<endl;

	if((jaiLesBlancs&&monEchiquier.Trait()=="Blancs")||(!jaiLesBlancs&&monEchiquier.Trait()=="Noirs")||mode==1)
	{   do
		{	cout<<"Votre deplacement: ex 0 0 4 5 (piece en 0,0 vers 4,5) -1 pour abandonner : ";
			cin>>idep;
			if(idep==-1)
			{   //envoi abandon
				if(mode==2) modeServeur.EnvoyerUnMessage("Abandon !",10);
				if(mode==3) modeClient.Envoyer("Abandon !",10);
				abandon=true; break;
			}
			cin>>jdep>>iarr>>jarr;
			if(monEchiquier.EstUnePieceNoire(idep,jdep)) cout<<"piece noire"<<endl;
			if(monEchiquier.EstUnePieceBlanche(idep,jdep)) cout<<"piece blanche"<<endl;
			if(monEchiquier.EstVide(idep,jdep)) cout<<"case vide"<<endl;
			//promotion
			char piecePromo=' ';
			if ((monEchiquier.Trait()=="Blancs" && monEchiquier.LireCaseEchiquier(idep,jdep)=='P' && iarr==0)
			  ||(monEchiquier.Trait()=="Noirs" && monEchiquier.LireCaseEchiquier(idep,jdep)=='p' && iarr==7))
			{ cout<<"Promotion : D T C ou F ? "; cin>>piecePromo; cout<<endl;
			}
			if(!monEchiquier.Deplacer(idep,jdep,iarr,jarr,piecePromo))
			{	cout<<"coup illegal"<<endl; coupIllegal=true;
			}
			else
			{	coupIllegal=false;
				if(mode==2)
				{	modeServeur.EnvoyerUnMessage((char *)monEchiquier.Les64Caracteres().c_str(),64);
				}
				if(mode==3)
				{   modeClient.Envoyer((char *)monEchiquier.Les64Caracteres().c_str(),64);
				}
			}
		}while(coupIllegal);
	}
	else
	{   //attente du coup adverse
		char message[151];
		if(mode==2) modeServeur.RecevoirUnMessage(message,150);
		if(mode==3) modeClient.Recevoir(message,150);
		if(!strcmp(message,"Abandon !"))
		{   cout<<"Votre adversaire abandonne !"<<endl;
			abandon=true;
		}
		else
		{	monEchiquier.ChargerEchiquierComplet(message);
			monEchiquier.ChangerLeTrait();
		}
	}
	}while(!abandon);
	//Fermeture de la communication
	if(mode==2)
	{	modeServeur.FermerLaCommunicationAvecLeClient();
		modeServeur.ArreterLeServeur();
	}
	cin.get();	cin.get();
	return 0;
}
