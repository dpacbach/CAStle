###############################################################################
# This is where all of the top-level, project-specific information is supplied.

CFLAGS         += -MMD -MP -m64 -Wall -Wpedantic
CXXFLAGS       += $(CFLAGS) -std=c++1y

CFLAGS_DEBUG   += $(CXXFLAGS) -g -ggdb -gstabs
CFLAGS_RELEASE += $(CXXFLAGS) -Ofast -march=corei7 -mtune=corei7

CFLAGS_LIB     += -fPIC

ifdef OPT
    CXXFLAGS_TO_USE = $(CFLAGS_RELEASE)
else
    CXXFLAGS_TO_USE = $(CFLAGS_DEBUG)
endif

GCC_HOME = /usr/local/bin

CC  := $(GCC_HOME)/g++
CXX := $(CC)
LD  := $(CC)

LDFLAGS     :=
LDFLAGS_LIB := $(LDFLAGS) -shared

INSTALL_PREFIX := $(HOME)/tmp

ifeq ($(OS),OSX)
    CFLAGS          += -DOS_OSX
else
    CFLAGS          += -DOS_LINUX
endif

###############################################################################
# Dependency info

PARSERS.deps              := TOOLS
PARSERSDEFAULT.deps       := PARSERS

CASNUMBER.deps            := PARSERS
CASNUMBERDEFAULT.deps     := CASNUMBER

CASEXPR.deps              := CASNUMBER
CASEXPRBASIC.deps         := CASEXPR
CASEXPRBUILDERS.deps      := CASEXPRBASIC

CASCREATION.deps        := CASEXPR
CASCREATIONPARSERS.deps := CASCREATION

CASVISITING.deps               := CASEXPRBASIC
CASVISITINGNUMEVAL.deps        := CASVISITING
CASVISITINGRENDERING.deps      := CASVISITING
CASVISITINGRENDERINGINFIX.deps := CASVISITINGRENDERING

CASVISITINGRESTRUCTURING.deps  := CASVISITING

CASREDUCTION.deps              := CASVISITINGRESTRUCTURING

CLI.deps := NBRS \
            CASNUMBER \
            CASNUMBERDEFAULT \
            CASEXPRBUILDERS \
            PARSERSDEFAULT \
            CASREDUCTION \
            CASVISITINGNUMEVAL \
            CASVISITINGRESTRUCTURING \
            CASVISITINGRENDERINGINFIX \
            CASCREATION \
            CASCREATIONPARSERS \
            CASEXPR \
            CASEXPRBASIC \
            PARSERS \
            CASVISITING \
            CASVISITINGRENDERING

#LIB.deps  := LIB_INT

# This is the location holding the main runnable program
#MAIN_PROGRAM := CMD
