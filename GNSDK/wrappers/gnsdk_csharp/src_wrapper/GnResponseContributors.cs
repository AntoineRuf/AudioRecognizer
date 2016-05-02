
namespace GracenoteSDK {

using System;
using System.Runtime.InteropServices;

/**
*  \class GnResponseContributors
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
public class GnResponseContributors : GnDataObject {
  private HandleRef swigCPtr;

  internal GnResponseContributors(IntPtr cPtr, bool cMemoryOwn) : base(gnsdk_csharp_marshalPINVOKE.GnResponseContributors_SWIGUpcast(cPtr), cMemoryOwn) {
    swigCPtr = new HandleRef(this, cPtr);
  }

  internal static HandleRef getCPtr(GnResponseContributors obj) {
    return (obj == null) ? new HandleRef(null, IntPtr.Zero) : obj.swigCPtr;
  }

  ~GnResponseContributors() {
    Dispose();
  }

  public override void Dispose() {
    lock(this) {
      if (swigCPtr.Handle != IntPtr.Zero) {
        if (swigCMemOwn) {
          swigCMemOwn = false;
          gnsdk_csharp_marshalPINVOKE.delete_GnResponseContributors(swigCPtr);
        }
        swigCPtr = new HandleRef(null, IntPtr.Zero);
      }
      GC.SuppressFinalize(this);
      base.Dispose();
    }
  }

/**
*  Total number of results
*/
  public uint ResultCount {
    get {
      uint ret = gnsdk_csharp_marshalPINVOKE.GnResponseContributors_ResultCount_get(swigCPtr);
      return ret;
    } 
  }

/**
*	Ordinal of the first result in the returned range.
*	@ingroup GDO_ValueKeys_Misc
*/
  public uint RangeStart {
    get {
      uint ret = gnsdk_csharp_marshalPINVOKE.GnResponseContributors_RangeStart_get(swigCPtr);
      return ret;
    } 
  }

/**
*	Ordinal of the last result in the returned range.
*	@ingroup GDO_ValueKeys_Misc
*/
  public uint RangeEnd {
    get {
      uint ret = gnsdk_csharp_marshalPINVOKE.GnResponseContributors_RangeEnd_get(swigCPtr);
      return ret;
    } 
  }

/**
*	Estimated total number of results possible.
*	@ingroup GDO_ValueKeys_Misc
*/
  public uint RangeTotal {
    get {
      uint ret = gnsdk_csharp_marshalPINVOKE.GnResponseContributors_RangeTotal_get(swigCPtr);
      return ret;
    } 
  }

/**
* Flag indicating if response match(es) need a user or app decision - either multiple matches returned or less than perfect single match..
*/
  public bool NeedsDecision {
    get {
      bool ret = gnsdk_csharp_marshalPINVOKE.GnResponseContributors_NeedsDecision_get(swigCPtr);
      return ret;
    } 
  }

  public GnContributorEnumerable Contributors {
    get {
      IntPtr cPtr = gnsdk_csharp_marshalPINVOKE.GnResponseContributors_Contributors_get(swigCPtr);
      GnContributorEnumerable ret = (cPtr == IntPtr.Zero) ? null : new GnContributorEnumerable(cPtr, true);
      return ret;
    } 
  }

}

}
