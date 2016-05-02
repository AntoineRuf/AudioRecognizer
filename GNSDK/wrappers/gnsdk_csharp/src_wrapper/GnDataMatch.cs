
namespace GracenoteSDK {

using System;
using System.Runtime.InteropServices;

/**
*  Represents a match to query where any type of match is desired, album or contributor.
*/
public class GnDataMatch : GnDataObject {
  private HandleRef swigCPtr;

  internal GnDataMatch(IntPtr cPtr, bool cMemoryOwn) : base(gnsdk_csharp_marshalPINVOKE.GnDataMatch_SWIGUpcast(cPtr), cMemoryOwn) {
    swigCPtr = new HandleRef(this, cPtr);
  }

  internal static HandleRef getCPtr(GnDataMatch obj) {
    return (obj == null) ? new HandleRef(null, IntPtr.Zero) : obj.swigCPtr;
  }

  ~GnDataMatch() {
    Dispose();
  }

  public override void Dispose() {
    lock(this) {
      if (swigCPtr.Handle != IntPtr.Zero) {
        if (swigCMemOwn) {
          swigCMemOwn = false;
          gnsdk_csharp_marshalPINVOKE.delete_GnDataMatch(swigCPtr);
        }
        swigCPtr = new HandleRef(null, IntPtr.Zero);
      }
      GC.SuppressFinalize(this);
      base.Dispose();
    }
  }

/**
*  Flag indicating if match is album
*  @return True if album is a match, false otherwise
*/
  public bool IsAlbum() {
    bool ret = gnsdk_csharp_marshalPINVOKE.GnDataMatch_IsAlbum(swigCPtr);
    return ret;
  }

/**
*  Flag indicating if match is contributor
*  @return True if result is a contributor, false otherwise
*/
  public bool IsContributor() {
    bool ret = gnsdk_csharp_marshalPINVOKE.GnDataMatch_IsContributor(swigCPtr);
    return ret;
  }

/**
*  If album, get match as album object
*  @return Album
*/
  public GnAlbum GetAsAlbum() {
    GnAlbum ret = new GnAlbum(gnsdk_csharp_marshalPINVOKE.GnDataMatch_GetAsAlbum(swigCPtr), true);
    return ret;
  }

/**
*  If contributor, get match as contributor object
*  @return Contributor
*/
  public GnContributor GetAsContributor() {
    GnContributor ret = new GnContributor(gnsdk_csharp_marshalPINVOKE.GnDataMatch_GetAsContributor(swigCPtr), true);
    return ret;
  }

}

}
