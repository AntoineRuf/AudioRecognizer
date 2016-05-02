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

public class GnVideoDiscEnumerable : System.Collections.Generic.IEnumerable<GnVideoDisc>, IDisposable {
  private HandleRef swigCPtr;
  protected bool swigCMemOwn;

  internal GnVideoDiscEnumerable(IntPtr cPtr, bool cMemoryOwn) {
    swigCMemOwn = cMemoryOwn;
    swigCPtr = new HandleRef(this, cPtr);
  }

  internal static HandleRef getCPtr(GnVideoDiscEnumerable obj) {
    return (obj == null) ? new HandleRef(null, IntPtr.Zero) : obj.swigCPtr;
  }

  ~GnVideoDiscEnumerable() {
    Dispose();
  }

  public virtual void Dispose() {
    lock(this) {
      if (swigCPtr.Handle != IntPtr.Zero) {
        if (swigCMemOwn) {
          swigCMemOwn = false;
          gnsdk_csharp_marshalPINVOKE.delete_GnVideoDiscEnumerable(swigCPtr);
        }
        swigCPtr = new HandleRef(null, IntPtr.Zero);
      }
      GC.SuppressFinalize(this);
    }
  }

			System.Collections.Generic.IEnumerator<GnVideoDisc> System.Collections.Generic.IEnumerable<GnVideoDisc> .GetEnumerator( )
			{
				return GetEnumerator( );
			}
			System.Collections.IEnumerator System.Collections.IEnumerable.
			    GetEnumerator( )
			{
				return GetEnumerator( );
			}

		
  public GnVideoDiscEnumerable(GnVideoDiscProvider provider, uint start) : this(gnsdk_csharp_marshalPINVOKE.new_GnVideoDiscEnumerable(GnVideoDiscProvider.getCPtr(provider), start), true) {
    if (gnsdk_csharp_marshalPINVOKE.SWIGPendingException.Pending) throw gnsdk_csharp_marshalPINVOKE.SWIGPendingException.Retrieve();
  }

  public GnVideoDiscEnumerator GetEnumerator() {
    GnVideoDiscEnumerator ret = new GnVideoDiscEnumerator(gnsdk_csharp_marshalPINVOKE.GnVideoDiscEnumerable_GetEnumerator(swigCPtr), true);
    return ret;
  }

  public GnVideoDiscEnumerator end() {
    GnVideoDiscEnumerator ret = new GnVideoDiscEnumerator(gnsdk_csharp_marshalPINVOKE.GnVideoDiscEnumerable_end(swigCPtr), true);
    return ret;
  }

  public uint count() {
    uint ret = gnsdk_csharp_marshalPINVOKE.GnVideoDiscEnumerable_count(swigCPtr);
    return ret;
  }

  public GnVideoDiscEnumerator at(uint index) {
    GnVideoDiscEnumerator ret = new GnVideoDiscEnumerator(gnsdk_csharp_marshalPINVOKE.GnVideoDiscEnumerable_at(swigCPtr, index), true);
    return ret;
  }

  public GnVideoDiscEnumerator getByIndex(uint index) {
    GnVideoDiscEnumerator ret = new GnVideoDiscEnumerator(gnsdk_csharp_marshalPINVOKE.GnVideoDiscEnumerable_getByIndex(swigCPtr, index), true);
    return ret;
  }

}

}
