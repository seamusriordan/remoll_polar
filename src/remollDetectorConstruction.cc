#include "remollDetectorConstruction.hh"
#include "G4SystemOfUnits.hh"
#include "G4PhysicalConstants.hh"
#include "remollBeamTarget.hh"
#include "remollIO.hh"

#include "G4TransportationManager.hh"
#include "G4FieldManager.hh"
#include "remollGenericDetector.hh"
#include "G4SDManager.hh"

#include "G4Material.hh"
#include "G4MaterialTable.hh"
#include "G4Element.hh"
#include "G4ElementTable.hh"
#include "G4LogicalBorderSurface.hh"
#include "G4LogicalSkinSurface.hh"
#include "G4Box.hh"
#include "G4Tubs.hh"
#include "G4VPhysicalVolume.hh"
#include "G4LogicalVolume.hh"
#include "G4RotationMatrix.hh"
#include "G4ThreeVector.hh"
#include "G4Transform3D.hh"
#include "G4PVPlacement.hh"
#include "G4OpticalSurface.hh"
#include "G4VisAttributes.hh"



remollDetectorConstruction::remollDetectorConstruction()
{
	meas_loc_x = 0.*cm;
	meas_loc_y = 50.*cm;
	meas_loc_z = 100.*cm;
	

	fIO = NULL;

	CreateGlobalMagneticField();
	

}

remollDetectorConstruction::~remollDetectorConstruction(){;}

G4VPhysicalVolume* remollDetectorConstruction::Construct()
{
	
	remollBeamTarget *beamtarg = remollBeamTarget::GetBeamTarget();
	beamtarg->Reset();
	/////
	// Material Definitions
	
	G4double a, z, density;
	G4int nelements;

	G4Element* H = new G4Element("Hydrogen", "H", z=1 , a = 1.00794*g/mole);
	G4Material* TargetGas = new G4Material("TargetGas", density=1.29*mg/cm3, nelements=1);
	TargetGas->AddElement(H, 1);

	G4Element* N = new G4Element("Nitrogen", "N", z=7, a=14.01*g/mole);
	G4Element* O = new G4Element("Oxygen", "O", z=8, a=16.00*g/mole);
	G4Material* Air = new G4Material("Air", density=1.29*mg/cm3, nelements=2);
	Air->AddElement(N, 70.*perCent);
	Air->AddElement(O, 30.*perCent);

	G4Element* Al = new G4Element("Aluminum", "Al", z=13, a=26.98*g/mole);
	G4Material* Aluminum = new G4Material("TargetWall", density=2.703*g/cm3, nelements=1);
	Aluminum->AddElement(Al, 1);


	/////
	// Grab the detector manager
	
	G4SDManager* SDman = G4SDManager::GetSDMpointer();


	///////////////////////////////
	///// ----- Volumes ----- /////

	G4double world_r, world_z;
	G4double starting_angle, spanning_angle;
	G4double targ_r, targ_z;
	G4double det_r, det_z;
	G4double container_inner_r, container_outer_r, container_z;
	G4double meas_x, meas_y, meas_z;
	
	world_r = 500.*cm;
	world_z = 1000.*cm;
	starting_angle = 0.*deg;
	spanning_angle = 360.*deg;
	det_r = 250.*cm;
	det_z = 500.*cm;
	targ_r = 1.*cm;
	targ_z = 10.*cm;
	container_inner_r = targ_r;
	container_outer_r = container_inner_r + 1.*cm;
	container_z = targ_z;
	meas_x = 3*cm;
	meas_y = 3*meas_x;
	meas_z = meas_x/3;

	/////
	// World
	
	G4Tubs* world_cyl 
		= new G4Tubs("World",0.,world_r,world_z,starting_angle,spanning_angle);
	
	G4LogicalVolume* world_log
		= new G4LogicalVolume(world_cyl,Air,"World",0,0,0);
	
	world_log->SetVisAttributes(G4VisAttributes::Invisible);
	

	G4VPhysicalVolume* world_phys
		= new G4PVPlacement(NULL,G4ThreeVector(0.,0.,0.),world_log,"World",0,false,0);
	beamtarg->SetMotherVolume(world_phys);
	
	/////
	// Detector system intialization
	
	G4Tubs* det_cyl 
		= new G4Tubs("Detector",0.,det_r,det_z,starting_angle,spanning_angle);
	
	G4LogicalVolume* det_log
		= new G4LogicalVolume(det_cyl,Air,"Detector_log",0,0,0);

	det_log->SetVisAttributes(G4VisAttributes::Invisible);

	/////
	// Target cell building and sensetization

	G4Tubs* targ_cyl 
		= new G4Tubs("Target",0.,targ_r,targ_z,starting_angle,spanning_angle);
	
	G4LogicalVolume* targ_log
		= new G4LogicalVolume(targ_cyl,TargetGas,"Target",0,0,0);

	remollGenericDetector* targSD 
		= new remollGenericDetector("TargetSD",1);

	//SDman->AddNewDetector(targSD);
	targ_log->SetSensitiveDetector(targSD);

	G4RotationMatrix* rotTarg
		= new G4RotationMatrix;
	rotTarg->rotateZ(0.*deg);

	G4VPhysicalVolume* targ_phys
		= new G4PVPlacement(rotTarg,G4ThreeVector(0.,0.,0.),targ_log,"Target",
			det_log,false,0);

	beamtarg->AddVolume(targ_phys);
	
	/////
	// External container blocking some mollers from exiting the target cell
	// therefore, hitting det == 2 should be a veto parameter, made of Al for now
	// for no particular reason
	
	G4Tubs* container_cyl 
		= new G4Tubs("Container",container_inner_r,container_outer_r,container_z,starting_angle,spanning_angle);

	G4LogicalVolume* container_log 
		= new G4LogicalVolume(container_cyl,Aluminum,"Container",0,0,0);

	remollGenericDetector* containerSD
		= new remollGenericDetector("ContainerSD",2);

	//SDman->AddNewDetector(containerSD);
	container_log->SetSensitiveDetector(containerSD);
	
	G4RotationMatrix* rotContainer
		= new G4RotationMatrix;
	rotContainer->rotateZ(0.*deg);

	G4VPhysicalVolume* container_phys
		= new G4PVPlacement(rotContainer,G4ThreeVector(0.,0.,0.),container_log,"Container",
			det_log,false,0);

	
	/////
	// Measurement device (just sensitive regions used to find coincident particles)
	
	G4Box* up_meas_box
		= new G4Box("UpMeasurer",meas_x,meas_y,meas_z);

	G4LogicalVolume* up_meas_log
		= new G4LogicalVolume(up_meas_box,Aluminum,"UpMeasurer",0,0,0);

	remollGenericDetector* up_measSD
		= new remollGenericDetector("UpMeasurerSD",3);

	//SDman->AddNewDetector(up_measSD);
	up_meas_log->SetSensitiveDetector(up_measSD);

	G4RotationMatrix* rotUM
		= new G4RotationMatrix;
	rotUM->rotateZ(0.*deg);

	G4VPhysicalVolume* up_meas_phys
		= new G4PVPlacement(rotUM,G4ThreeVector(meas_loc_x,meas_loc_y,meas_loc_z),up_meas_log,"UpMeasurer",
			det_log,false,0);

	// Down measurer
	
	G4Box* down_meas_box
		= new G4Box("DownMeasurer",meas_x,meas_y,meas_z);

	G4LogicalVolume* down_meas_log
		= new G4LogicalVolume(down_meas_box,Aluminum,"DownMeasurer",0,0,0);

	remollGenericDetector* down_measSD
		= new remollGenericDetector("DownMeasurerSD",4);

	//SDman->AddNewDetector(down_measSD);
	down_meas_log->SetSensitiveDetector(down_measSD);

	G4RotationMatrix* rotDM
		= new G4RotationMatrix;
	rotDM->rotateZ(180.*deg);

	G4VPhysicalVolume* down_meas_phys
		= new G4PVPlacement(rotDM,G4ThreeVector(meas_loc_x,-meas_loc_y,meas_loc_z),down_meas_log,"DownMeasurer",
			det_log,false,0);


	// Make a flat plane detector and register with SDman.

	/////
	// Place the detector volume

	G4RotationMatrix* detrot
		= new G4RotationMatrix;
	detrot->rotateZ(0.*deg);

	G4VPhysicalVolume* det_phys
		= new G4PVPlacement(detrot,G4ThreeVector(0.,0.,0.),det_log,"detector_phys",
			world_log,false,0);


	///// --- End Volumes --- /////
	///////////////////////////////
	
	return world_phys;
}
/*
G4int remollDetectorConstruction::UpdateCopyNo(G4VPhysicalVolume* aVolume,G4int index){
	aVolume->SetCopyNo(index);
	index++;
	for(int i=0;i<aVolume->GetLogicalVolume()->GetNoDaughters();i++){
		index = UpdateCopyNo(aVolume->GetLogicalVolume()->GetDaughter(i),index);
	}
	return index;
}


void remollDetectorConstruction::DumpGeometricalTree(G4VPhysicalVolume* aVolume,G4int depth)
{
	for(int isp=0;isp<depth;isp++)
		{ G4cout << "  "; }
	G4cout << aVolume->GetName() << "[" << aVolume->GetCopyNo() << "] "
		<< aVolume->GetLogicalVolume()->GetName() << " "
		<< aVolume->GetLogicalVolume()->GetNoDaughters() << " "
		<< aVolume->GetLogicalVolume()->GetMaterial()->GetName() << " "
		<< G4BestUnit(aVolume->GetLogicalVolume()->GetMass(true),"Mass");
	if(aVolume->GetLogicalVolume()->GetSensitiveDetector())
	{
		G4cout << " " << aVolume->GetLogicalVolume()->GetSensitiveDetector()
					->GetFullPathName();
	}
	G4cout << G4endl;
	for(int i=0;i<aVolume->GetLogicalVolume()->GetNoDaughters();i++)
	{ DumpGeometricalTree(aVolume->GetLogicalVolume()->GetDaughter(i),depth+1); }
}
*/
void remollDetectorConstruction::CreateGlobalMagneticField() {
	fGlobalField = new remollGlobalField();

	fGlobalFieldManager = G4TransportationManager::GetTransportationManager()->GetFieldManager();
	fGlobalFieldManager->SetDetectorField(fGlobalField);
	fGlobalFieldManager->CreateChordFinder(fGlobalField);

	return;
}

void remollDetectorConstruction::SetDetectorGeomFile(const G4String &str){
	fDetFileName = str;
}
