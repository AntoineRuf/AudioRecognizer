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

public class GnContentEnumerable : System.Collections.Generic.IEnumerable<GnContent>, IDisposable {
  private HandleRef swigCPtr;
  protected bool swigCMemOwn;

  internal GnContentEnumerable(IntPtr cPtr, bool cMemoryOwn) {
    swigCMemOwn = cMemoryOwn;
    swigCPtr = new HandleRef(this, cPtr);
  }

  internal static HandleRef getCPtr(GnContentEnumerable obj) {
    return (obj == null) ? new HandleRef(null, IntPtr.Zero) : obj.swigCPtr;
  }

  ~GnContentEnumerable() {
    Dispose();
  }

  public virtual void Dispose() {
    lock(this) {
      if (swigCPtr.Handle != IntPtr.Zero) {
        if (swigCMemOwn) {
          swigCMemOwn = false;
          gnsdk_csharp_marshalPINVOKE.delete_GnContentEnumerable(swigCPtr);
        }
        swigCPtr = new HandleRef(null, IntPtr.Zero);
      }
      GC.SuppressFinalize(this);
    }
  }

			System.Collections.Generic.IEnumerator<GnContent> System.Collections.Generic.IEnumerable<GnContent> .GetEnumerator( )
			{
				return GetEnumerator( );
			}
			System.Collections.IEnumerator System.Collections.IEnumerable.
			    GetEnumerator( )
			{
				return GetEnumerator( );
			}

		
  public GnContentEnumerable(GnContentProvider provider, uint start) : this(gnsdk_csharp_marshalPINVOKE.new_GnContentEnumerable(GnContentProvider.getCPtr(provider), start), true) {
    if (gnsdk_csharp_marshalPINVOKE.SWIGPendingException.Pending) throw gnsdk_csharp_marshalPINVOKE.SWIGPendingException.Retrieve();
  }

  public GnContentEnumerator GetEnumerator() {
    GnContentEnumerator ret = new GnContentEnumerator(gnsdk_csharp_marshalPINVOKE.GnContentEnumerable_GetEnumerator(swigCPtr), true);
    return ret;
  }

  public GnContentEnumerator end() {
    GnContentEnumerator ret = new GnContentEnumerator(gnsdk_csharp_marshalPINVOKE.GnContentEnumerable_end(swigCPtr), true);
    return ret;
  }

  public uint count() {
    uint ret = gnsdk_csharp_marshalPINVOKE.GnContentEnumerable_count(swigCPtr);
    return ret;
  }

  public GnContentEnumerator at(uint index) {
    GnContentEnumerator ret = new GnContentEnumerator(gnsdk_csharp_marshalPINVOKE.GnContentEnumerable_at(swigCPtr, index), true);
    return ret;
  }

  public GnContentEnumerator getByIndex(uint index) {
    GnContentEnumerator ret = new GnContentEnumerator(gnsdk_csharp_marshalPINVOKE.GnContentEnumerable_getByIndex(swigCPtr, index), true);
    return ret;
  }

}

}
