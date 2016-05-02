
namespace GracenoteSDK {

using System;
using System.Runtime.InteropServices;

/**
** GnMoodgridDataPoint
*/
public class GnMoodgridDataPoint : IDisposable {
  private HandleRef swigCPtr;
  protected bool swigCMemOwn;

  internal GnMoodgridDataPoint(IntPtr cPtr, bool cMemoryOwn) {
    swigCMemOwn = cMemoryOwn;
    swigCPtr = new HandleRef(this, cPtr);
  }

  internal static HandleRef getCPtr(GnMoodgridDataPoint obj) {
    return (obj == null) ? new HandleRef(null, IntPtr.Zero) : obj.swigCPtr;
  }

  ~GnMoodgridDataPoint() {
    Dispose();
  }

  public virtual void Dispose() {
    lock(this) {
      if (swigCPtr.Handle != IntPtr.Zero) {
        if (swigCMemOwn) {
          swigCMemOwn = false;
          gnsdk_csharp_marshalPINVOKE.delete_GnMoodgridDataPoint(swigCPtr);
        }
        swigCPtr = new HandleRef(null, IntPtr.Zero);
      }
      GC.SuppressFinalize(this);
    }
  }

  public GnMoodgridDataPoint() : this(gnsdk_csharp_marshalPINVOKE.new_GnMoodgridDataPoint__SWIG_0(), true) {
  }

  public GnMoodgridDataPoint(uint x, uint y) : this(gnsdk_csharp_marshalPINVOKE.new_GnMoodgridDataPoint__SWIG_1(x, y), true) {
  }

  public uint X {
    set {
      gnsdk_csharp_marshalPINVOKE.GnMoodgridDataPoint_X_set(swigCPtr, value);
    } 
    get {
      uint ret = gnsdk_csharp_marshalPINVOKE.GnMoodgridDataPoint_X_get(swigCPtr);
      return ret;
    } 
  }

  public uint Y {
    set {
      gnsdk_csharp_marshalPINVOKE.GnMoodgridDataPoint_Y_set(swigCPtr, value);
    } 
    get {
      uint ret = gnsdk_csharp_marshalPINVOKE.GnMoodgridDataPoint_Y_get(swigCPtr);
      return ret;
    } 
  }

}

}
