CXXFLAGS += -std=c++1z

GPLUSPLUS ?= /usr/bin/g++

CC  := $(GPLUSPLUS)
CXX := $(GPLUSPLUS)
LD  := $(GPLUSPLUS)

ifeq ($(OS),Linux)
    # On linux let's do a static linkage
    LDFLAGS += -static-libgcc -static-libstdc++
endif

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
