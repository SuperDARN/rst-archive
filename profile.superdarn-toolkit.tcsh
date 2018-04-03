# default .profile.toolkit


#####################################################################
#                                                                   #
# Base Data Tables                                                  #
#                                                                   #
#####################################################################

setenv FONTPATH "$HOMEPATH/tables/base/fonts"
setenv FONTDB "$HOMEPATH/tables/base/fonts/fontdb.xml"
setenv MAPDATA "$HOMEPATH/tables/general/map_data"
setenv BNDDATA "$HOMEPATH/tables/general/bnd_data"
setenv MAPOVERLAY "$HOMEPATH/tables/general/overlay.dat"

#####################################################################
#                                                                   #
# SuperDARN Data Tables                                             #
#                                                                   #
#####################################################################

setenv SD_HDWPATH "$HOMEPATH/tables/superdarn/hdw/"
setenv SD_RADAR "$HOMEPATH/tables/superdarn/radar.dat"

setenv AACGM_DAT_PREFIX "$HOMEPATH/tables/aacgm/aacgm_coeffs"
setenv IGRF_PATH "$HOMEPATH/tables/mag/"
setenv SD_MODEL_TABLE "$HOMEPATH/tables/superdarn/model"


#####################################################################
#                                                                   #
# Compilation directives                                            #
#                                                                   #
#####################################################################

# Path of the X11 packages

setenv XPATH /usr/X11R6

# Compile netCDF software

# setenv NETCDF_PATH /usr

# pathname for the CDF software

setenv CDF_PATH /usr/local/cdf

# IDL header directory

setenv IDL_IPATH /usr/local/rsi/idl/external/include

#####################################################################
#                                                                   #
# IDL Configuration                                                 #
#                                                                   #
#####################################################################

setenv IDL_PATH  +/usr/local/rsi:+/${HOMEPATH}/idl/lib
setenv IDL_STARTUP ${HOMEPATH}/idl/startup.pro

setenv LIB_FITIDL ${HOMEPATH}/lib/libfitidl.1.so
setenv LIB_RAWIDL ${HOMEPATH}/lib/librawidl.1.so
setenv LIB_OLDFITIDL ${HOMEPATH}/lib/liboldfitidl.1.so
setenv LIB_OLDRAWIDL ${HOMEPATH}/lib/liboldrawidl.1.so
setenv LIB_RPOSIDL ${HOMEPATH}/lib/librposidl.1.so
setenv LIB_AACGMIDL ${HOMEPATH}/lib/libaacgmidl.1.so
setenv LIB_IGRFIDL ${HOMEPATH}/lib/libigrfidl.1.so
setenv LIB_GEOPIDL ${HOMEPATH}/lib/libgeopidl.1.so

#####################################################################
#                                                                   #
# Legacy environment variables                                      #
#                                                                   #
#####################################################################

setenv SD_TABLES  ${HOMEPATH}/tables/idl
setenv SD_RAWROPEN_PATH :/data/raw/:.
setenv SD_FITROPEN_PATH :/data/fit/:.
setenv SD_IDL ${HOMEPATH}/idl/

