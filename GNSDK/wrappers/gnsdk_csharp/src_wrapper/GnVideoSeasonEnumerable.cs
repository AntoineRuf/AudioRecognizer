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

public class GnVideoSeasonEnumerable : System.Collections.Generic.IEnumerable<GnVideoSeason>, IDisposable {
  private HandleRef swigCPtr;
  protected bool swigCMemOwn;

  internal GnVideoSeasonEnumerable(IntPtr cPtr, bool cMemoryOwn) {
    swigCMemOwn = cMemoryOwn;
    swigCPtr = new HandleRef(this, cPtr);
  }

  internal static HandleRef getCPtr(GnVideoSeasonEnumerable obj) {
    return (obj == null) ? new HandleRef(null, IntPtr.Zero) : obj.swigCPtr;
  }

  ~GnVideoSeasonEnumerable() {
    Dispose();
  }

  public virtual void Dispose() {
    lock(this) {
      if (swigCPtr.Handle != IntPtr.Zero) {
        if (swigCMemOwn) {
          swigCMemOwn = false;
          gnsdk_csharp_marshalPINVOKE.delete_GnVideoSeasonEnumerable(swigCPtr);
        }
        swigCPtr = new HandleRef(null, IntPtr.Zero);
      }
      GC.SuppressFinalize(this);
    }
  }

			System.Collections.Generic.IEnumerator<GnVideoSeason> System.Collections.Generic.IEnumerable<GnVideoSeason> .GetEnumerator( )
			{
				return GetEnumerator( );
			}
			System.Collections.IEnumerator System.Collections.IEnumerable.
			    GetEnumerator( )
			{
				return GetEnumerator( );
			}

		
  public GnVideoSeasonEnumerable(GnVideoSeasonProvider provider, uint start) : this(gnsdk_csharp_marshalPINVOKE.new_GnVideoSeasonEnumerable(GnVideoSeasonProvider.getCPtr(provider), start), true) {
    if (gnsdk_csharp_marshalPINVOKE.SWIGPendingException.Pending) throw gnsdk_csharp_marshalPINVOKE.SWIGPendingException.Retrieve();
  }

  public GnVideoSeasonEnumerator GetEnumerator() {
    GnVideoSeasonEnumerator ret = new GnVideoSeasonEnumerator(gnsdk_csharp_marshalPINVOKE.GnVideoSeasonEnumerable_GetEnumerator(swigCPtr), true);
    return ret;
  }

  public GnVideoSeasonEnumerator end() {
    GnVideoSeasonEnumerator ret = new GnVideoSeasonEnumerator(gnsdk_csharp_marshalPINVOKE.GnVideoSeasonEnumerable_end(swigCPtr), true);
    return ret;
  }

  public uint count() {
    uint ret = gnsdk_csharp_marshalPINVOKE.GnVideoSeasonEnumerable_count(swigCPtr);
    return ret;
  }

  public GnVideoSeasonEnumerator at(uint index) {
    GnVideoSeasonEnumerator ret = new GnVideoSeasonEnumerator(gnsdk_csharp_marshalPINVOKE.GnVideoSeasonEnumerable_at(swigCPtr, index), true);
    return ret;
  }

  public GnVideoSeasonEnumerator getByIndex(uint index) {
    GnVideoSeasonEnumerator ret = new GnVideoSeasonEnumerator(gnsdk_csharp_marshalPINVOKE.GnVideoSeasonEnumerable_getByIndex(swigCPtr, index), true);
    return ret;
  }

}

}