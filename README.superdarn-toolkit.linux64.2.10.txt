RST - SuperDARN Toolkit  2.10
===================================
R.J.Barnes

Version Log
===========

2.10     bug fixes to the fitacfex library and rnk hardware.dat
2.09     fixed known errors in the documentation - gold release
2.08     further bug fixes, fitacfex and documentation system
         included. 
2.07     introduced fitacf version 2.0 and numerous bug fixes
2.06     introduction of the origin flag and the beam azimuth parameter
	 together with numerous bug fixes
2.05     modification to deal with arbitrary numbers of radar beams
2.04     bug fixes from the deployment of the Radar Operating System
2.03     added ksh enviroment as an option plus more bug fixes
2.02     more bug fixes and more XML documentation completed.
2.01     various bug fixes and improvements to the IDL libraries
2.00     code adopted as official release.
1.07     numerous bug fixes.
1.06     completed IDL interfaces for grid and map data, incorporated help
         and error messages derived from XML documentation.
1.05     adopted the DataMap format for grid and map data, incorporated
         outline documentation and fixed a lot of bugs.
1.04     general bug fixes, addition of Mac OS X support
1.03	 implemented the legacy IDL interfaces and incorporated the
         data tables into this release
1.02	 incorporated the IDL interfaces and fixed a lot of bugs
1.01	 initial revision of the code.

Overview
========

The SuperDARN Toolkit contains the major part of the SuperDARN data analysis software. The software is distributed as a self extracting archive.

System Requirements
===================

	+ Any modern Linux distribution (RedHat, Suse, Debian) 
          or Mac OS X 10.3 
	 
	+ IDL 6.0 
	
	+ CDF 2.6 or higher (http://nssdc.gsfc.nasa.gov/cdf/cdf_home.html)

	+ netCDF 3.5 or higher (Optional)
          (http://my.unidata.ucar.edu/content/software/netcdf/index.html)

Note:
	To use the X displays you must have the X developement libraries installed on your Linux machine. Check your distribution documentation to see if you need to install them.

Installation
============

Copy the the installer into the directory that you wish to install the software. Next change the permissions on the file so that it is executable:
chmod u+x superdarn-toolkit.linux64.2.10.sh

Then run the installer:

./superdarn-toolkit.linux64.2.10.sh

This should install the source code for the software.

Before you can compile the software you will need to make some changes to the file "/rst/profile.superdarn-toolkit.tcsh". Look for the section entitled "Compilation directives" and then check the the paths given for the X11, netCDF, CDF software are correct. 
You should also check the the environment variable IDL_IPATH points to the directory that contains the IDL header files for compiling external software.

Next include these new environment variables in your default profile by adding the following line to ".cshrc":

source ${HOMEPATH}/profile.superdarn-toolkit.tcsh

Refresh your profile:

source ~/.cshrc

Now you can go ahead and compile the software:

/rst/script/make.all

A log of the compilation is recorded in the "log" directory of the installation.

IDL Interfaces
==============

This version of the software toolkit includes the necessary IDL libraries to work with SuperDARN data within IDL. Two versions of the routines are available, the native, IDL versions and the external interfaces that use the CALL_EXTERNAL function to interface with the C libraries. 
If your installation is correctly installed, the IDL routines will automatically detect whether they should use the native or the external routines. 
The libraries are located in the "rst/code/srd.idl/lib" directory, but symbolic links are created to the most recent versions of the libraring in the "/rst/idl/lib" directory.

Bugs/Comments
=============

Please Email bugs and/or comments to robin.barnes@jhuapl.edu









