#include "SNServeurHTTP.h"
#include <iostream>
using namespace std;

string SNServeurHTTP::LireLaDate()
{   time_t rawtime;
	struct tm * timeinfo;
	char buffer[80];
	time (&rawtime);
	timeinfo = localtime(&rawtime);
	strftime(buffer,80,"%a,%d %b %Y %H:%M:%S GMT",timeinfo);
	std::string str(buffer);
	return str;
}
string SNServeurHTTP::SansAccents(string s)
{    for(int i=0;i<s.length();i++)
	 {	if(s[i]=='é'||s[i]=='è'||s[i]=='ê'||s[i]=='ë') s[i]='e';
		if(s[i]=='à'||s[i]=='â') s[i]='a';
		if(s[i]=='î'||s[i]=='ï') s[i]='i';
		if(s[i]=='ù'||s[i]=='û') s[i]='u';
		if(s[i]=='ô'||s[i]=='ö') s[i]='o';
		if(s[i]=='ÿ') s[i]='y';
	 }	return s;
}
SNServeurHTTP::SNServeurHTTP()
{   repertoire="";
	donneeTXT="data.txt";
	indexHTML="index.html";
	httpOK="HTTP/1.0 200 OK\r\nDate: "+LireLaDate()+"\r\nServer: SNIR\r\nContent-length: ";
	keepAlive="\r\nkeep-Alive: timeout=5, max=100\r\nContent-Type: text/";
	finHTTP="\r\n\r\n";
	erreur404="HTTP/1.0 404 Not Found\r\n\r\n";
	tailleRessourceDemandee=0;
	cestUneDemande=true;
	cestUneImage=false;
	nomVariableJS="envoiValeur";
	tailleMAXRessource=500000;
}
void SNServeurHTTP::ModifierRepertoireWeb(string rep)
{   repertoire=rep;
}

void SNServeurHTTP::EcrireDonneeTxt(string texte)
{	ofstream f;
	f.open((repertoire+"\\"+donneeTXT).c_str());
	f<<texte;
	f.close();
}
void SNServeurHTTP::EcrireDonneeTxtSansAccents(string texte)
{	ofstream f;
	char d[1000]; strcpy(d,repertoire.c_str()); strcat(d,donneeTXT.c_str()); d[donneeTXT.length()-4]=0; strcat(d,"_.txt");
	f.open(d);
	f<<SansAccents(texte);
	f.close();
}
void SNServeurHTTP::ChargerDernierMessage(string texte)
{   dernierMessage=texte;
}
string SNServeurHTTP::DernierMessage()
{   return dernierMessage;
}

int SNServeurHTTP::AnalyserGET()  	  // 0 GET non trouvé, 1 Ressource demandée, 2 Valeur reçue
{	int numDepart = dernierMessage.find("GET ");
	if(numDepart != string::npos)
	{       int numFin = dernierMessage.find("HTTP");
			//envoi de la page index.html
			if(( numFin-1-(numDepart+5) == 0)||(dernierMessage.find("GET /?")!= string::npos))
			{       int debutTexteRecu=dernierMessage.find(nomVariableJS);
					nomRessourceDemandee = "index.html";
					if(debutTexteRecu==string::npos)
					{	cestUneDemande=true;
					}
					else
					{   cestUneDemande=false;
						//cout<<"Envoi de donnees"<<endl;
						int finTexteRecu=dernierMessage.find(" HTTP/");
						//ShowMessage(dernierMessage.c_str());
						if(finTexteRecu!=string::npos)
						{   texteRecu=dernierMessage.substr(debutTexteRecu+nomVariableJS.length()+1,finTexteRecu-debutTexteRecu-12);
						}
					}
			}
			else
			{       cestUneDemande=true;
					nomRessourceDemandee = dernierMessage.substr(numDepart+5, numFin-1-(numDepart+5));
					int positionPoint = nomRessourceDemandee.find(".");
					int positionEt = nomRessourceDemandee.find("&");//-1;
					if (positionEt <= positionPoint) { positionEt = nomRessourceDemandee.length();}
					nomRessourceDemandee =  nomRessourceDemandee.substr(0,positionEt);
			}
			int positionPoint = nomRessourceDemandee.find(".");
			extensionDemandee = nomRessourceDemandee.substr(positionPoint+1, nomRessourceDemandee.length() -positionPoint);
			stringstream httpOKetLg; ifstream fichier;
			char *octets;
			bufferRessourceDemandee=new char [tailleMAXRessource];
			octets=new char [tailleMAXRessource];
			int i=0,j,lg,finentete;
			cestUneImage=!((extensionDemandee == "html") || (extensionDemandee == "css") || (extensionDemandee == "js") || (extensionDemandee == "txt") || (extensionDemandee == "log"));
			nomRessourceDemandee=nomRessourceDemandee;
			if(!cestUneImage)
			{
				fichier.open((repertoire+"\\"+nomRessourceDemandee).c_str());
			}
			else
			{       fichier.open((repertoire+"\\"+nomRessourceDemandee).c_str(),std::fstream::binary);
			}
			if(fichier.is_open())
			{
					cout << "Ouverture du fichier reussie" << endl;
					while (!fichier.eof())   octets[i++]=fichier.get();
					lg=i-1;
					fichier.close();
					if(!cestUneImage)
					{       httpOKetLg<<httpOK<<lg<<"\r\nkeep-Alive: timeout=5, max=100\r\nContent-Type: text/"<<extensionDemandee<<"\r\n\r\n";
					}
					else
					{       httpOKetLg<<httpOK<<lg<<"\r\nkeep-Alive: timeout=5, max=100\r\nContent-Type: image/"<<extensionDemandee<<"\r\n\r\n";
					}
					strcpy(bufferRessourceDemandee,(httpOKetLg.str()).c_str());
					finentete=strlen(bufferRessourceDemandee);
					for(j=0;j<lg;j++)bufferRessourceDemandee[finentete+j]=octets[j];
					tailleRessourceDemandee=finentete+lg;
			}
			else
			{
				cout << "Ouverture du fichier impossible" << endl;
				strcpy(bufferRessourceDemandee,erreur404.c_str());
					tailleRessourceDemandee=strlen(bufferRessourceDemandee);
			}
			delete[] octets;
			if(cestUneDemande) return 1;
			return 2;
	}        //reste à gérer CestUneDemande + extraire données recues
	return 0;
}

bool SNServeurHTTP::CestUneDemande()
{   return cestUneDemande;
}
string SNServeurHTTP::NomRessourceDemandee()
{   return nomRessourceDemandee;
}
string SNServeurHTTP::ExtensionDemandee()
{   return extensionDemandee;
}
char * SNServeurHTTP::BufferRessourceDemandee()
{   return bufferRessourceDemandee;
}
int SNServeurHTTP::TailleRessourceDemandee()
{   return tailleRessourceDemandee;
}
void SNServeurHTTP::LibererBuffer()
{   delete[] bufferRessourceDemandee;
}
string SNServeurHTTP::TexteRecu()
{   return texteRecu;
}
string SNServeurHTTP::NomVariableJS()
{	return nomVariableJS;
}
void SNServeurHTTP::ModifierNomVariableJS(string nomVariable)
{	nomVariableJS=nomVariable;
}
void SNServeurHTTP::ModifierTailleMAXRessource(int taille)
{   tailleMAXRessource=taille;
}
void SNServeurHTTP::MettreEnEcouteSurLePort(int port)
{	monServeurTcp.Initialisation();
	monServeurTcp.MettreEnEcouteSurLePort(port);
}
void SNServeurHTTP::ArreterLeServeur()
{	monServeurTcp.ArreterLeServeur();
}

string SNServeurHTTP::AttendreRequetteHTTP(string repertoireRessourcesWeb)
{   monServeurTcp.AttendreUnNouveauClient();
	char message[1501];
	int tailleMessageRecu=monServeurTcp.RecevoirUnMessage(message,1500);
	ModifierRepertoireWeb(repertoireRessourcesWeb);
	ChargerDernierMessage(message);
	//analyse du GET et envoi de la ressource associée
	if(AnalyserGET())	  // 0 GET non trouvé, 1 Ressource demandée, 2 Valeur reçue
	{	char * buffer=BufferRessourceDemandee();
		int taille=TailleRessourceDemandee();
		monServeurTcp.EnvoyerUnMessage(buffer,taille);
		//affichage des informations
//		if(extensionDemandee=="jpg"||extensionDemandee=="txt"||extensionDemandee=="html"||extensionDemandee=="css"||extensionDemandee=="js")
//		{	cout<<"Ressource : "<<nomRessourceDemandee<<endl;
//			cout<<"Extension : "<<extensionDemandee<<endl;
//			cout<<"Taille : "<<taille<<endl;
//		}
//		else
//		{   cout<<"Erreur : "<<buffer<<endl;
//		}
		monServeurTcp.FermerLaCommunicationAvecLeClient();
		//libération de la mémoire
		LibererBuffer();
		if(!CestUneDemande())  // c'est l'envoi d'un message depuis le navigateur
		{   //retour du texte reçu
			return TexteRecu();
		}
	}
	return message;
}
