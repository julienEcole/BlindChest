//---------------------------------------------------------------------------

#include <System.hpp>
#pragma hdrstop
#include "visuel.h"
#include "threadWeb.h"
#pragma package(smart_init)
//---------------------------------------------------------------------------

//   Important : Les méthodes et les propriétés des objets de la VCL peuvent seulement être
//   utilisées dans une méthode appelée avec Synchronize, par exemple :
//
//      Synchronize(&UpdateCaption);
//
//   où UpdateCaption pourrait ressembler à :
//
//      void __fastcall ThWeb::UpdateCaption()
//      {
//        Form1->Caption = "Mis à jour dans un thread";
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

