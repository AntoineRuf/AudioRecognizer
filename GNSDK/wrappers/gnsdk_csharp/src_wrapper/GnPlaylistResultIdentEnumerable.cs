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

public class GnPlaylistResultIdentEnumerable : System.Collections.Generic.IEnumerable<GnPlaylistIdentifier >, IDisposable {
  private HandleRef swigCPtr;
  protected bool swigCMemOwn;

  internal GnPlaylistResultIdentEnumerable(IntPtr cPtr, bool cMemoryOwn) {
    swigCMemOwn = cMemoryOwn;
    swigCPtr = new HandleRef(this, cPtr);
  }

  internal static HandleRef getCPtr(GnPlaylistResultIdentEnumerable obj) {
    return (obj == null) ? new HandleRef(null, IntPtr.Zero) : obj.swigCPtr;
  }

  ~GnPlaylistResultIdentEnumerable() {
    Dispose();
  }

  public virtual void Dispose() {
    lock(this) {
      if (swigCPtr.Handle != IntPtr.Zero) {
        if (swigCMemOwn) {
          swigCMemOwn = false;
          gnsdk_csharp_marshalPINVOKE.delete_GnPlaylistResultIdentEnumerable(swigCPtr);
        }
        swigCPtr = new HandleRef(null, IntPtr.Zero);
      }
      GC.SuppressFinalize(this);
    }
  }

System.Collections.Generic.IEnumerator<GnPlaylistIdentifier> System.Collections.Generic.IEnumerable<GnPlaylistIdentifier>.GetEnumerator( )
{
	return GetEnumerator( );
}
System.Collections.IEnumerator System.Collections.IEnumerable.GetEnumerator( )
{
	return GetEnumerator( );
}

  public GnPlaylistResultIdentEnumerable(result_provider provider, uint start) : this(gnsdk_csharp_marshalPINVOKE.new_GnPlaylistResultIdentEnumerable(result_provider.getCPtr(provider), start), true) {
    if (gnsdk_csharp_marshalPINVOKE.SWIGPendingException.Pending) throw gnsdk_csharp_marshalPINVOKE.SWIGPendingException.Retrieve();
  }

  public GnPlaylistResultIdentEnumerator GetEnumerator() {
    GnPlaylistResultIdentEnumerator ret = new GnPlaylistResultIdentEnumerator(gnsdk_csharp_marshalPINVOKE.GnPlaylistResultIdentEnumerable_GetEnumerator(swigCPtr), true);
    return ret;
  }

  public GnPlaylistResultIdentEnumerator end() {
    GnPlaylistResultIdentEnumerator ret = new GnPlaylistResultIdentEnumerator(gnsdk_csharp_marshalPINVOKE.GnPlaylistResultIdentEnumerable_end(swigCPtr), true);
    return ret;
  }

  public uint count() {
    uint ret = gnsdk_csharp_marshalPINVOKE.GnPlaylistResultIdentEnumerable_count(swigCPtr);
    return ret;
  }

  public GnPlaylistResultIdentEnumerator at(uint index) {
    GnPlaylistResultIdentEnumerator ret = new GnPlaylistResultIdentEnumerator(gnsdk_csharp_marshalPINVOKE.GnPlaylistResultIdentEnumerable_at(swigCPtr, index), true);
    return ret;
  }

  public GnPlaylistResultIdentEnumerator getByIndex(uint index) {
    GnPlaylistResultIdentEnumerator ret = new GnPlaylistResultIdentEnumerator(gnsdk_csharp_marshalPINVOKE.GnPlaylistResultIdentEnumerable_getByIndex(swigCPtr, index), true);
    return ret;
  }

}

}
