#
# GNSDK Build System: Platform Variable Setup
#

#
# TARGET PLATFORM: Linux
#


ifneq ($(GNSDK_BUILD_PLATFORM),linux)
$(error Building Linux target is currently only supported on Linux clients)
endif


SHARED_LIB_EXT = so
STATIC_LIB_EXT = a
SHARED_LINK_EXT = $(STATIC_LIB_EXT)
STATIC_LINK_EXT = $(STATIC_LIB_EXT)

APP_EXE_PATTERN := %
ifneq ($(LIBRARY_VERSION),)
SHARED_LIB_PATTERN := libgroup_library.$(SHARED_LIB_EXT).$(LIBRARY_VERSION)
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

TOOLDIR=

# gcov
CFLAGS_GCOV=-fprofile-arcs -ftest-coverage
LINKFLAGS_GCOV=$(CFLAGS_GCOV)
SHOW_GCOV=ls *.c | xargs gcov -o $(OUTPUT_DIR)/debug
RESET_GCOV=find . -type f -name '*.gcda' -print | xargs $(RM)
CLEAN_GCOV=-$(RM) *.gcov;$(RESET_GCOV)

# Compilation 
CC=$(TOOLDIR)gcc
CCPP=$(TOOLDIR)gcc
COUTFLAG=-o
CWARNERR=-Werror
CDEFS=-D_THREAD_SAFE -D_REENTRANT -DGCSL_STRICT_HANDLES -DGNSDK_STRICT_HANDLES
CFLAGS_DEBUG=-g $(ARCHFLAGS) -fPIC -funsigned-char -Wall -Wformat -Wpointer-arith -D_DEBUG
CFLAGS_RELEASE=-O2 $(ARCHFLAGS) -fPIC -funsigned-char -Wall -Wformat -Wpointer-arith -DNDEBUG
CFLAGS_COVERAGE=$(CFLAGS_GCOV)

# Shared Linker
LD=$(TOOLDIR)gcc
LDOUTFLAG=-o
LDFLAGS_DEBUG=$(LD_ARCHFLAGS)
LDFLAGS_RELEASE=$(LD_ARCHFLAGS)
LDLIBS_PLATFORM = -lpthread -lm -ldl -lrt -Wl,-soname,$(SHARED_LIB_TARGET)

# Static Linker Flags
LDS=$(TOOLDIR)ar
LDSOUTFLAG=
LDSFLAGS_DEBUG=rcs
LDSFLAGS_RELEASE=rcs

# Application Linker Flags
LINK=$(TOOLDIR)gcc
LINKOUTFLAG=-o 
LINKFLAGS_DEBUG=$(ARCHFLAGS) -Wl,-rpath,'$$ORIGIN'
LINKFLAGS_RELEASE=$(ARCHFLAGS) -Wl,-rpath,'$$ORIGIN'
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
	# detect 64/32-bit linux
	arch := $(shell uname -m)
	ifeq ($(arch), x86_64)
		ARCH=x86_64
	else
		ARCH=x86
	endif
endif
	
ifneq ($(filter i386 x86_32 x86-32 x86,$(ARCH)),)
	IMPLDIR = linux
	IMPLARCH = x86-32
	ARCHFLAGS = -m32
	LD_ARCHFLAGS = -m32 -shared -Wl,-rpath,'$$ORIGIN'
	CFLAGS_DEBUG += -Wno-unused-but-set-variable
	CFLAGS_RELEASE += -Wno-unused-but-set-variable

else ifneq ($(filter x86_64 x86-64 x64,$(ARCH)),)
	IMPLDIR = linux
	IMPLARCH = x86-64
	ARCHFLAGS = -m64
	LD_ARCHFLAGS = -m64 -shared -Wl,-rpath,'$$ORIGIN'
	CFLAGS_DEBUG += -Wno-unused-but-set-variable
	CFLAGS_RELEASE += -Wno-unused-but-set-variable

# check AISIN-AW SDK is available
else ifneq ($(filter arm-32aw,$(ARCH)),)
	CC=/opt/montavista/tools/arm-gnueabi/bin/arm-montavista-linux-gnueabi-gcc-4.4.1
	LD=/opt/montavista/tools/arm-gnueabi/bin/arm-montavista-linux-gnueabi-gcc-4.4.1
	LINK=/opt/montavista/tools/arm-gnueabi/bin/arm-montavista-linux-gnueabi-gcc-4.4.1
	LDS=/opt/montavista/tools/arm-gnueabi/bin/arm-montavista-linux-gnueabi-ar
	STRIP=/opt/montavista/tools/arm-gnueabi/bin/arm-montavista-linux-gnueabi-strip
	IMPLDIR = linux
	IMPLARCH = arm-32aw
	ARCHFLAGS = -tarmv6 -fexpensive-optimizations -fomit-frame-pointer -frename-registers -O0 -g -D_GNU_SOURCE -Wcast-align -I/opt/default-rootfs-image/usr/include
	LD_ARCHFLAGS = -shared -Wl,-rpath,'$$ORIGIN',-O0 -L$(WORK_ROOT)/runtime/lib/$(TARGET_CPU) -L$(WORK_ROOT)/runtime/bin/$(TARGET_CPU) --sysroot=/opt/default-rootfs-image -L/opt/default-rootfs-image/lib  -Wl,-rpath-link,/opt/default-rootfs-image/lib -L/opt/default-rootfs-image/usr/lib -Wl,-rpath-link,/opt/default-rootfs-image/usr/lib -L/opt/montavista/tools/arm-gnueabi/arm-montavista-linux-gnueabi/libc/lib -Wl,-rpath-link,/opt/montavista/tools/arm-gnueabi/arm-montavista-linux-gnueabi/libc/lib -L/opt/montavista/tools/arm-gnueabi/arm-montavista-linux-gnueabi/libc/usr/lib -Wl,-rpath-link,/opt/montavista/tools/arm-gnueabi/arm-montavista-linux-gnueabi/libc/usr/lib
	LDLIBS_PLATFORM = -lpthread -lm -ldl -lrt
	LINKLIBS_PLATFORM =
	#STATIC = static

else ifneq ($(filter arm arm-32,$(ARCH)),)
	CC=arm-none-linux-gnueabi-gcc
	CCPP=arm-none-linux-gnueabi-gcc
	LD=arm-none-linux-gnueabi-gcc
	LINK=arm-none-linux-gnueabi-gcc
	LDS=arm-none-linux-gnueabi-ar
	STRIP=arm-none-linux-gnueabi-strip
	IMPLDIR = linux
	IMPLARCH = arm-32
	ARCHFLAGS = 
	LD_ARCHFLAGS = -shared -Wl,-rpath,'$$ORIGIN',-soname,$(SHARED_LIB_TARGET)
	LDLIBS_PLATFORM = -lpthread -lm -ldl -lrt 
	LINKLIBS_PLATFORM =
	#STATIC = static

else ifneq ($(filter armhf armhf-32,$(ARCH)),)
	CC=arm-linux-gnueabihf-gcc
	CCPP=arm-linux-gnueabihf-gcc
	LD=arm-linux-gnueabihf-gcc
	LINK=arm-linux-gnueabihf-gcc
	LDS=arm-linux-gnueabihf-ar
	STRIP=arm-linux-gnueabihf-strip
	IMPLDIR = linux
	IMPLARCH = armhf-32
	ARCHFLAGS = 
	LD_ARCHFLAGS = -shared -Wl,-rpath,'$$ORIGIN',-soname=$(SHARED_LIB_TARGET)
	LDLIBS_PLATFORM = -lpthread -lm -ldl -lrt
	LINKLIBS_PLATFORM =
	#STATIC = static


else ifneq ($(filter arm-64,$(ARCH)),)
	CC=arm-none-linux-gnueabi-gcc
	CCPP=arm-none-linux-gnueabi-gcc
	LD=arm-none-linux-gnueabi-gcc
	LINK=arm-none-linux-gnueabi-gcc
	LDS=arm-none-linux-gnueabi-ar
	STRIP=arm-none-linux-gnueabi-strip
	IMPLDIR = linux
	IMPLARCH = arm-64
	ARCHFLAGS =
	LD_ARCHFLAGS = -shared -Wl,-rpath,'$$ORIGIN',-soname,$(SHARED_LIB_TARGET)
	LDLIBS_PLATFORM = -lpthread -lm -ldl -lrt 
	LINKLIBS_PLATFORM =
	#STATIC = static

else ifneq ($(filter mips32 mips32-el mips-32el,$(ARCH)),)
	IMPLDIR=linux
	IMPLARCH=mips-32EL
	TOOLDIR=/usr/local/CodeSourcery/bin
	#STATIC = static
	
	CC=$(TOOLDIR)/mips-linux-gnu-gcc
	CCPP=$(TOOLDIR)/mips-linux-gnu-gcc
	LD=$(TOOLDIR)/mips-linux-gnu-gcc
	LDS=$(TOOLDIR)/mips-linux-gnu-ar
	AR=$(TOOLDIR)/mips-linux-gnu-ar
	STRIP=$(TOOLDIR)/mips-linux-gnu-strip
	
	ARCHFLAGS = -march=mips32 -EL -mhard-float 

else ifneq ($(filter sh sh-32,$(ARCH)),)
	CC=sh-linux-gnu-gcc
	CCPP=sh-linux-gnu-gcc
	LD=sh-linux-gnu-gcc
	LINK=sh-linux-gnu-gcc
	LDS=sh-linux-gnu-ar
	STRIP=sh-linux-gnu-strip
	IMPLDIR = linux
	IMPLARCH = sh-32
	ARCHFLAGS =
	LD_ARCHFLAGS = -shared -Wl,-rpath,'$$ORIGIN'
	LDLIBS_PLATFORM = -lpthread -lm -ldl -lrt
	LINKLIBS_PLATFORM =
	#STATIC = static

else ifneq ($(filter sdtv sdtv-32,$(ARCH)),)
	CC=arm-sony-linux-gnueabi-thumb2-dev-gcc
	CCPP=arm-sony-linux-gnueabi-thumb2-dev-gcc
	LD=arm-sony-linux-gnueabi-thumb2-dev-gcc
	LINK=arm-sony-linux-gnueabi-thumb2-dev-gcc
	LDS=arm-sony-linux-gnueabi-thumb2-dev-ar
	STRIP=arm-sony-linux-gnueabi-thumb2-dev-strip
	IMPLDIR = linux
	IMPLARCH = sdtv-32
	ARCHFLAGS = 
	LD_ARCHFLAGS = -shared -Wl,-rpath,'$$ORIGIN'
	LDLIBS_PLATFORM = -lpthread -lm -ldl -lrt
	LINKLIBS_PLATFORM =
	#STATIC = static

else
$(error ARCH="$(ARCH)" is unsupported.)
endif


