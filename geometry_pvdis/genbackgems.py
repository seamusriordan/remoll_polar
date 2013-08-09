#!/usr/bin/python

backgemdet1no = 3000
backgemdet2no = 4000

# GEM parameters

z1 = 306.0
z2 = 315.0

r1min = 105.0
r1max = 200.0

r2min = 115.0
r2max = 215.0

nlayer  = 23
nsector = 30

gemthick = (0.012,0.0003,0.012,0.005,0.0005,0.3,0.0005,0.005,0.0005,0.2,0.0005,0.005,0.0005,0.2,0.0005,0.005,0.0005,0.2,0.001,0.005,0.012,0.0003,0.012)
gemmat  = ("NEMAG10","NOMEX","NEMAG10","Kapton","GEMCopper","GEMgas","GEMCopper","Kapton","GEMCopper","GEMgas","GEMCopper","Kapton","GEMCopper","GEMgas","GEMCopper","Kapton","GEMCopper","GEMgas","GEMCopper","Kapton","NEMAG10","NOMEX","NEMAG10")

detlayer = (4,5,6,18)

motherdepth = z2-z1+1.0

# lab coordinate z of center of mother volume
# This needs to agree with main gdml coordinate
mother_z0 = ( (z2+1.0)+z1 )/2

####################################################################

header = """<?xml version="1.0" encoding="UTF-8"?>
<gdml xmlns:gdml="http://cern.ch/2001/Schemas/GDML" xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance" xsi:noNamespaceSchemaLocation="schema/gdml.xsd">
    <!-- Back GEMs -->

        <define>
	   <position name="backgem_origin" x="0.0" y="0.0" z="0.0" unit="cm"/>
	   <rotation name="identity"/>
	   <variable name="i0" value="1"/>"""

print header

print "\t   <constant name=\"backgem_z1\" value=\"%f\"/>" % z1
print "\t   <constant name=\"backgem_z2\" value=\"%f\"/>" % z2
print "\t   <variable name=\"backgem_rmin1\" value=\"%f\"/>" % r1min
print "\t   <constant name=\"backgem_rmax1\" value=\"%f\"/>" % r1max
print "\t   <constant name=\"backgem_rmin2\" value=\"%f\"/>" % r2min
print "\t   <constant name=\"backgem_rmax2\" value=\"%f\"/>" % r2max

print "        </define>"


print """        <materials>
	   <material Z="1" name="Vacuum" state="gas">
	       <T unit="K" value="2.73"/>
  	       <P unit="pascal" value="3e-18"/>
	       <D unit="g/cm3" value="1e-25"/>
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
	   <material name="Carbon" Z="6">
	       <D    unit="g/cm3" value="2.21"/>
	       <atom unit="g/mole" value="12.011"/>
	   </material>
	   <material name="Hydrogen" Z="1">
	       <D    unit="g/cm3" value="0.067"/>
	       <atom unit="g/mole" value="1.01"/>
	   </material>
	   <material name="Silicon" Z="14">
	       <D    unit="g/cm3" value="2.329"/>
	       <atom unit="g/mole" value="28.086"/>
	   </material>
           <material name="Chlorine" Z="17">
               <D    unit="g/cm3" value="1.574"/>
               <atom unit="g/mole" value="35.453"/>
           </material>


	   <material name="Air" state="gas">
	       <D value="0.00129" />
	       <fraction n="0.7" ref="Nitrogen" />
	       <fraction n="0.3" ref="Oxygen" />
	   </material>

	   <material name="NEMAG10" state="solid">
	       <D unit="g/cm3" value="1.7"/>
	       <composite n="1" ref="Silicon"/>
	       <composite n="2" ref="Oxygen"/>
	       <composite n="3" ref="Carbon"/>
	       <composite n="4" ref="Hydrogen"/>
	   </material>

	   <material name="NOMEX_pure" state="solid">
	       <D unit="g/cm3" value="1.38"/>
	       <fraction n="0.23" ref="Chlorine"/>
	       <fraction n="0.09" ref="Nitrogen"/>
	       <fraction n="0.10" ref="Oxygen"/>
	       <fraction n="0.54" ref="Carbon"/>
	       <fraction n="0.04" ref="Hydrogen"/>
	   </material>

	   <material name="NOMEX" state="solid">
	       <D unit="g/cm3" value="0.04"/>
	       <fraction n="0.45" ref="NOMEX_pure"/>
	       <fraction n="0.55" ref="Air"/>
	   </material>

	   <material  name="Kapton" state="solid">
	       <D unit="g/cm3" value="1.42"/>
	       <fraction n="0.026" ref="Hydrogen"/>
	       <fraction n="0.692" ref="Carbon"/>
	       <fraction n="0.073" ref="Nitrogen"/>
	       <fraction n="0.209" ref="Oxygen"/>
	   </material>

	   <material Z="29" name="GEMCopper" state="solid">
	       <D unit="g/cm3" value="8.960"/>
	       <atom unit="g/mole" value="63.546"/>
	   </material>

	   <material Z="18" name="Argon" state="gas">
	       <D unit="g/L" value="1.662"/>
	       <atom unit="g/mole" value="39.948"/>
	   </material>

	   <material  name="CO2">
	       <D unit="g/cm3" value="1.563"/>
	       <composite n="1" ref="Carbon"/>
	       <composite n="2" ref="Oxygen"/>
	   </material>

	   <material name="GEMgas" state="gas">
	       <D unit="g/cm3" value="1e-25"/>
	       <fraction n="0.713" ref="Argon"/>
	       <fraction n="0.287" ref="CO2"/>
	   </material>

	   <material Z="82" name="Lead" state="solid">
	       <D unit="g/cm3" value="11.350"/>
	       <atom unit="g/mole" value="207.2"/>
	   </material>

        </materials>
	
	<solids>"""
#print """	      <cone name="backgemvol" aunit="deg" startphi="0" deltaphi="360" lunit="cm" rmin1="backgem_rmin1-%f" rmax1="backgem_rmax1" rmin2="backgem_rmin2" rmax2="backgem_rmax2+%f"  z="%f" />""" % (0.5, 0.5, motherdepth)
print """	      <cone name="backgemvol" aunit="deg" startphi="0" deltaphi="360" lunit="cm" rmin1="backgem_rmin1+%f" rmax1="backgem_rmax1" rmin2="backgem_rmin2" rmax2="backgem_rmax2+%f"  z="%f" />""" % (-0.5, 0.5, motherdepth)

"""	     <!--  Main 23 GEM layers -->"""

for i in range(nlayer):
    print "	         <tube name=\"backgemlay1_%02d\" aunit=\"deg\" startphi=\"-5\" deltaphi=\"10\" lunit=\"cm\" rmin=\"backgem_rmin1\" rmax=\"backgem_rmax1\" z=\"%f\" />" % (i, gemthick[i])

for i in range(nlayer):
    print "	         <tube name=\"backgemlay2_%02d\" aunit=\"deg\" startphi=\"-5\" deltaphi=\"10\" lunit=\"cm\" rmin=\"backgem_rmin2\" rmax=\"backgem_rmax2\" z=\"%f\" />" % (i, gemthick[i])

print """        </solids>

	<structure>
"""

# Make logical volumes
# We need unique volumes for detector layers, but not for non-detectors so
# that we can assign detector numbers
for i in range(nlayer):
    #  Non detector layer
    if not i in detlayer:
	####  First plane
	print """	         <volume name="logicbackgemlay1_%02d">
		      <materialref ref =\"%s\"/> 
		      <solidref ref =\"backgemlay1_%02d\"/>"""  % (i, gemmat[i], i)
        if i == 0 or i == nlayer-1: 
	    print """		      <auxiliary auxtype="Visibility" auxvalue="true"/>
		      <auxiliary auxtype="Color" auxvalue="Magenta"/>"""
        else:
	    print """		      <auxiliary auxtype="Visibility" auxvalue="false"/>"""

        print """		   </volume>"""
	####  Second plane
	print """	         <volume name="logicbackgemlay2_%02d">
		      <materialref ref =\"%s\"/> 
		      <solidref ref =\"backgemlay2_%02d\"/>"""  % (i, gemmat[i], i)
        if i == 0 or i == nlayer-1: 
	    print """		      <auxiliary auxtype="Visibility" auxvalue="true"/>
		      <auxiliary auxtype="Color" auxvalue="Magenta"/>"""
        else:
	    print """		      <auxiliary auxtype="Visibility" auxvalue="false"/>"""
        print """		   </volume>"""
    else: 
    #  Detector layers
	    for j in range(nsector):
		detno = backgemdet1no + j + 100*i
	        #  First plane
	        print """	         <volume name="logicbackgemlay1_%02d_%02d">
		      <materialref ref =\"%s\"/> 
		      <solidref ref =\"backgemlay1_%02d\"/>"""  % (i, j, gemmat[i], i)
	        print """		      <auxiliary auxtype="SensDet" auxvalue="planeDet"/>
		      <auxiliary auxtype="DetNo" auxvalue="%d"/>
		  </volume>""" % detno

	        detno = backgemdet2no + j + 100*i
	        #  Second plane
	        print """	         <volume name="logicbackgemlay2_%02d_%02d">
		      <materialref ref =\"%s\"/> 
		      <solidref ref =\"backgemlay2_%02d\"/>"""  % (i, j, gemmat[i], i)
	        print """		      <auxiliary auxtype="SensDet" auxvalue="planeDet"/>
		      <auxiliary auxtype="DetNo" auxvalue="%d"/>
		  </volume>""" % detno




print """
        <!---  Place volumes -->
	        <volume name="logicbackGEMMother">
		      <materialref ref="Vacuum"/>
		      <solidref ref="backgemvol"/>
	              <auxiliary auxtype="Visibility" auxvalue="false"/>
    """

print """	        <loop for=\"i0\" to=\"%d\" step=\"1\">""" % nsector

thisz = 0.0
for i in range(nlayer):
    if i > 0:
    	thisz += gemthick[i-1]/2.0

    thisz += gemthick[i]/2.0
    #  Non detector layer
    if not i in detlayer:
        print	"""                   <physvol>
                        <volumeref ref="logicbackgemlay1_%02d"/>
		        <position name="backgempos1_%02d" unit="cm" x="0" y="0" z="%f"/>
		        <rotation name="backgemrot1_%02d" unit="deg" x="0" y="0" z="360.0*i0/30"/>
                   </physvol>""" % (i, i, thisz + z1 - mother_z0, i)
        print	"""                   <physvol>
                        <volumeref ref="logicbackgemlay2_%02d"/>
		        <position name="backgempos2_%02d" unit="cm" x="0" y="0" z="%f"/>
		        <rotation name="backgemrot2_%02d" unit="deg" x="0" y="0" z="360.0*i0/30"/>
                   </physvol>""" % (i, i, thisz + z2 - mother_z0, i)

print """	        </loop>"""
	
# Calculate detector layer zposition
for k in range(len(detlayer)):
    thisz = 0.0
    for i in range(detlayer[k]+1):
         if i > 0:
	     thisz += gemthick[i-1]/2.0
         thisz += gemthick[i]/2.0

    for j in range(nsector):
	print	"""                <physvol>
		   <volumeref ref="logicbackgemlay1_%02d_%02d"/>
		   <position name="backgempos1_%02d_%02d" unit="cm" x="0" y="0" z="%f"/>
		   <rotation name="backgemrot1_%02d_%02d" unit="deg" x="0" y="0" z="360.0*%0.1f/30.0"/>
                </physvol>""" % (detlayer[k], j, detlayer[k], j, thisz + z1 - mother_z0, detlayer[k], j, float(j))
        print	"""                <physvol>
                   <volumeref ref="logicbackgemlay2_%02d_%02d"/>
		   <position name="backgempos2_%02d_%02d" unit="cm" x="0" y="0" z="%f"/>
		   <rotation name="backgemrot2_%02d_%02d" unit="deg" x="0" y="0" z="360.0*%0.1f/30.0"/>
                </physvol>""" % (detlayer[k], j, detlayer[k], j, thisz + z2 - mother_z0, detlayer[k], j, float(j))


print """
	        </volume>
	</structure>

	<setup name="backGEM" version="1.0">
	     <world ref="logicbackGEMMother"/>
	</setup>
</gdml>"""








