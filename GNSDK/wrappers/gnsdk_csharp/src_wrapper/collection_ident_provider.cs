
namespace GracenoteSDK {

using System;
using System.Runtime.InteropServices;

public class collection_ident_provider : IDisposable {
  private HandleRef swigCPtr;
  protected bool swigCMemOwn;

  internal collection_ident_provider(IntPtr cPtr, bool cMemoryOwn) {
    swigCMemOwn = cMemoryOwn;
    swigCPtr = new HandleRef(this, cPtr);
  }

  internal static HandleRef getCPtr(collection_ident_provider obj) {
    return (obj == null) ? new HandleRef(null, IntPtr.Zero) : obj.swigCPtr;
  }

  ~collection_ident_provider() {
    Dispose();
  }

  public virtual void Dispose() {
    lock(this) {
      if (swigCPtr.Handle != IntPtr.Zero) {
        if (swigCMemOwn) {
          swigCMemOwn = false;
          gnsdk_csharp_marshalPINVOKE.delete_collection_ident_provider(swigCPtr);
        }
        swigCPtr = new HandleRef(null, IntPtr.Zero);
      }
      GC.SuppressFinalize(this);
    }
  }

  public collection_ident_provider() : this(gnsdk_csharp_marshalPINVOKE.new_collection_ident_provider(), true) {
  }

  public GnPlaylistIdentifier get_data(uint pos) {
    GnPlaylistIdentifier ret = new GnPlaylistIdentifier(gnsdk_csharp_marshalPINVOKE.collection_ident_provider_get_data(swigCPtr, pos), true);
    return ret;
  }

  public uint count() {
    uint ret = gnsdk_csharp_marshalPINVOKE.collection_ident_provider_count(swigCPtr);
    return ret;
  }

}

}
