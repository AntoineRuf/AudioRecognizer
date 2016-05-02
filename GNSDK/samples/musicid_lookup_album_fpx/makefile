#
# Makefile:
# gnsdk_musicid sample app
#

sdkdepends = musicid storage_sqlite dsp manager

ifeq ($(filter static, $(MAKECMDGOALS)), static)
	extra_libs = ../../xtralibs/ipp
endif

include ../sample_vars.mk
include $(build_dir)/rules_samples.mk
