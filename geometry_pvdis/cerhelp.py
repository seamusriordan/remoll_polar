#!/usr/bin/python

from ROOT import TVector3, TRotation
from math import sin, cos, asin, acos, fabs, pi, tan, sqrt

# Find equivalent rotation matrix
# For ZYX rotation, we use components to pick out terms which
# have two possible solutions for the new rotation angles
# We go by trial and error and compare the two rotation matrix
# elements to find the one we want

def XYZrotToZYX(x,y,z):
    tol = 1e-8

    arot = TRotation()
    arot.RotateX(x)
    arot.RotateY(y)
    arot.RotateZ(z)

    for tix in range(2):
	for tiy in range(2):
	    for tiz in range(2):
		testy = asin(arot.XZ());
		if tiy == 0:
		    thisy = testy
		else:
		    thisy = pi-testy

		testx = asin(-arot.YZ()/cos(thisy))
		if tix == 0:
		    thisx = testx
		else:
		    thisx = pi-testx

		testz = asin(-arot.XY()/cos(thisy))
		if tiz == 0:
		    thisz = testz
		else:
		    thisz = pi-testz

		isequiv = True

		newrot = TRotation()
		newrot.RotateZ(thisz)
		newrot.RotateY(thisy)
		newrot.RotateX(thisx)

		for mi in range(3):
		    for mj in range(3):
			if( fabs(newrot(mi,mj) - arot(mi,mj))>tol ):
			    isequiv = False
	        if isequiv:
		    break;
    if tix == 2 or tiy == 2 or tiz == 2:
	print "Error:  could not find equivalent rotation matrix"
	exit(1)
    return (thisx, thisy, thisz)


def ZYXrotToXYZ(x,y,z):
    tol = 1e-8

    arot = TRotation()
    arot.RotateZ(z)
    arot.RotateY(y)
    arot.RotateX(x)

    for tix in range(2):
	for tiy in range(2):
	    for tiz in range(2):
		testy = -asin(arot.ZX());
		if tiy == 0:
		    thisy = testy
		else:
		    thisy = pi-testy

		testx = asin(arot.ZY()/cos(thisy))
		if tix == 0:
		    thisx = testx
		else:
		    thisx = pi-testx

		testz = asin(arot.YX()/cos(thisy))
		if tiz == 0:
		    thisz = testz
		else:
		    thisz = pi-testz

		isequiv = True

		newrot = TRotation()
		newrot.RotateX(thisx)
		newrot.RotateY(thisy)
		newrot.RotateZ(thisz)

		for mi in range(3):
		    for mj in range(3):
			if( fabs(newrot(mi,mj) - arot(mi,mj))>tol ):
			    isequiv = False
	        if isequiv:
		    break;
    if tix == 2 or tiy == 2 or tiz == 2:
	print "Error:  could not find equivalent rotation matrix"
	exit(1)
    return (thisx, thisy, thisz)


def ZXYrotToXYZ(x,y,z):
    return ZYXrotToXYZ(x,y,z)




def buildSPmirror( P1V, P2V, centAng_deg, Z, edit_rot = False, edit_R = False):
    centAng = centAng_deg*pi/180.0

    V0V = TVector3(0, sin(centAng), cos(centAng)) # normal vector containing central angle
#    ViV = ((Z - P1V.Z())/V0V.Z())*V0V             # incident vector w.r.t the source
    ViV = V0V
    ViV.SetMag(((Z - P1V.Z())/V0V.Z())/V0V.Mag()) # incident vector w.r.t the source
    PmV = P1V + ViV				  # crossing point on mirror plane w.r.t the origin of coordinates
    VrV = P2V - PmV				  # reflected vector
    VnV = VrV.Unit() - ViV.Unit()		  # unitary normal vector

    if edit_rot:
	VnV.RotateX(edit_rot*pi/180.0)
    VnV = VnV.Unit()
    ang_cos = -(ViV.Dot(VnV))/ViV.Mag()

    R = 2.0/(ang_cos*(1.0/ViV.Mag() + 1.0/VrV.Mag()))
    if edit_R:
	R = edit_R*R
    
#    PosV = PmV + R*VnV
    temp = VnV
    temp.SetMag( R/VnV.Mag() )
    PosV = PmV + temp

    return (R, PosV)

def mirrorRot(PosV, R, centAng, posVec, degRot, zvert, mirrorZ ):

    mPoint = TVector3( 0.0, PosV.Y() - sqrt(R*R - (mirrorZ - PosV.Z())*(mirrorZ - PosV.Z())), mirrorZ)
    dVec = mPoint - posVec;
    Rloc = dVec.Mag()
    delta = TVector3(0.0, 0.0, 0.0);
    alpha = 0;
    beta = degRot*pi/180/2.0;
    dVecy = dVec.Y();

    if dVecy <=0:
	if degRot > 0:
	     alpha = pi - asin(dVec.Z()/Rloc) - acos(sin(beta));
             delta = TVector3(0.0, 2.0*Rloc*cos(alpha)*sin(beta), 2.0*Rloc*sin(alpha)*sin(beta));
	if degRot < 0:
	     alpha = pi - asin(-dVecy/Rloc) - acos(sin(-beta));
	     delta = TVector3(0.0, -2.0*Rloc*sin(alpha)*sin(-beta), -2.0*Rloc*cos(alpha)*sin(-beta));

    if dVecy >=0:
	if degRot < 0:
	     alpha = pi - asin(dVec.Z()/Rloc) - acos(sin(-beta));
	     delta = TVector3(0.0, -2.0*Rloc*cos(alpha)*sin(-beta), 2.0*Rloc*sin(alpha)*sin(-beta));
	if degRot > 0:
	     alpha = pi - asin( dVecy/ Rloc) - acos(sin( beta));
	     delta = TVector3(0.0, 2.0* Rloc*sin( alpha)*sin( beta), -2.0* Rloc*cos( alpha)*sin( beta));

    return delta

	
def calcIntPoints( sphereR, sphereV, coneV, coneZh, coneRin1, coneRout1, coneRin2, coneRout2,  rotAng = None ):
    #this subroutine finds the intersection points of the cone segment corners on the sphere that contructs the mirror.  The output is useful for getting mirror dimensions.
    coneAngIn = 84.0
    coneAngOut = 84.0 + 12.0

    #first take the paramters of the incoming cone segment:

    D2R = pi/180.
    ray1p = []
    ray2p = []

    ray1p.append( TVector3(coneRin1*cos(coneAngIn*D2R), coneRin1*sin(coneAngIn*D2R), coneV.Z() - coneZh) )
    ray1p.append( TVector3(coneRin1*cos(coneAngOut*D2R), coneRin1*sin(coneAngOut*D2R), coneV.Z() - coneZh) )
    ray1p.append( TVector3(coneRout1*cos(coneAngIn*D2R), coneRout1*sin(coneAngIn*D2R), coneV.Z() - coneZh) )
    ray1p.append( TVector3(coneRout1*cos(coneAngOut*D2R), coneRout1*sin(coneAngOut*D2R), coneV.Z() - coneZh) )

    ray2p.append( TVector3(coneRin2*cos(coneAngIn*D2R), coneRin1*sin(coneAngIn*D2R), coneV.Z() + coneZh) )
    ray2p.append( TVector3(coneRin2*cos(coneAngOut*D2R), coneRin1*sin(coneAngOut*D2R), coneV.Z() + coneZh) )
    ray2p.append( TVector3(coneRout2*cos(coneAngIn*D2R), coneRout1*sin(coneAngIn*D2R), coneV.Z() + coneZh) )
    ray2p.append( TVector3(coneRout2*cos(coneAngOut*D2R), coneRout1*sin(coneAngOut*D2R), coneV.Z() + coneZh) )

    tempos = TVector3(0.0, 0.0, coneV.Z() - 250.5 )
    if rotAng:
	for i in range(len(ray1p)):
	    ray1p[i] -= tempos
	    ray1p[i] -= coneV 
	    ray1p[i].RotateX(rotAng*D2R)
	    ray1p[i] += coneV
	for i in range(len(ray2p)):
	    ray2p[i] -= tempos
	    ray2p[i] -= coneV 
	    ray2p[i].RotateX(rotAng*D2R)
	    ray2p[i] += coneV

    rayR0 = []
    rayRd = []
    int1 = []
    int2 = []

    for i in range(len(ray1p)):
	rayRd.append( (ray2p[i] - ray1p[i]).Unit())
	rayR0.append( ray1p[i] )

	# print "rayd: $rayRd[$i]\n";

	A = rayRd[i].Dot(rayRd[i])
	B = 2.0*((rayR0[i] - sphereV).Dot(rayRd[i]))
	C = (rayR0[i] - sphereV).Dot( rayR0[i] - sphereV ) - sphereR*sphereR

	t0 = (-B - sqrt(B*B - 4.0*A*C))/(2.0*A)
	t1 = (-B + sqrt(B*B - 4.0*A*C))/(2.0*A)

	temp1 = rayRd[i]
	temp1.SetMag( t0*temp1.Mag() )
	temp2 = rayRd[i]
	temp2.SetMag( t1*temp1.Mag() )

	int1.append( rayR0[i] + temp1 )
	int2.append( rayR0[i] + temp2 )

	#  print "for ray $i, int points are $int1[$i], and $int2[$i]\n";


    intL  = (int2[0] - int2[1]).Mag()
    depth = (int2[2] - int2[1]).Mag()
    outL  = (int2[3] - int2[2]).Mag()

    #  print " inner length: $inL\n depth: $depth\n outer length: $outL\n";


    iny = int2[0].Y()
    inz = int2[0].Z()

    outy = int2[2].Y()
    outZ = int2[2].Z()
    #  print " mirror inside y,z: $iny  $inz \n mirror outside y,z: $outy  $outz \n";


def arrangetables( tablestr ):
    toks = tablestr.split()
    npair = len(toks)/2
    newtable = ""
    for i in range(npair):
	newtable += toks[i]
	newtable += " "
	newtable += toks[i+npair]
	if not i == npair-1:
	    newtable += " "
    return newtable




















