
package com.gracenote.gnsdk;

/** 
* Name 
*/ 
 
public class GnName extends GnDataObject {
  private long swigCPtr;

  protected GnName(long cPtr, boolean cMemoryOwn) {
    super(gnsdk_javaJNI.GnName_SWIGUpcast(cPtr), cMemoryOwn);
    swigCPtr = cPtr;
  }

  protected static long getCPtr(GnName obj) {
    return (obj == null) ? 0 : obj.swigCPtr;
  }

  protected void finalize() {
    delete();
  }

  public synchronized void delete() {
    if (swigCPtr != 0) {
      if (swigCMemOwn) {
        swigCMemOwn = false;
        gnsdk_javaJNI.delete_GnName(swigCPtr);
      }
      swigCPtr = 0;
    }
    super.delete();
  }

  public static String gnType() {
    return gnsdk_javaJNI.GnName_gnType();
  }

  public static GnName from(GnDataObject obj) throws com.gracenote.gnsdk.GnException {
    return new GnName(gnsdk_javaJNI.GnName_from(GnDataObject.getCPtr(obj), obj), true);
  }

/** 
*  Name display language 
*  @return Langauge string 
*/ 
 
  public String language() {
    return gnsdk_javaJNI.GnName_language(swigCPtr, this);
  }

/** 
*  3-letter ISO code for display langauge 
*  @return Language code 
*/ 
 
  public String languageCode() {
    return gnsdk_javaJNI.GnName_languageCode(swigCPtr, this);
  }

/** 
*  Display name string 
*  @return Name suitable for displaying to the end user 
*/ 
 
  public String display() {
    return gnsdk_javaJNI.GnName_display(swigCPtr, this);
  }

/** 
*  Sortable name 
*  @return Sortable string 
*/ 
 
  public String sortable() {
    return gnsdk_javaJNI.GnName_sortable(swigCPtr, this);
  }

/** 
*  Sortable scheme 
*  @return Sortable Scheme 
*/ 
 
  public String sortableScheme() {
    return gnsdk_javaJNI.GnName_sortableScheme(swigCPtr, this);
  }

/** 
*  Name prefix, e.g., "The" 
*  @return Prefix 
*/ 
 
  public String prefix() {
    return gnsdk_javaJNI.GnName_prefix(swigCPtr, this);
  }

/** 
*  Family name 
*  @return Name 
*/ 
 
  public String family() {
    return gnsdk_javaJNI.GnName_family(swigCPtr, this);
  }

/** 
*  Given name 
*  @return name 
*/ 
 
  public String given() {
    return gnsdk_javaJNI.GnName_given(swigCPtr, this);
  }

/** 
*  Name global ID - used for transcriptions 
*  @return Gracenote Global ID 
*/ 
 
  public String globalId() {
    return gnsdk_javaJNI.GnName_globalId(swigCPtr, this);
  }

}
