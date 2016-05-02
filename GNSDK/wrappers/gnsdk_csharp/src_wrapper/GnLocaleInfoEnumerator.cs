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

public class GnLocaleInfoEnumerator : System.Collections.Generic.IEnumerator<GnLocaleInfo >, IDisposable {
  private HandleRef swigCPtr;
  protected bool swigCMemOwn;

  internal GnLocaleInfoEnumerator(IntPtr cPtr, bool cMemoryOwn) {
    swigCMemOwn = cMemoryOwn;
    swigCPtr = new HandleRef(this, cPtr);
  }

  internal static HandleRef getCPtr(GnLocaleInfoEnumerator obj) {
    return (obj == null) ? new HandleRef(null, IntPtr.Zero) : obj.swigCPtr;
  }

  ~GnLocaleInfoEnumerator() {
    Dispose();
  }

  public virtual void Dispose() {
    lock(this) {
      if (swigCPtr.Handle != IntPtr.Zero) {
        if (swigCMemOwn) {
          swigCMemOwn = false;
          gnsdk_csharp_marshalPINVOKE.delete_GnLocaleInfoEnumerator(swigCPtr);
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

public GnLocaleInfo Current {
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

  public GnLocaleInfo next() {
    GnLocaleInfo ret = new GnLocaleInfo(gnsdk_csharp_marshalPINVOKE.GnLocaleInfoEnumerator_next(swigCPtr), true);
    if (gnsdk_csharp_marshalPINVOKE.SWIGPendingException.Pending) throw gnsdk_csharp_marshalPINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

  public bool hasNext() {
    bool ret = gnsdk_csharp_marshalPINVOKE.GnLocaleInfoEnumerator_hasNext(swigCPtr);
    return ret;
  }

  public uint distance(GnLocaleInfoEnumerator itr) {
    uint ret = gnsdk_csharp_marshalPINVOKE.GnLocaleInfoEnumerator_distance(swigCPtr, GnLocaleInfoEnumerator.getCPtr(itr));
    if (gnsdk_csharp_marshalPINVOKE.SWIGPendingException.Pending) throw gnsdk_csharp_marshalPINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

  public GnLocaleInfoEnumerator(locale_info_provider provider, uint pos) : this(gnsdk_csharp_marshalPINVOKE.new_GnLocaleInfoEnumerator(locale_info_provider.getCPtr(provider), pos), true) {
    if (gnsdk_csharp_marshalPINVOKE.SWIGPendingException.Pending) throw gnsdk_csharp_marshalPINVOKE.SWIGPendingException.Retrieve();
  }

}

}
