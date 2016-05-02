
namespace GracenoteSDK {

using System;
using System.Runtime.InteropServices;

public class collection_storage_provider : IDisposable {
  private HandleRef swigCPtr;
  protected bool swigCMemOwn;

  internal collection_storage_provider(IntPtr cPtr, bool cMemoryOwn) {
    swigCMemOwn = cMemoryOwn;
    swigCPtr = new HandleRef(this, cPtr);
  }

  internal static HandleRef getCPtr(collection_storage_provider obj) {
    return (obj == null) ? new HandleRef(null, IntPtr.Zero) : obj.swigCPtr;
  }

  ~collection_storage_provider() {
    Dispose();
  }

  public virtual void Dispose() {
    lock(this) {
      if (swigCPtr.Handle != IntPtr.Zero) {
        if (swigCMemOwn) {
          swigCMemOwn = false;
          gnsdk_csharp_marshalPINVOKE.delete_collection_storage_provider(swigCPtr);
        }
        swigCPtr = new HandleRef(null, IntPtr.Zero);
      }
      GC.SuppressFinalize(this);
    }
  }

  public collection_storage_provider() : this(gnsdk_csharp_marshalPINVOKE.new_collection_storage_provider__SWIG_0(), true) {
  }

  public collection_storage_provider(collection_storage_provider arg0) : this(gnsdk_csharp_marshalPINVOKE.new_collection_storage_provider__SWIG_1(collection_storage_provider.getCPtr(arg0)), true) {
    if (gnsdk_csharp_marshalPINVOKE.SWIGPendingException.Pending) throw gnsdk_csharp_marshalPINVOKE.SWIGPendingException.Retrieve();
  }

  public string get_data(uint pos) {
    string ret = gnsdk_csharp_marshalPINVOKE.collection_storage_provider_get_data(swigCPtr, pos);
    return ret;
  }

  public uint count() {
    uint ret = gnsdk_csharp_marshalPINVOKE.collection_storage_provider_count(swigCPtr);
    return ret;
  }

}

}
