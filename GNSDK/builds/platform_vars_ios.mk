#
# GNSDK Build System: Platform Variable Setup
#

#
# TARGET PLATFORM: Mac iOS
#


ifneq ($(GNSDK_BUILD_PLATFORM),macos)
$(error Building iOS target is currently only supported on MacOS clients)
endif

ifeq ($(BUILD_ENV),swig)
SYMBOL_EXPORT_LIST=
else ifeq ($(GNSDK_WRAPPER_BUILD),1)
SYMBOL_EXPORT_LIST=
else
SYMBOL_EXPORT_LIST=-exported_symbols_list $(group_name)_exports.txt
endif

ifeq ($(SHARED_LIB_EXT),)
SHARED_LIB_EXT = dylib
endif

STATIC_LIB_EXT = a
SHARED_LINK_EXT = $(SHARED_LIB_EXT)
STATIC_LINK_EXT = a
	
APP_EXE_PATTERN := %
ifneq ($(LIBRARY_VERSION),)
SHARED_LIB_PATTERN := libgroup_library.$(LIBRARY_VERSION).$(SHARED_LIB_EXT)
else
SHARED_LIB_PATTERN := libgroup_library.$(SHARED_LIB_EXT)
endif
STATIC_LIB_PATTERN := libgroup_library.$(STATIC_LIB_EXT)
SHARED_LINK_PATTERN = $(SHARED_LIB_PATTERN)
STATIC_LINK_PATTERN = $(STATIC_LIB_PATTERN)

ifneq ($(library_name),)
	SHARED_LIB_TARGET = $(subst group,$(group_name),$(subst library,$(library_name),$(SHARED_LIB_PATTERN)))
	STATIC_LIB_TARGET = $(subst group,$(group_name),$(subst library,$(library_name),$(STATIC_LIB_PATTERN)))
	SHARED_LINK_TARGET = $(subst group,$(group_name),$(subst library,$(library_name),$(SHARED_LINK_PATTERN)))
	STATIC_LINK_TARGET = $(subst group,$(group_name),$(subst library,$(library_name),$(STATIC_LINK_PATTERN)))
else
	SHARED_LIB_TARGET = $(subst group_library,$(group_name),$(SHARED_LIB_PATTERN))
	STATIC_LIB_TARGET = $(subst group_library,$(group_name),$(STATIC_LIB_PATTERN))
	SHARED_LINK_TARGET = $(subst group_library,$(group_name),$(SHARED_LINK_PATTERN))
	STATIC_LINK_TARGET = $(subst group_library,$(group_name),$(STATIC_LINK_PATTERN))
endif

#
# Tool Chain variables
#
OSX_VER = $(shell sw_vers -productVersion)
OSX_VER_MAJOR := $(shell echo $(OSX_VER) | cut -f1 -d.)
OSX_VER_MINOR := $(shell echo $(OSX_VER) | cut -f2 -d.)
OSX_GE_10_7 := $(shell [ $(OSX_VER_MAJOR) -ge 11 -o \( $(OSX_VER_MAJOR) -eq 10 -a $(OSX_VER_MINOR) -ge 7 \) ] && echo true)

DEVROOT_IOS = $(shell xcode-select -print-path)
ifeq ($(OSX_GE_10_7),true)
	TOOLDIR = $(DEVROOT_IOS)/Toolchains/XcodeDefault.xctoolchain/usr/bin/
	
	# Hack until gcsl_fingerprint succeeds on llvm
	GCSL_FP_FEATURES = 0
else
	TOOLDIR = $(DEVROOT_IOS)/Platforms/$(PLATFORM_IOS).platform/Developer/usr/bin/
endif

MIN_VERSION_OSX_FLAG = -mmacosx-version-min=10.7



# gcov
CFLAGS_GCOV=-fprofile-arcs -ftest-coverage
LINKFLAGS_GCOV=$(CFLAGS_GCOV)
SHOW_GCOV=ls *.c | xargs gcov -o $(OUTPUT_DIR)/debug
RESET_GCOV=find . -type f -name '*.gcda' -print | xargs $(RM)
CLEAN_GCOV=-$(RM) *.gcov;$(RESET_GCOV)

# Compilation 
ifeq ($(OSX_GE_10_7),true)
	CC=$(TOOLDIR)clang
	CCPP=$(TOOLDIR)clang
else
	CC=$(TOOLDIR)gcc
	CCPP=$(TOOLDIR)gcc
endif
COUTFLAG=-o 
CWARNERR=-Werror
CDEFS=-D_THREAD_SAFE -D_REENTRANT -DGCSL_STRICT_HANDLES -DGNSDK_STRICT_HANDLES
CFLAGS_DEBUG=-g $(ARCHFLAGS) -fPIC -funsigned-char -Wall -Wformat -Wpointer-arith -D_DEBUG
CFLAGS_RELEASE=-O2 $(ARCHFLAGS) -fPIC -funsigned-char -Wall -Wformat -Wpointer-arith -DNDEBUG 

# Shared Linker
ifeq ($(OSX_GE_10_7),true)
	LD=$(TOOLDIR)clang
else
	LD=$(TOOLDIR)gcc
endif
LDOUTFLAG=-o 
LDFLAGS_DEBUG=$(ARCHFLAGS) -dynamiclib -single_module -install_name @loader_path/$(SHARED_LIB_TARGET)
LDFLAGS_RELEASE=$(ARCHFLAGS) -dynamiclib -single_module -s -exported_symbols_list $(group_name)_exports.txt -install_name @loader_path/$(SHARED_LIB_TARGET)
LDLIBS_PLATFORM=

ifneq ($(LIBRARY_VERSION),)
LDFLAGS_DEBUG+=-compatibility_version $(LIBRARY_VERSION) -current_version $(LIBRARY_VERSION)
LDFLAGS_RELEASE+=-compatibility_version $(LIBRARY_VERSION) -current_version $(LIBRARY_VERSION)
endif

# Static Linker Flags
LDS=$(TOOLDIR)ar
LDSOUTFLAG=
LDSFLAGS_DEBUG=rcs
LDSFLAGS_RELEASE=rcs
	
# Application Linker Flags
ifeq ($(OSX_GE_10_7),true)
	LINK=$(TOOLDIR)clang
else
	LINK=$(TOOLDIR)gcc
endif
LINKOUTFLAG=-o 
LINKFLAGS_DEBUG=$(ARCHFLAGS)
LINKFLAGS_RELEASE=$(ARCHFLAGS)

# Other Tools
AR=$(TOOLDIR)ar
STRIP=$(TOOLDIR)strip
CP=cp -fp
MV=mv -f

# check cross-compiling setting
ifeq ($(ARCH),ios_armv6)
	PLATFORM_IOS = iPhoneOS
	IMPLDIR = ios
	IMPLARCH = armv6-32
	ARCHFLAGS = -arch armv6 -isysroot $(SDKROOT_IOS) -miphoneos-version-min=$(MIN_VERSION_IOS) 
	STATIC = static
	
else ifeq ($(ARCH),ios_armv7)
	PLATFORM_IOS = iPhoneOS
	IMPLDIR = ios
	IMPLARCH = armv7-32
	ARCHFLAGS = -arch armv7 -isysroot $(SDKROOT_IOS) -miphoneos-version-min=$(MIN_VERSION_IOS)
	STATIC = static
	
else ifeq ($(ARCH),ios_armv7s)
	PLATFORM_IOS = iPhoneOS
	IMPLDIR = ios
	IMPLARCH = armv7s-32
	ARCHFLAGS = -arch armv7s -isysroot $(SDKROOT_IOS) -miphoneos-version-min=$(MIN_VERSION_IOS)
	STATIC = static

else ifeq ($(ARCH),ios_arm64)
        PLATFORM_IOS = iPhoneOS
        IMPLDIR = ios
        IMPLARCH = arm64
        ARCHFLAGS = -arch arm64 -isysroot $(SDKROOT_IOS) -miphoneos-version-min=$(MIN_VERSION_IOS)
        STATIC = static

else ifneq ($(filter ios_x86 ios_simulator,$(ARCH)),)
	PLATFORM_IOS = iPhoneSimulator
	IMPLDIR = ios
	IMPLARCH = x86-32
	ARCHFLAGS = -arch i386 -isysroot $(SDKROOT_IOS) -miphoneos-version-min=$(MIN_VERSION_IOS)
	STATIC = static
	
else ifneq ($(filter ios_x64,$(ARCH)),)
	PLATFORM_IOS = iPhoneSimulator
	IMPLDIR = ios
	IMPLARCH = x86-64
	ARCHFLAGS = -arch x86_64 -isysroot $(SDKROOT_IOS) -miphoneos-version-min=$(MIN_VERSION_IOS)
	STATIC = static


else
$(error ARCH="$(ARCH)" is unsupported. Try ios_armv6, ios_armv7, ios_armv7s, ios_arm64, ios_x86, ios_x64, ios_simulator.)
endif

# check IOS SDK is available
MIN_VERSION_IOS = 6.0
MAX_VERSION_IOS = 8.3
SDKROOT_IOS = $(DEVROOT_IOS)/Platforms/$(PLATFORM_IOS).platform/Developer/SDKs/$(PLATFORM_IOS)$(MAX_VERSION_IOS).sdk

# check 8.0 SDK is available
ifeq ($(wildcard $(SDKROOT_IOS)),)
$(info '$(SDKROOT_IOS)' not found)
	# then check 8.2 SDK is available
	MAX_VERSION_IOS = 8.2
	CCTOOL=gcc
	ifeq ($(wildcard $(SDKROOT_IOS)),)
$(info '$(SDKROOT_IOS)' not found)
		# then check 8.1 SDK is available
		MAX_VERSION_IOS = 8.1
		CCTOOL=gcc
		ifeq ($(wildcard $(SDKROOT_IOS)),)
$(info '$(SDKROOT_IOS)' not found)	
			# then check 8.0 SDK is available
			MAX_VERSION_IOS = 8.0
			CCTOOL=gcc
			ifeq ($(wildcard $(SDKROOT_IOS)),)
$(info '$(SDKROOT_IOS)' not found)
				# then check 7.1 SDK is available
				MAX_VERSION_IOS = 7.1
				ifeq ($(wildcard $(SDKROOT_IOS)),)
# if still not available, error
$(error Could not locale suitable iPhone development SDK)
				endif
			endif
		endif
	endif
endif
	
