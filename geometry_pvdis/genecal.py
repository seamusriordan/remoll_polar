#!/usr/bin/python
from math import sin,cos,sqrt,fabs, pi

preshowerdetno = 80000
showerdetno = 90000

# ECal Paramters
# This defines a preshower and shower

zfront = 335.0
dz     = 25
zback  = zfront + 2.0*dz

rmin = 118.0
rmax = 261.0

blockside = 6.25

nlayer  = 23
nsector = 30

absorbthick = 0.05
scintthick  = 0.15
gapthick = 0.024

leadinglead  = 0.05137*2
leadingscint = 2

numsides = 6
nscintlayer  = 194

blockdepth = (absorbthick+scintthick+gapthick)*nscintlayer - gapthick + leadingscint
motherdepth = blockdepth + leadinglead

# lab coordinate z of center of mother volume
# This needs to agree with main gdml coordinate
mother_z0 = (zfront + zback)/2 

ecalmat = "Lead"
#ecalmat = "Kryptonite"

####################################################################
def checkhexpoints( x, y, r ):
    # return true if all points lie within anulus, otherwise false
    isOK = True
    for i in range(6):
	x1 = x + r*cos(i*pi/3.0)
	y1 = y + r*sin(i*pi/3.0)

	if sqrt(x1*x1 + y1*y1) > rmax:
		isOK = False
	if sqrt(x1*x1 + y1*y1) < rmin:
		isOK = False
    return isOK


####################################################################

header = """<?xml version="1.0" encoding="UTF-8"?>
<gdml xmlns:gdml="http://cern.ch/2001/Schemas/GDML" xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance" xsi:noNamespaceSchemaLocation="schema/gdml.xsd">
    <!-- Hex Calorimeter -->

        <define>
	   <position name="ecal_origin" x="0.0" y="0.0" z="0.0" unit="cm"/>
	   <rotation name="identity"/>
	   <variable name="i0" value="1"/>"""

print header
print "        </define>"


print """        <materials>
	   <material Z="1" name="Vacuum" state="gas">
	       <T unit="K" value="2.73"/>
  	       <P unit="pascal" value="3e-18"/>
	       <D unit="g/cm3" value="1e-25"/>
	       <atom unit="g/mole" value="1.01"/>
	   </material>
	   <material name="Carbon" Z="6">
	       <D    unit="g/cm3" value="2.21"/>
	       <atom unit="g/mole" value="12.011"/>
	   </material>
	   <material name="Hydrogen" Z="1">
	       <D    unit="g/cm3" value="0.067"/>
	       <atom unit="g/mole" value="1.01"/>
	   </material>
	   <material name="Nitrogen" Z="7">
	       <D    unit="g/L" value="1.165"/>
	       <atom unit="g/mole" value="14.0067"/>
	   </material>
	   <material name="Oxygen" Z="8">
	       <D    unit="g/L" value="1.332"/>
	       <atom unit="g/mole" value="16"/>
	   </material>

	   <material Z="82" name="Lead" state="solid">
	       <D unit="g/cm3" value="11.350"/>
	       <atom unit="g/mole" value="207.2"/>
	   </material>
	   <material Z="82" name="Kryptonite" state="solid">
	       <D unit="g/cm3" value="11.350"/>
	       <atom unit="g/mole" value="207.2"/>
	   </material>

	   <material name="Scint" state="gas">
	       <D unit="g/cm3" value="1.032"/>
	       <composite n="10" ref="Hydrogen"/>
	       <composite n="9" ref="Carbon"/>
	   </material>

	   <material name="Air" state="gas">
	       <D value="0.00129" />
	       <fraction n="0.7" ref="Nitrogen" />
	       <fraction n="0.3" ref="Oxygen" />
	   </material>

        </materials>
	
	<solids>"""

print """	      <tube name="ecalmother" aunit="deg" startphi="0" deltaphi="360" lunit="cm" rmin="%f" rmax="%f" z="%f"/>"""% (rmin, rmax, motherdepth)
print """	      <polyhedra name="ecalblock" aunit="deg" startphi="0" deltaphi="360" lunit="cm" numsides="%d" >
   	          <zplane rmin="0" rmax="%f" z="%f"/>
   	          <zplane rmin="0" rmax="%f" z="%f"/>
	      </polyhedra>""" % (numsides,  blockside/sqrt(3.0), -blockdepth/2, blockside/sqrt(3.0),  blockdepth/2 )

print """	      <tube name="ecalleadinglead" aunit="deg" startphi="0" deltaphi="360" lunit="cm" rmin="%f" rmax="%f" z="%f"/>"""% (rmin, rmax, leadinglead)

print """	      <polyhedra name="ecalleadscint" aunit="deg" startphi="0" deltaphi="360" lunit="cm" numsides="%d" >
   	          <zplane rmin="0" rmax="%f" z="%f"/>
   	          <zplane rmin="0" rmax="%f" z="%f"/>
	      </polyhedra>""" % (numsides,  blockside/sqrt(3.0), -leadingscint/2, blockside/sqrt(3.0),  leadingscint/2)

print """	      <polyhedra name="ecalgap" aunit="deg" startphi="0" deltaphi="360" lunit="cm" numsides="%d" >
   	          <zplane rmin="0" rmax="%f" z="%f"/>
   	          <zplane rmin="0" rmax="%f" z="%f"/>
	      </polyhedra>""" % (numsides,  blockside/sqrt(3.0), -gapthick/2, blockside/sqrt(3.0),  gapthick/2)
print """	      <polyhedra name="ecalblockscint" aunit="deg" startphi="0" deltaphi="360" lunit="cm" numsides="%d" >
   	          <zplane rmin="0" rmax="%f" z="%f"/>
   	          <zplane rmin="0" rmax="%f" z="%f"/>
	      </polyhedra>""" % (numsides,  blockside/sqrt(3.0), -scintthick/2, blockside/sqrt(3.0),  scintthick/2)

print """        </solids>

	<structure>
"""

print """	         <volume name="logicecalleadinglead">
		      <materialref ref="%s"/> 
		      <solidref ref="ecalleadinglead"/>
		      <auxiliary auxtype="Visibility" auxvalue="true"/>
		      <auxiliary auxtype="Color" auxvalue="Gray"/>
	        </volume>""" % (ecalmat)
print """	         <volume name="logicecalleadscint">
		      <materialref ref ="Scint"/> 
		      <solidref ref ="ecalleadscint"/>
		      <auxiliary auxtype="Visibility" auxvalue="true"/>
		      <auxiliary auxtype="Color" auxvalue="Yellow"/>
		      <auxiliary auxtype="SensDet" auxvalue="Cal"/>
		      <auxiliary auxtype="DetNo" auxvalue="%d"/>
	        </volume>""" % preshowerdetno

print """	         <volume name="logicecalgap">
		      <materialref ref ="Air"/> 
		      <solidref ref ="ecalgap"/>
		      <auxiliary auxtype="Visibility" auxvalue="false"/>
	        </volume>"""

print """	         <volume name="logicecalblockscint">
		      <materialref ref ="Scint"/> 
		      <solidref ref ="ecalblockscint"/>
		      <auxiliary auxtype="Visibility" auxvalue="false"/>
<!--		      <auxiliary auxtype="Color" auxvalue="Yellow"/> -->
		      <auxiliary auxtype="SensDet" auxvalue="Cal"/>
		      <auxiliary auxtype="DetNo" auxvalue="%d"/>
	        </volume>""" % showerdetno

# Now build blocks		
# Preshower scint + mainshower layers

print """	         <volume name="logicecalblock">
		      <materialref ref ="%s"/> 
		      <solidref ref ="ecalblock"/>
		      <auxiliary auxtype="Visibility" auxvalue="True"/>
		      <auxiliary auxtype="Color" auxvalue="Gray"/> 
		      """ % (ecalmat)
print """	              <physvol>
			     <volumeref ref="logicecalleadscint" />
			     <position name="ecalleadscintpos" unit="cm" x="0.0" y="0.0" z="%f"/>
                        </physvol>""" % (-blockdepth/2 + leadingscint/2)

for i in range(nscintlayer):
    thiszoff = -blockdepth/2 + leadingscint + (i+1)*absorbthick + i*(scintthick + gapthick)
    print """	              <physvol>
			     <volumeref ref="logicecalblockscint" />
			     <position name="ecalblockscintpos_%d" unit="cm" x="0.0" y="0.0" z="%f"/>
                        </physvol>""" %  (i, 0.5*scintthick + thiszoff)
    print """	              <physvol>
			     <volumeref ref="logicecalgap" />
			     <position name="ecalgappos_%d" unit="cm" x="0.0" y="0.0" z="%f"/>
                        </physvol>""" %  (i,0.5*gapthick + scintthick + thiszoff)

print """	        </volume>""" # logicecalblock


print """
        <!---  Place volumes -->
	        <volume name="logicEcalMother">
		      <materialref ref="Vacuum"/>
		      <solidref ref="ecalmother"/>
	              <auxiliary auxtype="Visibility" auxvalue="false"/>"""

print """	      <physvol>
                      <volumeref ref="logicecalleadinglead"/>
		      <position name="ecalleadingleadpos" unit="cm" x="0.0" y ="0.0" z="%f"/>
	        </physvol>""" % (-motherdepth/2 + leadinglead/2)

# number of x and y steps to consider
xspace = blockside*2
yspace = 2.0*blockside/sqrt(3.0)

nx = int(2.0*rmax/xspace) + 1
ny = int(2.0*rmax/yspace) + 1
for i in range(nx):
    for j in range(ny):
	thisx = -rmax + i*xspace
	thisy = -rmax + j*yspace

	if checkhexpoints( thisx, thisy, blockside ):
	    print """             <physvol>
		  <volumeref ref="logicecalblock"/>
		  <position name="ecalblockpos_%d_%d_%d" unit="cm" x="%f" y ="%f" z="%f"/>
	    </physvol>""" % (i, j, 0, thisx, thisy, motherdepth/2-blockdepth/2)

	thisx = -rmax + i*xspace+ blockside
	thisy = -rmax + j*yspace + blockside/sqrt(3.0)
	if checkhexpoints( thisx, thisy, blockside ):
	    print """             <physvol>
		  <volumeref ref="logicecalblock"/>
		  <position  name="ecalblockpos_%d_%d_%d " unit="cm" x="%f" y ="%f" z="%f"/>
	    </physvol>""" % (i, j, 1, thisx, thisy, motherdepth/2-blockdepth/2)

print """      </volume>
	</structure>

	<setup name="Ecal" version="1.0">
	     <world ref="logicEcalMother"/>
	</setup>
</gdml>"""








