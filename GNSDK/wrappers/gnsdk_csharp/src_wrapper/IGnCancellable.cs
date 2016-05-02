
namespace GracenoteSDK {

using System;
using System.Runtime.InteropServices;

/**
* Interface for defining a Cancellable object
*/
public class IGnCancellable : IDisposable {
  private HandleRef swigCPtr;
  protected bool swigCMemOwn;

  internal IGnCancellable(IntPtr cPtr, bool cMemoryOwn) {
    swigCMemOwn = cMemoryOwn;
    swigCPtr = new HandleRef(this, cPtr);
  }

  internal static HandleRef getCPtr(IGnCancellable obj) {
    return (obj == null) ? new HandleRef(null, IntPtr.Zero) : obj.swigCPtr;
  }

  ~IGnCancellable() {
    Dispose();
  }

  public virtual void Dispose() {
    lock(this) {
      if (swigCPtr.Handle != IntPtr.Zero) {
        if (swigCMemOwn) {
          swigCMemOwn = false;
          gnsdk_csharp_marshalPINVOKE.delete_IGnCancellable(swigCPtr);
        }
        swigCPtr = new HandleRef(null, IntPtr.Zero);
      }
      GC.SuppressFinalize(this);
    }
  }

/**
* Set cancel state
* @param bCancel 	[in] Cancel state
*/
  public virtual void SetCancel(bool bCancel) {
    gnsdk_csharp_marshalPINVOKE.IGnCancellable_SetCancel(swigCPtr, bCancel);
  }

/**
* Get cancel state
* @return True of cancelled, false otherwise
*/
  public virtual bool IsCancelled() {
    bool ret = gnsdk_csharp_marshalPINVOKE.IGnCancellable_IsCancelled(swigCPtr);
    return ret;
  }

}

}
