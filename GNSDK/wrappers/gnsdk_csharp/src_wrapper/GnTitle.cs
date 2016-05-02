
namespace GracenoteSDK {

using System;
using System.Runtime.InteropServices;

/**
* Title of a work or product
*/
public class GnTitle : GnDataObject {
  private HandleRef swigCPtr;

  internal GnTitle(IntPtr cPtr, bool cMemoryOwn) : base(gnsdk_csharp_marshalPINVOKE.GnTitle_SWIGUpcast(cPtr), cMemoryOwn) {
    swigCPtr = new HandleRef(this, cPtr);
  }

  internal static HandleRef getCPtr(GnTitle obj) {
    return (obj == null) ? new HandleRef(null, IntPtr.Zero) : obj.swigCPtr;
  }

  ~GnTitle() {
    Dispose();
  }

  public override void Dispose() {
    lock(this) {
      if (swigCPtr.Handle != IntPtr.Zero) {
        if (swigCMemOwn) {
          swigCMemOwn = false;
          gnsdk_csharp_marshalPINVOKE.delete_GnTitle(swigCPtr);
        }
        swigCPtr = new HandleRef(null, IntPtr.Zero);
      }
      GC.SuppressFinalize(this);
      base.Dispose();
    }
  }

  public static string GnType() {
    string ret = gnsdk_csharp_marshalPINVOKE.GnTitle_GnType();
    return ret;
  }

  public static GnTitle From(GnDataObject obj) {
    GnTitle ret = new GnTitle(gnsdk_csharp_marshalPINVOKE.GnTitle_From(GnDataObject.getCPtr(obj)), true);
    if (gnsdk_csharp_marshalPINVOKE.SWIGPendingException.Pending) throw gnsdk_csharp_marshalPINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

/**
*  Title display string
*  @return Strng suitable for displaying to end user
*/
  public string Display {
	get
	{   
		/* csvarout typemap code */
		return GnMarshalUTF8.StringFromNativeUtf8(gnsdk_csharp_marshalPINVOKE.GnTitle_Display_get(swigCPtr) );
	} 

  }

/**
*  Title display language
*  @return Language string
*/
  public string Language {
	get
	{   
		/* csvarout typemap code */
		return GnMarshalUTF8.StringFromNativeUtf8(gnsdk_csharp_marshalPINVOKE.GnTitle_Language_get(swigCPtr) );
	} 

  }

/**
*  3 letter ISO code for display language
*  @return Language code
*/
  public string LanguageCode {
	get
	{   
		/* csvarout typemap code */
		return GnMarshalUTF8.StringFromNativeUtf8(gnsdk_csharp_marshalPINVOKE.GnTitle_LanguageCode_get(swigCPtr) );
	} 

  }

/**
*  Sortable title
*  @return Sortable string
*/
  public string Sortable {
	get
	{   
		/* csvarout typemap code */
		return GnMarshalUTF8.StringFromNativeUtf8(gnsdk_csharp_marshalPINVOKE.GnTitle_Sortable_get(swigCPtr) );
	} 

  }

/**
*  Sortable title scheme
*  @return Sortable scheme
*/
  public string SortableScheme {
	get
	{   
		/* csvarout typemap code */
		return GnMarshalUTF8.StringFromNativeUtf8(gnsdk_csharp_marshalPINVOKE.GnTitle_SortableScheme_get(swigCPtr) );
	} 

  }

/**
* Title edition
* @return Edition
*/
  public string Edition {
	get
	{   
		/* csvarout typemap code */
		return GnMarshalUTF8.StringFromNativeUtf8(gnsdk_csharp_marshalPINVOKE.GnTitle_Edition_get(swigCPtr) );
	} 

  }

/**
* Main title
* @return Title
*/
  public string MainTitle {
	get
	{   
		/* csvarout typemap code */
		return GnMarshalUTF8.StringFromNativeUtf8(gnsdk_csharp_marshalPINVOKE.GnTitle_MainTitle_get(swigCPtr) );
	} 

  }

/**
*  Title prefix, e.g., The
*  @return Prefix
*/
  public string Prefix {
	get
	{   
		/* csvarout typemap code */
		return GnMarshalUTF8.StringFromNativeUtf8(gnsdk_csharp_marshalPINVOKE.GnTitle_Prefix_get(swigCPtr) );
	} 

  }

}

}
