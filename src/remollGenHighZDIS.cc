#include "remollGenHighZDIS.hh"
#include "CLHEP/Random/RandFlat.h"

#include "remollEvent.hh"
#include "remollVertex.hh"
#include "G4Material.hh"

#include "remolltypes.hh"

// not required any more rakitha - Wed Nov 20 16:56:30 EST 2013
#include "remollBeamTarget.hh"



////////////////////////////////////////////////////////
/*
Implementation of CTEQ6 access is not the best way as CTEQ6 variables are defined in remollGenDIS and remollGenHighZDIS classes. Rakitha Mon Apr 28 09:21:36 EDT 2014
 */
#include "cteq/cteqpdf.h"

cteq_pdf_t *__dis_pdf2;

// Use CTEQ6 parameterization
//
void initcteqpdf2(){
         __dis_pdf2 = cteq_pdf_alloc_id(400); 
}

void freecteqpdf2(){
         cteq_pdf_free(__dis_pdf2); 
}

////////////////////////////////////////////////////////

remollGenHighZDIS::remollGenHighZDIS(){
  fTh_min =     5.0*deg;
  fTh_max =     60.0*deg;

  fApplyMultScatt = true;

  // init DIS cteq pdf
  initcteqpdf2();  
}

remollGenHighZDIS::~remollGenHighZDIS(){
  freecteqpdf2(); 
}



void remollGenHighZDIS::SamplePhysics(remollVertex *vert, remollEvent *evt){
  // update the A_PV for High Z (Lead or Iron for us). The cross section computations are same as in remollGenDIS class.

     // Generate inelastic event

  double beamE = vert->GetBeamE();
  //beamE = remollBeamTarget::GetBeamTarget()->fBeamE;//generic beam energy uncorrected for rad-loss remollBeamTarget::GetBeamTarget()->fBeamE; //rakitha - Wed Nov 20 16:56:30 EST 2013
    double mp    = proton_mass_c2;

    double th = acos(CLHEP::RandFlat::shoot(cos(fTh_max), cos(fTh_min)));
    double ph = CLHEP::RandFlat::shoot(fPh_min, fPh_max);
    double efmax = mp*beamE/(mp + beamE*(1.0-cos(th)));;
    double efmin = 0.0;


    if( efmax > fE_max ){
	efmax = fE_max;
    }

    if( fE_min < 0.0 || fE_min > efmax ){
	G4cerr << __FILE__ << " line " << __LINE__ <<
		             ": Warning!  minimum energy specified is nonmeaninful (" << fE_min/GeV << " GeV), setting to 0" << G4endl;
	efmin = 0.0;
    } else {
	efmin = fE_min;
    }

    double ef = CLHEP::RandFlat::shoot(efmin, efmax);


    if( vert->GetMaterial()->GetNumberOfElements() != 1 ){
	G4cerr << __FILE__ << " line " << __LINE__ << 
	    ": Error!  Some lazy programmer didn't account for complex materials in the moller process!" << G4endl;
	exit(1);
    }

    double Q2 = 2.0*beamE*ef*(1.0-cos(th));
    evt->SetQ2( Q2 );

    double nu = beamE-ef;
    evt->SetW2( mp*mp + 2.0*mp*nu - Q2 );
    double x = Q2/(2.0*mp*nu);
    evt->SetXbj( x );
    double y = nu/beamE;

    double numax = beamE;

    double Ynum = 2.0*x*(1.0-y/2.0);
    double Yden = 2.0*x*y + 4.0*x*(1.0-y-x*y*mp/(2.0*numax))/y;
    double Y = Ynum/Yden;


    double evQ2 = Q2/(GeV*GeV);
    // Force a mimimum evolution
    if( evQ2 < 1.0 ){
	evQ2 = 1.0;
    }

    double qu =    cteq_pdf_evolvepdf(__dis_pdf2, 1, x, sqrt(evQ2) );
    double qd =    cteq_pdf_evolvepdf(__dis_pdf2, 2, x, sqrt(evQ2) );
    double qubar = cteq_pdf_evolvepdf(__dis_pdf2, -1, x, sqrt(evQ2) );
    double qdbar = cteq_pdf_evolvepdf(__dis_pdf2, -2, x, sqrt(evQ2) );

    double quv = qu-qubar;
    double qdv = qd-qdbar;

    double qs = cteq_pdf_evolvepdf(__dis_pdf2, 3, x, sqrt(evQ2) );


    double F2p = x*( e_u*e_u*quv + e_d*e_d*qdv );
    double F2n = x*( e_u*e_u*qdv + e_d*e_d*quv );

    double F1gZp = e_u*gV_u*quv + e_d*gV_d*qdv;
    double F1gZn = e_u*gV_u*qdv + e_d*gV_d*quv;

    double F3gZp = 2.0*(e_u*gA_u*quv + e_d*gA_d*qdv);
    double F3gZn = 2.0*(e_u*gA_u*qdv + e_d*gA_d*quv);

    // Sea quarks, 2 is to account for quarks and antiquarks
    F2p  += x*(2.0*e_u*e_u*qubar + 2.0*e_d*e_d*(qdbar + qs));
    F2n  += x*(2.0*e_u*e_u*qdbar + 2.0*e_d*e_d*(qubar + qs));

    F1gZp += 2.0*e_u*gV_u*qubar + 2.0*e_d*gV_d*(qdbar+qs);
    F1gZn += 2.0*e_u*gV_u*qdbar + 2.0*e_d*gV_d*(qubar+qs);

    // Sea quarks cancel for F3gZ

    double F1p = F2p/(2.0*x);
    double F1n = F2n/(2.0*x);


    //  PDG formulas for cross section
    double sigmap_dxdy = 4.0*pi*alpha*alpha*((1.0-y-pow(x*y*mp,2.0)/Q2)*F2p+y*y*x*F1p)/(x*y*Q2);
    double sigman_dxdy = 4.0*pi*alpha*alpha*((1.0-y-pow(x*y*mp,2.0)/Q2)*F2n+y*y*x*F1n)/(x*y*Q2);

    double sigmap_dOmega_dE = sigmap_dxdy*ef*hbarc*hbarc/(2.0*pi*mp*nu);
    double sigman_dOmega_dE = sigman_dxdy*ef*hbarc*hbarc/(2.0*pi*mp*nu);

    double vert_A=vert->GetMaterial()->GetA()*mole/g;
    double vert_Z=vert->GetMaterial()->GetZ();

    double pcont = sigmap_dOmega_dE*vert_Z;
	//  Effective neutron number...  I don't like it either  SPR 2/14/2013
    double ncont = sigman_dOmega_dE*(vert_A - vert_Z);

    double sigmatot = pcont + ncont;

    double V = (fPh_max - fPh_min)*(cos(fTh_min) - cos(fTh_max))*(efmax-efmin);

    evt->SetEffCrossSection(sigmatot*V);
    G4double APV = 0.0;
    /*
    multiplicative factor of asymmetry from I.C. Cloet, PRL 109, 182301 (2012) needs to be implemented here. In remollGenDIS class this factor is multiplied by 2 : Rakitha Mon Apr 28 09:43:13 EDT 2014
     */
    G4double eta_gZ = GF*Q2*MZ*MZ/(alpha*4.0*sqrt(2.0)*pi)/(Q2+MZ*MZ);

    /*
      The Bjorken limit asymmetry from I.C. Cloet, PRL 109, 182301 (2012) needs to be implemented here
    */
    //weak mixing angle at Z-pole
    Double_t sin2_theta_w_Z = 0.2312; //weak mixing angle at E=Z-pole (\hat{s^2}_Z) from PDG 2012

    /*
      For now the only the isoscalar result for the asymmetry is implemented here. Full results with nuclear medium corrections will be implemented Rakitha Mon Apr 28 09:43:13 EDT 2014
     */
    //APV = eta_gZ * (9/5 - 4*sin2_theta_w_Z);//isoscalar implementation commented out see below for naive computation

    /*
      Naive implementation of the asymmetry ignoring nuclear medium corrections
    */
    G4double APVp = eta_gZ*(gA*F1gZp + Y*gV*F3gZp)/F1p;
    G4double APVn = eta_gZ*(gA*F1gZn + Y*gV*F3gZn)/F1n;

    if( (pcont + ncont > 0.0) ){
      APV = (APVp*pcont + APVn*ncont)/(pcont+ncont);
    }


    evt->SetAsymmetry(APV);

    evt->ProduceNewParticle( G4ThreeVector(0.0, 0.0, 0.0), 
	                     G4ThreeVector(ef*sin(th)*cos(ph), ef*sin(th)*sin(ph), ef*cos(th) ), 
			     "e-" );

    return; 
}
