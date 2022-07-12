//---------------------------------------------------------------------------

#pragma hdrstop

#include "Joueur.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)

Joueur::Joueur()
{	trait=0;
}
void Joueur::DonnerLeTrait()
{	trait=1;
}
void Joueur::RetirerLeTrait()
{   trait=0;
}
bool Joueur::Trait()
{   return trait;
}

