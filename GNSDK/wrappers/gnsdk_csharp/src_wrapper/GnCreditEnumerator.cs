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

public class GnCreditEnumerator : System.Collections.Generic.IEnumerator<GnCredit>, IDisposable {
  private HandleRef swigCPtr;
  protected bool swigCMemOwn;

  internal GnCreditEnumerator(IntPtr cPtr, bool cMemoryOwn) {
    swigCMemOwn = cMemoryOwn;
    swigCPtr = new HandleRef(this, cPtr);
  }

  internal static HandleRef getCPtr(GnCreditEnumerator obj) {
    return (obj == null) ? new HandleRef(null, IntPtr.Zero) : obj.swigCPtr;
  }

  ~GnCreditEnumerator() {
    Dispose();
  }

  public virtual void Dispose() {
    lock(this) {
      if (swigCPtr.Handle != IntPtr.Zero) {
        if (swigCMemOwn) {
          swigCMemOwn = false;
          gnsdk_csharp_marshalPINVOKE.delete_GnCreditEnumerator(swigCPtr);
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

			public GnCredit Current {
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

		
  public GnCredit __ref__() {
    GnCredit ret = new GnCredit(gnsdk_csharp_marshalPINVOKE.GnCreditEnumerator___ref__(swigCPtr), false);
    if (gnsdk_csharp_marshalPINVOKE.SWIGPendingException.Pending) throw gnsdk_csharp_marshalPINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

  public GnCredit next() {
    GnCredit ret = new GnCredit(gnsdk_csharp_marshalPINVOKE.GnCreditEnumerator_next(swigCPtr), true);
    if (gnsdk_csharp_marshalPINVOKE.SWIGPendingException.Pending) throw gnsdk_csharp_marshalPINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

  public bool hasNext() {
    bool ret = gnsdk_csharp_marshalPINVOKE.GnCreditEnumerator_hasNext(swigCPtr);
    return ret;
  }

  public uint distance(GnCreditEnumerator itr) {
    uint ret = gnsdk_csharp_marshalPINVOKE.GnCreditEnumerator_distance(swigCPtr, GnCreditEnumerator.getCPtr(itr));
    if (gnsdk_csharp_marshalPINVOKE.SWIGPendingException.Pending) throw gnsdk_csharp_marshalPINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

  public GnCreditEnumerator(GnCreditProvider provider, uint pos) : this(gnsdk_csharp_marshalPINVOKE.new_GnCreditEnumerator(GnCreditProvider.getCPtr(provider), pos), true) {
    if (gnsdk_csharp_marshalPINVOKE.SWIGPendingException.Pending) throw gnsdk_csharp_marshalPINVOKE.SWIGPendingException.Retrieve();
  }

}

}
