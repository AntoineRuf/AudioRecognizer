/* ----------------------------------------------------------------------------
 * This file was automatically generated by SWIG (http://www.swig.org).
 * Version 2.0.12
 *
 * Do not make changes to this file unless you know what you are doing--modify
 * the SWIG interface file instead.
 * ----------------------------------------------------------------------------- */

namespace GracenoteSDK {

using System;
using System.Runtime.InteropServices;

public class GnAssetEnumerable : IDisposable {
  private HandleRef swigCPtr;
  protected bool swigCMemOwn;

  internal GnAssetEnumerable(IntPtr cPtr, bool cMemoryOwn) {
    swigCMemOwn = cMemoryOwn;
    swigCPtr = new HandleRef(this, cPtr);
  }

  internal static HandleRef getCPtr(GnAssetEnumerable obj) {
    return (obj == null) ? new HandleRef(null, IntPtr.Zero) : obj.swigCPtr;
  }

  ~GnAssetEnumerable() {
    Dispose();
  }

  public virtual void Dispose() {
    lock(this) {
      if (swigCPtr.Handle != IntPtr.Zero) {
        if (swigCMemOwn) {
          swigCMemOwn = false;
          gnsdk_csharp_marshalPINVOKE.delete_GnAssetEnumerable(swigCPtr);
        }
        swigCPtr = new HandleRef(null, IntPtr.Zero);
      }
      GC.SuppressFinalize(this);
    }
  }

  public GnAssetEnumerable(GnAssetProvider provider, uint start) : this(gnsdk_csharp_marshalPINVOKE.new_GnAssetEnumerable(GnAssetProvider.getCPtr(provider), start), true) {
    if (gnsdk_csharp_marshalPINVOKE.SWIGPendingException.Pending) throw gnsdk_csharp_marshalPINVOKE.SWIGPendingException.Retrieve();
  }

  public GnAssetEnumerator GetEnumerator() {
    GnAssetEnumerator ret = new GnAssetEnumerator(gnsdk_csharp_marshalPINVOKE.GnAssetEnumerable_GetEnumerator(swigCPtr), true);
    return ret;
  }

  public GnAssetEnumerator end() {
    GnAssetEnumerator ret = new GnAssetEnumerator(gnsdk_csharp_marshalPINVOKE.GnAssetEnumerable_end(swigCPtr), true);
    return ret;
  }

  public uint count() {
    uint ret = gnsdk_csharp_marshalPINVOKE.GnAssetEnumerable_count(swigCPtr);
    return ret;
  }

  public GnAssetEnumerator at(uint index) {
    GnAssetEnumerator ret = new GnAssetEnumerator(gnsdk_csharp_marshalPINVOKE.GnAssetEnumerable_at(swigCPtr, index), true);
    return ret;
  }

  public GnAssetEnumerator getByIndex(uint index) {
    GnAssetEnumerator ret = new GnAssetEnumerator(gnsdk_csharp_marshalPINVOKE.GnAssetEnumerable_getByIndex(swigCPtr, index), true);
    return ret;
  }

}

}
