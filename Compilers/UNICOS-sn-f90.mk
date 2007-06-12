# svn $Id$
#::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
# Copyright (c) 2002-2007 The ROMS/TOMS Group                           :::
#   Licensed under a MIT/X style license                                :::
#   See License_ROMS.txt                                                :::
#::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
#
# Include file for UNICOS F90 compiler on CRAY T3D
# -------------------------------------------------------------------------
#
# ARPACK_LIBDIR  ARPACK libary directory
# FC             Name of the fortran compiler to use
# FFLAGS         Flags to the fortran compiler
# CPP            Name of the C-preprocessor
# CPPFLAGS       Flags to the C-preprocessor
# CLEAN          Name of cleaning executable after C-preprocessing
# NETCDF_INCDIR  NetCDF include directory
# NETCDF_LIBDIR  NetCDF libary directory
# LD             Program to load the objects into an executable
# LDFLAGS        Flags to the loader
# RANLIB         Name of ranlib command
# MDEPFLAGS      Flags for sfmakedepend  (-s if you keep .f files)
#
# First the defaults
#
               FC := f90
           FFLAGS := -e Im
              CPP := /opt/ctl/bin/cpp
         CPPFLAGS := -P -N
               LD := $(FC)
          LDFLAGS :=
               AR := ar
          ARFLAGS := -r
            MKDIR := mkdir -p
               RM := rm -f
           RANLIB := touch
             PERL := perl
             TEST := test

        MDEPFLAGS := --cpp --fext=f90 --file=- --objdir=$(SCRATCH_DIR)

#
# Names of module files for netCDF f90 interface: override the lower-case
# file names specified in makefile
#

   NETCDF_MODFILE := NETCDF.mod
TYPESIZES_MODFILE := TYPESIZES.mod

#
# Library locations, can be overridden by environment variables.
#

       MCT_INCDIR ?= /usr/local/mct/include
       MCT_LIBDIR ?= /usr/local/mct/lib
    NETCDF_INCDIR ?= /usr/local/include
    NETCDF_LIBDIR ?= /usr/local/lib

         CPPFLAGS += -I$(NETCDF_INCDIR)
             LIBS := -L$(NETCDF_LIBDIR) -lnetcdf

ifdef USE_ARPACK
 ifdef USE_MPI
   PARPACK_LIBDIR ?= /usr/local/lib
             LIBS += -L$(PARPACK_LIBDIR) -lparpack
 endif
    ARPACK_LIBDIR ?= /usr/local/lib
             LIBS += -L$(ARPACK_LIBDIR) -larpack
endif

ifdef USE_MPI
         CPPFLAGS += -DMPI
endif

ifdef USE_OpenMP
         CPPFLAGS += -D_OPENMP
endif

ifdef USE_DEBUG
           FFLAGS += -g -O 0 -e in -R abcnp
else
           FFLAGS += -O3
endif

ifdef SWAN_COUPLE
           FFLAGS += -I$(MCT_INCDIR)
             LIBS += -L$(MCT_LIBDIR) -lmct -lmpeu
endif

#
# Set free form format in source files to allow long string for
# local directory and compilation flags inside the code.
#

$(SCRATCH_DIR)/mod_ncparam.o: FFLAGS += -f free
$(SCRATCH_DIR)/mod_strings.o: FFLAGS += -f free

#
# Supress free format in SWAN source files since there are comments
# beyond column 72.
#

ifdef SWAN_COUPLE

$(SCRATCH_DIR)/ocpcre.o: FFLAGS += -f fixed
$(SCRATCH_DIR)/ocpids.o: FFLAGS += -f fixed
$(SCRATCH_DIR)/ocpmix.o: FFLAGS += -f fixed
$(SCRATCH_DIR)/swancom1.o: FFLAGS += -f fixed
$(SCRATCH_DIR)/swancom2.o: FFLAGS += -f fixed
$(SCRATCH_DIR)/swancom3.o: FFLAGS += -f fixed
$(SCRATCH_DIR)/swancom4.o: FFLAGS += -f fixed
$(SCRATCH_DIR)/swancom5.o: FFLAGS += -f fixed
$(SCRATCH_DIR)/swanmain.o: FFLAGS += -f fixed
$(SCRATCH_DIR)/swanout1.o: FFLAGS += -f fixed
$(SCRATCH_DIR)/swanout2.o: FFLAGS += -f fixed
$(SCRATCH_DIR)/swanparll.o: FFLAGS += -f fixed
$(SCRATCH_DIR)/swanpre1.o: FFLAGS += -f fixed
$(SCRATCH_DIR)/swanpre2.o: FFLAGS += -f fixed
$(SCRATCH_DIR)/swanser.o: FFLAGS += -f fixed
$(SCRATCH_DIR)/swmod1.o: FFLAGS += -f fixed
$(SCRATCH_DIR)/swmod2.o: FFLAGS += -f fixed
$(SCRATCH_DIR)/swmod3.o: FFLAGS += -f fixed

endif
