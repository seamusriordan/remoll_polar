#ifndef __REMOLLGENHIGHZDIS_HH 
#define __REMOLLGENHIGHZDIS_HH 
/*!
 * DIS event generator
 *
 * Seamus Riordan
 * August 9, 2013
 *
*/

#include "remollVEventGen.hh"


class remollGenHighZDIS : public remollVEventGen {
    public:
	 remollGenHighZDIS();
	~remollGenHighZDIS();

    private:
	void SamplePhysics(remollVertex *, remollEvent *);

	virtual void SetEmin( double emin ){ fE_min = emin; }
	virtual void SetEmax( double emax ){ fE_max = emax; }

};

#endif//__REMOLLGENDIS_HH 
