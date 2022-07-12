//---------------------------------------------------------------------------

#ifndef ThreadH
#define ThreadH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include "SNClientTCP.h"
#include "SNServeurTcpMonoClient.h"
//---------------------------------------------------------------------------
class thClientServeur : public TThread
{
private:
protected:
	void __fastcall Execute();
public:
	__fastcall ~thClientServeur();
	String information;
	SNClientTCP modeClient;
	SNServeurTcpMonoClient modeServeur;
	__fastcall thClientServeur(bool CreateSuspended);
	void __fastcall MiseAJourInterfacePrincipale();
};
//---------------------------------------------------------------------------
#endif
