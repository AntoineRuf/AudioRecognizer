
package com.gracenote.gnsdk;

/** 
** A video disc can be either DVD (Digital Video Disc) or Blu-ray. 
*/ 
 
public class GnVideoDisc extends GnDataObject {
  private long swigCPtr;

  protected GnVideoDisc(long cPtr, boolean cMemoryOwn) {
    super(gnsdk_javaJNI.GnVideoDisc_SWIGUpcast(cPtr), cMemoryOwn);
    swigCPtr = cPtr;
  }

  protected static long getCPtr(GnVideoDisc obj) {
    return (obj == null) ? 0 : obj.swigCPtr;
  }

  protected void finalize() {
    delete();
  }

  public synchronized void delete() {
    if (swigCPtr != 0) {
      if (swigCMemOwn) {
        swigCMemOwn = false;
        gnsdk_javaJNI.delete_GnVideoDisc(swigCPtr);
      }
      swigCPtr = 0;
    }
    super.delete();
  }

  public static String gnType() {
    return gnsdk_javaJNI.GnVideoDisc_gnType();
  }

  public static GnVideoDisc from(GnDataObject obj) throws com.gracenote.gnsdk.GnException {
    return new GnVideoDisc(gnsdk_javaJNI.GnVideoDisc_from(GnDataObject.getCPtr(obj), obj), true);
  }

  public GnVideoDisc(String id, String idTag) throws com.gracenote.gnsdk.GnException {
    this(gnsdk_javaJNI.new_GnVideoDisc(id, idTag), true);
  }

/** 
* Gracenote ID 
* 
*/ 
 
  public String gnId() {
    return gnsdk_javaJNI.GnVideoDisc_gnId(swigCPtr, this);
  }

/** 
* Gracenote unique ID 
* 
*/ 
 
  public String gnUId() {
    return gnsdk_javaJNI.GnVideoDisc_gnUId(swigCPtr, this);
  }

/** 
*  Product ID aka Tag ID 
* 
*/ 
 
  public String productId() {
    return gnsdk_javaJNI.GnVideoDisc_productId(swigCPtr, this);
  }

/** 
*  TUI - title-unique identifier 
* 
*/ 
 
  public String tui() {
    return gnsdk_javaJNI.GnVideoDisc_tui(swigCPtr, this);
  }

/** 
* Tui Tag value 
* 
*/ 
 
  public String tuiTag() {
    return gnsdk_javaJNI.GnVideoDisc_tuiTag(swigCPtr, this);
  }

/** 
*  Ordinal value 
* 
*/ 
 
  public long ordinal() {
    return gnsdk_javaJNI.GnVideoDisc_ordinal(swigCPtr, this);
  }

/** 
*  Matched boolean value indicating whether this type 
*   is the one that matched the input criteria. 
* 
*/ 
 
  public boolean matched() {
    return gnsdk_javaJNI.GnVideoDisc_matched(swigCPtr, this);
  }

/** 
*  Notes 
* 
*/ 
 
  public String notes() {
    return gnsdk_javaJNI.GnVideoDisc_notes(swigCPtr, this);
  }

/** 
*  Official title object 
* 
*/ 
 
  public GnTitle officialTitle() {
    return new GnTitle(gnsdk_javaJNI.GnVideoDisc_officialTitle(swigCPtr, this), true);
  }

  public GnVideoSideIterable sides() {
    return new GnVideoSideIterable(gnsdk_javaJNI.GnVideoDisc_sides(swigCPtr, this), true);
  }

}
