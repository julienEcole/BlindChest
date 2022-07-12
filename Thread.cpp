//---------------------------------------------------------------------------

#include <System.hpp>
#pragma hdrstop
#include "visuel.h"
#include "Thread.h"
#pragma package(smart_init)
//---------------------------------------------------------------------------

//   Important : Les méthodes et les propriétés des objets de la VCL peuvent seulement être
//   utilisées dans une méthode appelée avec Synchronize, par exemple :
//
//      Synchronize(&UpdateCaption);
//
//   où UpdateCaption pourrait ressembler à :
//
//      void __fastcall thClientServeur::UpdateCaption()
//      {
//        Form1->Caption = "Mis à jour dans un thread";
//      }
//---------------------------------------------------------------------------

__fastcall thClientServeur::thClientServeur(bool CreateSuspended)
	: TThread(CreateSuspended)
{
}
//---------------------------------------------------------------------------
void __fastcall thClientServeur::Execute(){

	//lancement serveur
	char message[151];
	if(Form1->mode == 2){
		modeServeur.Initialisation();
		modeServeur.MettreEnEcouteSurLePort(2022);
		information = "Ecoute sur le port 2022...";
		Synchronize(&MiseAJourInterfacePrincipale);
		modeServeur.AttendreUnNouveauClient();
		strcpy(message,"Quel est votre couleur ?");
		modeServeur.EnvoyerUnMessage(message,strlen(message)+1);
		modeServeur.RecevoirUnMessage(message,150);
		if(message[0] == 'N'||message[0] == 'n'){
			information = "vous avez les blancs...";
			Synchronize(&MiseAJourInterfacePrincipale);
			Form1->JAiLesBlancs = true;
		}
		else{
			information = "vous avez les noirs...";
			Synchronize(&MiseAJourInterfacePrincipale);
			Form1->JAiLesBlancs = false;
		}
	}
	if (Form1->mode==3) {
		char IP[20];
		strcpy(IP,AnsiString(Form1->Edit1->Text).c_str());
		modeClient.SeConnecterAUnServeur(IP,2022);
		modeClient.Recevoir(message,150);
		information=message;
		Synchronize(&MiseAJourInterfacePrincipale);
		modeClient.Envoyer("Blancs", strlen(message));
        if(message[0] == 'N'||message[0] == 'n'){
			information = "vous avez les noirs...";
			Synchronize(&MiseAJourInterfacePrincipale);
			Form1->JAiLesBlancs = false;
		}
		else{
			information = "vous avez les blancs...";
			Synchronize(&MiseAJourInterfacePrincipale);
			Form1->JAiLesBlancs = true;
        }
	}
	while(!Terminated){
		if(Form1->AttendreCoupDistant()){
			information = "Attendre coup distant...";
			Synchronize(&MiseAJourInterfacePrincipale);
			if(Form1->mode==2){
				modeServeur.RecevoirUnMessage(message,150);
			}
			if(Form1->mode==3){
				modeClient.Recevoir(message,150);
			}
			Form1->monEchiquier.ChargerEchiquierComplet(message);
			Form1->monEchiquier.ChangerLeTrait();
			Form1->envoyerCoup = false;
			Synchronize(&MiseAJourInterfacePrincipale);
		}
		else{
			information = "A vous de jouer avec les :";
			if(Form1->JAiLesBlancs){
				information+=" Blancs";
			}
			else{
				information+=" Noirs";
			}
			Synchronize(&MiseAJourInterfacePrincipale);
			while(!Form1->envoyerCoup);
			strcpy(message,(char *)Form1->monEchiquier.Les64Caracteres().c_str());
			if(Form1->mode == 2){
				modeServeur.EnvoyerUnMessage(message,strlen(message)+1);
			}
			if(Form1->mode == 3){
				modeClient.Envoyer(message,strlen(message)+1);
			}
        }
	}
}
//---------------------------------------------------------------------------
void __fastcall thClientServeur::MiseAJourInterfacePrincipale(){
	Form1->Caption = information;
	Form1->MiseAJourEchiquierIHM();
}
//---------------------------------------------------------------------------
__fastcall thClientServeur::~thClientServeur(){
	//fermeture de la connexion
	if(Form1->mode==2){
		modeServeur.FermerLaCommunicationAvecLeClient();
		modeServeur.ArreterLeServeur();
	}
	if (Form1->mode == 3) {
    	modeClient.SeDeconnecter();
	}
}
//---------------------------------------------------------------------------
