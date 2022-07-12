//---------------------------------------------------------------------------

#ifndef threadWebH
#define threadWebH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include "SNServeurHTTP.h"
//---------------------------------------------------------------------------
class ThWeb : public TThread
{
private:
	SNServeurHTTP monServeurHTTP;
protected:
	void __fastcall Execute();
public:
	__fastcall ThWeb(bool CreateSuspended);
	__fastcall ~ThWeb();
};
//---------------------------------------------------------------------------
#endif
