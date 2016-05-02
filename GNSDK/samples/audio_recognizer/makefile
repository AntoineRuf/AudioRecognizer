#
# Makefile:
# gnsdk_musicid sample app
#

sdkdepends = musicid lookup_local storage_sqlite dsp musicid_stream lookup_localstream manager

ifeq ($(filter static, $(MAKECMDGOALS)), static)
	extra_libs = ../../xtralibs/ipp
endif

include ../sample_vars.mk
include $(build_dir)/rules_samples.mk

