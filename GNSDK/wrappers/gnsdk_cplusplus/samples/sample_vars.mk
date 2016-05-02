group_name = sample
appname = sample

ifneq "$(wildcard ../../../../builds )" ""

	# Code samples
	build_dir = ../../../../builds
	install_dir = ../../../..

else ifneq "$(wildcard ../../../../../builds )" ""
	
	build_dir = ../../../../../builds
	install_dir = $(build_dir)/../install/common

else

$(error Where am I? Can't find builds dir)

endif

include $(build_dir)/platform_vars.mk

# C++ sources and Loader
extra_srcs += ../../src_wrapper ../../src_marshal ../../src_helpers ../../../../xtralibs/bass

# Audio Library
extra_libs += ../../../../xtralibs/bass

# IPP dependency
ifeq ($(extra_libs),../../xtralibs/ipp)
	ifeq "$(wildcard ../../builds )" ""
		extra_libs = ../../../../xtralibs/ipp
	endif
endif

include $(build_dir)/rules_samples.mk

# Platform dependencies
ifeq ($(IMPLDIR),win)
	platformlibs += winmm.lib
else ifeq ($(IMPLDIR), mac)
	platformlibs += -framework AudioToolbox
endif
