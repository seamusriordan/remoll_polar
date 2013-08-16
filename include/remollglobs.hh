#ifndef __REMOLLGLOBS_HH
#define __REMOLLGLOBS_HH

#include "G4SystemOfUnits.hh"

/*
   remollglobs.hh

   Global type stuff
*/


const double GF = 1.16637e-5/GeV/GeV; 
const double alpha = 0.007299; 
const double sin2thW_ms = 0.23116; // PDG 2012
const double QWe =  0.0435;  // arxiv 1302.6263 - KK's low Q2 EW review
const double QWp = -0.0707;
const double gV_u =  0.5 - 4.0*sin2thW_ms/3.0;
const double gV_d = -0.5 + 2.0*sin2thW_ms/3.0;
const double gA_u =  0.5;
const double gA_d = -0.5;

const double gA = -0.5;
const double gV = -0.5 + 2.0*sin2thW_ms;

const double MZ = 91.1876*GeV;

const double e_u = 2.0/3.0;
const double e_d = -1.0/3.0;

const double gDefaultBeamE   = 11.0*GeV;
const double gDefaultBeamPol = 0.85;
const double gDefaultBeamCur = 50e-6*ampere;


#endif//__REMOLLGLOBS_HH
