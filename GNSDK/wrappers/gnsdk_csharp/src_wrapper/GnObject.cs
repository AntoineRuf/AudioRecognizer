
namespace GracenoteSDK {

using System;
using System.Runtime.InteropServices;

/**
* Base object for managing objects in natively running GNSDK.
*/
public class GnObject : IDisposable {
  private HandleRef swigCPtr;
  protected bool swigCMemOwn;

  internal GnObject(IntPtr cPtr, bool cMemoryOwn) {
    swigCMemOwn = cMemoryOwn;
    swigCPtr = new HandleRef(this, cPtr);
  }

  internal static HandleRef getCPtr(GnObject obj) {
    return (obj == null) ? new HandleRef(null, IntPtr.Zero) : obj.swigCPtr;
  }

  public virtual void Dispose() {
    lock(this) {
      if (swigCPtr.Handle != IntPtr.Zero) {
        if (swigCMemOwn) {
          swigCMemOwn = false;
          throw new MethodAccessException("C++ destructor does not have public access");
        }
        swigCPtr = new HandleRef(null, IntPtr.Zero);
      }
      GC.SuppressFinalize(this);
    }
  }

/**
*  Get flag indicating if GnObject contains no native object handle
*  @return True if null, false otherwise
*/
  public bool IsNull() {
    bool ret = gnsdk_csharp_marshalPINVOKE.GnObject_IsNull(swigCPtr);
    return ret;
  }

}

}
