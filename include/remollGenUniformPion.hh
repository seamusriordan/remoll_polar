#ifndef __REMOLLGENUNIFORMPION_HH 
#define __REMOLLGENUNIFORMPION_HH 
/*!
 * Uniform Pion event generator
 * from Wiser parameterization following eicRate implementation by Seamus Riordan
 *
 * Rakitha Beminiwattha
 * Fri Jun 27 10:10:39 EDT 2014
 *
*/

//#include "remollVEventGen.hh"
#include "remollGenPion.hh"

class remollGenUniformPion : public remollGenPion {
public:
  remollGenUniformPion();
  ~remollGenUniformPion();
  
  
private:
  void SamplePhysics(remollVertex *, remollEvent *);
  
  
  Pion_t fPionType;
  Bool_t fHaveTotalXs;
  Double_t fTotal0Xs;
  Double_t fTotal1Xs;
};

#endif//__REMOLLGENUNIFORMPION_HH 
