CXXFLAGS += -std=c++1y

GCC_HOME = /usr/bin

CC  := $(GCC_HOME)/g++
CXX := $(CC)
LD  := $(CC)

###############################################################################
# Dependency info

PARSERS.deps                    :=  TOOLS
PARSERSDEFAULT.deps             :=  PARSERS
CASNUMBER.deps                  :=  PARSERS
CASNUMBERDEFAULT.deps           :=  CASNUMBER
CASEXPR.deps                    :=  CASNUMBER
CASEXPRBASIC.deps               :=  CASEXPR
CASEXPRBUILDERS.deps            :=  CASEXPRBASIC
CASCREATION.deps                :=  CASEXPR
CASCREATIONPARSERS.deps         :=  CASCREATION
CASVISITING.deps                :=  CASEXPRBASIC
CASVISITINGNUMEVAL.deps         :=  CASVISITING
CASVISITINGRENDERING.deps       :=  CASVISITING
CASVISITINGRENDERINGINFIX.deps  :=  CASVISITINGRENDERING
CASVISITINGRESTRUCTURING.deps   :=  CASVISITING
CASREDUCTION.deps               :=  CASVISITINGRESTRUCTURING

CLI.deps   := NBRS                       \
              CASNUMBER                  \
              CASNUMBERDEFAULT           \
              CASEXPRBUILDERS            \
              PARSERSDEFAULT             \
              CASREDUCTION               \
              CASVISITINGNUMEVAL         \
              CASVISITINGRESTRUCTURING   \
              CASVISITINGRENDERINGINFIX  \
              CASCREATION                \
              CASCREATIONPARSERS         \
              CASEXPR                    \
              CASEXPRBASIC               \
              PARSERS                    \
              CASVISITING                \
              CASVISITINGRENDERING

IFACE.deps := NBRS                       \
              CASNUMBER                  \
              CASNUMBERDEFAULT           \
              CASEXPRBUILDERS            \
              PARSERSDEFAULT             \
              CASREDUCTION               \
              CASVISITINGNUMEVAL         \
              CASVISITINGRESTRUCTURING   \
              CASVISITINGRENDERINGINFIX  \
              CASCREATION                \
              CASCREATIONPARSERS         \
              CASEXPR                    \
              CASEXPRBASIC               \
              PARSERS                    \
              CASVISITING                \
              CASVISITINGRENDERING

#LIB.deps  := LIB_INT

# This is the location holding the main runnable program
#MAIN_PROGRAM := CMD

################################
$(call enter,src)
