
namespace GracenoteSDK {

using System;
using System.Runtime.InteropServices;

/**
* <b>Experimental</b>: Provides access to information regarding the underlying
* GNSDK playlist library. For working with user collections to create playlists
* see GnPlaylistCollection.
*/
public class GnPlaylist : IDisposable {
  private HandleRef swigCPtr;
  protected bool swigCMemOwn;

  internal GnPlaylist(IntPtr cPtr, bool cMemoryOwn) {
    swigCMemOwn = cMemoryOwn;
    swigCPtr = new HandleRef(this, cPtr);
  }

  internal static HandleRef getCPtr(GnPlaylist obj) {
    return (obj == null) ? new HandleRef(null, IntPtr.Zero) : obj.swigCPtr;
  }

  ~GnPlaylist() {
    Dispose();
  }

  public virtual void Dispose() {
    lock(this) {
      if (swigCPtr.Handle != IntPtr.Zero) {
        if (swigCMemOwn) {
          swigCMemOwn = false;
          gnsdk_csharp_marshalPINVOKE.delete_GnPlaylist(swigCPtr);
        }
        swigCPtr = new HandleRef(null, IntPtr.Zero);
      }
      GC.SuppressFinalize(this);
    }
  }

  public GnPlaylist() : this(gnsdk_csharp_marshalPINVOKE.new_GnPlaylist(), true) {
    if (gnsdk_csharp_marshalPINVOKE.SWIGPendingException.Pending) throw gnsdk_csharp_marshalPINVOKE.SWIGPendingException.Retrieve();
  }

/** @internal Version @endinternal
*  Retrieves the Playlist SDK version string.
*  @return version string if successful
*  @return GNSDK_NULL if not successful
*  <p><b>Remarks:</b></p>
*  This API can be called at any time, after getting instance of GnManager successfully. The returned
*   string is a constant. Do not attempt to modify or delete.
*  Example version string: 1.2.3.123 (Major.Minor.Improvement.Build)
*  Major: New functionality
*  Minor: New or changed features
*  Improvement: Improvements and fixes
*  Build: Internal build number
* @ingroup Music_Playlist_InitializationFunctions
*/
  public string Version {
	get
	{   
		/* csvarout typemap code */
		return GnMarshalUTF8.StringFromNativeUtf8(gnsdk_csharp_marshalPINVOKE.GnPlaylist_Version_get(swigCPtr) );
	} 

  }

/** @internal BuildDate @endinternal
*  Retrieves the Playlist SDK's build date string.
*  @return Note Build date string of the format: YYYY-MM-DD hh:mm UTC
*  <p><b>Remarks:</b></p>
*  This API can be called at any time, after getting instance of GnManager successfully. The returned
*   string is a constant. Do not attempt to modify or delete.
*  Example build date string: 2008-02-12 00:41 UTC
* @ingroup Music_Playlist_InitializationFunctions
*/
  public string BuildDate {
	get
	{   
		/* csvarout typemap code */
		return GnMarshalUTF8.StringFromNativeUtf8(gnsdk_csharp_marshalPINVOKE.GnPlaylist_BuildDate_get(swigCPtr) );
	} 

  }

  public GnPlaylistAttributeEnumerable AttributesSupported {
    get {
      IntPtr cPtr = gnsdk_csharp_marshalPINVOKE.GnPlaylist_AttributesSupported_get(swigCPtr);
      GnPlaylistAttributeEnumerable ret = (cPtr == IntPtr.Zero) ? null : new GnPlaylistAttributeEnumerable(cPtr, true);
      return ret;
    } 
  }

}

}
