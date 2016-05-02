
namespace GracenoteSDK {

using System;
using System.Runtime.InteropServices;

/**
* \class GnResponseVideoObjects
*
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
public class GnResponseVideoObjects : GnDataObject {
  private HandleRef swigCPtr;

  internal GnResponseVideoObjects(IntPtr cPtr, bool cMemoryOwn) : base(gnsdk_csharp_marshalPINVOKE.GnResponseVideoObjects_SWIGUpcast(cPtr), cMemoryOwn) {
    swigCPtr = new HandleRef(this, cPtr);
  }

  internal static HandleRef getCPtr(GnResponseVideoObjects obj) {
    return (obj == null) ? new HandleRef(null, IntPtr.Zero) : obj.swigCPtr;
  }

  ~GnResponseVideoObjects() {
    Dispose();
  }

  public override void Dispose() {
    lock(this) {
      if (swigCPtr.Handle != IntPtr.Zero) {
        if (swigCMemOwn) {
          swigCMemOwn = false;
          gnsdk_csharp_marshalPINVOKE.delete_GnResponseVideoObjects(swigCPtr);
        }
        swigCPtr = new HandleRef(null, IntPtr.Zero);
      }
      GC.SuppressFinalize(this);
      base.Dispose();
    }
  }

  public static string GnType() {
    string ret = gnsdk_csharp_marshalPINVOKE.GnResponseVideoObjects_GnType();
    return ret;
  }

  public static GnResponseVideoObjects From(GnDataObject obj) {
    GnResponseVideoObjects ret = new GnResponseVideoObjects(gnsdk_csharp_marshalPINVOKE.GnResponseVideoObjects_From(GnDataObject.getCPtr(obj)), true);
    if (gnsdk_csharp_marshalPINVOKE.SWIGPendingException.Pending) throw gnsdk_csharp_marshalPINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

  public GnVideoProductEnumerable Products() {
    GnVideoProductEnumerable ret = new GnVideoProductEnumerable(gnsdk_csharp_marshalPINVOKE.GnResponseVideoObjects_Products(swigCPtr), true);
    return ret;
  }

  public GnVideoWorkEnumerable Works() {
    GnVideoWorkEnumerable ret = new GnVideoWorkEnumerable(gnsdk_csharp_marshalPINVOKE.GnResponseVideoObjects_Works(swigCPtr), true);
    return ret;
  }

  public GnVideoSeasonEnumerable Seasons() {
    GnVideoSeasonEnumerable ret = new GnVideoSeasonEnumerable(gnsdk_csharp_marshalPINVOKE.GnResponseVideoObjects_Seasons(swigCPtr), true);
    return ret;
  }

  public GnVideoSeriesEnumerable Series() {
    GnVideoSeriesEnumerable ret = new GnVideoSeriesEnumerable(gnsdk_csharp_marshalPINVOKE.GnResponseVideoObjects_Series(swigCPtr), true);
    return ret;
  }

  public GnContributorEnumerable Contributors() {
    GnContributorEnumerable ret = new GnContributorEnumerable(gnsdk_csharp_marshalPINVOKE.GnResponseVideoObjects_Contributors(swigCPtr), true);
    return ret;
  }

/**
*  ResultCount - total number of returned matches
*/
  public uint ResultCount {
    get {
      uint ret = gnsdk_csharp_marshalPINVOKE.GnResponseVideoObjects_ResultCount_get(swigCPtr);
      return ret;
    } 
  }

/**
*	Ordinal of the first result in the returned range.
* @ingroup GDO_ValueKeys_Misc
*/
  public uint RangeStart {
    get {
      uint ret = gnsdk_csharp_marshalPINVOKE.GnResponseVideoObjects_RangeStart_get(swigCPtr);
      return ret;
    } 
  }

/**
*	Ordinal of the last result in the returned range.
* @ingroup GDO_ValueKeys_Misc
*/
  public uint RangeEnd {
    get {
      uint ret = gnsdk_csharp_marshalPINVOKE.GnResponseVideoObjects_RangeEnd_get(swigCPtr);
      return ret;
    } 
  }

/**
*	Estimated total number of results possible.
* @ingroup GDO_ValueKeys_Misc
*/
  public uint RangeTotal {
    get {
      uint ret = gnsdk_csharp_marshalPINVOKE.GnResponseVideoObjects_RangeTotal_get(swigCPtr);
      return ret;
    } 
  }

/**
* Flag indicating if response match(es) need a user or app decision - either multiple matches returned or less than perfect single match..
*/
  public bool NeedsDecision {
    get {
      bool ret = gnsdk_csharp_marshalPINVOKE.GnResponseVideoObjects_NeedsDecision_get(swigCPtr);
      return ret;
    } 
  }

}

}
