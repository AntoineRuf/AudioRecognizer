
namespace GracenoteSDK {

using System;
using System.Runtime.InteropServices;

/**
* Person or group primarily responsible for creating the Album or Track.
*/
public class GnArtist : GnDataObject {
  private HandleRef swigCPtr;

  internal GnArtist(IntPtr cPtr, bool cMemoryOwn) : base(gnsdk_csharp_marshalPINVOKE.GnArtist_SWIGUpcast(cPtr), cMemoryOwn) {
    swigCPtr = new HandleRef(this, cPtr);
  }

  internal static HandleRef getCPtr(GnArtist obj) {
    return (obj == null) ? new HandleRef(null, IntPtr.Zero) : obj.swigCPtr;
  }

  ~GnArtist() {
    Dispose();
  }

  public override void Dispose() {
    lock(this) {
      if (swigCPtr.Handle != IntPtr.Zero) {
        if (swigCMemOwn) {
          swigCMemOwn = false;
          gnsdk_csharp_marshalPINVOKE.delete_GnArtist(swigCPtr);
        }
        swigCPtr = new HandleRef(null, IntPtr.Zero);
      }
      GC.SuppressFinalize(this);
      base.Dispose();
    }
  }

  public static string GnType() {
    string ret = gnsdk_csharp_marshalPINVOKE.GnArtist_GnType();
    return ret;
  }

  public static GnArtist From(GnDataObject obj) {
    GnArtist ret = new GnArtist(gnsdk_csharp_marshalPINVOKE.GnArtist_From(GnDataObject.getCPtr(obj)), true);
    if (gnsdk_csharp_marshalPINVOKE.SWIGPendingException.Pending) throw gnsdk_csharp_marshalPINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

/**
* Artist's official name.
* @return Name
*/
  public GnName Name {
    get {
      IntPtr cPtr = gnsdk_csharp_marshalPINVOKE.GnArtist_Name_get(swigCPtr);
      GnName ret = (cPtr == IntPtr.Zero) ? null : new GnName(cPtr, true);
      return ret;
    } 
  }

/**
* Contributor object - contributor associated with the work
* @return Contributor
*/
  public GnContributor Contributor {
    get {
      IntPtr cPtr = gnsdk_csharp_marshalPINVOKE.GnArtist_Contributor_get(swigCPtr);
      GnContributor ret = (cPtr == IntPtr.Zero) ? null : new GnContributor(cPtr, true);
      return ret;
    } 
  }

}

}
