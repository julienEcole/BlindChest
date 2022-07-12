//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "visuel.h"
#include "Thread.h"
#include "ReglesEtNotation.h"


using namespace std;

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm1 *Form1;
//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
	: TForm(Owner)
{
	laCase[0][0]=Image1; laCase[0][1]=Image2; laCase[0][2]=Image3; laCase[0][3]=Image4;
	laCase[0][4]=Image5; laCase[0][5]=Image6; laCase[0][6]=Image7; laCase[0][7]=Image8;
	laCase[1][0]=Image9; laCase[1][1]=Image10; laCase[1][2]=Image11; laCase[1][3]=Image12;
	laCase[1][4]=Image13; laCase[1][5]=Image14; laCase[1][6]=Image15; laCase[1][7]=Image16;
	laCase[2][0]=Image17; laCase[2][1]=Image18; laCase[2][2]=Image19; laCase[2][3]=Image20;
	laCase[2][4]=Image21; laCase[2][5]=Image22; laCase[2][6]=Image23; laCase[2][7]=Image24;
	laCase[3][0]=Image25; laCase[3][1]=Image26; laCase[3][2]=Image27; laCase[3][3]=Image28;
	laCase[3][4]=Image29; laCase[3][5]=Image30; laCase[3][6]=Image31; laCase[3][7]=Image32;
	laCase[4][0]=Image33; laCase[4][1]=Image34; laCase[4][2]=Image35; laCase[4][3]=Image36;
	laCase[4][4]=Image37; laCase[4][5]=Image38; laCase[4][6]=Image39; laCase[4][7]=Image40;
	laCase[5][0]=Image41; laCase[5][1]=Image42; laCase[5][2]=Image43; laCase[5][3]=Image44;
	laCase[5][4]=Image45; laCase[5][5]=Image46; laCase[5][6]=Image47; laCase[5][7]=Image48;
	laCase[6][0]=Image49; laCase[6][1]=Image50; laCase[6][2]=Image51; laCase[6][3]=Image52;
	laCase[6][4]=Image53; laCase[6][5]=Image54; laCase[6][6]=Image55; laCase[6][7]=Image56;
	laCase[7][0]=Image57; laCase[7][1]=Image58; laCase[7][2]=Image59; laCase[7][3]=Image60;
	laCase[7][4]=Image61; laCase[7][5]=Image62; laCase[7][6]=Image63; laCase[7][7]=Image64;	MiseAJourEchiquierIHM();	monEchiquier.JBlancs()->Initialiser(5,0);	monEchiquier.JNoirs()->Initialiser(5,0);	mode = 1;	envoyerCoup = false;	ifstream fichier;	fichier.open("Web\\web.ini");	if(fichier.is_open()){		string actual;		fichier >> actual >> portHTTP;		//ShowMessage(portHTTP);				//DEBUG	}	fichier.close();	monAfficheur.ModifierAdresseIPDuServeurUDP("172.20.21.57");	monAfficheur.ModifierPortDuServeurUDP(4321);}

void TForm1::MiseAJourEchiquierIHM(){
	if(threadPosition) delete threadPosition;
	for (int i=0; i<8; i++){
		for (int j=0; j<8; j++){
			if(aveugle){
				laCase[i][j]->Picture->LoadFromFile("Images\\vide.bmp");
			}
			else{
				if(monEchiquier.LireCaseEchiquier(i,j)=='P')
					laCase[i][j]->Picture->LoadFromFile("Images\\pionB.bmp");
				if(monEchiquier.LireCaseEchiquier(i,j)=='p')
					laCase[i][j]->Picture->LoadFromFile("Images\\pionN.bmp");
				if(monEchiquier.LireCaseEchiquier(i,j)==' ')
					laCase[i][j]->Picture->LoadFromFile("Images\\vide.bmp");
				if(monEchiquier.LireCaseEchiquier(i,j)=='T')
					laCase[i][j]->Picture->LoadFromFile("Images\\tourB.bmp");
				if(monEchiquier.LireCaseEchiquier(i,j)=='t')
					laCase[i][j]->Picture->LoadFromFile("Images\\tourN.bmp");
				if(monEchiquier.LireCaseEchiquier(i,j)=='F')
					laCase[i][j]->Picture->LoadFromFile("Images\\fouB.bmp");
				if(monEchiquier.LireCaseEchiquier(i,j)=='f')
					laCase[i][j]->Picture->LoadFromFile("Images\\fouN.bmp");
				if(monEchiquier.LireCaseEchiquier(i,j)=='C')
					laCase[i][j]->Picture->LoadFromFile("Images\\cavB.bmp");
				if(monEchiquier.LireCaseEchiquier(i,j)=='c')
					laCase[i][j]->Picture->LoadFromFile("Images\\cavN.bmp");
				if(monEchiquier.LireCaseEchiquier(i,j)=='D')
					laCase[i][j]->Picture->LoadFromFile("Images\\dameB.bmp");
				if(monEchiquier.LireCaseEchiquier(i,j)=='d')
					laCase[i][j]->Picture->LoadFromFile("Images\\dameN.bmp");
				if(monEchiquier.LireCaseEchiquier(i,j)=='R')
					laCase[i][j]->Picture->LoadFromFile("Images\\roiB.bmp");
				if(monEchiquier.LireCaseEchiquier(i,j)=='r')
					laCase[i][j]->Picture->LoadFromFile("Images\\roiN.bmp");
			}
		}
	}
	if(portHTTP) threadPosition = new thPosition(false);
}

//---------------------------------------------------------------------------
void __fastcall TForm1::AccepterPiece(TObject *Sender, TObject *Source, int X, int Y, TDragState State,
		  bool &Accept)
{
	Accept = 1;
	//peut être pas auy bon endroit
	/*ReglesEtNotation regle;
	accept*/
	//a voir si besoin sup avant

}
//---------------------------------------------------------------------------
void __fastcall TForm1::LacherPiece(TObject *Sender, TObject *Source, int X, int Y)

{
	int idep,jdep,iarr,jarr;
	char piecePromo='D';
	if (Source!=Sender){
		for (int i=0; i<8; i++){
			for (int j=0; j<8; j++){
				if(Source == laCase[i][j]){
					idep = i;
					jdep = j;
					ShapeBegin->Top = laCase[i][j]->Top;
					ShapeBegin->Left = laCase[i][j]->Left;
					ShapeBegin->Width = laCase[i][j]->Width;
					ShapeBegin->Height = laCase[i][j]->Height;
				}
				if(Sender == laCase[i][j]){
					iarr = i;
					jarr = j;
					ShapeEnd->Top = laCase[i][j]->Top;
					ShapeEnd->Left = laCase[i][j]->Left;
					ShapeEnd->Width = laCase[i][j]->Width;
					ShapeEnd->Height = laCase[i][j]->Height;
				}
			}
		}
		if (RadioButton1->Checked)   piecePromo='D';
		if (RadioButton2->Checked)   piecePromo='T';
		if (RadioButton3->Checked)   piecePromo='C';
		if (RadioButton4->Checked)   piecePromo='F';
		if (monEchiquier.Deplacer(idep,jdep,iarr,jarr,piecePromo)){
			if(monEchiquier.JBlancs()->Trait()){
				LabelInfoJoue->Caption = "Au blanc de jouer";
			}
			else{
				LabelInfoJoue->Caption = "Au noir de jouer";
			}
			Timer1->Enabled = true;
			if(mode!=1){
				envoyerCoup = true;
			}
			if(mode!=3){
				threadWeb = new ThWeb(false);
			}
			MiseAJourEchiquierIHM();
			string coupActuel;
			coupActuel = monEchiquier.Notation();   //cette partie sert a mettre a jour l'historique des coups
			if(monEchiquier.JBlancs()->Trait()){
				maLigne.ModifierMessage(coupActuel);
				monAfficheur.EnvoyerLigneEnUDP(maLigne);
				LabelHistoriqueAncienCoup->Caption = (LabelHistoriqueAncienCoup->Caption+'\r'+coupActuel.c_str()); //C moche mais fonctionnel
			}
			//fin partie pour afficher notation
		}
		else{
			LabelInfoJoue->Caption = "Coup Illegal";
		}
	}

}
//---------------------------------------------------------------------------


void __fastcall TForm1::Timer1Timer(TObject *Sender)
{
	if (monEchiquier.JBlancs()->Trait()){
		monEchiquier.JBlancs()->Decrementer();
		Label1->Font->Color = clGrayText;
		Label2->Font->Color = clDefault;
	}
	if (monEchiquier.JNoirs()->Trait()){
		monEchiquier.JNoirs()->Decrementer();
		Label2->Font->Color = clGrayText;
		Label1->Font->Color = clDefault;
	}
	Label1->Caption=(String)monEchiquier.JNoirs()->Minutes() + ":" + (String)monEchiquier.JNoirs()-> Secondes();
	Label2->Caption=(String)monEchiquier.JBlancs()->Minutes() + ":" + (String)monEchiquier.JBlancs()->Secondes();
	}
//---------------------------------------------------------------------------
void __fastcall TForm1::ChangerMode(TObject *Sender)
{
	if(Sender == CheckBox1 && CheckBox1->Checked){
		CheckBox2->Checked = false;
		CheckBox3->Checked = false;
		Edit1->Visible = false;
		Button1->Visible = false;
		mode = 1;
	}
	if(Sender == CheckBox2 && CheckBox2->Checked){
		CheckBox1->Checked = false;
		CheckBox3->Checked = false;
		Edit1->Visible = false;
		Button1->Visible = true;
		mode = 2;
	}
	if(Sender == CheckBox3 && CheckBox3->Checked){
		CheckBox2->Checked = false;
		CheckBox1->Checked = false;
		Edit1->Visible = true;
		Button1->Visible = true;
		mode = 3;
	}
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Connexion(TObject *Sender)
{
	threadClientServeur = new thClientServeur(false);
	Button1->Visible = false;
	CheckBox1->Visible = false;
	if(mode == 2){	CheckBox3->Visible = false;
	}
	if(mode == 3){	CheckBox2->Visible = false;
	}
}
//---------------------------------------------------------------------------
bool TForm1::AttendreCoupDistant(){
	return(!((monEchiquier.Trait()=="Blancs" && JAiLesBlancs) || (monEchiquier.Trait()=="Noirs" && !JAiLesBlancs)));
}
//---------------------------------------------------------------------------



void __fastcall TForm1::NewGame(TObject *Sender)
{
	Form1->monEchiquier.InitialiserEchiquier();
	monEchiquier.JBlancs()->Initialiser(5,0);
	monEchiquier.JNoirs()->Initialiser(5,0);	mode = 1;	envoyerCoup = false;
	Timer1->Enabled = false;
	MiseAJourEchiquierIHM();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::ChangerVuePiece(TObject *Sender)
{
	aveugle = !aveugle;
	MiseAJourEchiquierIHM();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::ChangeTimeLeft(TObject *Sender)
{
	if(Timer1->Enabled == false){
		monEchiquier.JBlancs()->Initialiser(TrackBarTime->Position * 5,00);
		monEchiquier.JNoirs()->Initialiser(TrackBarTime->Position * 5,00);
		Label1->Caption=(String)monEchiquier.JNoirs()->Minutes() + ":" + (String)monEchiquier.JNoirs()-> Secondes();
		Label2->Caption=(String)monEchiquier.JBlancs()->Minutes() + ":" + (String)monEchiquier.JBlancs()->Secondes();
	}
}
//---------------------------------------------------------------------------


void __fastcall TForm1::DemandePartieNul(TObject *Sender)
{
	//TODO
	//creer uun formulaire de question avec demande de l'utilisateur si partie nulle ou non
	//enlever la possibilité a celui qui a demander la partie nulle de le redemander une nouvelle fois
	//Le mieu serait d'ajouter un bool demandePartieNul dans l'objet joueur,
	//et de cacher ce bouton si le bool est true ainsi que de mettre une condition sur cette fonction pour éviter les magouilleur
}
//---------------------------------------------------------------------------

