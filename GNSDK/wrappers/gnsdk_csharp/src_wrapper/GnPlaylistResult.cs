
namespace GracenoteSDK {

using System;
using System.Runtime.InteropServices;

/**
* <b>Experimental</b>: GnPlaylistResult
*/
public class GnPlaylistResult : GnObject {
  private HandleRef swigCPtr;

  internal GnPlaylistResult(IntPtr cPtr, bool cMemoryOwn) : base(gnsdk_csharp_marshalPINVOKE.GnPlaylistResult_SWIGUpcast(cPtr), cMemoryOwn) {
    swigCPtr = new HandleRef(this, cPtr);
  }

  internal static HandleRef getCPtr(GnPlaylistResult obj) {
    return (obj == null) ? new HandleRef(null, IntPtr.Zero) : obj.swigCPtr;
  }

  ~GnPlaylistResult() {
    Dispose();
  }

  public override void Dispose() {
    lock(this) {
      if (swigCPtr.Handle != IntPtr.Zero) {
        if (swigCMemOwn) {
          swigCMemOwn = false;
          gnsdk_csharp_marshalPINVOKE.delete_GnPlaylistResult(swigCPtr);
        }
        swigCPtr = new HandleRef(null, IntPtr.Zero);
      }
      GC.SuppressFinalize(this);
      base.Dispose();
    }
  }

  public GnPlaylistResultIdentEnumerable Identifiers {
    get {
      IntPtr cPtr = gnsdk_csharp_marshalPINVOKE.GnPlaylistResult_Identifiers_get(swigCPtr);
      GnPlaylistResultIdentEnumerable ret = (cPtr == IntPtr.Zero) ? null : new GnPlaylistResultIdentEnumerable(cPtr, true);
      return ret;
    } 
  }

}

}
