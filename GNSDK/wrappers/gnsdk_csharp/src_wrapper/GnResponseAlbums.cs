
namespace GracenoteSDK {

using System;
using System.Runtime.InteropServices;

/**
* Collection of album results received in response to an album query.
*/
public class GnResponseAlbums : GnDataObject {
  private HandleRef swigCPtr;

  internal GnResponseAlbums(IntPtr cPtr, bool cMemoryOwn) : base(gnsdk_csharp_marshalPINVOKE.GnResponseAlbums_SWIGUpcast(cPtr), cMemoryOwn) {
    swigCPtr = new HandleRef(this, cPtr);
  }

  internal static HandleRef getCPtr(GnResponseAlbums obj) {
    return (obj == null) ? new HandleRef(null, IntPtr.Zero) : obj.swigCPtr;
  }

  ~GnResponseAlbums() {
    Dispose();
  }

  public override void Dispose() {
    lock(this) {
      if (swigCPtr.Handle != IntPtr.Zero) {
        if (swigCMemOwn) {
          swigCMemOwn = false;
          gnsdk_csharp_marshalPINVOKE.delete_GnResponseAlbums(swigCPtr);
        }
        swigCPtr = new HandleRef(null, IntPtr.Zero);
      }
      GC.SuppressFinalize(this);
      base.Dispose();
    }
  }

  public static string GnType() {
    string ret = gnsdk_csharp_marshalPINVOKE.GnResponseAlbums_GnType();
    return ret;
  }

  public static GnResponseAlbums From(GnDataObject obj) {
    GnResponseAlbums ret = new GnResponseAlbums(gnsdk_csharp_marshalPINVOKE.GnResponseAlbums_From(GnDataObject.getCPtr(obj)), true);
    if (gnsdk_csharp_marshalPINVOKE.SWIGPendingException.Pending) throw gnsdk_csharp_marshalPINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

/**
*  Number of matches returned
*  @return Count
*/
  public uint ResultCount {
    get {
      uint ret = gnsdk_csharp_marshalPINVOKE.GnResponseAlbums_ResultCount_get(swigCPtr);
      return ret;
    } 
  }

/**
*  Ordinal of the first result in the returned range.
*  @return Range start
*  <p><b>Remarks:</b></p>
*  If you do not set a starting value, the default behavior is to return the first set of results.
*  Range values are available to aid in paging results. Gracenote limits the number of
*  responses returned in any one request, so the range values are available to indicate the total
*  number of results, and where the current results fit in within that total.
*
*  <p><b>Important:</b></p>
*  The number of results actually returned for a query may not equal the number of results initially
*  requested. To accurately iterate through results, always check the range start, end, and total
*  values and the responses returned for the query (or queries). Ensure that you
*  are incrementing by using the actual last range end value plus one (range_end+1), and not by simply
*  using the initial requested value.
*/
  public uint RangeStart {
    get {
      uint ret = gnsdk_csharp_marshalPINVOKE.GnResponseAlbums_RangeStart_get(swigCPtr);
      return ret;
    } 
  }

/**
* Ordinal of the last result in the returned range.
* @return Range end
* <p><b>Remarks:</b></p>
* Range values are available to aid in paging results. Gracenote limits the number of
* responses returned in any one request, so the range values are available to indicate the total
* number of results, and where the current results fit in within that total.
*
* <p><b>Important:</b></p>
* The number of results actually returned for a query may not equal the number of results initially
* requested. To accurately iterate through results, always check the range start, end, and total
* values and the responses returned for the query (or queries). Ensure that you
* are incrementing by using the actual last range end value plus one (range_end+1), and not by simply
* using the initial requested value.
*/
  public uint RangeEnd {
    get {
      uint ret = gnsdk_csharp_marshalPINVOKE.GnResponseAlbums_RangeEnd_get(swigCPtr);
      return ret;
    } 
  }

/**
* Estimated total number of results possible.
* @return Range total
* <p><b>Remarks:</b></p>
* Range values are available to aid in paging results. Gracenote limits the number of
* responses returned in any one request, so the range values are available to indicate the total
* number of results, and where the current results fit in within that total.
* The total value may be estimated.
*
* <p><b>Important:</b></p>
* The number of results actually returned for a query may not equal the number of results initially
* requested. To accurately iterate through results, always check the range start, end, and total
* values and the responses returned for the query (or queries). Ensure that you
* are incrementing by using the actual last range end value plus one (range_end+1), and not by simply
* using the initial requested value.
*/
  public uint RangeTotal {
    get {
      uint ret = gnsdk_csharp_marshalPINVOKE.GnResponseAlbums_RangeTotal_get(swigCPtr);
      return ret;
    } 
  }

/**
* Flag indicating if response need a user or app decision - either multiple matches returned or less than perfect single match.
* @return True if user decision needed, false otherwise
*/
  public bool NeedsDecision {
    get {
      bool ret = gnsdk_csharp_marshalPINVOKE.GnResponseAlbums_NeedsDecision_get(swigCPtr);
      return ret;
    } 
  }

  public GnAlbumEnumerable Albums {
    get {
      IntPtr cPtr = gnsdk_csharp_marshalPINVOKE.GnResponseAlbums_Albums_get(swigCPtr);
      GnAlbumEnumerable ret = (cPtr == IntPtr.Zero) ? null : new GnAlbumEnumerable(cPtr, true);
      return ret;
    } 
  }

}

}
