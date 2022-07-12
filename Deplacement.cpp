//---------------------------------------------------------------------------

#pragma hdrstop

#include "Deplacement.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
bool Deplacement::ValiderPositionArrivee(int iarr, int jarr)
{       for(int n=0;n<nbPositionArrivee;n++)
                if(iarr==tabPositionArrivee[0][n] && jarr==tabPositionArrivee[1][n])
                        return true;
        return false;
}

void DeplacementTour::CalculerPositionArrivee(int idep,int jdep,Echiquier *PE)
{       int diri[4]={-1,+1,+0,+0};      //direction en ligne
        int dirj[4]={+0,+0,-1,+1};      //direction en colonne
        int d,iarr,jarr;
        bool couleur=0,stop;            //0=blanc
        nbPositionArrivee=0;
        if(PE->LireCaseEchiquier(idep,jdep)=='t' || PE->LireCaseEchiquier(idep,jdep)=='T')
        {    if(PE->LireCaseEchiquier(idep,jdep)=='t') couleur=1;     //noir
             for(d=0;d<4;d++)           //pour les 4 directions
             {       iarr=idep+diri[d]; //une case plus loin que la case de départ
                     jarr=jdep+dirj[d];
                     stop=false;
                     while((iarr>=0 && iarr<8 && jarr>=0 && jarr<8)   //dans l'échiquier
                        &&!(PE->LireCaseEchiquier(iarr,jarr)>=('A'+couleur*32) && PE->LireCaseEchiquier(iarr,jarr)<=('Z'+couleur*32))
                        &&!stop)
                     {  tabPositionArrivee[0][nbPositionArrivee]=iarr;
                        tabPositionArrivee[1][nbPositionArrivee]=jarr;
                        nbPositionArrivee++;
                        if(PE->LireCaseEchiquier(iarr,jarr)!=' ') stop=true;  //une pièce a été rencontrée
                        iarr=iarr+diri[d]; //case suivante
                        jarr=jarr+dirj[d];
                     }
             }
        }
}
void DeplacementFou::CalculerPositionArrivee(int idep,int jdep,Echiquier *PE)
{       int diri[4]={-1,+1,-1,+1};      //direction en ligne
        int dirj[4]={-1,-1,+1,+1};      //direction en colonne
        int d,iarr,jarr;
        bool couleur=0,stop;            //0=blanc
        nbPositionArrivee=0;
        if(PE->LireCaseEchiquier(idep,jdep)=='f' || PE->LireCaseEchiquier(idep,jdep)=='F')
        {    if(PE->LireCaseEchiquier(idep,jdep)=='f') couleur=1;     //noir
             for(d=0;d<4;d++)           //pour les 4 directions
             {       iarr=idep+diri[d]; //une case plus loin que la case de départ
                     jarr=jdep+dirj[d];
                     stop=false;
                     while((iarr>=0 && iarr<8 && jarr>=0 && jarr<8)   //dans l'échiquier
                        &&!(PE->LireCaseEchiquier(iarr,jarr)>=('A'+couleur*32) && PE->LireCaseEchiquier(iarr,jarr)<=('Z'+couleur*32))
                        &&!stop)
                     {  tabPositionArrivee[0][nbPositionArrivee]=iarr;
                        tabPositionArrivee[1][nbPositionArrivee]=jarr;
                        nbPositionArrivee++;
                        if(PE->LireCaseEchiquier(iarr,jarr)!=' ') stop=true;  //une pièce a été rencontrée
                        iarr=iarr+diri[d]; //case suivante
                        jarr=jarr+dirj[d];
                     }
             }
        }
}
void DeplacementDame::CalculerPositionArrivee(int idep,int jdep,Echiquier *PE)
{       int diri[8]={-1,+1,+0,+0,-1,+1,-1,+1};      //direction en ligne
        int dirj[8]={+0,+0,-1,+1,-1,-1,+1,+1};      //direction en colonne
        int d,iarr,jarr;
        bool couleur=0,stop;            //0=blanc
        nbPositionArrivee=0;
        if(PE->LireCaseEchiquier(idep,jdep)=='d' || PE->LireCaseEchiquier(idep,jdep)=='D')
        {    if(PE->LireCaseEchiquier(idep,jdep)=='d') couleur=1;     //noir
             for(d=0;d<8;d++)           //pour les 8 directions
             {       iarr=idep+diri[d]; //une case plus loin que la case de départ
                     jarr=jdep+dirj[d];
                     stop=false;
                     while((iarr>=0 && iarr<8 && jarr>=0 && jarr<8)   //dans l'échiquier
                        &&!(PE->LireCaseEchiquier(iarr,jarr)>=('A'+couleur*32) && PE->LireCaseEchiquier(iarr,jarr)<=('Z'+couleur*32))
                        &&!stop)
                     {  tabPositionArrivee[0][nbPositionArrivee]=iarr;
                        tabPositionArrivee[1][nbPositionArrivee]=jarr;
                        nbPositionArrivee++;
                        if(PE->LireCaseEchiquier(iarr,jarr)!=' ') stop=true;  //une pièce a été rencontrée
                        iarr=iarr+diri[d]; //case suivante
                        jarr=jarr+dirj[d];
                     }
             }
        }
}
void DeplacementRoi::CalculerPositionArrivee(int idep,int jdep,Echiquier *PE)
{       int sauti[10]={-1,-1,-1,+0,+0,+1,+1,+1,+0,+0};
        int sautj[10]={-1,+0,+1,-1,+1,-1,+0,+1,+2,-2};
        int n,iarr,jarr;
        bool couleur=0;//0=blanc
        nbPositionArrivee=0;
        if(PE->LireCaseEchiquier(idep,jdep)=='r' || PE->LireCaseEchiquier(idep,jdep)=='R')
        {    if(PE->LireCaseEchiquier(idep,jdep)=='r') couleur=1;
             for(n=0;n<10;n++)
             {       iarr=idep+sauti[n];
                     jarr=jdep+sautj[n];
                     if(iarr>=0 && iarr<8 && jarr>=0 && jarr<8)//dans l'échiquier
                     {  if((n<8 && !(PE->LireCaseEchiquier(iarr,jarr)>=('A'+couleur*32) && PE->LireCaseEchiquier(iarr,jarr)<=('Z'+couleur*32)))
                         || (n==8 && jdep==4 && iarr==(7-couleur*7) && PE->LireCaseEchiquier(iarr,jarr)==' ' && PE->LireCaseEchiquier(iarr,jarr-1)==' '//cas du petit roque
                             && PE->LireCaseEchiquier(iarr,jarr+1)=='T'+couleur*32)
                         || (n==9 && jdep==4 && iarr==(7-couleur*7) && PE->LireCaseEchiquier(iarr,jarr)==' ' && PE->LireCaseEchiquier(iarr,jarr+1)==' '//cas du grand roque
                             && PE->LireCaseEchiquier(iarr,jarr-1)==' ' && PE->LireCaseEchiquier(iarr,jarr-2)=='T'+couleur*32))
                        {       tabPositionArrivee[0][nbPositionArrivee]=iarr;
                                tabPositionArrivee[1][nbPositionArrivee]=jarr;
                                nbPositionArrivee++;
                        }
                     }
             }
        }
}
void DeplacementCavalier::CalculerPositionArrivee(int idep,int jdep,Echiquier *PE)
{       int sauti[8]={-2,-2,-1,-1,+1,+1,+2,+2};
        int sautj[8]={-1,+1,-2,+2,-2,+2,-1,+1};
        int n,iarr,jarr;
        bool couleur=0;//0=blanc
        nbPositionArrivee=0;
        if(PE->LireCaseEchiquier(idep,jdep)=='c' || PE->LireCaseEchiquier(idep,jdep)=='C')
        {    if(PE->LireCaseEchiquier(idep,jdep)=='c') couleur=1;
             for(n=0;n<8;n++)
             {
                     iarr=idep+sauti[n];
                     jarr=jdep+sautj[n];
                     if(iarr>=0 && iarr<8 && jarr>=0 && jarr<8)//dans l'échiquier
                     {  if(!(PE->LireCaseEchiquier(iarr,jarr)>=('A'+couleur*32) && PE->LireCaseEchiquier(iarr,jarr)<=('Z'+couleur*32)))
                        {       tabPositionArrivee[0][nbPositionArrivee]=iarr;
                                tabPositionArrivee[1][nbPositionArrivee]=jarr;
                                nbPositionArrivee++;
                        }
                     }
             }
        }
}
void DeplacementPion::CalculerPositionArrivee(int idep,int jdep,Echiquier *PE)
{       int Desti[4]={-1,-2,-1,-1};
        int Destj[4]={+0,+0,-1,+1};
        int n,iarr,jarr;
        bool couleur=0;//0=blanc
        nbPositionArrivee=0;
        if(PE->LireCaseEchiquier(idep,jdep)=='p' || PE->LireCaseEchiquier(idep,jdep)=='P')
        {    if(PE->LireCaseEchiquier(idep,jdep)=='p') couleur=1;
             for(n=0;n<4;n++)
             {       if(couleur) Desti[n]*=-1;
                     iarr=idep+Desti[n];
                     jarr=jdep+Destj[n];
                     if(iarr>=0 && iarr<8 && jarr>=0 && jarr<8)//dans l'échiquier
                     {  if(  (n==0 && PE->LireCaseEchiquier(iarr,jarr)==' ')
                           ||(n==1 && PE->LireCaseEchiquier(iarr,jarr)==' ' && PE->LireCaseEchiquier(idep+Desti[0],jdep+Destj[0])==' '
                                   && idep==(6-couleur*5))
                           ||(Destj[n]!=0 && (PE->LireCaseEchiquier(iarr,jarr)>=('a'-couleur*32) && PE->LireCaseEchiquier(iarr,jarr)<=('z'-couleur*32)))
                           ||(Destj[n]!=0 && (PE->LireCaseEchiquier(idep,jarr)>=('a'-couleur*32) && PE->LireCaseEchiquier(idep,jarr)<=('z'-couleur*32))//Prise en passant
										  && PE->LireCaseEchiquier(iarr,jarr)==' ' && PE->LireCaseEchiquier(1+couleur*5,jarr)==' ' && iarr==(2+couleur*3)))
                        {       tabPositionArrivee[0][nbPositionArrivee]=iarr;
                                tabPositionArrivee[1][nbPositionArrivee]=jarr;
                                nbPositionArrivee++;
                        }
                     }
             }
        }
}

