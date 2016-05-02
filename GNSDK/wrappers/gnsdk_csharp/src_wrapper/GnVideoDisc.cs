
namespace GracenoteSDK {

using System;
using System.Runtime.InteropServices;

/**
* \class GnVideoDisc
* A video disc can be either DVD (Digital Video Disc) or Blu-ray.
*/
public class GnVideoDisc : GnDataObject {
  private HandleRef swigCPtr;

  internal GnVideoDisc(IntPtr cPtr, bool cMemoryOwn) : base(gnsdk_csharp_marshalPINVOKE.GnVideoDisc_SWIGUpcast(cPtr), cMemoryOwn) {
    swigCPtr = new HandleRef(this, cPtr);
  }

  internal static HandleRef getCPtr(GnVideoDisc obj) {
    return (obj == null) ? new HandleRef(null, IntPtr.Zero) : obj.swigCPtr;
  }

  ~GnVideoDisc() {
    Dispose();
  }

  public override void Dispose() {
    lock(this) {
      if (swigCPtr.Handle != IntPtr.Zero) {
        if (swigCMemOwn) {
          swigCMemOwn = false;
          gnsdk_csharp_marshalPINVOKE.delete_GnVideoDisc(swigCPtr);
        }
        swigCPtr = new HandleRef(null, IntPtr.Zero);
      }
      GC.SuppressFinalize(this);
      base.Dispose();
    }
  }

  public static string GnType() {
    string ret = gnsdk_csharp_marshalPINVOKE.GnVideoDisc_GnType();
    return ret;
  }

  public static GnVideoDisc From(GnDataObject obj) {
    GnVideoDisc ret = new GnVideoDisc(gnsdk_csharp_marshalPINVOKE.GnVideoDisc_From(GnDataObject.getCPtr(obj)), true);
    if (gnsdk_csharp_marshalPINVOKE.SWIGPendingException.Pending) throw gnsdk_csharp_marshalPINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

  public GnVideoDisc(string id, string idTag) : this(gnsdk_csharp_marshalPINVOKE.new_GnVideoDisc(id, idTag), true) {
    if (gnsdk_csharp_marshalPINVOKE.SWIGPendingException.Pending) throw gnsdk_csharp_marshalPINVOKE.SWIGPendingException.Retrieve();
  }

/**
* Gracenote ID
* @ingroup GDO_ValueKeys_GracenoteIDs
*/
  public string GnId {
	get
	{   
		/* csvarout typemap code */
		return GnMarshalUTF8.StringFromNativeUtf8(gnsdk_csharp_marshalPINVOKE.GnVideoDisc_GnId_get(swigCPtr) );
	} 

  }

/**
* Gracenote unique ID
* @ingroup GDO_ValueKeys_GracenoteIDs
*/
  public string GnUId {
	get
	{   
		/* csvarout typemap code */
		return GnMarshalUTF8.StringFromNativeUtf8(gnsdk_csharp_marshalPINVOKE.GnVideoDisc_GnUId_get(swigCPtr) );
	} 

  }

/**
*  Product ID aka Tag ID
* @ingroup GDO_ValueKeys_GracenoteIDs
*/
  public string ProductId {
	get
	{   
		/* csvarout typemap code */
		return GnMarshalUTF8.StringFromNativeUtf8(gnsdk_csharp_marshalPINVOKE.GnVideoDisc_ProductId_get(swigCPtr) );
	} 

  }

/**
*  TUI - title-unique identifier
* @ingroup GDO_ValueKeys_GracenoteIDs
*/
  public string Tui {
	get
	{   
		/* csvarout typemap code */
		return GnMarshalUTF8.StringFromNativeUtf8(gnsdk_csharp_marshalPINVOKE.GnVideoDisc_Tui_get(swigCPtr) );
	} 

  }

/**
* Tui Tag value
* @ingroup GDO_ValueKeys_GracenoteIDs
*/
  public string TuiTag {
	get
	{   
		/* csvarout typemap code */
		return GnMarshalUTF8.StringFromNativeUtf8(gnsdk_csharp_marshalPINVOKE.GnVideoDisc_TuiTag_get(swigCPtr) );
	} 

  }

/**
*  Notes
* @ingroup GDO_ValueKeys_Video
*/
  public string Notes {
	get
	{   
		/* csvarout typemap code */
		return GnMarshalUTF8.StringFromNativeUtf8(gnsdk_csharp_marshalPINVOKE.GnVideoDisc_Notes_get(swigCPtr) );
	} 

  }

/**
*  Ordinal value
* @ingroup GDO_ValueKeys_Misc
*/
  public uint Ordinal {
    get {
      uint ret = gnsdk_csharp_marshalPINVOKE.GnVideoDisc_Ordinal_get(swigCPtr);
      return ret;
    } 
  }

/**
*  Matched boolean value indicating whether this type
*   is the one that matched the input criteria.
* @ingroup GDO_ValueKeys_Misc
*/
  public bool Matched {
    get {
      bool ret = gnsdk_csharp_marshalPINVOKE.GnVideoDisc_Matched_get(swigCPtr);
      return ret;
    } 
  }

/**
*  Official title object
* @ingroup GDO_ChildKeys_Title
*/
  public GnTitle OfficialTitle {
    get {
      IntPtr cPtr = gnsdk_csharp_marshalPINVOKE.GnVideoDisc_OfficialTitle_get(swigCPtr);
      GnTitle ret = (cPtr == IntPtr.Zero) ? null : new GnTitle(cPtr, true);
      return ret;
    } 
  }

  public GnVideoSideEnumerable Sides {
    get {
      IntPtr cPtr = gnsdk_csharp_marshalPINVOKE.GnVideoDisc_Sides_get(swigCPtr);
      GnVideoSideEnumerable ret = (cPtr == IntPtr.Zero) ? null : new GnVideoSideEnumerable(cPtr, true);
      return ret;
    } 
  }

}

}
