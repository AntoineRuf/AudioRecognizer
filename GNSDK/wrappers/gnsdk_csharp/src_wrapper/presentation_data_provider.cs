
namespace GracenoteSDK {

using System;
using System.Runtime.InteropServices;

/**
** Internal class  presentation_data_provider
*/
public class presentation_data_provider : IDisposable {
  private HandleRef swigCPtr;
  protected bool swigCMemOwn;

  internal presentation_data_provider(IntPtr cPtr, bool cMemoryOwn) {
    swigCMemOwn = cMemoryOwn;
    swigCPtr = new HandleRef(this, cPtr);
  }

  internal static HandleRef getCPtr(presentation_data_provider obj) {
    return (obj == null) ? new HandleRef(null, IntPtr.Zero) : obj.swigCPtr;
  }

  ~presentation_data_provider() {
    Dispose();
  }

  public virtual void Dispose() {
    lock(this) {
      if (swigCPtr.Handle != IntPtr.Zero) {
        if (swigCMemOwn) {
          swigCMemOwn = false;
          gnsdk_csharp_marshalPINVOKE.delete_presentation_data_provider(swigCPtr);
        }
        swigCPtr = new HandleRef(null, IntPtr.Zero);
      }
      GC.SuppressFinalize(this);
    }
  }

  public presentation_data_provider() : this(gnsdk_csharp_marshalPINVOKE.new_presentation_data_provider__SWIG_0(), true) {
  }

  public presentation_data_provider(GnMoodgridPresentationType type) : this(gnsdk_csharp_marshalPINVOKE.new_presentation_data_provider__SWIG_1((int)type), true) {
  }

  public GnMoodgridDataPoint get_data(uint pos) {
    GnMoodgridDataPoint ret = new GnMoodgridDataPoint(gnsdk_csharp_marshalPINVOKE.presentation_data_provider_get_data(swigCPtr, pos), true);
    return ret;
  }

  public uint count() {
    uint ret = gnsdk_csharp_marshalPINVOKE.presentation_data_provider_count(swigCPtr);
    return ret;
  }

}

}
