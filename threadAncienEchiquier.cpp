//---------------------------------------------------------------------------

#include <System.hpp>
#pragma hdrstop

#include "threadAncienEchiquier.h"
#include "visuel.h"
#include <Vcl.Imaging.jpeg.hpp>
#pragma package(smart_init)
//---------------------------------------------------------------------------

//   Important : Les m�thodes et les propri�t�s des objets de la VCL peuvent seulement �tre
//   utilis�es dans une m�thode appel�e avec Synchronize, par exemple :
//
//      Synchronize(&UpdateCaption);
//
//   o� UpdateCaption pourrait ressembler � :
//
//      void __fastcall thPosition::UpdateCaption()
//      {
//        Form1->Caption = "Mis � jour dans un thread";
//      }
//---------------------------------------------------------------------------

__fastcall thPosition::thPosition(bool CreateSuspended)
	: TThread(CreateSuspended)
{
}
//---------------------------------------------------------------------------
void __fastcall thPosition::Execute()
{
	Form1->monEchiquier.SauvegarderEchiquierBMP("Web\\Position.bmp");
	TJPEGImage *imagejpg = new TJPEGImage;
	Form1->Image66->Picture->LoadFromFile("Web\\Position.bmp");
	imagejpg->Assign(Form1->Image66->Picture->Bitmap);
	imagejpg->SaveToFile("Web\\Position.jpg");
	//---- Placer le code du thread ici ----
}
//---------------------------------------------------------------------------
