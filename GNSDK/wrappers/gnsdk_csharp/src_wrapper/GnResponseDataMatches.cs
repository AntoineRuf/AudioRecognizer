
namespace GracenoteSDK {

using System;
using System.Runtime.InteropServices;

/**
* Collection of data match results received in response to a data match query.
*/
public class GnResponseDataMatches : GnDataObject {
  private HandleRef swigCPtr;

  internal GnResponseDataMatches(IntPtr cPtr, bool cMemoryOwn) : base(gnsdk_csharp_marshalPINVOKE.GnResponseDataMatches_SWIGUpcast(cPtr), cMemoryOwn) {
    swigCPtr = new HandleRef(this, cPtr);
  }

  internal static HandleRef getCPtr(GnResponseDataMatches obj) {
    return (obj == null) ? new HandleRef(null, IntPtr.Zero) : obj.swigCPtr;
  }

  ~GnResponseDataMatches() {
    Dispose();
  }

  public override void Dispose() {
    lock(this) {
      if (swigCPtr.Handle != IntPtr.Zero) {
        if (swigCMemOwn) {
          swigCMemOwn = false;
          gnsdk_csharp_marshalPINVOKE.delete_GnResponseDataMatches(swigCPtr);
        }
        swigCPtr = new HandleRef(null, IntPtr.Zero);
      }
      GC.SuppressFinalize(this);
      base.Dispose();
    }
  }

/**
*  Result count - number of matches returned
*  @return Count
*/
  public uint ResultCount() {
    uint ret = gnsdk_csharp_marshalPINVOKE.GnResponseDataMatches_ResultCount(swigCPtr);
    return ret;
  }

/**
*  Range start - ordinal value of first match in range total
*  @return Range start
*/
  public uint RangeStart() {
    uint ret = gnsdk_csharp_marshalPINVOKE.GnResponseDataMatches_RangeStart(swigCPtr);
    return ret;
  }

/**
*  Range end - ordinal value of last match in range total
*  @return Range end
*/
  public uint RangeEnd() {
    uint ret = gnsdk_csharp_marshalPINVOKE.GnResponseDataMatches_RangeEnd(swigCPtr);
    return ret;
  }

/**
*  Range total - total number of matches that could be returned
*  @return Range total
*/
  public uint RangeTotal() {
    uint ret = gnsdk_csharp_marshalPINVOKE.GnResponseDataMatches_RangeTotal(swigCPtr);
    return ret;
  }

/**
*  Flag indicating if response needs user or app decision - either multiple matches returned or less than perfect single match
*  @return True is user decision needed, false otherwise
*/
  public bool NeedsDecision() {
    bool ret = gnsdk_csharp_marshalPINVOKE.GnResponseDataMatches_NeedsDecision(swigCPtr);
    return ret;
  }

  public GnDataMatchEnumerable DataMatches {
    get {
      IntPtr cPtr = gnsdk_csharp_marshalPINVOKE.GnResponseDataMatches_DataMatches_get(swigCPtr);
      GnDataMatchEnumerable ret = (cPtr == IntPtr.Zero) ? null : new GnDataMatchEnumerable(cPtr, true);
      return ret;
    } 
  }

}

}
