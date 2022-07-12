
#ifndef ServeurHTTPDIH
#define ServeurHTTPDIH
#include <string>
#include <string.h>
#include <fstream>
#include <sstream>
#include "SNServeurTcpMonoClient.h"
using namespace std;
class SNServeurHTTP
{   private:
		SNServeurTcpMonoClient monServeurTcp;
		string donneeTXT, historiqueLOG;
		string indexHTML;
		string httpOK, keepAlive,finHTTP,erreur404;
		string dernierMessage;
		bool cestUneDemande,cestUneImage;
		string nomRessourceDemandee;
		string extensionDemandee;
		string nomVariableJS;
		char * bufferRessourceDemandee;
		int tailleRessourceDemandee;
		int tailleMAXRessource;
		string texteRecu;
		string repertoire;
		string LireLaDate();
	public:
		SNServeurHTTP();
		void ModifierRepertoireWeb(string rep);
		void EcrireDonneeTxt(string texte);	//texte correspondant à la ressource data.txt destinée à envoyer des données au navigateur
		void EcrireDonneeTxtSansAccents(string texte);
		void ChargerDernierMessage(string texte);
		int AnalyserGET();	  // 0 GET non trouvé, 1 Ressource demandée, 2 Valeur reçue
		bool CestUneDemande();
		string DernierMessage();
		string NomRessourceDemandee();
		string ExtensionDemandee();
		char * BufferRessourceDemandee();
		int TailleRessourceDemandee();
		void LibererBuffer();
		string NomVariableJS();
		void ModifierNomVariableJS(string nomVariable);
		string TexteRecu();
		void ModifierTailleMAXRessource(int taille);
		void ModifierDonneeTXT(string nomFichier){donneeTXT=nomFichier;};
		void ModifierHistoriqueLOG(string nomFichier){historiqueLOG=nomFichier;};
		string SansAccents(string s);
		void MettreEnEcouteSurLePort(int port);
		void ArreterLeServeur();
		string AttendreRequetteHTTP(string repertoireRessourcesWeb);
};
#endif
