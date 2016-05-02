
package com.gracenote.gnsdk;

/** 
* Third-party identifier used to match identified media to merchandise IDs in online stores and other services 
* <p> 
*/ 
 
public class GnExternalId extends GnDataObject {
  private long swigCPtr;

  protected GnExternalId(long cPtr, boolean cMemoryOwn) {
    super(gnsdk_javaJNI.GnExternalId_SWIGUpcast(cPtr), cMemoryOwn);
    swigCPtr = cPtr;
  }

  protected static long getCPtr(GnExternalId obj) {
    return (obj == null) ? 0 : obj.swigCPtr;
  }

  protected void finalize() {
    delete();
  }

  public synchronized void delete() {
    if (swigCPtr != 0) {
      if (swigCMemOwn) {
        swigCMemOwn = false;
        gnsdk_javaJNI.delete_GnExternalId(swigCPtr);
      }
      swigCPtr = 0;
    }
    super.delete();
  }

  public static String gnType() {
    return gnsdk_javaJNI.GnExternalId_gnType();
  }

  public static GnExternalId from(GnDataObject obj) throws com.gracenote.gnsdk.GnException {
    return new GnExternalId(gnsdk_javaJNI.GnExternalId_from(GnDataObject.getCPtr(obj), obj), true);
  }

/** 
*  External ID source (e.g., Amazon) 
*  @return External ID source 
*/ 
 
  public String source() {
    return gnsdk_javaJNI.GnExternalId_source(swigCPtr, this);
  }

/** 
*  External ID type 
*  @return External ID type 
*/ 
 
  public String type() {
    return gnsdk_javaJNI.GnExternalId_type(swigCPtr, this);
  }

/** 
*  External ID value 
*  @return External ID value 
*/ 
 
  public String value() {
    return gnsdk_javaJNI.GnExternalId_value(swigCPtr, this);
  }

}
