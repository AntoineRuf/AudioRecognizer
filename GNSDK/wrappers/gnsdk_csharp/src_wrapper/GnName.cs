
namespace GracenoteSDK {

using System;
using System.Runtime.InteropServices;

/**
* Name
*/
public class GnName : GnDataObject {
  private HandleRef swigCPtr;

  internal GnName(IntPtr cPtr, bool cMemoryOwn) : base(gnsdk_csharp_marshalPINVOKE.GnName_SWIGUpcast(cPtr), cMemoryOwn) {
    swigCPtr = new HandleRef(this, cPtr);
  }

  internal static HandleRef getCPtr(GnName obj) {
    return (obj == null) ? new HandleRef(null, IntPtr.Zero) : obj.swigCPtr;
  }

  ~GnName() {
    Dispose();
  }

  public override void Dispose() {
    lock(this) {
      if (swigCPtr.Handle != IntPtr.Zero) {
        if (swigCMemOwn) {
          swigCMemOwn = false;
          gnsdk_csharp_marshalPINVOKE.delete_GnName(swigCPtr);
        }
        swigCPtr = new HandleRef(null, IntPtr.Zero);
      }
      GC.SuppressFinalize(this);
      base.Dispose();
    }
  }

  public static string GnType() {
    string ret = gnsdk_csharp_marshalPINVOKE.GnName_GnType();
    return ret;
  }

  public static GnName From(GnDataObject obj) {
    GnName ret = new GnName(gnsdk_csharp_marshalPINVOKE.GnName_From(GnDataObject.getCPtr(obj)), true);
    if (gnsdk_csharp_marshalPINVOKE.SWIGPendingException.Pending) throw gnsdk_csharp_marshalPINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

/**
*  Display name string
*  @return Name suitable for displaying to the end user
*/
  public string Display {
	get
	{   
		/* csvarout typemap code */
		return GnMarshalUTF8.StringFromNativeUtf8(gnsdk_csharp_marshalPINVOKE.GnName_Display_get(swigCPtr) );
	} 

  }

/**
*  Name display language
*  @return Langauge string
*/
  public string Language {
	get
	{   
		/* csvarout typemap code */
		return GnMarshalUTF8.StringFromNativeUtf8(gnsdk_csharp_marshalPINVOKE.GnName_Language_get(swigCPtr) );
	} 

  }

/**
*  3-letter ISO code for display langauge
*  @return Language code
*/
  public string LanguageCode {
	get
	{   
		/* csvarout typemap code */
		return GnMarshalUTF8.StringFromNativeUtf8(gnsdk_csharp_marshalPINVOKE.GnName_LanguageCode_get(swigCPtr) );
	} 

  }

/**
*  Sortable name
*  @return Sortable string
*/
  public string Sortable {
	get
	{   
		/* csvarout typemap code */
		return GnMarshalUTF8.StringFromNativeUtf8(gnsdk_csharp_marshalPINVOKE.GnName_Sortable_get(swigCPtr) );
	} 

  }

/**
*  Sortable scheme
*  @return Sortable Scheme
*/
  public string SortableScheme {
	get
	{   
		/* csvarout typemap code */
		return GnMarshalUTF8.StringFromNativeUtf8(gnsdk_csharp_marshalPINVOKE.GnName_SortableScheme_get(swigCPtr) );
	} 

  }

/**
*  Name prefix, e.g., "The"
*  @return Prefix
*/
  public string Prefix {
	get
	{   
		/* csvarout typemap code */
		return GnMarshalUTF8.StringFromNativeUtf8(gnsdk_csharp_marshalPINVOKE.GnName_Prefix_get(swigCPtr) );
	} 

  }

/**
*  Family name
*  @return Name
*/
  public string Family {
	get
	{   
		/* csvarout typemap code */
		return GnMarshalUTF8.StringFromNativeUtf8(gnsdk_csharp_marshalPINVOKE.GnName_Family_get(swigCPtr) );
	} 

  }

/**
*  Given name
*  @return name
*/
  public string Given {
	get
	{   
		/* csvarout typemap code */
		return GnMarshalUTF8.StringFromNativeUtf8(gnsdk_csharp_marshalPINVOKE.GnName_Given_get(swigCPtr) );
	} 

  }

/**
*  Name global ID - used for transcriptions
*  @return Gracenote Global ID
*/
  public string GlobalId {
	get
	{   
		/* csvarout typemap code */
		return GnMarshalUTF8.StringFromNativeUtf8(gnsdk_csharp_marshalPINVOKE.GnName_GlobalId_get(swigCPtr) );
	} 

  }

}

}
