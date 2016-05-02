
namespace GracenoteSDK {

using System;
using System.Runtime.InteropServices;

public class musicid_file_info_provider : IDisposable {
  private HandleRef swigCPtr;
  protected bool swigCMemOwn;

  internal musicid_file_info_provider(IntPtr cPtr, bool cMemoryOwn) {
    swigCMemOwn = cMemoryOwn;
    swigCPtr = new HandleRef(this, cPtr);
  }

  internal static HandleRef getCPtr(musicid_file_info_provider obj) {
    return (obj == null) ? new HandleRef(null, IntPtr.Zero) : obj.swigCPtr;
  }

  ~musicid_file_info_provider() {
    Dispose();
  }

  public virtual void Dispose() {
    lock(this) {
      if (swigCPtr.Handle != IntPtr.Zero) {
        if (swigCMemOwn) {
          swigCMemOwn = false;
          gnsdk_csharp_marshalPINVOKE.delete_musicid_file_info_provider(swigCPtr);
        }
        swigCPtr = new HandleRef(null, IntPtr.Zero);
      }
      GC.SuppressFinalize(this);
    }
  }

/** 
*@internal
*  Gets the GnMusicIdFileInfo object at the requested position
*  @param pos				[in] the index of obect to retrieve
*@endinternal 
*/
  public GnMusicIdFileInfo get_data(uint pos) {
    GnMusicIdFileInfo ret = new GnMusicIdFileInfo(gnsdk_csharp_marshalPINVOKE.musicid_file_info_provider_get_data(swigCPtr, pos), true);
    return ret;
  }

/** 
*@internal
*  Gets the number of GnMusicIdFileInfo objects available
*@endinternal 
*/
  public uint count() {
    uint ret = gnsdk_csharp_marshalPINVOKE.musicid_file_info_provider_count(swigCPtr);
    return ret;
  }

}

}
