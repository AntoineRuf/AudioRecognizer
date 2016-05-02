#
# GNSDK Build System: Platform Variable Setup
#

#
# TARGET PLATFORM: Windows 32/64-bit
#


ifneq ($(GNSDK_BUILD_PLATFORM),windows)
$(error Building MSWindows target is currently only supported on Windows clients)
endif

ifeq ($(SHARED_LIB_EXT),)
SHARED_LIB_EXT = dll
endif

STATIC_LIB_EXT = lib
SHARED_LINK_EXT = $(STATIC_LIB_EXT)
STATIC_LINK_EXT = $(STATIC_LIB_EXT)

APP_EXE_PATTERN := %.exe
SHARED_LIB_PATTERN := group_library.$(SHARED_LIB_EXT)
STATIC_LIB_PATTERN := group_library.$(STATIC_LIB_EXT)
SHARED_LINK_PATTERN := group_library.$(STATIC_LIB_EXT)
STATIC_LINK_PATTERN := group_library.$(STATIC_LIB_EXT)

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

TOOLDIR=

# Compilation 
CCPP=$(CC)
COUTFLAG=-Fo
CWARNERR=-WX
PDB_NAME=$(group_library_name)
CDEFS_COMMON = -DWIN32 -DUNICODE -D_UNICODE -D_CRT_SECURE_NO_WARNINGS -D_CRT_SECURE_NO_DEPRECATE -D_WIN32_WINNT=0x0501 -DGCSL_STRICT_HANDLES -DGNSDK_STRICT_HANDLES
CFLAGS_DEBUG=-Od -MTd -J -W4 -GS -GF -Gm- -RTC1 -nologo -Zi -EHsc -Fd$(PDB_NAME) -D_DEBUG $(CDEFS_COMMON)
CFLAGS_RELEASE=-O2 -MT -J -W4 -GS -GF -Gm- -Zi -EHsc -Fd$(PDB_NAME) -DNDEBUG $(CDEFS_COMMON)

# dynamic library building
ifdef NMCL
	ifdef no_nmcl
		LD=$(TOOLDIR)/link.exe
	else
		LD=nmlink.exe $(NMCL)
	endif
else
	LD=$(TOOLDIR)/link.exe
endif
LDOUTFLAG=-OUT:
LDFLAGS_DEBUG=-NOLOGO -DEBUG -DLL -DEF:$(group_name)_exports.def -DYNAMICBASE -NXCOMPAT -INCREMENTAL:NO -NODEFAULTLIB:libcmt.lib
LDFLAGS_RELEASE=-NOLOGO -DEBUG -DLL -DEF:$(group_name)_exports.def -RELEASE -OPT:REF -OPT:ICF -DYNAMICBASE -NXCOMPAT -INCREMENTAL:NO -NODEFAULTLIB:libcmtd.lib
LDLIBS_PLATFORM=ws2_32.lib advapi32.lib

# static library building
LDS=$(TOOLDIR)/lib.exe
LDSOUTFLAG=-OUT:
LDSFLAGS_DEBUG=-NOLOGO
LDSFLAGS_RELEASE=-NOLOGO

# application linking
LINK=$(TOOLDIR)/link.exe
LINKOUTFLAG=-OUT:
LINKFLAGS_DEBUG=-NOLOGO -DEBUG -NODEFAULTLIB:libcmt.lib
LINKFLAGS_RELEASE=-NOLOGO -RELEASE -NODEFAULTLIB:libcmtd.lib

# resource compiling
RC=rc.exe
RCOUTFLAG=-fo
RCFLAGS_DEBUG=-d_DEBUG
RCFLAGS_RELEASE=

# Java
JDK_DIR=
JAVAC=javac
JAR=jar

# CSharp
CSHARP_CC=csc.exe
CSHARP_OUTFLAG=-OUT:
CSHARP_FLAGS=/noconfig /nowarn:1701,1702 /nostdlib+ /errorreport:prompt /warn:4 /define:TRACE
CSHARP_REFERENCES=/r:mscorlib.dll /r:System.Core.dll /r:System.Data.DataSetExtensions.dll /r:System.Data.dll /r:System.dll /r:System.Xml.dll /r:System.Xml.Linq.dll

# Other Tools
AR=
STRIP=
CP=cp -fpu
MV=mv -f


ifeq ($(ARCH),)
	# detect 32/64-bit compiler (since arch is driven by compiler, not flags)
	ccver := $(shell cl.exe 2>&1)
	ifneq ($(findstring x86,$(ccver)),)
		IMPLDIR = win
		IMPLARCH = x86-32
		TOOLDIR := "$(shell cygpath -u $$VCINSTALLDIR)/bin"
		TOOLDIR := $(TOOLDIR:%/=%)
		ifneq ($(ARCH),)
			ifeq ($(filter i386 x86_32 x86-32 x86,$(ARCH)),)
				IMPLARCH =
			endif
		endif
	else ifneq ($(findstring x64,$(ccver)),)
		IMPLDIR = win
		IMPLARCH = x86-64
		TOOLDIR := "$(shell cygpath -u $$VCINSTALLDIR)/bin/amd64"
		TOOLDIR := $(TOOLDIR:%/=%)
		ifneq ($(ARCH),)
			ifeq ($(filter x86_64 x86-64 x64,$(ARCH)),)
				IMPLARCH =
			endif
		endif
	endif

	# set compiler version (needed for Windows static lib linking)
	ifneq ($(findstring Version 18,$(ccver)),)
		COMPILER_VER=vs13
	else ifneq ($(findstring Version 17,$(ccver)),)
		COMPILER_VER=vs12
	else ifneq ($(findstring Version 16,$(ccver)),)
		COMPILER_VER=vs10
	else
		COMPILER_VER=vs8
	endif

	ifdef NMCL
		ifdef no_nmcl
			CC=$(TOOLDIR)/cl.exe
		else
			CC=nmcl.exe $(NMCL)
		endif
	else
		CC=$(TOOLDIR)/cl.exe
	endif
endif

ifneq ($(filter arm arm-32,$(ARCH)),)
	GNSDK_BUILD_PLATFORM=linux
	include $(build_dir)/platform_vars_linux.mk
endif

ifneq ($(filter arm arm-32,$(ARCH)),)
	GNSDK_BUILD_PLATFORM=linux
	include $(build_dir)/platform_vars_linux.mk
endif

ifeq ($(IMPLARCH),)
$(error ARCH="$(ARCH)" is unsupported. Windows can't cross compile (use different vcvars.bat setting))
endif

ifeq ($(IMPLARCH),x86-32)
	LDFLAGS_DEBUG += -SAFESEH
	LDFLAGS_RELEASE += -SAFESEH
endif

#If the SUBSYTEM link flag is set use what they gave us
ifeq ($(findstring SUBSYSTEM,$(LINKFLAGS)),)

	ifeq ($(SUBSYSTEM),)
		#Default to CONSOLE SUBSYSTEM
		SUBSYSTEM = CONSOLE
	endif

	ifeq ($(MINVERSION),)
		#Set the minversion so apps we build will run on Windows XP/2000
		#Different architectures need different minversions
		ifeq ($(IMPLARCH),x86-32)
			MINVERSION = 5.01
		else ifeq ($(IMPLARCH),x86-64)
			MINVERSION = 5.02
		endif
	endif

	ifeq ($(MINVERSION),)
		LINKFLAGS_DEBUG += -SUBSYSTEM:$(SUBSYSTEM)
		LINKFLAGS_RELEASE += -SUBSYSTEM:$(SUBSYSTEM)
	else
		LINKFLAGS_DEBUG += -SUBSYSTEM:$(SUBSYSTEM),$(MINVERSION)
		LINKFLAGS_RELEASE += -SUBSYSTEM:$(SUBSYSTEM),$(MINVERSION)
	endif

endif


