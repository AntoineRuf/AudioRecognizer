# gnsdk C# wrapper sample makefile
##

CC=Csc.exe
CP=cp

GNSDK_LIB_PATH=../../../../lib/$(GNSDK_PLATFORM)
GNSDK_WRAPPER_LIB_PATH=../../lib/$(GNSDK_PLATFORM)
GNSDK_MARSHAL_LIB=$(GNSDK_WRAPPER_LIB_PATH)/gnsdk_csharp_marshal.dll
GNSDK_CSHARP_LIB=../../lib/gnsdk_csharp.dll


CSHARP_FLAGS=/noconfig /nowarn:1701,1702 /nostdlib+ /errorendlocation
CSHARP_REFS=/reference:$(GNSDK_CSHARP_LIB) /reference:"Microsoft.CSharp.dll" /reference:"mscorlib.dll" /reference:"System.Core.dll" /reference:"System.Data.DataSetExtensions.dll" /reference:"System.Data.dll" /reference:"System.dll" /reference:"System.Xml.dll" 

ifeq ($(GNSDK_PLATFORM), win_x86-32)
	CSHARP_FLAGS+=/platform:x86
endif

ifeq ($(GNSDK_PLATFORM), win_x86-64)
	CSHARP_FLAGS+=/platform:x64
endif

SAMPLE_TARGET=sample.exe


build_sample:
	$(CC) $(CSHARP_FLAGS) $(CSHARP_REFS) /out:$(SAMPLE_TARGET) /target:exe /utf8output MusicIDFileTrackID.cs
	$(CP) $(GNSDK_MARSHAL_LIB) .
	$(CP) $(GNSDK_CSHARP_LIB) .