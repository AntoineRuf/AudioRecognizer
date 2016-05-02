
namespace GracenoteSDK {

using System;
using System.Runtime.InteropServices;

/**
** <b>Experimental</b>: GnMoodgridIdentifier
*/
public class GnMoodgridIdentifier : IDisposable {
  private HandleRef swigCPtr;
  protected bool swigCMemOwn;

  internal GnMoodgridIdentifier(IntPtr cPtr, bool cMemoryOwn) {
    swigCMemOwn = cMemoryOwn;
    swigCPtr = new HandleRef(this, cPtr);
  }

  internal static HandleRef getCPtr(GnMoodgridIdentifier obj) {
    return (obj == null) ? new HandleRef(null, IntPtr.Zero) : obj.swigCPtr;
  }

  ~GnMoodgridIdentifier() {
    Dispose();
  }

  public virtual void Dispose() {
    lock(this) {
      if (swigCPtr.Handle != IntPtr.Zero) {
        if (swigCMemOwn) {
          swigCMemOwn = false;
          gnsdk_csharp_marshalPINVOKE.delete_GnMoodgridIdentifier(swigCPtr);
        }
        swigCPtr = new HandleRef(null, IntPtr.Zero);
      }
      GC.SuppressFinalize(this);
    }
  }

/**
* Retrieves a read only string that is the media identifier.
*/
  public string MediaIdentifier {
	get
	{   
		/* csvarout typemap code */
		return GnMarshalUTF8.StringFromNativeUtf8(gnsdk_csharp_marshalPINVOKE.GnMoodgridIdentifier_MediaIdentifier_get(swigCPtr) );
	} 

  }

/**
* Retrieves a read only string that is the group the MediaIdentifier belongs too.
*  E.g. in the case of a Playlist provider , the group represents the name of the collection.
*/
  public string Group {
	get
	{   
		/* csvarout typemap code */
		return GnMarshalUTF8.StringFromNativeUtf8(gnsdk_csharp_marshalPINVOKE.GnMoodgridIdentifier_Group_get(swigCPtr) );
	} 

  }

}

}
