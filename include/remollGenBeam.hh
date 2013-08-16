#ifndef __REMOLLGENBEAM_HH 
#define __REMOLLGENBEAM_HH 
/*!
 * Boring beam event generator
 *
 * Seamus Riordan
 * July 9, 2013
 *
*/

#include "remollVEventGen.hh"

class remollBeamTarget;

class remollGenBeam : public remollVEventGen {
    public:
	remollGenBeam();
	~remollGenBeam();

    private:
	void SamplePhysics(remollVertex *, remollEvent *);

	virtual void SetThMin(double){  G4cerr << __FILE__ << " line " << __LINE__ << " " << __PRETTY_FUNCTION__ << " :  Generator does not respond to this command" << G4endl; }
	virtual void SetThMax(double){  G4cerr << __FILE__ << " line " << __LINE__ << " " << __PRETTY_FUNCTION__ << " :  Generator does not respond to this command" << G4endl; }
	virtual void SetPhMin(double){  G4cerr << __FILE__ << " line " << __LINE__ << " " << __PRETTY_FUNCTION__ << " :  Generator does not respond to this command" << G4endl; }
	virtual void SetPhMax(double){  G4cerr << __FILE__ << " line " << __LINE__ << " " << __PRETTY_FUNCTION__ << " :  Generator does not respond to this command" << G4endl; }
	virtual void SetEmin(double){  G4cerr << __FILE__ << " line " << __LINE__ << " " << __PRETTY_FUNCTION__ << " :  Generator does not respond to this command" << G4endl; }

	remollBeamTarget *fBeamTarg;

	double fZpos;
};

#endif//__REMOLLGENBEAM_HH 
