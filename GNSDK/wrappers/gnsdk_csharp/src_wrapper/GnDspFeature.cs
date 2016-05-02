
namespace GracenoteSDK {

using System;
using System.Runtime.InteropServices;

/**************************************************************************
** GnDspFeature
*/
public class GnDspFeature : GnObject {
  private HandleRef swigCPtr;

  internal GnDspFeature(IntPtr cPtr, bool cMemoryOwn) : base(gnsdk_csharp_marshalPINVOKE.GnDspFeature_SWIGUpcast(cPtr), cMemoryOwn) {
    swigCPtr = new HandleRef(this, cPtr);
  }

  internal static HandleRef getCPtr(GnDspFeature obj) {
    return (obj == null) ? new HandleRef(null, IntPtr.Zero) : obj.swigCPtr;
  }

  ~GnDspFeature() {
    Dispose();
  }

  public override void Dispose() {
    lock(this) {
      if (swigCPtr.Handle != IntPtr.Zero) {
        if (swigCMemOwn) {
          swigCMemOwn = false;
          gnsdk_csharp_marshalPINVOKE.delete_GnDspFeature(swigCPtr);
        }
        swigCPtr = new HandleRef(null, IntPtr.Zero);
      }
      GC.SuppressFinalize(this);
      base.Dispose();
    }
  }

  public string FeatureData() {
    string ret = gnsdk_csharp_marshalPINVOKE.GnDspFeature_FeatureData(swigCPtr);
    return ret;
  }

  public GnDspFeatureQuality FeatureQuality() {
    GnDspFeatureQuality ret = (GnDspFeatureQuality)gnsdk_csharp_marshalPINVOKE.GnDspFeature_FeatureQuality(swigCPtr);
    return ret;
  }

}

}
