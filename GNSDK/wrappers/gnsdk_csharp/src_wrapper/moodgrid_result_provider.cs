
namespace GracenoteSDK {

using System;
using System.Runtime.InteropServices;

public class moodgrid_result_provider : IDisposable {
  private HandleRef swigCPtr;
  protected bool swigCMemOwn;

  internal moodgrid_result_provider(IntPtr cPtr, bool cMemoryOwn) {
    swigCMemOwn = cMemoryOwn;
    swigCPtr = new HandleRef(this, cPtr);
  }

  internal static HandleRef getCPtr(moodgrid_result_provider obj) {
    return (obj == null) ? new HandleRef(null, IntPtr.Zero) : obj.swigCPtr;
  }

  ~moodgrid_result_provider() {
    Dispose();
  }

  public virtual void Dispose() {
    lock(this) {
      if (swigCPtr.Handle != IntPtr.Zero) {
        if (swigCMemOwn) {
          swigCMemOwn = false;
          gnsdk_csharp_marshalPINVOKE.delete_moodgrid_result_provider(swigCPtr);
        }
        swigCPtr = new HandleRef(null, IntPtr.Zero);
      }
      GC.SuppressFinalize(this);
    }
  }

  public GnMoodgridIdentifier get_data(uint pos) {
    GnMoodgridIdentifier ret = new GnMoodgridIdentifier(gnsdk_csharp_marshalPINVOKE.moodgrid_result_provider_get_data(swigCPtr, pos), true);
    return ret;
  }

  public uint count() {
    uint ret = gnsdk_csharp_marshalPINVOKE.moodgrid_result_provider_count(swigCPtr);
    return ret;
  }

}

}
