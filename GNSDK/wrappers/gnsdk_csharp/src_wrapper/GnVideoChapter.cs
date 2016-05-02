
namespace GracenoteSDK {

using System;
using System.Runtime.InteropServices;

/**
* \class GnVideoChapter
*/
public class GnVideoChapter : GnDataObject {
  private HandleRef swigCPtr;

  internal GnVideoChapter(IntPtr cPtr, bool cMemoryOwn) : base(gnsdk_csharp_marshalPINVOKE.GnVideoChapter_SWIGUpcast(cPtr), cMemoryOwn) {
    swigCPtr = new HandleRef(this, cPtr);
  }

  internal static HandleRef getCPtr(GnVideoChapter obj) {
    return (obj == null) ? new HandleRef(null, IntPtr.Zero) : obj.swigCPtr;
  }

  ~GnVideoChapter() {
    Dispose();
  }

  public override void Dispose() {
    lock(this) {
      if (swigCPtr.Handle != IntPtr.Zero) {
        if (swigCMemOwn) {
          swigCMemOwn = false;
          gnsdk_csharp_marshalPINVOKE.delete_GnVideoChapter(swigCPtr);
        }
        swigCPtr = new HandleRef(null, IntPtr.Zero);
      }
      GC.SuppressFinalize(this);
      base.Dispose();
    }
  }

  public static string GnType() {
    string ret = gnsdk_csharp_marshalPINVOKE.GnVideoChapter_GnType();
    return ret;
  }

  public static GnVideoChapter From(GnDataObject obj) {
    GnVideoChapter ret = new GnVideoChapter(gnsdk_csharp_marshalPINVOKE.GnVideoChapter_From(GnDataObject.getCPtr(obj)), true);
    if (gnsdk_csharp_marshalPINVOKE.SWIGPendingException.Pending) throw gnsdk_csharp_marshalPINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

/**
* Video chapter's ordinal value.
* @ingroup GDO_ValueKeys_Misc
*/
  public uint Ordinal {
    get {
      uint ret = gnsdk_csharp_marshalPINVOKE.GnVideoChapter_Ordinal_get(swigCPtr);
      return ret;
    } 
  }

/**
*  Chapter's duration value in seconds such as "3600" for a 60-minute program.
* @ingroup GDO_ValueKeys_Video
*/
  public uint Duration {
    get {
      uint ret = gnsdk_csharp_marshalPINVOKE.GnVideoChapter_Duration_get(swigCPtr);
      return ret;
    } 
  }

/**
*  Chapter's duration units value (seconds, "SEC").
* @ingroup GDO_ValueKeys_Video
*/
  public string DurationUnits {
	get
	{   
		/* csvarout typemap code */
		return GnMarshalUTF8.StringFromNativeUtf8(gnsdk_csharp_marshalPINVOKE.GnVideoChapter_DurationUnits_get(swigCPtr) );
	} 

  }

/**
*  Official Title object.
* @ingroup GDO_ChildKeys_Title
*/
  public GnTitle OfficialTitle {
    get {
      IntPtr cPtr = gnsdk_csharp_marshalPINVOKE.GnVideoChapter_OfficialTitle_get(swigCPtr);
      GnTitle ret = (cPtr == IntPtr.Zero) ? null : new GnTitle(cPtr, true);
      return ret;
    } 
  }

  public GnVideoCreditEnumerable VideoCredits {
    get {
      IntPtr cPtr = gnsdk_csharp_marshalPINVOKE.GnVideoChapter_VideoCredits_get(swigCPtr);
      GnVideoCreditEnumerable ret = (cPtr == IntPtr.Zero) ? null : new GnVideoCreditEnumerable(cPtr, true);
      return ret;
    } 
  }

}

}
