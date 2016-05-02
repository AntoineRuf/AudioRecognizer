
package com.gracenote.gnsdk;

/** 
* Collection of data match results received in response to a data match query. 
*/ 
 
public class GnResponseDataMatches extends GnDataObject {
  private long swigCPtr;

  protected GnResponseDataMatches(long cPtr, boolean cMemoryOwn) {
    super(gnsdk_javaJNI.GnResponseDataMatches_SWIGUpcast(cPtr), cMemoryOwn);
    swigCPtr = cPtr;
  }

  protected static long getCPtr(GnResponseDataMatches obj) {
    return (obj == null) ? 0 : obj.swigCPtr;
  }

  protected void finalize() {
    delete();
  }

  public synchronized void delete() {
    if (swigCPtr != 0) {
      if (swigCMemOwn) {
        swigCMemOwn = false;
        gnsdk_javaJNI.delete_GnResponseDataMatches(swigCPtr);
      }
      swigCPtr = 0;
    }
    super.delete();
  }

/** 
*  Result count - number of matches returned 
*  @return Count 
*/ 
 
  public long resultCount() {
    return gnsdk_javaJNI.GnResponseDataMatches_resultCount(swigCPtr, this);
  }

/** 
*  Range start - ordinal value of first match in range total 
*  @return Range start 
*/ 
 
  public long rangeStart() {
    return gnsdk_javaJNI.GnResponseDataMatches_rangeStart(swigCPtr, this);
  }

/** 
*  Range end - ordinal value of last match in range total 
*  @return Range end 
*/ 
 
  public long rangeEnd() {
    return gnsdk_javaJNI.GnResponseDataMatches_rangeEnd(swigCPtr, this);
  }

/** 
*  Range total - total number of matches that could be returned 
*  @return Range total 
*/ 
 
  public long rangeTotal() {
    return gnsdk_javaJNI.GnResponseDataMatches_rangeTotal(swigCPtr, this);
  }

/** 
*  Flag indicating if response needs user or app decision - either multiple matches returned or less than perfect single match 
*  @return True is user decision needed, false otherwise 
*/ 
 
  public boolean needsDecision() {
    return gnsdk_javaJNI.GnResponseDataMatches_needsDecision(swigCPtr, this);
  }

  public GnDataMatchIterable dataMatches() {
    return new GnDataMatchIterable(gnsdk_javaJNI.GnResponseDataMatches_dataMatches(swigCPtr, this), true);
  }

}
