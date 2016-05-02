#
# GNSDK Build System: Platform Variable Setup
#

#
# TARGET PLATFORM: Mac OS X
#


ifneq ($(GNSDK_BUILD_PLATFORM),macos)
$(error Building MacOS X target is currently only supported on MacOS clients)
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
	SHARED_LIB_TARGET = $(subst group_library,$(group_name),$(SHARED_LIB_PATTERN)))
	STATIC_LIB_TARGET = $(subst group_library,$(group_name),$(STATIC_LIB_PATTERN)))
	SHARED_LINK_TARGET = $(subst group_library,$(group_name),$(SHARED_LINK_PATTERN)))
	STATIC_LINK_TARGET = $(subst group_library,$(group_name),$(STATIC_LINK_PATTERN)))
endif

#
# Tool Chain variables
#
OSX_VER = $(shell sw_vers -productVersion)
OSX_VER_MAJOR := $(shell echo $(OSX_VER) | cut -f1 -d.)
OSX_VER_MINOR := $(shell echo $(OSX_VER) | cut -f2 -d.)
OSX_GE_10_7 := $(shell [ $(OSX_VER_MAJOR) -ge 11 -o \( $(OSX_VER_MAJOR) -eq 10 -a $(OSX_VER_MINOR) -ge 7 \) ] && echo true)

DEVROOT_OSX = $(shell xcode-select -print-path)
ifeq ($(OSX_GE_10_7),true)
	TOOLDIR = $(DEVROOT_OSX)/Toolchains/XcodeDefault.xctoolchain/usr/bin/
	
	# Hack until gcsl_fingerprint succeeds on llvm
	GCSL_FP_FEATURES = 0
else
	TOOLDIR = /usr/bin/
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
CFLAGS_DEBUG=-g $(ARCHFLAGS) -fPIC -funsigned-char -Wall -pedantic -Wextra -Wno-long-long -Wno-variadic-macros -Wno-missing-field-initializers -Wpointer-arith -D_DEBUG 
CFLAGS_RELEASE=-Os $(ARCHFLAGS) -fPIC -funsigned-char -Wall -pedantic -Wextra -Wno-long-long -Wno-variadic-macros -Wno-missing-field-initializers -Wpointer-arith -DNDEBUG
CFLAGS_COVERAGE=$(CFLAGS_GCOV)

# Symbol export list
SYMBOL_EXPORT_LIST_OPTION= 
ifneq ($(SYMBOL_EXPORT_LIST),)
	SYMBOL_EXPORT_LIST_OPTION=-s $(SYMBOL_EXPORT_LIST)
endif

# Shared Linker
ifeq ($(OSX_GE_10_7),true)
	LD=$(TOOLDIR)clang
else
	LD=$(TOOLDIR)gcc
endif
LDOUTFLAG=-o 
LDFLAGS_DEBUG=-g $(ARCHFLAGS) -dynamiclib -single_module -install_name @loader_path/$(SHARED_LIB_TARGET)
LDFLAGS_RELEASE=$(ARCHFLAGS) -dynamiclib -single_module $(SYMBOL_EXPORT_LIST_OPTION) -install_name @loader_path/$(SHARED_LIB_TARGET)
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
LINKFLAGS_DEBUG=$(ARCHFLAGS) -lstdc++
LINKFLAGS_RELEASE=$(ARCHFLAGS) -lstdc++
LINKFLAGS_COVERAGE=$(LINKFLAGS_GCOV)

# Java
JDK_DIR=
JAVAC=javac
JAR=jar

# Other Tools
AR=$(TOOLDIR)ar
STRIP=$(TOOLDIR)strip
CP=cp -fp
MV=mv -f
SHOW_COVERAGE=$(SHOW_GCOV)
RESET_COVERAGE=$(RESET_GCOV)
CLEAN_COVERAGE=$(CLEAN_GCOV)

# check cross-compiling setting
ifeq ($(ARCH),)
	IMPLDIR = mac
	IMPLARCH = x86-64
	ifeq ($(OSX_GE_10_7),true)
		ARCHFLAGS = -arch x86_64 $(MIN_VERSION_OSX_FLAG)
	else
		ARCHFLAGS = -arch i386 -m64 $(MIN_VERSION_OSX_FLAG)
	
		# detect PPC
		arch := $(shell uname -m)
		ifneq ($(findstring Power, $(arch)),)
			IMPLARCH = ppc-32
			ARCHFLAGS= -arch ppc $(MIN_VERSION_OSX_FLAG)
		endif
	endif
	
else ifneq ($(filter i386 x86-32 x86,$(ARCH)),)
	IMPLDIR = mac
	IMPLARCH = x86-32
	ifeq ($(OSX_GE_10_7),true)
		ARCHFLAGS = -arch i386 $(MIN_VERSION_OSX_FLAG)
	else
		ARCHFLAGS = -arch i386 -m32 $(MIN_VERSION_OSX_FLAG)
	endif
	
else ifneq ($(filter x86_64 x86-64 x64,$(ARCH)),)
	IMPLDIR = mac
	IMPLARCH = x86-64
	ifeq ($(OSX_GE_10_7),true)
		ARCHFLAGS = -arch x86_64 $(MIN_VERSION_OSX_FLAG)
	else
		ARCHFLAGS = -arch i386 -m64 $(MIN_VERSION_OSX_FLAG)
	endif
	
else ifneq ($(filter ppc ppc32 ppc-32,$(ARCH)),)
	IMPLDIR = mac
	IMPLARCH = ppc-32
	ARCHFLAGS= -arch ppc -mmacosx-version-min=10.4

else ifneq ($(filter ppc64 ppc-64,$(ARCH)),)
	IMPLDIR = mac
	IMPLARCH = ppc-64
	ARCHFLAGS= -arch ppc64 -mmacosx-version-min=10.4

else
$(error ARCH="$(ARCH)" is unsupported.)
endif

