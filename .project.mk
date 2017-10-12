CXXFLAGS += -std=c++1y

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

PARSERS.deps                    :=  TOOLS
CASNUMBER.deps                  :=  PARSERS CASUTILS
CASEXPR.deps                    :=  CASNUMBER
CASCREATION.deps                :=  CASEXPR
CASCREATIONPARSERS.deps         :=  CASCREATION
CASVISITORSNUMEVAL.deps         :=  CASEXPR
CASVISITORSRENDERING.deps       :=  CASEXPR
CASVISITORSRENDERINGINFIX.deps  :=  CASVISITORSRENDERING
CASVISITORSRESTRUCTURING.deps   :=  CASEXPR
CASREDUCTION.deps               :=  CASVISITORSRESTRUCTURING

CLI.deps   := NBRS                       \
              CASNUMBER                  \
              CASREDUCTION               \
              CASVISITORSNUMEVAL         \
              CASVISITORSRESTRUCTURING   \
              CASVISITORSRENDERINGINFIX  \
              CASCREATION                \
              CASCREATIONPARSERS         \
              CASEXPR                    \
              PARSERS                    \
              CASEXPR                    \
              CASVISITORSRENDERING

IFACE.deps := NBRS                       \
              CASNUMBER                  \
              CASREDUCTION               \
              CASVISITORSNUMEVAL         \
              CASVISITORSRESTRUCTURING   \
              CASVISITORSRENDERINGINFIX  \
              CASCREATION                \
              CASCREATIONPARSERS         \
              CASEXPR                    \
              PARSERS                    \
              CASEXPR                    \
              CASVISITORSRENDERING

#LIB.deps  := LIB_INT

# This is the location holding the main runnable program
main_is := CLI

################################
$(call enter,src)
