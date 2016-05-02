
namespace GracenoteSDK {

using System;
using System.Runtime.InteropServices;

public class attribute_provider : IDisposable {
  private HandleRef swigCPtr;
  protected bool swigCMemOwn;

  internal attribute_provider(IntPtr cPtr, bool cMemoryOwn) {
    swigCMemOwn = cMemoryOwn;
    swigCPtr = new HandleRef(this, cPtr);
  }

  internal static HandleRef getCPtr(attribute_provider obj) {
    return (obj == null) ? new HandleRef(null, IntPtr.Zero) : obj.swigCPtr;
  }

  ~attribute_provider() {
    Dispose();
  }

  public virtual void Dispose() {
    lock(this) {
      if (swigCPtr.Handle != IntPtr.Zero) {
        if (swigCMemOwn) {
          swigCMemOwn = false;
          gnsdk_csharp_marshalPINVOKE.delete_attribute_provider(swigCPtr);
        }
        swigCPtr = new HandleRef(null, IntPtr.Zero);
      }
      GC.SuppressFinalize(this);
    }
  }

  public attribute_provider() : this(gnsdk_csharp_marshalPINVOKE.new_attribute_provider(), true) {
  }

  public string get_data(uint pos) {
    string ret = gnsdk_csharp_marshalPINVOKE.attribute_provider_get_data(swigCPtr, pos);
    return ret;
  }

  public uint count() {
    uint ret = gnsdk_csharp_marshalPINVOKE.attribute_provider_count(swigCPtr);
    return ret;
  }

}

}
