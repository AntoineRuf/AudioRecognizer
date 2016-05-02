
namespace GracenoteSDK {

using System;
using System.Runtime.InteropServices;

/**
** Internal class  moodgrid_provider
*/
public class moodgrid_provider : IDisposable {
  private HandleRef swigCPtr;
  protected bool swigCMemOwn;

  internal moodgrid_provider(IntPtr cPtr, bool cMemoryOwn) {
    swigCMemOwn = cMemoryOwn;
    swigCPtr = new HandleRef(this, cPtr);
  }

  internal static HandleRef getCPtr(moodgrid_provider obj) {
    return (obj == null) ? new HandleRef(null, IntPtr.Zero) : obj.swigCPtr;
  }

  ~moodgrid_provider() {
    Dispose();
  }

  public virtual void Dispose() {
    lock(this) {
      if (swigCPtr.Handle != IntPtr.Zero) {
        if (swigCMemOwn) {
          swigCMemOwn = false;
          gnsdk_csharp_marshalPINVOKE.delete_moodgrid_provider(swigCPtr);
        }
        swigCPtr = new HandleRef(null, IntPtr.Zero);
      }
      GC.SuppressFinalize(this);
    }
  }

  public GnMoodgridProvider get_data(uint pos) {
    GnMoodgridProvider ret = new GnMoodgridProvider(gnsdk_csharp_marshalPINVOKE.moodgrid_provider_get_data(swigCPtr, pos), true);
    return ret;
  }

  public uint count() {
    uint ret = gnsdk_csharp_marshalPINVOKE.moodgrid_provider_count(swigCPtr);
    return ret;
  }

  public moodgrid_provider() : this(gnsdk_csharp_marshalPINVOKE.new_moodgrid_provider(), true) {
  }

}

}
