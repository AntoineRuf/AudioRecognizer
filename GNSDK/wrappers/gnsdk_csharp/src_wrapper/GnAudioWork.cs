
namespace GracenoteSDK {

using System;
using System.Runtime.InteropServices;

/**
* \class GnAudioWork
* A collection of classical music recordings.
*/
public class GnAudioWork : GnDataObject {
  private HandleRef swigCPtr;

  internal GnAudioWork(IntPtr cPtr, bool cMemoryOwn) : base(gnsdk_csharp_marshalPINVOKE.GnAudioWork_SWIGUpcast(cPtr), cMemoryOwn) {
    swigCPtr = new HandleRef(this, cPtr);
  }

  internal static HandleRef getCPtr(GnAudioWork obj) {
    return (obj == null) ? new HandleRef(null, IntPtr.Zero) : obj.swigCPtr;
  }

  ~GnAudioWork() {
    Dispose();
  }

  public override void Dispose() {
    lock(this) {
      if (swigCPtr.Handle != IntPtr.Zero) {
        if (swigCMemOwn) {
          swigCMemOwn = false;
          gnsdk_csharp_marshalPINVOKE.delete_GnAudioWork(swigCPtr);
        }
        swigCPtr = new HandleRef(null, IntPtr.Zero);
      }
      GC.SuppressFinalize(this);
      base.Dispose();
    }
  }

  public static string GnType() {
    string ret = gnsdk_csharp_marshalPINVOKE.GnAudioWork_GnType();
    return ret;
  }

  public static GnAudioWork From(GnDataObject obj) {
    GnAudioWork ret = new GnAudioWork(gnsdk_csharp_marshalPINVOKE.GnAudioWork_From(GnDataObject.getCPtr(obj)), true);
    if (gnsdk_csharp_marshalPINVOKE.SWIGPendingException.Pending) throw gnsdk_csharp_marshalPINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

/**
* Audio work's product ID (aka Tag ID).
* <p><b>Remarks:</b></p>
* Available for most types, this value can be stored or transmitted. Can
* be used as a static identifier for the current content as it will not change over time.
* @ingroup GDO_ValueKeys_GracenoteIDs
*/
  public string ProductId() {
	IntPtr temp = gnsdk_csharp_marshalPINVOKE.GnAudioWork_ProductId(swigCPtr); 
	return GnMarshalUTF8.StringFromNativeUtf8(temp);
}

/**
* Audio work's geographic location, e.g., New York City. List/locale dependent multi-leveled field.
* @param level	[in] Data level
* @return Origin
* <p><b>Remarks:</b></p>
* This is a list-based value requiring that a corresponding locale or list be loaded.
*/
  public string Origin(GnDataLevel level) {
    string ret = gnsdk_csharp_marshalPINVOKE.GnAudioWork_Origin(swigCPtr, (int)level);
    return ret;
  }

/**
* Audio work's era. List/locale dependent, multi-leveled field.
* @param level	[in] Data level
* @return Era
* <p><b>Remarks:</b></p>
* This is a list-based value requiring that a corresponding locale or list be loaded.
*/
  public string Era(GnDataLevel level) {
    string ret = gnsdk_csharp_marshalPINVOKE.GnAudioWork_Era(swigCPtr, (int)level);
    return ret;
  }

/**
* Audio work's genre, e.g. punk rock, rock opera, etc. List/locale dependent, multi-level field.
* @param level	[in] Data level
* @return Genre
* <p><b>Remarks:</b></p>
* This is a list-based value requiring that a corresponding locale or list be loaded.
*/
  public string Genre(GnDataLevel level) {
    string ret = gnsdk_csharp_marshalPINVOKE.GnAudioWork_Genre(swigCPtr, (int)level);
    return ret;
  }

/**
* Audio work's official title.
* @return Title
*/
  public GnTitle Title {
    get {
      IntPtr cPtr = gnsdk_csharp_marshalPINVOKE.GnAudioWork_Title_get(swigCPtr);
      GnTitle ret = (cPtr == IntPtr.Zero) ? null : new GnTitle(cPtr, true);
      return ret;
    } 
  }

/**
* Credit object for this audio work.
* @return Credit
*/
  public GnCredit Credit {
    get {
      IntPtr cPtr = gnsdk_csharp_marshalPINVOKE.GnAudioWork_Credit_get(swigCPtr);
      GnCredit ret = (cPtr == IntPtr.Zero) ? null : new GnCredit(cPtr, true);
      return ret;
    } 
  }

/**
* Gracenote Tui (title unique identifier) for this audio work.
* @return Tui
*/
  public string Tui {
	get
	{   
		/* csvarout typemap code */
		return GnMarshalUTF8.StringFromNativeUtf8(gnsdk_csharp_marshalPINVOKE.GnAudioWork_Tui_get(swigCPtr) );
	} 

  }

/**
* Gracenote Tui Tag for this audio work.
* @return Tui Tag
*/
  public string TuiTag {
	get
	{   
		/* csvarout typemap code */
		return GnMarshalUTF8.StringFromNativeUtf8(gnsdk_csharp_marshalPINVOKE.GnAudioWork_TuiTag_get(swigCPtr) );
	} 

  }

/**
* Gracenote Tag identifier for this audio work (Tag ID is same as Product ID)
* @return Tag identifier
* <p><b>Remarks:</b></p>
* This method exists primarily to support legacy implementations. We recommend using
* the Product ID method to retrieve product related identifiers
*/
  public string TagId {
	get
	{   
		/* csvarout typemap code */
		return GnMarshalUTF8.StringFromNativeUtf8(gnsdk_csharp_marshalPINVOKE.GnAudioWork_TagId_get(swigCPtr) );
	} 

  }

/**
* Audio work's Gracenote identifier
* @return Gracenote identifier
*/
  public string GnId {
	get
	{   
		/* csvarout typemap code */
		return GnMarshalUTF8.StringFromNativeUtf8(gnsdk_csharp_marshalPINVOKE.GnAudioWork_GnId_get(swigCPtr) );
	} 

  }

/**
* Audio work's Gracenote unique identifier.
* @return Gracenote unique identifier
*/
  public string GnUId {
	get
	{   
		/* csvarout typemap code */
		return GnMarshalUTF8.StringFromNativeUtf8(gnsdk_csharp_marshalPINVOKE.GnAudioWork_GnUId_get(swigCPtr) );
	} 

  }

/**
* Audio work's classical music composition form value (e.g., Symphony).
* @return Compsition form
* <p><b>Remarks:</b></p>
* This is a list-based value requiring that a corresponding locale or list be loaded.
*/
  public string CompositionForm {
	get
	{   
		/* csvarout typemap code */
		return GnMarshalUTF8.StringFromNativeUtf8(gnsdk_csharp_marshalPINVOKE.GnAudioWork_CompositionForm_get(swigCPtr) );
	} 

  }

}

}
