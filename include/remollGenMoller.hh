#ifndef __REMOLLGENMOLLER_HH 
#define __REMOLLGENMOLLER_HH 
/*!
 * Moller (ee) event generator
 *
 * Seamus Riordan
 * February 4, 2013
 *
 * Based heavily on previous work from mollersim
*/

#include "remollVEventGen.hh"

class remollGenMoller : public remollVEventGen {
    public:
	 remollGenMoller();
	~remollGenMoller();

    private:
	void SamplePhysics(remollVertex *, remollEvent *);

	virtual void SetThCoM_min( double th ){ fThCoM_min  = th; }
	virtual void SetThCoM_max( double th ){ fThCoM_max  = th; }
	virtual void SetThMin( double ){ G4cerr << __FILE__ << " line " << __LINE__ << " " << __PRETTY_FUNCTION__ << " :  Generator does not respond to this command" << G4endl; }
	virtual void SetThMax( double ){ G4cerr << __FILE__ << " line " << __LINE__ << " " << __PRETTY_FUNCTION__ << " :  Generator does not respond to this command" << G4endl; }


};

#endif//__REMOLLGENMOLLER_HH 
