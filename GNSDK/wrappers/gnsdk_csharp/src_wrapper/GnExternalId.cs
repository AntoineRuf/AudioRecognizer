
namespace GracenoteSDK {

using System;
using System.Runtime.InteropServices;

/**
* Third-party identifier used to match identified media to merchandise IDs in online stores and other services
*
*/
public class GnExternalId : GnDataObject {
  private HandleRef swigCPtr;

  internal GnExternalId(IntPtr cPtr, bool cMemoryOwn) : base(gnsdk_csharp_marshalPINVOKE.GnExternalId_SWIGUpcast(cPtr), cMemoryOwn) {
    swigCPtr = new HandleRef(this, cPtr);
  }

  internal static HandleRef getCPtr(GnExternalId obj) {
    return (obj == null) ? new HandleRef(null, IntPtr.Zero) : obj.swigCPtr;
  }

  ~GnExternalId() {
    Dispose();
  }

  public override void Dispose() {
    lock(this) {
      if (swigCPtr.Handle != IntPtr.Zero) {
        if (swigCMemOwn) {
          swigCMemOwn = false;
          gnsdk_csharp_marshalPINVOKE.delete_GnExternalId(swigCPtr);
        }
        swigCPtr = new HandleRef(null, IntPtr.Zero);
      }
      GC.SuppressFinalize(this);
      base.Dispose();
    }
  }

  public static string GnType() {
    string ret = gnsdk_csharp_marshalPINVOKE.GnExternalId_GnType();
    return ret;
  }

  public static GnExternalId From(GnDataObject obj) {
    GnExternalId ret = new GnExternalId(gnsdk_csharp_marshalPINVOKE.GnExternalId_From(GnDataObject.getCPtr(obj)), true);
    if (gnsdk_csharp_marshalPINVOKE.SWIGPendingException.Pending) throw gnsdk_csharp_marshalPINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

/**
*  External ID source (e.g., Amazon)
*  @return External ID source
*/
  public string Source {
	get
	{   
		/* csvarout typemap code */
		return GnMarshalUTF8.StringFromNativeUtf8(gnsdk_csharp_marshalPINVOKE.GnExternalId_Source_get(swigCPtr) );
	} 

  }

/**
*  External ID type
*  @return External ID type
*/
  public string Type {
	get
	{   
		/* csvarout typemap code */
		return GnMarshalUTF8.StringFromNativeUtf8(gnsdk_csharp_marshalPINVOKE.GnExternalId_Type_get(swigCPtr) );
	} 

  }

/**
*  External ID value
*  @return External ID value
*/
  public string Value {
	get
	{   
		/* csvarout typemap code */
		return GnMarshalUTF8.StringFromNativeUtf8(gnsdk_csharp_marshalPINVOKE.GnExternalId_Value_get(swigCPtr) );
	} 

  }

}

}
