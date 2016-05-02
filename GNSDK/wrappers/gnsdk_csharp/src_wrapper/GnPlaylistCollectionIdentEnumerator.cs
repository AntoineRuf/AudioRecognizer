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

public class GnPlaylistCollectionIdentEnumerator : System.Collections.Generic.IEnumerator<GnPlaylistIdentifier>, IDisposable {
  private HandleRef swigCPtr;
  protected bool swigCMemOwn;

  internal GnPlaylistCollectionIdentEnumerator(IntPtr cPtr, bool cMemoryOwn) {
    swigCMemOwn = cMemoryOwn;
    swigCPtr = new HandleRef(this, cPtr);
  }

  internal static HandleRef getCPtr(GnPlaylistCollectionIdentEnumerator obj) {
    return (obj == null) ? new HandleRef(null, IntPtr.Zero) : obj.swigCPtr;
  }

  ~GnPlaylistCollectionIdentEnumerator() {
    Dispose();
  }

  public virtual void Dispose() {
    lock(this) {
      if (swigCPtr.Handle != IntPtr.Zero) {
        if (swigCMemOwn) {
          swigCMemOwn = false;
          gnsdk_csharp_marshalPINVOKE.delete_GnPlaylistCollectionIdentEnumerator(swigCPtr);
        }
        swigCPtr = new HandleRef(null, IntPtr.Zero);
      }
      GC.SuppressFinalize(this);
    }
  }

public bool
MoveNext( )
{
return hasNext( );
}

public GnPlaylistIdentifier Current {
get {
return next( );
}
}
object System.Collections.IEnumerator.Current {
get {
return Current;
}
}
public void
Reset( )
{
}

  public GnPlaylistIdentifier __ref__() {
    GnPlaylistIdentifier ret = new GnPlaylistIdentifier(gnsdk_csharp_marshalPINVOKE.GnPlaylistCollectionIdentEnumerator___ref__(swigCPtr), false);
    if (gnsdk_csharp_marshalPINVOKE.SWIGPendingException.Pending) throw gnsdk_csharp_marshalPINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

  public GnPlaylistIdentifier next() {
    GnPlaylistIdentifier ret = new GnPlaylistIdentifier(gnsdk_csharp_marshalPINVOKE.GnPlaylistCollectionIdentEnumerator_next(swigCPtr), true);
    if (gnsdk_csharp_marshalPINVOKE.SWIGPendingException.Pending) throw gnsdk_csharp_marshalPINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

  public bool hasNext() {
    bool ret = gnsdk_csharp_marshalPINVOKE.GnPlaylistCollectionIdentEnumerator_hasNext(swigCPtr);
    return ret;
  }

  public uint distance(GnPlaylistCollectionIdentEnumerator itr) {
    uint ret = gnsdk_csharp_marshalPINVOKE.GnPlaylistCollectionIdentEnumerator_distance(swigCPtr, GnPlaylistCollectionIdentEnumerator.getCPtr(itr));
    if (gnsdk_csharp_marshalPINVOKE.SWIGPendingException.Pending) throw gnsdk_csharp_marshalPINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

  public GnPlaylistCollectionIdentEnumerator(collection_ident_provider provider, uint pos) : this(gnsdk_csharp_marshalPINVOKE.new_GnPlaylistCollectionIdentEnumerator(collection_ident_provider.getCPtr(provider), pos), true) {
    if (gnsdk_csharp_marshalPINVOKE.SWIGPendingException.Pending) throw gnsdk_csharp_marshalPINVOKE.SWIGPendingException.Retrieve();
  }

}

}
