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

public class GnVideoSeriesEnumerable : System.Collections.Generic.IEnumerable<GnVideoSeries>, IDisposable {
  private HandleRef swigCPtr;
  protected bool swigCMemOwn;

  internal GnVideoSeriesEnumerable(IntPtr cPtr, bool cMemoryOwn) {
    swigCMemOwn = cMemoryOwn;
    swigCPtr = new HandleRef(this, cPtr);
  }

  internal static HandleRef getCPtr(GnVideoSeriesEnumerable obj) {
    return (obj == null) ? new HandleRef(null, IntPtr.Zero) : obj.swigCPtr;
  }

  ~GnVideoSeriesEnumerable() {
    Dispose();
  }

  public virtual void Dispose() {
    lock(this) {
      if (swigCPtr.Handle != IntPtr.Zero) {
        if (swigCMemOwn) {
          swigCMemOwn = false;
          gnsdk_csharp_marshalPINVOKE.delete_GnVideoSeriesEnumerable(swigCPtr);
        }
        swigCPtr = new HandleRef(null, IntPtr.Zero);
      }
      GC.SuppressFinalize(this);
    }
  }

			System.Collections.Generic.IEnumerator<GnVideoSeries> System.Collections.Generic.IEnumerable<GnVideoSeries> .GetEnumerator( )
			{
				return GetEnumerator( );
			}
			System.Collections.IEnumerator System.Collections.IEnumerable.
			    GetEnumerator( )
			{
				return GetEnumerator( );
			}

		
  public GnVideoSeriesEnumerable(GnVideoSeriesProvider provider, uint start) : this(gnsdk_csharp_marshalPINVOKE.new_GnVideoSeriesEnumerable(GnVideoSeriesProvider.getCPtr(provider), start), true) {
    if (gnsdk_csharp_marshalPINVOKE.SWIGPendingException.Pending) throw gnsdk_csharp_marshalPINVOKE.SWIGPendingException.Retrieve();
  }

  public GnVideoSeriesEnumerator GetEnumerator() {
    GnVideoSeriesEnumerator ret = new GnVideoSeriesEnumerator(gnsdk_csharp_marshalPINVOKE.GnVideoSeriesEnumerable_GetEnumerator(swigCPtr), true);
    return ret;
  }

  public GnVideoSeriesEnumerator end() {
    GnVideoSeriesEnumerator ret = new GnVideoSeriesEnumerator(gnsdk_csharp_marshalPINVOKE.GnVideoSeriesEnumerable_end(swigCPtr), true);
    return ret;
  }

  public uint count() {
    uint ret = gnsdk_csharp_marshalPINVOKE.GnVideoSeriesEnumerable_count(swigCPtr);
    return ret;
  }

  public GnVideoSeriesEnumerator at(uint index) {
    GnVideoSeriesEnumerator ret = new GnVideoSeriesEnumerator(gnsdk_csharp_marshalPINVOKE.GnVideoSeriesEnumerable_at(swigCPtr, index), true);
    return ret;
  }

  public GnVideoSeriesEnumerator getByIndex(uint index) {
    GnVideoSeriesEnumerator ret = new GnVideoSeriesEnumerator(gnsdk_csharp_marshalPINVOKE.GnVideoSeriesEnumerable_getByIndex(swigCPtr, index), true);
    return ret;
  }

}

}
