//---------------------------------------------------------------------------

#ifndef JoueurH
#define JoueurH
//---------------------------------------------------------------------------

class Joueur
{   private:
	bool trait;
	int minutes;
	int secondes;
	public:
	Joueur();
	int Minutes(){return minutes;};
	int Secondes(){return secondes;};
	void Initialiser(int m,int s){minutes=m;secondes=s;};
	void Decrementer(){secondes--;if(secondes<0){secondes=59;minutes--;if(minutes<0){secondes=0;minutes=0;}}};
	void MinutesPlusUn(){minutes++;if(minutes>99)minutes=99;};
	void MinutesMoinsUn(){minutes--;if(minutes<1)minutes=1;};
	bool DefaiteAuTemps(){if(minutes==0 && secondes==0) return true; return false;}
	void DonnerLeTrait();
	void RetirerLeTrait();
	bool Trait();
};

#endif
