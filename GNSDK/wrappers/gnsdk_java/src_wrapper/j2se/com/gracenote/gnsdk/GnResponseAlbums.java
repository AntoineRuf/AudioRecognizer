
package com.gracenote.gnsdk;

/** 
* Collection of album results received in response to an album query. 
*/ 
 
public class GnResponseAlbums extends GnDataObject {
  private long swigCPtr;

  protected GnResponseAlbums(long cPtr, boolean cMemoryOwn) {
    super(gnsdk_javaJNI.GnResponseAlbums_SWIGUpcast(cPtr), cMemoryOwn);
    swigCPtr = cPtr;
  }

  protected static long getCPtr(GnResponseAlbums obj) {
    return (obj == null) ? 0 : obj.swigCPtr;
  }

  protected void finalize() {
    delete();
  }

  public synchronized void delete() {
    if (swigCPtr != 0) {
      if (swigCMemOwn) {
        swigCMemOwn = false;
        gnsdk_javaJNI.delete_GnResponseAlbums(swigCPtr);
      }
      swigCPtr = 0;
    }
    super.delete();
  }

  public static String gnType() {
    return gnsdk_javaJNI.GnResponseAlbums_gnType();
  }

  public static GnResponseAlbums from(GnDataObject obj) throws com.gracenote.gnsdk.GnException {
    return new GnResponseAlbums(gnsdk_javaJNI.GnResponseAlbums_from(GnDataObject.getCPtr(obj), obj), true);
  }

/** 
*  Number of matches returned 
*  @return Count 
*/ 
 
  public long resultCount() {
    return gnsdk_javaJNI.GnResponseAlbums_resultCount(swigCPtr, this);
  }

/** 
*  Ordinal of the first result in the returned range. 
*  @return Range start 
*  <p><b>Remarks:</b></p> 
*  If you do not set a starting value, the default behavior is to return the first set of results. 
*  Range values are available to aid in paging results. Gracenote limits the number of 
*  responses returned in any one request, so the range values are available to indicate the total 
*  number of results, and where the current results fit in within that total. 
* <p> 
*  <p><b>Important:</b></p> 
*  The number of results actually returned for a query may not equal the number of results initially 
*  requested. To accurately iterate through results, always check the range start, end, and total 
*  values and the responses returned for the query (or queries). Ensure that you 
*  are incrementing by using the actual last range end value plus one (range_end+1), and not by simply 
*  using the initial requested value. 
*/ 
 
  public long rangeStart() {
    return gnsdk_javaJNI.GnResponseAlbums_rangeStart(swigCPtr, this);
  }

/** 
* Ordinal of the last result in the returned range. 
* @return Range end 
* <p><b>Remarks:</b></p> 
* Range values are available to aid in paging results. Gracenote limits the number of 
* responses returned in any one request, so the range values are available to indicate the total 
* number of results, and where the current results fit in within that total. 
* <p> 
* <p><b>Important:</b></p> 
* The number of results actually returned for a query may not equal the number of results initially 
* requested. To accurately iterate through results, always check the range start, end, and total 
* values and the responses returned for the query (or queries). Ensure that you 
* are incrementing by using the actual last range end value plus one (range_end+1), and not by simply 
* using the initial requested value. 
*/ 
 
  public long rangeEnd() {
    return gnsdk_javaJNI.GnResponseAlbums_rangeEnd(swigCPtr, this);
  }

/** 
* Estimated total number of results possible. 
* @return Range total 
* <p><b>Remarks:</b></p> 
* Range values are available to aid in paging results. Gracenote limits the number of 
* responses returned in any one request, so the range values are available to indicate the total 
* number of results, and where the current results fit in within that total. 
* The total value may be estimated. 
* <p> 
* <p><b>Important:</b></p> 
* The number of results actually returned for a query may not equal the number of results initially 
* requested. To accurately iterate through results, always check the range start, end, and total 
* values and the responses returned for the query (or queries). Ensure that you 
* are incrementing by using the actual last range end value plus one (range_end+1), and not by simply 
* using the initial requested value. 
*/ 
 
  public long rangeTotal() {
    return gnsdk_javaJNI.GnResponseAlbums_rangeTotal(swigCPtr, this);
  }

/** 
* Flag indicating if response need a user or app decision - either multiple matches returned or less than perfect single match. 
* @return True if user decision needed, false otherwise 
*/ 
 
  public boolean needsDecision() {
    return gnsdk_javaJNI.GnResponseAlbums_needsDecision(swigCPtr, this);
  }

  public GnAlbumIterable albums() {
    return new GnAlbumIterable(gnsdk_javaJNI.GnResponseAlbums_albums(swigCPtr, this), true);
  }

}
