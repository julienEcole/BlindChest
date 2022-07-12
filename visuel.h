//---------------------------------------------------------------------------

#ifndef visuelH
#define visuelH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.ComCtrls.hpp>
#include <Vcl.ExtCtrls.hpp>
#include <Vcl.Graphics.hpp>
#include <fstream>
#include "Echiquier.h"
#include "classAfficheur\\SNAfficheur.h"
#include "classAfficheur\\SNLigne.h"
#include "Thread.h"
#include "threadAncienEchiquier.h"
#include "threadWeb.h"
#include <Vcl.ExtCtrls.hpp>
#include <Vcl.Graphics.hpp>
#include <Vcl.Buttons.hpp>
#include <Vcl.ComCtrls.hpp>
//---------------------------------------------------------------------------
class TForm1 : public TForm
{
__published:	// Composants gérés par l'EDI
	TImage *Image1;
	TImage *Image2;
	TImage *Image3;
	TImage *Image4;
	TImage *Image5;
	TImage *Image6;
	TImage *Image7;
	TImage *Image8;
	TImage *Image9;
	TImage *Image10;
	TImage *Image11;
	TImage *Image12;
	TImage *Image13;
	TImage *Image14;
	TImage *Image15;
	TImage *Image16;
	TImage *Image17;
	TImage *Image18;
	TImage *Image19;
	TImage *Image20;
	TImage *Image21;
	TImage *Image22;
	TImage *Image23;
	TImage *Image24;
	TImage *Image25;
	TImage *Image26;
	TImage *Image27;
	TImage *Image28;
	TImage *Image29;
	TImage *Image30;
	TImage *Image31;
	TImage *Image32;
	TImage *Image33;
	TImage *Image34;
	TImage *Image35;
	TImage *Image36;
	TImage *Image37;
	TImage *Image38;
	TImage *Image39;
	TImage *Image40;
	TImage *Image41;
	TImage *Image42;
	TImage *Image43;
	TImage *Image44;
	TImage *Image45;
	TImage *Image46;
	TImage *Image47;
	TImage *Image48;
	TImage *Image49;
	TImage *Image50;
	TImage *Image51;
	TImage *Image52;
	TImage *Image53;
	TImage *Image54;
	TImage *Image55;
	TImage *Image56;
	TImage *Image57;
	TImage *Image58;
	TImage *Image59;
	TImage *Image60;
	TImage *Image61;
	TImage *Image62;
	TImage *Image63;
	TImage *Image64;
	TImage *Image65;
	TRadioButton *RadioButton1;
	TRadioButton *RadioButton2;
	TRadioButton *RadioButton3;
	TRadioButton *RadioButton4;
	TTimer *Timer1;
	TLabel *Label1;
	TLabel *Label2;
	TButton *Button1;
	TButton *Button2;
	TButton *Button3;
	TEdit *Edit1;
	TCheckBox *CheckBox1;
	TCheckBox *CheckBox2;
	TCheckBox *CheckBox3;
	TImage *Image66;
	TTrackBar *TrackBarTime;
	TShape *ShapeBegin;
	TShape *ShapeEnd;
	TLabel *LabelInfoJoue;
	TLabel *LabelHistoriqueAncienCoup;
	TButton *Button4;
	void __fastcall AccepterPiece(TObject *Sender, TObject *Source, int X, int Y, TDragState State,
		  bool &Accept);
	void __fastcall LacherPiece(TObject *Sender, TObject *Source, int X, int Y);
	void __fastcall Timer1Timer(TObject *Sender);
	void __fastcall ChangerMode(TObject *Sender);
	void __fastcall Connexion(TObject *Sender);
	void __fastcall NewGame(TObject *Sender);
	void __fastcall ChangerVuePiece(TObject *Sender);
	void __fastcall ChangeTimeLeft(TObject *Sender);
	void __fastcall DemandePartieNul(TObject *Sender);


private:	// Déclarations utilisateur
public:		// Déclarations utilisateur
	//les fonctions
	__fastcall TForm1(TComponent* Owner);
	bool AttendreCoupDistant();
	//les variables
	thClientServeur *threadClientServeur;
	thPosition *threadPosition;
	ThWeb *threadWeb;
	int mode, portHTTP;
	Echiquier monEchiquier;
	TImage * laCase[8][8];
	void MiseAJourEchiquierIHM();
	Joueur JBlanc, JNoir;
	bool JAiLesBlancs, envoyerCoup;
	bool aveugle;
	SNAfficheur monAfficheur;
	SNLigne maLigne;

};
//---------------------------------------------------------------------------
extern PACKAGE TForm1 *Form1;
//---------------------------------------------------------------------------
#endif
