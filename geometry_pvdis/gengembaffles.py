#!/usr/bin/python

frontgemdet1no = 1000
frontgemdet2no = 2000

#bafmat = "Kryptonite"
bafmat = "Lead"

####################################################################
# Beampipe/general parameters

piperad1 = 2.0
piperad2 = 20.0
outrad   = 140.0

nsector = 30

####################################################################
# GEM parameters

z1 = 157.5
z2 = 185.5

r1min = 48.0 
r1max = 122.0

r2min = 59.0
r2max = 143.0

rot1 = -2
rot2 = -4

nlayer  = 23

gemthick = (0.012,0.0003,0.012,0.005,0.0005,0.3,0.0005,0.005,0.0005,0.2,0.0005,0.005,0.0005,0.2,0.0005,0.005,0.0005,0.2,0.001,0.005,0.012,0.0003,0.012)
gemmat  = ("NEMAG10","NOMEX","NEMAG10","Kapton","GEMCopper","GEMgas","GEMCopper","Kapton","GEMCopper","GEMgas","GEMCopper","Kapton","GEMCopper","GEMgas","GEMCopper","Kapton","GEMCopper","GEMgas","GEMCopper","Kapton","NEMAG10","NOMEX","NEMAG10")

detlayer = (4,5,6,18)


####################################################################
# Baffle parameters

nbaf = 6

nblock = 20

z_baf = (40,68,96,124,152,180)
bafdepth = 9.0


rin_outbaf  = (34.8,54.3,73.9,93.4,112.8,132.1)
rout_outbaf = (140,140,140,140,140,140) #coil edge is at 142cm


rin_inbaf  = (3.89,14.,19.,23.9,28.9,33.8)
rout_inbaf = (3.9,15.3,26.6,37.9,49.2,60.4)



####################################################################
# Baffle definition

mybaf = (
	[   3.900000, 5.445000, 7.900000, 5.490000,
	    5.445000, 6.990000, 6.887500, 6.075000,
	    6.990000, 8.535000, 6.662500, 6.300000,
	    8.535000, 10.080000, 5.830000, 6.525000,
	    10.080000, 11.625000, 5.177500, 6.885000,
	    11.625000, 13.170000, 4.952500, 6.885000,
	    13.170000, 14.715000, 4.345000, 6.885000,
	    14.715000, 16.260000, 3.850000, 7.110000,
	    16.260000, 17.805000, 3.277000, 7.470000,
	    17.805000, 19.350000, 3.034000, 7.740000,
	    19.350000, 20.895000, 2.791000, 8.010000,
	    20.895000, 22.440000, 2.588500, 8.235000,
	    22.440000, 23.985000, 2.224000, 8.640000,
	    23.985000, 25.530000, 2.021500, 8.865000,
	    25.530000, 27.075000, 1.697500, 9.225000,
	    27.075000, 28.620000, 1.373500, 9.585000,
	    28.620000, 30.165000, 1.292500, 9.675000,
	    30.165000, 31.710000, 0.766000, 9.948000,
	    31.710000, 33.255000, 0.482500, 9.885000,
	    33.255000, 34.800000, 0.280000, 9.840000,
	    ],
	    [   15.300000, 17.250000, 8.998000, 5.436000,
	    17.250000, 19.200000, 8.102500, 6.075000,
	    19.200000, 21.150000, 7.922500, 6.255000,
	    21.150000, 23.100000, 7.135000, 6.678000,
	    23.100000, 25.050000, 6.554500, 7.083000,
	    25.050000, 27.000000, 6.329500, 7.173000,
	    27.000000, 28.950000, 5.722000, 7.416000,
	    28.950000, 30.900000, 5.272000, 7.704000,
	    30.900000, 32.850000, 4.771000, 8.077200,
	    32.850000, 34.800000, 4.582000, 8.282400,
	    34.800000, 36.750000, 4.393000, 8.487600,
	    36.750000, 38.700000, 4.235500, 8.658600,
	    38.700000, 40.650000, 3.952000, 8.966400,
	    40.650000, 42.600000, 3.794500, 9.137400,
	    42.600000, 44.550000, 3.542500, 9.411000,
	    44.550000, 46.500000, 3.290500, 9.684600,
	    46.500000, 48.450000, 3.227500, 9.753000,
	    48.450000, 50.400000, 2.818000, 9.948000,
	    50.400000, 52.350000, 2.597500, 9.885000,
	    52.350000, 54.300000, 2.440000, 9.840000,
	    ],
	[   26.600000, 28.965000, 10.096000, 5.382000,
	    28.965000, 31.330000, 9.317500, 6.075000,
	    31.330000, 33.695000, 9.182500, 6.210000,
	    33.695000, 36.060000, 8.440000, 6.831000,
	    36.060000, 38.425000, 7.931500, 7.281000,
	    38.425000, 40.790000, 7.706500, 7.461000,
	    40.790000, 43.155000, 7.099000, 7.947000,
	    43.155000, 45.520000, 6.694000, 8.298000,
	    45.520000, 47.885000, 6.265000, 8.684400,
	    47.885000, 50.250000, 6.130000, 8.824800,
	    50.250000, 52.615000, 5.995000, 8.965200,
	    52.615000, 54.980000, 5.882500, 9.082200,
	    54.980000, 57.345000, 5.680000, 9.292800,
	    57.345000, 59.710000, 5.567500, 9.409800,
	    59.710000, 62.075000, 5.387500, 9.597000,
	    62.075000, 64.440000, 5.207500, 9.784200,
	    64.440000, 66.805000, 5.162500, 9.831000,
	    66.805000, 69.170000, 4.870000, 9.948000,
	    69.170000, 71.535000, 4.712500, 9.885000,
	    71.535000, 73.900000, 4.600000, 9.840000,
	    ],
	[   37.900000, 40.675000, 11.194000, 5.328000,
		40.675000, 43.450000, 10.532500, 6.075000,
		43.450000, 46.225000, 10.442500, 6.165000,
		46.225000, 49.000000, 9.745000, 6.984000,
		49.000000, 51.775000, 9.308500, 7.479000,
		51.775000, 54.550000, 9.083500, 7.749000,
		54.550000, 57.325000, 8.476000, 8.478000,
		57.325000, 60.100000, 8.116000, 8.892000,
		60.100000, 62.875000, 7.759000, 9.291600,
		62.875000, 65.650000, 7.678000, 9.367200,
		65.650000, 68.425000, 7.597000, 9.442800,
		68.425000, 71.200000, 7.529500, 9.505800,
		71.200000, 73.975000, 7.408000, 9.619200,
		73.975000, 76.750000, 7.340500, 9.682200,
		76.750000, 79.525000, 7.232500, 9.783000,
		79.525000, 82.300000, 7.124500, 9.883800,
		82.300000, 85.075000, 7.097500, 9.909000,
		85.075000, 87.850000, 6.922000, 9.948000,
		87.850000, 90.625000, 6.827500, 9.885000,
		90.625000, 93.400000, 6.760000, 9.840000,
		],
	[   49.200000, 52.380000, 12.292000, 5.274000,
		52.380000, 55.560000, 11.747500, 6.075000,
		55.560000, 58.740000, 11.702500, 6.120000,
		58.740000, 61.920000, 11.050000, 7.137000,
		61.920000, 65.100000, 10.685500, 7.677000,
		65.100000, 68.280000, 10.460500, 8.037000,
		68.280000, 71.460000, 9.853000, 9.009000,
		71.460000, 74.640000, 9.538000, 9.486000,
		74.640000, 77.820000, 9.253000, 9.898800,
		77.820000, 81.000000, 9.226000, 9.909600,
		81.000000, 84.180000, 9.199000, 9.920400,
		84.180000, 87.360000, 9.176500, 9.929400,
		87.360000, 90.540000, 9.136000, 9.945600,
		90.540000, 93.720000, 9.113500, 9.954600,
		93.720000, 96.900000, 9.077500, 9.969000,
		96.900000, 100.080000, 9.041500, 9.983400,
		100.080000, 103.260000, 9.032500, 9.987000,
		103.260000, 106.440000, 8.974000, 9.948000,
		106.440000, 109.620000, 8.942500, 9.885000,
		109.620000, 112.800000, 8.920000, 9.840000,
		],
	[   60.400000, 63.985000, 13.390000, 5.220000,
		63.985000, 67.570000, 12.962500, 6.075000,
		67.570000, 71.155000, 12.962500, 6.075000,
		71.155000, 74.740000, 12.355000, 7.290000,
		74.740000, 78.325000, 12.062500, 7.875000,
		78.325000, 81.910000, 11.837500, 8.325000,
		81.910000, 85.495000, 11.230000, 9.540000,
		85.495000, 89.080000, 10.960000, 10.080000,
		89.080000, 92.665000, 10.747000, 10.506000,
		92.665000, 96.250000, 10.774000, 10.452000,
		96.250000, 99.835000, 10.801000, 10.398000,
		99.835000, 103.420000, 10.823500, 10.353000,
		103.420000, 107.005000, 10.864000, 10.272000,
		107.005000, 110.590000, 10.886500, 10.227000,
		110.590000, 114.175000, 10.922500, 10.155000,
		114.175000, 117.760000, 10.958500, 10.083000,
		117.760000, 121.345000, 10.967500, 10.065000,
		121.345000, 124.930000, 11.026000, 9.948000,
		124.930000, 128.515000, 11.057500, 9.885000,
		128.515000, 132.100000, 11.080000, 9.840000,
		],
)


####################################################################

# Virtual detector in front of each baffle
detthick = 0.0001

motherdepth = (z2+1.0)-(z_baf[0]-bafdepth/2)+2.0*detthick

# lab coordinate z of center of mother volume
# This needs to agree with main gdml coordinate
mother_z0 = ( (z2+1.0)+(z_baf[0]-bafdepth/2) )/2


####################################################################

header = """<?xml version="1.0" encoding="UTF-8"?>
<gdml xmlns:gdml="http://cern.ch/2001/Schemas/GDML" xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance" xsi:noNamespaceSchemaLocation="schema/gdml.xsd">
    <!-- Back GEMs -->

        <define>
	   <position name="frontgem_origin" x="0.0" y="0.0" z="0.0" unit="cm"/>
	   <rotation name="identity"/>
	   <variable name="i0" value="1"/>
	   <variable name="i1" value="1"/>"""

print header

print "\t   <constant name=\"frontgem_z1\" value=\"%f\"/>" % z1
print "\t   <constant name=\"frontgem_z2\" value=\"%f\"/>" % z2
print "\t   <constant name=\"frontgem_rmin1\" value=\"%f\"/>" % r1min
print "\t   <constant name=\"frontgem_rmax1\" value=\"%f\"/>" % r1max
print "\t   <constant name=\"frontgem_rmin2\" value=\"%f\"/>" % r2min
print "\t   <constant name=\"frontgem_rmax2\" value=\"%f\"/>" % r2max

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

	   <material Z="82" name="Kryptonite" state="solid">
	       <D unit="g/cm3" value="11.350"/>
	       <atom unit="g/mole" value="207.2"/>
	   </material>

        </materials>
	
	<solids>"""
print """	      <cone name="frontgemvol" aunit="deg" startphi="0" deltaphi="360" lunit="cm" rmin1="%f" rmax1="%f" rmin2="%f" rmax2="%f"  z="%f" />""" % (piperad1, outrad, piperad2, outrad, motherdepth)

print """	     <!--  Main 23 GEM layers -->"""

for i in range(nlayer):
    print "	         <tube name=\"frontgemlay1_%02d\" aunit=\"deg\" startphi=\"-5\" deltaphi=\"10\" lunit=\"cm\" rmin=\"frontgem_rmin1\" rmax=\"frontgem_rmax1\" z=\"%f\" />" % (i, gemthick[i])

for i in range(nlayer):
    print "	         <tube name=\"frontgemlay2_%02d\" aunit=\"deg\" startphi=\"-5\" deltaphi=\"10\" lunit=\"cm\" rmin=\"frontgem_rmin2\" rmax=\"frontgem_rmax2\" z=\"%f\" />" % (i, gemthick[i])

print """	     <!-- Baffle rings/dets -->"""

for i in range(nbaf):
    print """	         <tube name="bafring_in_%02d" aunit="deg" startphi="0" deltaphi="360" lunit="cm" rmin="%f" rmax="%f" z="%f" />""" % (i, rin_inbaf[i], rout_inbaf[i],  bafdepth)
    print """	         <tube name="bafring_out_%02d" aunit="deg" startphi="0" deltaphi="360" lunit="cm" rmin="%f" rmax="%f" z="%f" />""" % (i, rin_outbaf[i], rout_outbaf[i],  bafdepth)
    print """	         <tube name="bafdet_%02d" aunit="deg" startphi="0" deltaphi="360" lunit="cm" rmin="%f" rmax="%f" z="%f" />""" % (i, rout_inbaf[i], rin_outbaf[i], detthick)


print """	     <!-- Baffle block -->"""

for i in range(nbaf):
      for j in range(nblock):
	  sphi = mybaf[i][j*4+2]
	  dphi = mybaf[i][j*4+3]

	  startphi = sphi + dphi
	  stopphi  = sphi + 360/nsector
	  phidiff  = stopphi - startphi

	  print """	         <tube name="bafblock_%02d_%02d" aunit="deg" startphi="%f" deltaphi="%f" lunit="cm" rmin="%f" rmax="%f" z="%f" />""" % (i, j, startphi, phidiff, mybaf[i][j*4], mybaf[i][j*4+1],  bafdepth)




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
	print """	         <volume name="logicfrontgemlay1_%02d">
		      <materialref ref =\"%s\"/> 
		      <solidref ref =\"frontgemlay1_%02d\"/>"""  % (i, gemmat[i], i)
        if i == 0 or i == nlayer-1: 
	    print """		      <auxiliary auxtype="Visibility" auxvalue="true"/>
		      <auxiliary auxtype="Color" auxvalue="Magenta"/>"""
        else:
	    print """		      <auxiliary auxtype="Visibility" auxvalue="false"/>"""
        print """		   </volume>"""
	####  Second plane
	print """	         <volume name="logicfrontgemlay2_%02d">
		      <materialref ref =\"%s\"/> 
		      <solidref ref =\"frontgemlay2_%02d\"/>"""  % (i, gemmat[i], i)
        if i == 0 or i == nlayer-1: 
	    print """		      <auxiliary auxtype="Visibility" auxvalue="true"/>
		      <auxiliary auxtype="Color" auxvalue="Magenta"/>"""
        else:
	    print """		      <auxiliary auxtype="Visibility" auxvalue="false"/>"""
        print """		   </volume>"""
    else: 
    #  Detector layers
	for j in range(nsector):
	    detno = frontgemdet1no + j + 100*i
	    #  First plane
	    print """	         <volume name="logicfrontgemlay1_%02d_%02d">
		      <materialref ref =\"%s\"/> 
		      <solidref ref =\"frontgemlay1_%02d\"/>"""  % (i, j, gemmat[i], i)
	    print """		      <auxiliary auxtype="SensDet" auxvalue="planeDet"/>
		      <auxiliary auxtype="DetNo" auxvalue="%d"/>
	          </volume>""" % detno
	    #  Second plane
	    detno = frontgemdet2no + j + 100*i
	    print """	         <volume name="logicfrontgemlay2_%02d_%02d">
		      <materialref ref =\"%s\"/> 
		      <solidref ref =\"frontgemlay2_%02d\"/>"""  % (i, j, gemmat[i], i)
	    print """		      <auxiliary auxtype="SensDet" auxvalue="planeDet"/>
		      <auxiliary auxtype="DetNo" auxvalue="%d"/>
                  </volume>""" % detno

for i in range(nbaf):
    	    #  Inner baffle ring
	    print """	         <volume name="logicbafring_in_%02d">
		      <materialref ref ="%s"/> 
		      <solidref ref ="bafring_in_%02d"/>
	              <auxiliary auxtype="Visibility" auxvalue="true"/>
		      <auxiliary auxtype="Color" auxvalue="Cyan"/>
		      </volume>""" % (i, bafmat, i)
    	    #  Outer baffle ring
	    print """	         <volume name="logicbafring_out_%02d">
		      <materialref ref ="%s"/> 
		      <solidref ref ="bafring_out_%02d"/>
	              <auxiliary auxtype="Visibility" auxvalue="true"/>
		      <auxiliary auxtype="Color" auxvalue="Cyan"/>
		      </volume>""" % (i, bafmat, i)
	    # Detector for baffle
	    print """	         <volume name="logicbafdet_%02d">
		      <materialref ref ="%s"/> 
		      <solidref ref ="bafdet_%02d"/>
	              <auxiliary auxtype="Visibility" auxvalue="false"/>
		      <auxiliary auxtype="SensDet" auxvalue="planeDet"/>
		      <auxiliary auxtype="DetNo" auxvalue="%d"/>
		      </volume>""" % (i, "Air", i, 10+i+1)

for i in range(nbaf):
      for j in range(nblock):
	    print """	         <volume name="logicbafblock_%02d_%02d">
		      <materialref ref ="%s"/> 
		      <solidref ref ="bafblock_%02d_%02d"/>
	              <auxiliary auxtype="Visibility" auxvalue="true"/>
		      <auxiliary auxtype="Color" auxvalue="Cyan"/>
		      </volume>""" % (i,j, bafmat, i, j)

print """
        <!---  Place volumes -->
	        <volume name="logicGEMbafflesMother">
		      <materialref ref="Vacuum"/>
		      <solidref ref="frontgemvol"/>
	              <auxiliary auxtype="Visibility" auxvalue="false"/>
    """

print """	        <loop for=\"i0\" to=\"%d\" step=\"1\">""" % nsector

#######  GEM positioning
thisz = 0.0
for i in range(nlayer):
    if i > 0:
    	thisz += gemthick[i-1]/2.0

    thisz += gemthick[i]/2.0
    #  Non detector layer
    if not i in detlayer:
        print	"""                   <physvol>
                        <volumeref ref="logicfrontgemlay1_%02d"/>
		        <position name="frontgempos1_%02d" unit="cm" x="0" y="0" z="%f"/>
		        <rotation name="frontgemrot1_%02d" unit="deg" x="0" y="0" z="360.0*i0/%d+%f"/>
                   </physvol>""" % (i, i, thisz + z1 - mother_z0, i, nsector, rot1)
        print	"""                   <physvol>
                        <volumeref ref="logicfrontgemlay2_%02d"/>
		        <position name="frontgempos2_%02d" unit="cm" x="0" y="0" z="%f"/>
		        <rotation name="frontgemrot2_%02d" unit="deg" x="0" y="0" z="360.0*i0/%d+%f"/>
                   </physvol>""" % (i, i, thisz + z2 - mother_z0, i, nsector, rot2)

print """	        </loop>"""
	
for k in range(len(detlayer)):
  # Calculate detector layer zposition
  thisz = 0.0
  for i in range(detlayer[k]+1):
    if i > 0:
    	thisz += gemthick[i-1]/2.0
    thisz += gemthick[i]/2.0

  for j in range(nsector):
        print	"""                <physvol>
                   <volumeref ref="logicfrontgemlay1_%02d_%02d"/>
		   <position name="frontgempos1_%02d_%02d" unit="cm" x="0" y="0" z="%f"/>
		   <rotation name="frontgemrot1_%02d_%02d" unit="deg" x="0" y="0" z="360.0*%0.1f/%d+%f"/>
                </physvol>""" % (detlayer[k], j, detlayer[k], j, thisz + z1 - mother_z0, detlayer[k], j, float(j), nsector, rot1)
        print	"""                <physvol>
                   <volumeref ref="logicfrontgemlay2_%02d_%02d"/>
		   <position name="frontgempos2_%02d_%02d" unit="cm" x="0" y="0" z="%f"/>
		   <rotation name="frontgemrot2_%02d_%02d" unit="deg" x="0" y="0" z="360.0*%0.1f/%d+%f"/>
                </physvol>""" % (detlayer[k], j, detlayer[k], j, thisz + z2 - mother_z0, detlayer[k], j, float(j), nsector, rot2)

#######  Baffle Ring/Detector positioning
for i in range(nbaf):
        print	"""                <physvol>
                   <volumeref ref="logicbafring_in_%02d"/>
		   <position name="bafringinpos1_%02d" unit="cm" x="0" y="0" z="%f"/>
                </physvol>""" % (i, i, z_baf[i] - mother_z0 )
        print	"""                <physvol>
                   <volumeref ref="logicbafring_out_%02d"/>
		   <position name="bafringoutpos1_%02d" unit="cm" x="0" y="0" z="%f"/>
                </physvol>""" % (i, i, z_baf[i] - mother_z0 )
        print	"""                <physvol>
                   <volumeref ref="logicbafdet_%02d"/>
		   <position name="bafdetpos1_%02d" unit="cm" x="0" y="0" z="%f"/>
                </physvol>""" % (i, i, z_baf[i] - bafdepth/2.0 - detthick/2 - mother_z0 )


#######  Baffle block positioning
print """	        <loop for=\"i1\" to=\"%d\" step=\"1\">""" % nsector
for i in range(nbaf):
      for j in range(nblock):
	  print	"""                    <physvol>
                       <volumeref ref="logicbafblock_%02d_%02d"/>
		       <position name="bafblockpos_%02d_%02d" unit="cm" x="0" y="0" z="%f"/>
		       <rotation name="bafblockrot_%02d_%02d" unit="deg" x="0" y="0" z="(i1-1)*360.0/%d"/>
                    </physvol>""" % (i, j, i, j, z_baf[i] - mother_z0,  i,j,nsector )

print """	        </loop>"""

print """
	        </volume>
	</structure>

	<setup name="GEMbaffles" version="1.0">
	     <world ref="logicGEMbafflesMother"/>
	</setup>
</gdml>"""








