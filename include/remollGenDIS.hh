#ifndef __REMOLLGENDIS_HH 
#define __REMOLLGENDIS_HH 
/*!
 * DIS event generator
 *
 * Seamus Riordan
 * August 9, 2013
 *
*/

#include "remollVEventGen.hh"


class remollGenDIS : public remollVEventGen {
    public:
	 remollGenDIS();
	~remollGenDIS();

    private:
	void SamplePhysics(remollVertex *, remollEvent *);

};

#endif//__REMOLLGENDIS_HH 
