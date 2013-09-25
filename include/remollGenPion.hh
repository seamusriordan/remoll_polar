#ifndef __REMOLLGENPION_HH 
#define __REMOLLGENPION_HH 
/*!
 * Pion event generator
 * from Wiser parameterization
 *
 * Seamus Riordan
 * August 16, 2013
 *
*/

#include "remollVEventGen.hh"

class remollGenPion : public remollVEventGen {
    public:
	 remollGenPion();
	~remollGenPion();

	enum Pion_t {kPiPlus, kPiMinus, kPi0};

	void SetPionType(Pion_t t) { fPionType = t; }

	void SetEmin( double emin ){ fE_min=emin; }
	void SetEmax( double emax ){ fE_max=emax; }



    private:
	void SamplePhysics(remollVertex *, remollEvent *);


	Pion_t fPionType;
};

#endif//__REMOLLGENPION_HH 
