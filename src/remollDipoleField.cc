#include "remollDipoleField.hh"
#include "G4ThreeVector.hh"
#include <math.h>

remollDipoleField::remollDipoleField(G4ThreeVector orig, G4ThreeVector s, G4double B){
    origin = orig; 
    size = s; 
    BDip = B;
    fInit = true;
    printf("Origin: (%f, %f, %f), Size: (%f, %f, %f), Bfield = %f", origin[0], origin[1], origin[2], size[0], size[1], size[2], BDip);
}

remollDipoleField::~remollDipoleField(){}

void remollDipoleField::GetFieldValue(const G4double Point[4], G4double *Bfield) const{
    
    if(pointInRange(Point)){
        Bfield[0] = BDip;
    }

    else{
        Bfield[0] = 0.0;
    } 
    
    Bfield[1] = 0.0;
    Bfield[2] = 0.0;

   // printf("Field value at point (%f, %f, %f) is (%f, %f, %f)", Point[0], Point[1], Point[2], Bfield[0], Bfield[1], Bfield[2]);
    return;

}

bool remollDipoleField::pointInRange(const G4double Point[4]) const{
    return( fabs(Point[0] - origin[0]) < size[0] && 
            fabs(Point[1] - origin[1]) < size[1] && 
            fabs(Point[2] - origin[2]) < size[2]);
}

void remollDipoleField::SetSize(G4ThreeVector s){
    if(s[0] >= 0 && s[1] >=0 && s[2] >=0){
        size = s;
    }
    else{
        G4cerr << "Size cannot be set to a negative value" << G4endl;
    }
    return;
}

