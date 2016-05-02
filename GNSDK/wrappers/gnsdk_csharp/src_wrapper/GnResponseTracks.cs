
namespace GracenoteSDK {

using System;
using System.Runtime.InteropServices;

/**
* Collection of track results received in response to a track query
*/
public class GnResponseTracks : GnDataObject {
  private HandleRef swigCPtr;

  internal GnResponseTracks(IntPtr cPtr, bool cMemoryOwn) : base(gnsdk_csharp_marshalPINVOKE.GnResponseTracks_SWIGUpcast(cPtr), cMemoryOwn) {
    swigCPtr = new HandleRef(this, cPtr);
  }

  internal static HandleRef getCPtr(GnResponseTracks obj) {
    return (obj == null) ? new HandleRef(null, IntPtr.Zero) : obj.swigCPtr;
  }

  ~GnResponseTracks() {
    Dispose();
  }

  public override void Dispose() {
    lock(this) {
      if (swigCPtr.Handle != IntPtr.Zero) {
        if (swigCMemOwn) {
          swigCMemOwn = false;
          gnsdk_csharp_marshalPINVOKE.delete_GnResponseTracks(swigCPtr);
        }
        swigCPtr = new HandleRef(null, IntPtr.Zero);
      }
      GC.SuppressFinalize(this);
      base.Dispose();
    }
  }

  public static string GnType() {
    string ret = gnsdk_csharp_marshalPINVOKE.GnResponseTracks_GnType();
    return ret;
  }

  public static GnResponseTracks From(GnDataObject obj) {
    GnResponseTracks ret = new GnResponseTracks(gnsdk_csharp_marshalPINVOKE.GnResponseTracks_From(GnDataObject.getCPtr(obj)), true);
    if (gnsdk_csharp_marshalPINVOKE.SWIGPendingException.Pending) throw gnsdk_csharp_marshalPINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

/**
*  Result count - number of matches returned
*  @return Count
*/
  public uint ResultCount() {
    uint ret = gnsdk_csharp_marshalPINVOKE.GnResponseTracks_ResultCount(swigCPtr);
    return ret;
  }

/**
*  Range start - ordinal value of first match in range total
*  @return Range start ordinal
*/
  public uint RangeStart() {
    uint ret = gnsdk_csharp_marshalPINVOKE.GnResponseTracks_RangeStart(swigCPtr);
    return ret;
  }

/**
*  Range end - ordinal value of last match in range total
*  @return Range end ordinal
*/
  public uint RangeEnd() {
    uint ret = gnsdk_csharp_marshalPINVOKE.GnResponseTracks_RangeEnd(swigCPtr);
    return ret;
  }

/**
*  Range total - total number of matches that could be returned
*  @return Range total
*/
  public uint RangeTotal() {
    uint ret = gnsdk_csharp_marshalPINVOKE.GnResponseTracks_RangeTotal(swigCPtr);
    return ret;
  }

/**
*  Flag indicating if response needs user decision - either multiple matches returned or less than perfect single match
*  @return True if user decision required, false otherwise
*/
  public bool NeedsDecision() {
    bool ret = gnsdk_csharp_marshalPINVOKE.GnResponseTracks_NeedsDecision(swigCPtr);
    return ret;
  }

  public GnTrackEnumerable Tracks {
    get {
      IntPtr cPtr = gnsdk_csharp_marshalPINVOKE.GnResponseTracks_Tracks_get(swigCPtr);
      GnTrackEnumerable ret = (cPtr == IntPtr.Zero) ? null : new GnTrackEnumerable(cPtr, true);
      return ret;
    } 
  }

}

}
