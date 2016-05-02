#
# GNSDK Build System: Platform Variable Setup
#

#
# TARGET PLATFORM: Android
#

ifeq ($(GNSDK_BUILD_PLATFORM),windows)
	NDK_ROOT := $(strip $$NDK_ROOT)
else
	NDK_ROOT := $(strip $(NDK_ROOT))
endif

ifeq ($(NDK_ROOT),)
$(error Need to set NDK_ROOT environment variable to location of Android NDK)
else
	ifneq ($(words $(NDK_ROOT)),1)
$(info The Android NDK installation path contains spaces: '$(NDK_ROOT)')
$(error Please fix the problem by reinstalling to a different location.)
	endif
	ifneq ($(findstring CYGWIN, $(UNAME)),)
		NDK_ROOT:=$(shell cygpath -u $(NDK_ROOT))
	endif
	# get rid of trailing slash
	NDK_ROOT := $(NDK_ROOT:%/=%)
endif


# different sysroot and tools based on architecture
ARMEABIV7A_FLAGS=
ifeq ($(ARCH),android_armeabi)
	IMPLARCH = armeabi
	SYSROOT_ARCH = arm
	TOOLNAME = arm-linux-androideabi-4.6
	TOOLPREFIX = arm-linux-androideabi
	ARCHFLAGS = -mfpu=vfp -mfloat-abi=softfp -ffunction-sections -funwind-tables -fstack-protector -fomit-frame-pointer -fno-strict-aliasing -finline-limit=64 -Wa,--noexecstack -Wno-psabi
	
else ifeq ($(ARCH),android_armeabi-v7a)
	IMPLARCH = armeabi-v7a
	SYSROOT_ARCH = arm
	TOOLNAME = arm-linux-androideabi-4.6
	TOOLPREFIX = arm-linux-androideabi
	ARCHFLAGS =  -mfpu=vfpv3-d16 -mfloat-abi=softfp -ffunction-sections -funwind-tables -fstack-protector -fomit-frame-pointer -fno-strict-aliasing -finline-limit=64 -Wa,--noexecstack -Wno-psabi -march=armv7-a
	
else ifeq ($(ARCH),android_mips)
	IMPLARCH = mips
	SYSROOT_ARCH = mips
	TOOLNAME = mipsel-linux-android-4.6
	TOOLPREFIX = mipsel-linux-android
	ARCHFLAGS = -ffunction-sections -funwind-tables -fstack-protector -fomit-frame-pointer -fno-strict-aliasing -finline-limit=64 -Wa,--noexecstack -Wno-psabi -funsigned-char
	
else ifeq ($(ARCH),android_x86)
	IMPLARCH = x86
	SYSROOT_ARCH = x86
	TOOLNAME = x86-4.6
	TOOLPREFIX = i686-linux-android
	ARCHFLAGS = -ffunction-sections -funwind-tables -fstack-protector -fomit-frame-pointer -fno-strict-aliasing -finline-limit=64 -Wa,--noexecstack -Wno-psabi -Wall -fpic -pipe -DANDROID -DNDEBUG -mtune=atom -march=atom -msse3 -mssse3 -m32 -funsigned-char
	LD_ARCHFLAGS += -lm -lz -Wl,--no-undefined -Wl,-z,noexecstack -mtune=atom -march=atom -no-canonical-prefixes -landroid
	
else
$(error ARCH="$(ARCH)" is unsupported. Try android_armeabi, android_armeabi-v7a, android_mips & android_x86)
endif


SYSROOT:=$(NDK_ROOT)/platforms/android-9/arch-$(SYSROOT_ARCH)
ifneq ($(findstring CYGWIN, $(UNAME)),)
	SYSROOT:=$(shell cygpath -m $(SYSROOT))
endif


ifeq ($(GNSDK_BUILD_PLATFORM),macos)
	TOOLDIR=$(NDK_ROOT)/toolchains/$(TOOLNAME)/prebuilt/darwin-x86/bin
	ifeq ($(shell if [ -d $(TOOLDIR) ];then echo "found";fi),)
		TOOLDIR=$(NDK_ROOT)/toolchains/$(TOOLNAME)/prebuilt/darwin-x86_64/bin
		ifneq ($(shell test -d $(TOOLDIR)),)
$(error Cannot find appropriate tool chain)		
		endif
	endif
	
else ifeq ($(GNSDK_BUILD_PLATFORM),linux)
	TOOLDIR=$(NDK_ROOT)/toolchains/$(TOOLNAME)/prebuilt/linux-x86/bin
	ifeq ($(shell if [ -d $(TOOLDIR) ];then echo "found";fi),)
		TOOLDIR=$(NDK_ROOT)/toolchains/$(TOOLNAME)/prebuilt/linux-x86_64/bin
		ifneq ($(shell test -d $(TOOLDIR)),)
$(error Cannot find appropriate tool chain)		
		endif
	endif
			
else ifeq ($(GNSDK_BUILD_PLATFORM),windows)
	TOOLDIR=$(NDK_ROOT)/toolchains/$(TOOLNAME)/prebuilt/windows/bin
	ifeq ($(shell if [ -d $(TOOLDIR) ];then echo "found";fi),)
		TOOLDIR=$(NDK_ROOT)/toolchains/$(TOOLNAME)/prebuilt/windows-x86_64/bin
		ifneq ($(shell test -d $(TOOLDIR)),)
$(error Cannot find appropriate tool chain)		
		endif
	endif	

else
$(error Build system not setup to build on '$(GNSDK_BUILD_PLATFORM)')
endif


SHARED_LIB_EXT = so
STATIC_LIB_EXT = a
SHARED_LINK_EXT = $(STATIC_LIB_EXT)
STATIC_LINK_EXT = $(STATIC_LIB_EXT)

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

IMPLDIR = android

LD_ARCHFLAGS += -shared -lc -ldl -lm -lstdc++

CC=$(TOOLDIR)/$(TOOLPREFIX)-gcc --sysroot=$(SYSROOT)
CCPP=$(TOOLDIR)/$(TOOLPREFIX)-g++ --sysroot=$(SYSROOT)
CFLAGS_DEBUG += -g $(ARCHFLAGS) -DANDROID -D_DEBUG -D_REENTRANT -D_THREAD_SAFE
CFLAGS_RELEASE += -Os -O2 $(ARCHFLAGS) -DANDROID -DNDEBUG -D_REENTRANT -D_THREAD_SAFE
COUTFLAG=-o

LD=$(TOOLDIR)/$(TOOLPREFIX)-gcc --sysroot=$(SYSROOT)
LDOUTFLAG=-o
LDFLAGS_DEBUG+=$(LD_ARCHFLAGS) -llog -D_THREAD_SAFE
LDFLAGS_RELEASE+=$(LD_ARCHFLAGS) -D_THREAD_SAFE

LDS=$(TOOLDIR)/$(TOOLPREFIX)-ar
LDSOUTFLAG=
LDSFLAGS_DEBUG=rcs
LDSFLAGS_RELEASE=rcs

LINK=$(TOOLDIR)/$(TOOLPREFIX)-gcc --sysroot=$(SYSROOT)
LINKOUTFLAG=-o 
LINKFLAGS_DEBUG=$(LD_ARCHFLAGS)
LINKFLAGS_RELEASE=$(LD_ARCHFLAGS)

AR=$(TOOLDIR)/$(TOOLPREFIX)-ar

CP=cp -fp
MV=mv -f

# Java
JDK_DIR=
JAVAC=javac -source 1.6 -target 1.6
JAR=jar
JAVAH=javah

