
namespace GracenoteSDK {

using System;
using System.Runtime.InteropServices;

/**
* <b>Experimental</b>: GnPlaylistIdentifier
*/
public class GnPlaylistIdentifier : IDisposable {
  private HandleRef swigCPtr;
  protected bool swigCMemOwn;

  internal GnPlaylistIdentifier(IntPtr cPtr, bool cMemoryOwn) {
    swigCMemOwn = cMemoryOwn;
    swigCPtr = new HandleRef(this, cPtr);
  }

  internal static HandleRef getCPtr(GnPlaylistIdentifier obj) {
    return (obj == null) ? new HandleRef(null, IntPtr.Zero) : obj.swigCPtr;
  }

  ~GnPlaylistIdentifier() {
    Dispose();
  }

  public virtual void Dispose() {
    lock(this) {
      if (swigCPtr.Handle != IntPtr.Zero) {
        if (swigCMemOwn) {
          swigCMemOwn = false;
          gnsdk_csharp_marshalPINVOKE.delete_GnPlaylistIdentifier(swigCPtr);
        }
        swigCPtr = new HandleRef(null, IntPtr.Zero);
      }
      GC.SuppressFinalize(this);
    }
  }

  public string MediaIdentifier {
	get
	{   
		/* csvarout typemap code */
		return GnMarshalUTF8.StringFromNativeUtf8(gnsdk_csharp_marshalPINVOKE.GnPlaylistIdentifier_MediaIdentifier_get(swigCPtr) );
	} 

  }

  public string CollectionName {
	get
	{   
		/* csvarout typemap code */
		return GnMarshalUTF8.StringFromNativeUtf8(gnsdk_csharp_marshalPINVOKE.GnPlaylistIdentifier_CollectionName_get(swigCPtr) );
	} 

  }

}

}
