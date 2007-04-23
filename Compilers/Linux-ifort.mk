# svn $Id$
#::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
# Copyright (c) 2002-2007 The ROMS/TOMS Group                           :::
#   Licensed under a MIT/X style license                                :::
#   See License_ROMS.txt                                                :::
#::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
#
# Include file for Intel IFORT (version 8.x) compiler on Linux
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
               FC := ifort
           FFLAGS :=
              CPP := /usr/bin/cpp
         CPPFLAGS := -P -traditional
               LD := $(FC)
          LDFLAGS := -Vaxlib
               AR := ar
          ARFLAGS := r
            MKDIR := mkdir -p
               RM := rm -f
           RANLIB := ranlib
             PERL := perl
             TEST := test

        MDEPFLAGS := --cpp --fext=f90 --file=- --objdir=$(SCRATCH_DIR)

#
# Library locations, can be overridden by environment variables.
#

       MCT_LIBDIR ?= /usr/local/mct/lib
    NETCDF_INCDIR ?= /opt/intelsoft/netcdf/include
    NETCDF_LIBDIR ?= /opt/intelsoft/netcdf/lib

         CPPFLAGS += -I$(NETCDF_INCDIR)
             LIBS := -L$(NETCDF_LIBDIR) -lnetcdf

ifdef ARPACK
 ifdef MPI
   PARPACK_LIBDIR ?= /opt/intelsoft/PARPACK
             LIBS += -L$(PARPACK_LIBDIR) -lparpack
 endif
    ARPACK_LIBDIR ?= /opt/intelsoft/PARPACK
             LIBS += -L$(ARPACK_LIBDIR) -larpack
endif

ifdef MPI
         CPPFLAGS += -DMPI
 ifdef MPIF90
#              FC := /opt/intelsoft/mpich2/bin/mpif90
               FC := /opt/intelsoft/mpich2-1.0.5/bin/mpif90
               LD := $(FC)
 else
             LIBS += -lfmpi-pgi -lmpi-pgi 
 endif
endif

ifdef OpenMP
         CPPFLAGS += -D_OPENMP
           FFLAGS += -openmp -fpp
endif

ifdef DEBUG
           FFLAGS += -g -check bounds
else
           FFLAGS += -ip -O3
 ifeq ($(CPU),i686)
           FFLAGS += -pc80 -xW
 endif
 ifeq ($(CPU),x86_64)
           FFLAGS += -xW
 endif
endif

ifdef SWAN_COUPLE
           FFLAGS += -FI -I/usr/local/mct/include
             LIBS += -L$(MCT_LIBDIR) -lmct -lmpeu
endif

       clean_list += ifc* work.pc*

#
# Set free form format in source files to allow long string for
# local directory and compilation flags inside the code.
#

$(SCRATCH_DIR)/mod_ncparam.o: FFLAGS += -free
$(SCRATCH_DIR)/mod_strings.o: FFLAGS += -free
