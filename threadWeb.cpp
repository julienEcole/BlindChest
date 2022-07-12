//---------------------------------------------------------------------------

#include <System.hpp>
#pragma hdrstop
#include "visuel.h"
#include "threadWeb.h"
#pragma package(smart_init)
//---------------------------------------------------------------------------

//   Important : Les m�thodes et les propri�t�s des objets de la VCL peuvent seulement �tre
//   utilis�es dans une m�thode appel�e avec Synchronize, par exemple :
//
//      Synchronize(&UpdateCaption);
//
//   o� UpdateCaption pourrait ressembler � :
//
//      void __fastcall ThWeb::UpdateCaption()
//      {
//        Form1->Caption = "Mis � jour dans un thread";
//      }
//---------------------------------------------------------------------------

__fastcall ThWeb::ThWeb(bool CreateSuspended)
	: TThread(CreateSuspended)
{
}
//---------------------------------------------------------------------------
void __fastcall ThWeb::Execute()
{
	//---- Placer le code du thread ici ----
	monServeurHTTP.MettreEnEcouteSurLePort(Form1->portHTTP);
	while (true){
    	monServeurHTTP.AttendreRequetteHTTP("Web");
	}
}
//---------------------------------------------------------------------------
__fastcall ThWeb::~ThWeb(){
	monServeurHTTP.ArreterLeServeur();
}
//---------------------------------------------------------------------------

