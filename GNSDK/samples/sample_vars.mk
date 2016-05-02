group_name = sample
appname = sample

build_dir = ../../../builds
install_dir = ../../../install/common

# C++ sources and Loader
#extra_srcs += ../../xtralibs/bass

# Audio Library
#extra_libs += ../../xtralibs/bass

ifeq ($(extra_libs),../../xtralibs/ipp)
ifeq "$(wildcard ../../xtralibs/ipp )" ""
extra_libs = ../../../../xtralibs/ipp
endif
endif

# Code samples
ifneq "$(wildcard ../../builds )" ""
build_dir = ../../builds
install_dir = ../../..
endif

# Code snippets
ifneq "$(wildcard ../builds )" ""
build_dir = ../builds
install_dir = ../..
else ifeq ($(snippet),1)
build_dir = ../../../../../../builds
install_dir = ../../../../../../install/common
endif

ifeq ($(IMPLDIR),linux)
platformlibs = -lstdc++
endif

ifeq ($(IMPLDIR),qnx)
platformlibs = -lstdc++
endif

