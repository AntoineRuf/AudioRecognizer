
package com.gracenote.gnsdk;

/** 
**/ 
 
public class GnVideoChapter extends GnDataObject {
  private long swigCPtr;

  protected GnVideoChapter(long cPtr, boolean cMemoryOwn) {
    super(gnsdk_javaJNI.GnVideoChapter_SWIGUpcast(cPtr), cMemoryOwn);
    swigCPtr = cPtr;
  }

  protected static long getCPtr(GnVideoChapter obj) {
    return (obj == null) ? 0 : obj.swigCPtr;
  }

  protected void finalize() {
    delete();
  }

  public synchronized void delete() {
    if (swigCPtr != 0) {
      if (swigCMemOwn) {
        swigCMemOwn = false;
        gnsdk_javaJNI.delete_GnVideoChapter(swigCPtr);
      }
      swigCPtr = 0;
    }
    super.delete();
  }

  public static String gnType() {
    return gnsdk_javaJNI.GnVideoChapter_gnType();
  }

  public static GnVideoChapter from(GnDataObject obj) throws com.gracenote.gnsdk.GnException {
    return new GnVideoChapter(gnsdk_javaJNI.GnVideoChapter_from(GnDataObject.getCPtr(obj), obj), true);
  }

/** 
* Video chapter's ordinal value. 
* 
*/ 
 
  public long ordinal() {
    return gnsdk_javaJNI.GnVideoChapter_ordinal(swigCPtr, this);
  }

/** 
*  Chapter's duration value in seconds such as "3600" for a 60-minute program. 
* 
*/ 
 
  public long duration() {
    return gnsdk_javaJNI.GnVideoChapter_duration(swigCPtr, this);
  }

/** 
*  Chapter's duration units value (seconds, "SEC"). 
* 
*/ 
 
  public String durationUnits() {
    return gnsdk_javaJNI.GnVideoChapter_durationUnits(swigCPtr, this);
  }

/** 
*  Official Title object. 
* 
*/ 
 
  public GnTitle officialTitle() {
    return new GnTitle(gnsdk_javaJNI.GnVideoChapter_officialTitle(swigCPtr, this), true);
  }

  public GnVideoCreditIterable videoCredits() {
    return new GnVideoCreditIterable(gnsdk_javaJNI.GnVideoChapter_videoCredits(swigCPtr, this), true);
  }

}
