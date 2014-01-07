#include "remollCalDetectorSum.hh"

G4Allocator<remollCalDetectorSum> remollCalDetectorSumAllocator;

remollCalDetectorSum::remollCalDetectorSum(int detid, int copyid){
    fDetID  = detid;
    fCopyID = copyid;
    fEdep   = 0.0;
    fPhoton = 0.0;
    fX      = 0.0;
    fY      = 0.0;
    ffT      = 0.0;
    flT      = 0.0;
    fXsum   = 0.0;
    fYsum   = 0.0;
    fDet_X  = 0.0;
    fDet_Y  = 0.0;
    fDet_Z  = 0.0;
}

remollCalDetectorSum::~remollCalDetectorSum(){
}

remollCalDetectorSum::remollCalDetectorSum(const remollCalDetectorSum &right) : G4VHit(){
    // copy constructor
    fDetID  = right.fDetID;
    fCopyID = right.fCopyID;
    fEdep   = right.fEdep;
    fPhoton = right.fPhoton;
    fX      = right.fX;
    fY      = right.fY;
    ffT      = right.ffT;
    flT      = right.flT;
    fXsum   = right.fXsum;
    fYsum   = right.fYsum;
    fDet_X  = right.fDet_X;
    fDet_Y  = right.fDet_Y;
    fDet_Z  = right.fDet_Z;
}

const remollCalDetectorSum& remollCalDetectorSum::operator =(const remollCalDetectorSum &right){
    (*this) = right;
    return *this;
}

G4int remollCalDetectorSum::operator==(const remollCalDetectorSum &right ) const {
    return (this==&right) ? 1 : 0;
}
