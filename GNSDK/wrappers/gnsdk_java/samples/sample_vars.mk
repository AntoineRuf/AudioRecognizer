#
# Common Make Rules for Gracenote Java Samples
#
build_dir  =../../../../../builds
install_dir=../../../../../install

ifeq ($(wildcard $(build_dir)),)
	build_dir  = ../../../../builds
	install_dir= ../../../..
endif

include $(build_dir)/platform_vars.mk

CLASS_DIR=.
GNSDK_INSTALL_DIR= $(install_dir)/common/debug/lib/$(IMPLDIR)_$(IMPLARCH)
ifeq ($(wildcard $(GNSDK_INSTALL_DIR)),)
	GNSDK_INSTALL_DIR= $(install_dir)/lib/$(IMPLDIR)_$(IMPLARCH)
endif
GNSDK_JAVA_DIR   = $(install_dir)/wrappers/gnsdk_java
GNSDK_JAVA_LIBDIR= $(GNSDK_JAVA_DIR)/lib/debug/$(IMPLDIR)_$(IMPLARCH)
ifeq ($(wildcard $(GNSDK_JAVA_LIBDIR)),)
	GNSDK_JAVA_LIBDIR= $(GNSDK_JAVA_DIR)/lib/$(IMPLDIR)_$(IMPLARCH)
endif

ifeq ($(IMPLDIR),win)
	GNSDK_CLASSPATH := "$(wildcard $(GNSDK_JAVA_DIR)/jar/j2se/gnsdk.jar);$(wildcard $(GNSDK_JAVA_DIR)/jar/j2se/gnsdk_helpers.jar);."
else
	GNSDK_CLASSPATH := "$(wildcard $(GNSDK_JAVA_DIR)/jar/j2se/gnsdk.jar):$(wildcard $(GNSDK_JAVA_DIR)/jar/j2se/gnsdk_helpers.jar):."
endif

ifeq ($(GNSDK_CLASSPATH),)
	GNSDK_JAVA_DIR = ../../../gnsdk_java
	GNSDK_CLASSPATH := $(wildcard $(GNSDK_JAVA_DIR)/jar/j2se/gnsdk.jar)
endif

# to run Java samples customize this section and execute "make run" from the
# sample's directory
CID=clientid			# your Client ID
CTAG=clienttag			# your Client Tag
LIC=licensefile			# path to your GNSDK license file
LOCAL=					# online or local

class_files := $(java_files:%.java=$(CLASS_DIR)/%.class)

$(class_files): $(CLASS_DIR)/%.class: %.java | $(CLASS_DIR)
	javac -cp $(GNSDK_CLASSPATH) -encoding UTF-8 -d $(CLASS_DIR) $<

$(CLASS_DIR):
	mkdir -p $(@)

run: showinfo $(class_files)
	cp -f $(GNSDK_JAVA_LIBDIR)/*.$(SHARED_LIB_EXT) .
	java -cp $(GNSDK_CLASSPATH) $(notdir $(CURDIR))/$(basename $(java_files)) $(CID) $(CTAG) $(LIC) $(GNSDK_INSTALL_DIR) $(LOCAL)

clean:
	rm -rf $(CLASS_DIR)/*.class
	rm -rf $(notdir $(CURDIR))
	rm -f  *.$(SHARED_LIB_EXT)
	rm -f *.gdb *.log
ifneq ($(CLASS_DIR),.)
	rmdir -p $(CLASS_DIR)
endif


showinfo:
	$(info )
	$(info ********************************************)
	$(info * $(IMPLDIR)_$(IMPLARCH))
	$(info * GNSDK_CLASSPATH=$(GNSDK_CLASSPATH))
	$(info * GNSDK_JAVA_DIR =$(GNSDK_JAVA_DIR))
	$(info * )

