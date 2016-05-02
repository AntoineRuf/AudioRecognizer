
namespace GracenoteSDK {

using System;
using System.Runtime.InteropServices;

/**
** <b>Experimental</b>: GnMoodgridResult
*/
public class GnMoodgridResult : GnObject {
  private HandleRef swigCPtr;

  internal GnMoodgridResult(IntPtr cPtr, bool cMemoryOwn) : base(gnsdk_csharp_marshalPINVOKE.GnMoodgridResult_SWIGUpcast(cPtr), cMemoryOwn) {
    swigCPtr = new HandleRef(this, cPtr);
  }

  internal static HandleRef getCPtr(GnMoodgridResult obj) {
    return (obj == null) ? new HandleRef(null, IntPtr.Zero) : obj.swigCPtr;
  }

  ~GnMoodgridResult() {
    Dispose();
  }

  public override void Dispose() {
    lock(this) {
      if (swigCPtr.Handle != IntPtr.Zero) {
        if (swigCMemOwn) {
          swigCMemOwn = false;
          gnsdk_csharp_marshalPINVOKE.delete_GnMoodgridResult(swigCPtr);
        }
        swigCPtr = new HandleRef(null, IntPtr.Zero);
      }
      GC.SuppressFinalize(this);
      base.Dispose();
    }
  }

/**
*  Returns the count of the GnMoodgridIdentifier instances in this result.
* @return count
*/
  public uint Count() {
    uint ret = gnsdk_csharp_marshalPINVOKE.GnMoodgridResult_Count(swigCPtr);
    if (gnsdk_csharp_marshalPINVOKE.SWIGPendingException.Pending) throw gnsdk_csharp_marshalPINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

  public GnMoodgridResultEnumerable Identifiers {
    get {
      IntPtr cPtr = gnsdk_csharp_marshalPINVOKE.GnMoodgridResult_Identifiers_get(swigCPtr);
      GnMoodgridResultEnumerable ret = (cPtr == IntPtr.Zero) ? null : new GnMoodgridResultEnumerable(cPtr, true);
      return ret;
    } 
  }

}

}
