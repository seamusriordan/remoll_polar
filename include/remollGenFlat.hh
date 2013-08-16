#ifndef __REMOLLGENFLAT_HH 
#define __REMOLLGENFLAT_HH 
/*!
 * Flat event generator
 *
 * Seamus Riordan
 * August 9, 2013
 *
*/

#include "remollVEventGen.hh"

class remollGenFlat : public remollVEventGen {
    public:
	 remollGenFlat();
	~remollGenFlat();

    private:
	void SamplePhysics(remollVertex *, remollEvent *);

	virtual void SetEmin( double emin ){ fE_min = emin; }
	virtual void SetEmax( double emax ){ fE_max = emax; }
};

#endif//__REMOLLGENFLAT_HH 
