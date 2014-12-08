# $Id: GNUmakefile 66376 2012-12-18 09:42:59Z gcosmo $
# ----------------------------------------------------------------
# Makes test program in environment variable G4TARGET.
# ----------------------------------------------------------------

ifndef G4TARGET
  G4TARGET := $(TESTTARGET)
endif

ifndef G4INSTALL
  G4INSTALL = ../../..
endif

include $(G4INSTALL)/config/architecture.gmk

# Override some variables for binmake.gmk.
#
# INCFLAGS := 
# LDLIBS :=

include $(G4INSTALL)/config/binmake.gmk
