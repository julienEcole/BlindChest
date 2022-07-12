//---------------------------------------------------------------------------

#ifndef threadAncienEchiquierH
#define threadAncienEchiquierH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
//---------------------------------------------------------------------------
class thPosition : public TThread
{
private:
protected:
	void __fastcall Execute();
public:
	__fastcall thPosition(bool CreateSuspended);
};
//---------------------------------------------------------------------------
#endif
