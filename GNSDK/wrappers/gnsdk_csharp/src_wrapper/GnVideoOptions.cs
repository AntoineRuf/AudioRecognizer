
namespace GracenoteSDK {

using System;
using System.Runtime.InteropServices;

/**
* GnVideoOptions
*/
public class GnVideoOptions : IDisposable {
  private HandleRef swigCPtr;
  protected bool swigCMemOwn;

  internal GnVideoOptions(IntPtr cPtr, bool cMemoryOwn) {
    swigCMemOwn = cMemoryOwn;
    swigCPtr = new HandleRef(this, cPtr);
  }

  internal static HandleRef getCPtr(GnVideoOptions obj) {
    return (obj == null) ? new HandleRef(null, IntPtr.Zero) : obj.swigCPtr;
  }

  ~GnVideoOptions() {
    Dispose();
  }

  public virtual void Dispose() {
    lock(this) {
      if (swigCPtr.Handle != IntPtr.Zero) {
        if (swigCMemOwn) {
          swigCMemOwn = false;
          gnsdk_csharp_marshalPINVOKE.delete_GnVideoOptions(swigCPtr);
        }
        swigCPtr = new HandleRef(null, IntPtr.Zero);
      }
      GC.SuppressFinalize(this);
    }
  }

/**
*  Specifies the preferred language for returned results. This option applies only to TOC
*  Lookups.
*  @param preferredLanguage Set language option
*/
  public void ResultPreferLanguage(GnLanguage preferredLanguage) {
    gnsdk_csharp_marshalPINVOKE.GnVideoOptions_ResultPreferLanguage(swigCPtr, (int)preferredLanguage);
    if (gnsdk_csharp_marshalPINVOKE.SWIGPendingException.Pending) throw gnsdk_csharp_marshalPINVOKE.SWIGPendingException.Retrieve();
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
  public void ResultRangeStart(uint resultStart) {
    gnsdk_csharp_marshalPINVOKE.GnVideoOptions_ResultRangeStart(swigCPtr, resultStart);
    if (gnsdk_csharp_marshalPINVOKE.SWIGPendingException.Pending) throw gnsdk_csharp_marshalPINVOKE.SWIGPendingException.Retrieve();
  }

/**
*  Set number of results to be returned
*  @param resultCount 	[in] Maximum number of results a response can return.
*
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
  public void ResultCount(uint resultCount) {
    gnsdk_csharp_marshalPINVOKE.GnVideoOptions_ResultCount(swigCPtr, resultCount);
    if (gnsdk_csharp_marshalPINVOKE.SWIGPendingException.Pending) throw gnsdk_csharp_marshalPINVOKE.SWIGPendingException.Retrieve();
  }

/**
*  Indicates the lookup data value for the Video query.
*  @param lookupData [in] One of the #GnLookupData values
*  @param bEnable    [in] Set lookup data
*/
  public void LookupData(GnLookupData lookupData, bool bEnable) {
    gnsdk_csharp_marshalPINVOKE.GnVideoOptions_LookupData(swigCPtr, (int)lookupData, bEnable);
    if (gnsdk_csharp_marshalPINVOKE.SWIGPendingException.Pending) throw gnsdk_csharp_marshalPINVOKE.SWIGPendingException.Retrieve();
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
  public void QueryNoCache(bool bNoCache) {
    gnsdk_csharp_marshalPINVOKE.GnVideoOptions_QueryNoCache(swigCPtr, bNoCache);
    if (gnsdk_csharp_marshalPINVOKE.SWIGPendingException.Pending) throw gnsdk_csharp_marshalPINVOKE.SWIGPendingException.Retrieve();
  }

/**
*  Specifies that a TOC lookup includes the disc's commerce type.
*  @param bEnableCommerceType Set boolean to enable commerce type
*/
  public void QueryCommerceType(bool bEnableCommerceType) {
    gnsdk_csharp_marshalPINVOKE.GnVideoOptions_QueryCommerceType(swigCPtr, bEnableCommerceType);
    if (gnsdk_csharp_marshalPINVOKE.SWIGPendingException.Pending) throw gnsdk_csharp_marshalPINVOKE.SWIGPendingException.Retrieve();
  }

/**
*  Sets a filter for a Video Explore query handle, using a list value.
*  @param bInclude [in] Set Boolean value to True to include filter key; set to False to exclude the filter
*  @param listElementFilterType [in] One of the #GnVideoListElementFilterType filter types
*  @param listElement [in] A list element handle used to populate the filter value. The list
*   element must be from a list that corresponds to the filter name.
*
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
  public void ResultFilter(GnVideoListElementFilterType listElementFilterType, GnListElement listElement, bool bInclude) {
    gnsdk_csharp_marshalPINVOKE.GnVideoOptions_ResultFilter__SWIG_0(swigCPtr, (int)listElementFilterType, GnListElement.getCPtr(listElement), bInclude);
    if (gnsdk_csharp_marshalPINVOKE.SWIGPendingException.Pending) throw gnsdk_csharp_marshalPINVOKE.SWIGPendingException.Retrieve();
  }

/**
*
*  Sets a filter for a VideoID or Video Explore query handle.
*  @param filterValue [in] String value for corresponding data key
*  @param filterType [in] One of the #GnVideoFilterType filter types
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
*
*/
  public void ResultFilter(GnVideoFilterType filterType, string filterValue) {
    gnsdk_csharp_marshalPINVOKE.GnVideoOptions_ResultFilter__SWIG_1(swigCPtr, (int)filterType, filterValue);
    if (gnsdk_csharp_marshalPINVOKE.SWIGPendingException.Pending) throw gnsdk_csharp_marshalPINVOKE.SWIGPendingException.Retrieve();
  }

/**
* Use this  option to set a specific network interface for this object's connections.
* Setting this can be beneficial for systems with multiple
* network interfaces. Without setting this option, the operating system will dicate which network interface
* gets used for connections.
*  @param ipAddress [in] local IP address for the desired network interface
*/
  public void NetworkInterface(string ipAddress) {
    gnsdk_csharp_marshalPINVOKE.GnVideoOptions_NetworkInterface(swigCPtr, ipAddress);
    if (gnsdk_csharp_marshalPINVOKE.SWIGPendingException.Pending) throw gnsdk_csharp_marshalPINVOKE.SWIGPendingException.Retrieve();
  }

/**
*  General option setting for custom string options
*  @param optionKey   [in] Option name
*  @param value	   [in] Option value
*/
  public void Custom(string optionKey, string value) {
    gnsdk_csharp_marshalPINVOKE.GnVideoOptions_Custom(swigCPtr, optionKey, value);
    if (gnsdk_csharp_marshalPINVOKE.SWIGPendingException.Pending) throw gnsdk_csharp_marshalPINVOKE.SWIGPendingException.Retrieve();
  }

}

}
