
package com.gracenote.gnsdk;

/** 
* Collection of track results received in response to a track query 
*/ 
 
public class GnResponseTracks extends GnDataObject {
  private long swigCPtr;

  protected GnResponseTracks(long cPtr, boolean cMemoryOwn) {
    super(gnsdk_javaJNI.GnResponseTracks_SWIGUpcast(cPtr), cMemoryOwn);
    swigCPtr = cPtr;
  }

  protected static long getCPtr(GnResponseTracks obj) {
    return (obj == null) ? 0 : obj.swigCPtr;
  }

  protected void finalize() {
    delete();
  }

  public synchronized void delete() {
    if (swigCPtr != 0) {
      if (swigCMemOwn) {
        swigCMemOwn = false;
        gnsdk_javaJNI.delete_GnResponseTracks(swigCPtr);
      }
      swigCPtr = 0;
    }
    super.delete();
  }

  public static String gnType() {
    return gnsdk_javaJNI.GnResponseTracks_gnType();
  }

  public static GnResponseTracks from(GnDataObject obj) throws com.gracenote.gnsdk.GnException {
    return new GnResponseTracks(gnsdk_javaJNI.GnResponseTracks_from(GnDataObject.getCPtr(obj), obj), true);
  }

/** 
*  Result count - number of matches returned 
*  @return Count 
*/ 
 
  public long resultCount() {
    return gnsdk_javaJNI.GnResponseTracks_resultCount(swigCPtr, this);
  }

/** 
*  Range start - ordinal value of first match in range total 
*  @return Range start ordinal 
*/ 
 
  public long rangeStart() {
    return gnsdk_javaJNI.GnResponseTracks_rangeStart(swigCPtr, this);
  }

/** 
*  Range end - ordinal value of last match in range total 
*  @return Range end ordinal 
*/ 
 
  public long rangeEnd() {
    return gnsdk_javaJNI.GnResponseTracks_rangeEnd(swigCPtr, this);
  }

/** 
*  Range total - total number of matches that could be returned 
*  @return Range total 
*/ 
 
  public long rangeTotal() {
    return gnsdk_javaJNI.GnResponseTracks_rangeTotal(swigCPtr, this);
  }

/** 
*  Flag indicating if response needs user decision - either multiple matches returned or less than perfect single match 
*  @return True if user decision required, false otherwise 
*/ 
 
  public boolean needsDecision() {
    return gnsdk_javaJNI.GnResponseTracks_needsDecision(swigCPtr, this);
  }

  public GnTrackIterable tracks() {
    return new GnTrackIterable(gnsdk_javaJNI.GnResponseTracks_tracks(swigCPtr, this), true);
  }

}
