CXXFLAGS += -std=c++1z

# Enable if you need to
#STATIC_LIBSTDCXX=

###############################################################################
# Dependency info

PARSERS.deps          := UTILS
CASNUMBER.deps        := PARSERS UTILS
CASEXPR.deps          := CASNUMBER
CASRENDERING.deps     := CASEXPR UTILS
CASREDUCTION.deps     := CASEXPR

CLI.deps   := NBRS             \
              CASNUMBER        \
              CASREDUCTION     \
              CASEXPR          \
              PARSERS          \
              CASRENDERING

IFACE.deps := NBRS             \
              CASNUMBER        \
              CASREDUCTION     \
              CASEXPR          \
              PARSERS          \
              CASRENDERING

#LIB.deps  := LIB_INT

# This is the location holding the main runnable program
main_is := CLI

################################
$(call enter,src)
