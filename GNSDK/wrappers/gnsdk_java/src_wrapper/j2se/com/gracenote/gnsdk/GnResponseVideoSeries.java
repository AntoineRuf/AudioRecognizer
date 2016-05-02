
package com.gracenote.gnsdk;

/** 
** <p> 
*  <p><b>Remarks about range values:</b></p> 
*  If you do not set a starting value, the default behavior is to return the first set of results. 
*  Range values are available to aid in paging results. Gracenote Service limits the number of 
*  responses returned in any one request, so the range values are available to indicate the total 
*  number of results, and where the current results fit in within that total. 
*  <p><b>Important:</b></p> 
*  The number of results actually returned for a query may not equal the number of results 
*  requested. To accurately iterate through results, always check the range start, end, and total 
*  values and the responses returned by Gracenote Service for the query (or queries). Ensure that you 
*  are incrementing by using the actual last range end value plus one (range_end+1), and not by simply 
*  using the initial requested value. 
*/ 
 
public class GnResponseVideoSeries extends GnDataObject {
  private long swigCPtr;

  protected GnResponseVideoSeries(long cPtr, boolean cMemoryOwn) {
    super(gnsdk_javaJNI.GnResponseVideoSeries_SWIGUpcast(cPtr), cMemoryOwn);
    swigCPtr = cPtr;
  }

  protected static long getCPtr(GnResponseVideoSeries obj) {
    return (obj == null) ? 0 : obj.swigCPtr;
  }

  protected void finalize() {
    delete();
  }

  public synchronized void delete() {
    if (swigCPtr != 0) {
      if (swigCMemOwn) {
        swigCMemOwn = false;
        gnsdk_javaJNI.delete_GnResponseVideoSeries(swigCPtr);
      }
      swigCPtr = 0;
    }
    super.delete();
  }

  public static String gnType() {
    return gnsdk_javaJNI.GnResponseVideoSeries_gnType();
  }

  public static GnResponseVideoSeries from(GnDataObject obj) throws com.gracenote.gnsdk.GnException {
    return new GnResponseVideoSeries(gnsdk_javaJNI.GnResponseVideoSeries_from(GnDataObject.getCPtr(obj), obj), true);
  }

/** 
*  Total number of returned matches 
*/ 
 
  public long resultCount() {
    return gnsdk_javaJNI.GnResponseVideoSeries_resultCount(swigCPtr, this);
  }

/** 
*	Ordinal of the first result in the returned range. 
* 
*/ 
 
  public long rangeStart() {
    return gnsdk_javaJNI.GnResponseVideoSeries_rangeStart(swigCPtr, this);
  }

/** 
*	Ordinal of the last result in the returned range. 
* 
*/ 
 
  public long rangeEnd() {
    return gnsdk_javaJNI.GnResponseVideoSeries_rangeEnd(swigCPtr, this);
  }

/** 
*	Estimated total number of results possible. 
* 
*/ 
 
  public long rangeTotal() {
    return gnsdk_javaJNI.GnResponseVideoSeries_rangeTotal(swigCPtr, this);
  }

/** 
* Flag indicating if response match(es) need a user or app decision - either multiple matches returned or less than perfect single match.. 
*/ 
 
  public boolean needsDecision() {
    return gnsdk_javaJNI.GnResponseVideoSeries_needsDecision(swigCPtr, this);
  }

  public GnVideoSeriesIterable series() {
    return new GnVideoSeriesIterable(gnsdk_javaJNI.GnResponseVideoSeries_series(swigCPtr, this), true);
  }

}
