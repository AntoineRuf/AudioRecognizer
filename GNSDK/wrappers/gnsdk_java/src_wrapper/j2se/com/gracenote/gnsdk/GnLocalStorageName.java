
package com.gracenote.gnsdk;

/** 
* Gracenote local database names 
* Gracenote supports local lookup for various types of identification 
* and content, each is provided in it's own Gracenote database. Each name 
* herein represents a specific local Gracenote database. 
* 
*/ 
 
public enum GnLocalStorageName {
/** 
* Name of the local storage the SDK uses to query Gracenote Content. 
* 
*/ 
 
  kLocalStorageInvalid(0),
/** 
* Name of the local storage the SDK uses to query Gracenote Metadata. 
* 
*/ 
 
  kLocalStorageContent,
/** 
* Name of the local storage the SDK uses for CD TOC searching. 
* 
*/ 
 
  kLocalStorageMetadata,
/** 
* Name of the local storage the SDK uses for text searching. 
* 
*/ 
 
  kLocalStorageTOCIndex,
/** 
* For referencing all the above storages that make up the local storage. 
* 
*/ 
 
  kLocalStorageTextIndex,
 
 
  kLocalStorageAll;

  protected final int swigValue() {
    return swigValue;
  }

  protected static GnLocalStorageName swigToEnum(int swigValue) {
    GnLocalStorageName[] swigValues = GnLocalStorageName.class.getEnumConstants();
    if (swigValue < swigValues.length && swigValue >= 0 && swigValues[swigValue].swigValue == swigValue)
      return swigValues[swigValue];
    for (GnLocalStorageName swigEnum : swigValues)
      if (swigEnum.swigValue == swigValue)
        return swigEnum;
    throw new IllegalArgumentException("No enum " + GnLocalStorageName.class + " with value " + swigValue);
  }

  @SuppressWarnings("unused")
  private GnLocalStorageName() {
    this.swigValue = SwigNext.next++;
  }

  @SuppressWarnings("unused")
  private GnLocalStorageName(int swigValue) {
    this.swigValue = swigValue;
    SwigNext.next = swigValue+1;
  }

  @SuppressWarnings("unused")
  private GnLocalStorageName(GnLocalStorageName swigEnum) {
    this.swigValue = swigEnum.swigValue;
    SwigNext.next = this.swigValue+1;
  }

  private final int swigValue;

  private static class SwigNext {
    private static int next = 0;
  }
}

