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
PARSERSDEFAULT.deps             :=  PARSERS
CASNUMBER.deps                  :=  PARSERS CASUTILS
CASNUMBERDEFAULT.deps           :=  CASNUMBER
CASEXPR.deps                    :=  CASNUMBER
CASEXPRS.deps                   :=  CASEXPR CASVISITING
CASEXPRBUILDERS.deps            :=  CASEXPRS
CASCREATION.deps                :=  CASEXPR
CASCREATIONPARSERS.deps         :=  CASCREATION
CASVISITING.deps                :=  CASEXPR
CASVISITORSNUMEVAL.deps         :=  CASVISITING CASEXPRS
CASVISITORSRENDERING.deps       :=  CASVISITING CASEXPRS
CASVISITORSRENDERINGINFIX.deps  :=  CASVISITORSRENDERING CASEXPRS
CASVISITORSRESTRUCTURING.deps   :=  CASVISITING CASEXPRS
CASREDUCTION.deps               :=  CASVISITORSRESTRUCTURING

CLI.deps   := NBRS                       \
              CASNUMBER                  \
              CASNUMBERDEFAULT           \
              CASEXPRBUILDERS            \
              PARSERSDEFAULT             \
              CASREDUCTION               \
              CASVISITORSNUMEVAL         \
              CASVISITORSRESTRUCTURING   \
              CASVISITORSRENDERINGINFIX  \
              CASCREATION                \
              CASCREATIONPARSERS         \
              CASEXPR                    \
              CASEXPRS                   \
              PARSERS                    \
              CASVISITING                \
              CASVISITORSRENDERING

IFACE.deps := NBRS                       \
              CASNUMBER                  \
              CASNUMBERDEFAULT           \
              CASEXPRBUILDERS            \
              PARSERSDEFAULT             \
              CASREDUCTION               \
              CASVISITORSNUMEVAL         \
              CASVISITORSRESTRUCTURING   \
              CASVISITORSRENDERINGINFIX  \
              CASCREATION                \
              CASCREATIONPARSERS         \
              CASEXPR                    \
              CASEXPRS                   \
              PARSERS                    \
              CASVISITING                \
              CASVISITORSRENDERING

#LIB.deps  := LIB_INT

# This is the location holding the main runnable program
main_is := CLI

################################
$(call enter,src)
