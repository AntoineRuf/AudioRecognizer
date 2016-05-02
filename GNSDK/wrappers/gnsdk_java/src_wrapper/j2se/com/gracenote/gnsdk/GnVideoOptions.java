
package com.gracenote.gnsdk;

/** 
* {@link GnVideoOptions} 
*/ 
 
public class GnVideoOptions {
  private transient long swigCPtr;
  protected transient boolean swigCMemOwn;

  protected GnVideoOptions(long cPtr, boolean cMemoryOwn) {
    swigCMemOwn = cMemoryOwn;
    swigCPtr = cPtr;
  }

  protected static long getCPtr(GnVideoOptions obj) {
    return (obj == null) ? 0 : obj.swigCPtr;
  }

  protected void finalize() {
    delete();
  }

  public synchronized void delete() {
    if (swigCPtr != 0) {
      if (swigCMemOwn) {
        swigCMemOwn = false;
        gnsdk_javaJNI.delete_GnVideoOptions(swigCPtr);
      }
      swigCPtr = 0;
    }
  }

/** 
*  Specifies the preferred language for returned results. This option applies only to TOC 
*  Lookups. 
*  @param preferredLanguage Set language option 
*/ 
 
  public void resultPreferLanguage(GnLanguage preferredLanguage) throws com.gracenote.gnsdk.GnException {
    gnsdk_javaJNI.GnVideoOptions_resultPreferLanguage(swigCPtr, this, preferredLanguage.swigValue());
  }

/** 
*  Set ordinal for the first result to be returned 
*  @param resultStart Set the starting position for the result 
*  <p><b>Remarks:</b></p> 
*  This option is useful for paging through results. 
* <p><b>Note:</b></p> 
*   Gracenote Service limits the range size for some queries. If you specify a range size greater 
*   than the limit, the results are constrained. Additionally, neither Gracenote Service nor GNSDK 
*   returns an error about this behavior. 
*  <p><b>Important:</b></p> 
*   The number of results actually returned for a query may not equal the number of results initially 
*   requested. To accurately iterate through results, always check the range start, end, and total 
*   values and the responses Gracenote returns for the query (or queries). Ensure that you 
*   are incrementing by using the actual last range end value plus one (range_end+1), and not by simply 
*   using the initial requested value. 
*/ 
 
  public void resultRangeStart(long resultStart) throws com.gracenote.gnsdk.GnException {
    gnsdk_javaJNI.GnVideoOptions_resultRangeStart(swigCPtr, this, resultStart);
  }

/** 
*  Set number of results to be returned 
*  @param resultCount 	[in] Maximum number of results a response can return. 
* <p> 
*  <p><b>Remarks:</b></p> 
*  This option is useful for paging through results. 
* <p><b>Note:</b></p> 
*   Gracenote Service limits the range size for some queries. If you specify a range size greater 
*   than the limit, the results are constrained. Additionally, neither Gracenote Service nor GNSDK 
*   returns an error about this behavior. 
*  <p><b>Important:</b></p> 
*  The number of results actually returned for a query may not equal the number of results initially 
*   requested. To accurately iterate through results, always check the range start, end, and total 
*   values and the responses returned by Gracenote Service for the query (or queries). Ensure that you 
*   are incrementing by using the actual last range end value plus one (range_end+1), and not by simply 
*   using the initial requested value. 
*/ 
 
  public void resultCount(long resultCount) throws com.gracenote.gnsdk.GnException {
    gnsdk_javaJNI.GnVideoOptions_resultCount(swigCPtr, this, resultCount);
  }

/** 
*  Indicates the lookup data value for the Video query. 
*  @param lookupData [in] One of the {@link GnLookupData} values 
*  @param bEnable    [in] Set lookup data 
*/ 
 
  public void lookupData(GnLookupData lookupData, boolean bEnable) throws com.gracenote.gnsdk.GnException {
    gnsdk_javaJNI.GnVideoOptions_lookupData(swigCPtr, this, lookupData.swigValue(), bEnable);
  }

/** 
*  Indicates whether a response is not automatically stored in the cache. 
*  @param bNoCache Set boolean to enable caching 
*  <p><b>Remarks:</b></p> 
*  Set this option to True to retrieve query data from a call to Gracenote Service; doing this 
*   ensures retrieving the most recent available data. 
*  Set this option to False to retrieve query data that already exists in the lookup cache. When no 
*   data exists in the cache, VideoID 
*  or Video Explore automatically calls Gracenote Service with the query request. 
*/ 
 
  public void queryNoCache(boolean bNoCache) throws com.gracenote.gnsdk.GnException {
    gnsdk_javaJNI.GnVideoOptions_queryNoCache(swigCPtr, this, bNoCache);
  }

/** 
*  Specifies that a TOC lookup includes the disc's commerce type. 
*  @param bEnableCommerceType Set boolean to enable commerce type 
*/ 
 
  public void queryCommerceType(boolean bEnableCommerceType) throws com.gracenote.gnsdk.GnException {
    gnsdk_javaJNI.GnVideoOptions_queryCommerceType(swigCPtr, this, bEnableCommerceType);
  }

/** 
*  Sets a filter for a Video Explore query handle, using a list value. 
*  @param bInclude [in] Set Boolean value to True to include filter key; set to False to exclude the filter 
*  @param listElementFilterType [in] One of the {@link GnVideoListElementFilterType} filter types 
*  @param listElement [in] A list element handle used to populate the filter value. The list 
*   element must be from a list that corresponds to the filter name. 
* <p> 
*  <p><b>Remarks:</b></p> 
*  Use this function with the GNSDK Manager Lists functionality to apply filters on and improve the 
*   relevance for specific Video Explore search results. Your application must have Video Explore 
*   licensing to use this function. 
* <p><b>Note:</b></p> 
*  The system disregards filters when performing non-text related video queries, and filtering 
*   by list elements is restricted to performing a Works search using the following Filter Values: 
*  <ul> 
*  <li>kListElementFilterGenre</li> 
*  <li>kListElementFilterProductionType</li> 
*  <li>kListElementFilterSerialType</li> 
*  <li>kListElementFilterOrigin</li> 
*  </ul> 
*/ 
 
  public void resultFilter(GnVideoListElementFilterType listElementFilterType, GnListElement listElement, boolean bInclude) throws com.gracenote.gnsdk.GnException {
    gnsdk_javaJNI.GnVideoOptions_resultFilter__SWIG_0(swigCPtr, this, listElementFilterType.swigValue(), GnListElement.getCPtr(listElement), listElement, bInclude);
  }

/** 
* <p> 
*  Sets a filter for a VideoID or Video Explore query handle. 
*  @param filterValue [in] String value for corresponding data key 
*  @param filterType [in] One of the {@link GnVideoFilterType} filter types 
*  <p><b>Remarks:</b></p> 
*  Use this function to apply certain filters on and improve the relevance of Work text search query 
*   results. 
* <p><b>Note:</b></p> 
*  The system disregards filters when performing non-text related video queries, and that filtering by<br> 
*  list elements is restricted to performing a Works search using the following Filter Values: 
*  <ul> 
*  <li>kFilterSeasonNumber text (integer as a string)</li> 
*  <li>kFilterSeasonEpisodeNumber text (integer as a string)</li> 
*  <li>kFilterSeriesEpisodeNumber text (integer as a string)</li> 
*  </ul> 
* <p> 
*/ 
 
  public void resultFilter(GnVideoFilterType filterType, String filterValue) throws com.gracenote.gnsdk.GnException {
    gnsdk_javaJNI.GnVideoOptions_resultFilter__SWIG_1(swigCPtr, this, filterType.swigValue(), filterValue);
  }

/** 
* Use this  option to set a specific network interface for this object's connections. 
* Setting this can be beneficial for systems with multiple 
* network interfaces. Without setting this option, the operating system will dicate which network interface 
* gets used for connections. 
*  @param ipAddress [in] local IP address for the desired network interface 
*/ 
 
  public void networkInterface(String ipAddress) throws com.gracenote.gnsdk.GnException {
    gnsdk_javaJNI.GnVideoOptions_networkInterface(swigCPtr, this, ipAddress);
  }

/** 
*  General option setting for custom string options 
*  @param optionKey   [in] Option name 
*  @param value	   [in] Option value 
*/ 
 
  public void custom(String optionKey, String value) throws com.gracenote.gnsdk.GnException {
    gnsdk_javaJNI.GnVideoOptions_custom(swigCPtr, this, optionKey, value);
  }

}
