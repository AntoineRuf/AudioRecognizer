
namespace GracenoteSDK {

using System;
using System.Runtime.InteropServices;

public class result_provider : IDisposable {
  private HandleRef swigCPtr;
  protected bool swigCMemOwn;

  internal result_provider(IntPtr cPtr, bool cMemoryOwn) {
    swigCMemOwn = cMemoryOwn;
    swigCPtr = new HandleRef(this, cPtr);
  }

  internal static HandleRef getCPtr(result_provider obj) {
    return (obj == null) ? new HandleRef(null, IntPtr.Zero) : obj.swigCPtr;
  }

  ~result_provider() {
    Dispose();
  }

  public virtual void Dispose() {
    lock(this) {
      if (swigCPtr.Handle != IntPtr.Zero) {
        if (swigCMemOwn) {
          swigCMemOwn = false;
          gnsdk_csharp_marshalPINVOKE.delete_result_provider(swigCPtr);
        }
        swigCPtr = new HandleRef(null, IntPtr.Zero);
      }
      GC.SuppressFinalize(this);
    }
  }

  public result_provider() : this(gnsdk_csharp_marshalPINVOKE.new_result_provider(), true) {
  }

  public GnPlaylistIdentifier get_data(uint pos) {
    GnPlaylistIdentifier ret = new GnPlaylistIdentifier(gnsdk_csharp_marshalPINVOKE.result_provider_get_data(swigCPtr, pos), true);
    return ret;
  }

  public uint count() {
    uint ret = gnsdk_csharp_marshalPINVOKE.result_provider_count(swigCPtr);
    return ret;
  }

}

}
