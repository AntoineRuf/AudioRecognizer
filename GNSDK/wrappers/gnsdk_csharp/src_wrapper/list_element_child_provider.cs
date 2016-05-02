
namespace GracenoteSDK {

using System;
using System.Runtime.InteropServices;

public class list_element_child_provider : IDisposable {
  private HandleRef swigCPtr;
  protected bool swigCMemOwn;

  internal list_element_child_provider(IntPtr cPtr, bool cMemoryOwn) {
    swigCMemOwn = cMemoryOwn;
    swigCPtr = new HandleRef(this, cPtr);
  }

  internal static HandleRef getCPtr(list_element_child_provider obj) {
    return (obj == null) ? new HandleRef(null, IntPtr.Zero) : obj.swigCPtr;
  }

  ~list_element_child_provider() {
    Dispose();
  }

  public virtual void Dispose() {
    lock(this) {
      if (swigCPtr.Handle != IntPtr.Zero) {
        if (swigCMemOwn) {
          swigCMemOwn = false;
          gnsdk_csharp_marshalPINVOKE.delete_list_element_child_provider(swigCPtr);
        }
        swigCPtr = new HandleRef(null, IntPtr.Zero);
      }
      GC.SuppressFinalize(this);
    }
  }

/** 
* Constructor
*/
  public list_element_child_provider() : this(gnsdk_csharp_marshalPINVOKE.new_list_element_child_provider(), true) {
  }

/** 
* Get list elment by position
*/
  public GnListElement get_data(uint pos) {
    GnListElement ret = new GnListElement(gnsdk_csharp_marshalPINVOKE.list_element_child_provider_get_data(swigCPtr, pos), true);
    return ret;
  }

/** 
* Get child list element count
*/
  public uint count() {
    uint ret = gnsdk_csharp_marshalPINVOKE.list_element_child_provider_count(swigCPtr);
    return ret;
  }

}

}
