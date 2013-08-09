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
#include "cteq/cteqpdf.h"

// Use CTEQ6 parameterization
//
void initcteqpdf(){
         __dis_pdf = cteq_pdf_alloc_id(400); 
}


class remollGenDIS : public remollVEventGen {
    public:
	 remollGenDIS();
	~remollGenDIS();

    private:
	void SamplePhysics(remollVertex *, remollEvent *);

};

#endif//__REMOLLGENDIS_HH 
