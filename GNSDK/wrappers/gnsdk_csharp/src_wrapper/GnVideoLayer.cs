
namespace GracenoteSDK {

using System;
using System.Runtime.InteropServices;

/**
* \class GnVideoLayer
* Both DVDs and Blu-ray Discs can be dual layer. These discs are only writable on one side of the disc,
* but contain two layers on that single side for writing data to. Dual-Layer recordable DVDs come in two formats: DVD-R DL and DVD+R DL.
* They can hold up to 8.5GB on the two layers. Dual-layer Blu-ray discs can store 50 GB of data (25GB on each layer)
*/
public class GnVideoLayer : GnDataObject {
  private HandleRef swigCPtr;

  internal GnVideoLayer(IntPtr cPtr, bool cMemoryOwn) : base(gnsdk_csharp_marshalPINVOKE.GnVideoLayer_SWIGUpcast(cPtr), cMemoryOwn) {
    swigCPtr = new HandleRef(this, cPtr);
  }

  internal static HandleRef getCPtr(GnVideoLayer obj) {
    return (obj == null) ? new HandleRef(null, IntPtr.Zero) : obj.swigCPtr;
  }

  ~GnVideoLayer() {
    Dispose();
  }

  public override void Dispose() {
    lock(this) {
      if (swigCPtr.Handle != IntPtr.Zero) {
        if (swigCMemOwn) {
          swigCMemOwn = false;
          gnsdk_csharp_marshalPINVOKE.delete_GnVideoLayer(swigCPtr);
        }
        swigCPtr = new HandleRef(null, IntPtr.Zero);
      }
      GC.SuppressFinalize(this);
      base.Dispose();
    }
  }

  public static string GnType() {
    string ret = gnsdk_csharp_marshalPINVOKE.GnVideoLayer_GnType();
    return ret;
  }

  public static GnVideoLayer From(GnDataObject obj) {
    GnVideoLayer ret = new GnVideoLayer(gnsdk_csharp_marshalPINVOKE.GnVideoLayer_From(GnDataObject.getCPtr(obj)), true);
    if (gnsdk_csharp_marshalPINVOKE.SWIGPendingException.Pending) throw gnsdk_csharp_marshalPINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

/**
*  Ordinal value
* @ingroup GDO_ValueKeys_Misc
*/
  public uint Ordinal {
    get {
      uint ret = gnsdk_csharp_marshalPINVOKE.GnVideoLayer_Ordinal_get(swigCPtr);
      return ret;
    } 
  }

/**
*  Matched boolean value indicating whether this object
*   is the one that matched the input criteria.
* @ingroup GDO_ValueKeys_Misc
*/
  public bool Matched {
    get {
      bool ret = gnsdk_csharp_marshalPINVOKE.GnVideoLayer_Matched_get(swigCPtr);
      return ret;
    } 
  }

/**
*  Aspect ratio - describes the proportional relationship between the video's width and its height
* expressed as two numbers separated by a colon
* @ingroup GDO_ValueKeys_Video
*/
  public string AspectRatio {
	get
	{   
		/* csvarout typemap code */
		return GnMarshalUTF8.StringFromNativeUtf8(gnsdk_csharp_marshalPINVOKE.GnVideoLayer_AspectRatio_get(swigCPtr) );
	} 

  }

/**
*  Aspect ratio type, e.g. Standard
* @ingroup GDO_ValueKeys_Video
*/
  public string AspectRatioType {
	get
	{   
		/* csvarout typemap code */
		return GnMarshalUTF8.StringFromNativeUtf8(gnsdk_csharp_marshalPINVOKE.GnVideoLayer_AspectRatioType_get(swigCPtr) );
	} 

  }

/**
*  TV system value, e.g., NTSC.
* @ingroup GDO_ValueKeys_Video
*/
  public string TvSystem {
	get
	{   
		/* csvarout typemap code */
		return GnMarshalUTF8.StringFromNativeUtf8(gnsdk_csharp_marshalPINVOKE.GnVideoLayer_TvSystem_get(swigCPtr) );
	} 

  }

/**
*  Region code, e.g., FE - France
* @ingroup GDO_ValueKeys_Video
*/
  public string RegionCode {
	get
	{   
		/* csvarout typemap code */
		return GnMarshalUTF8.StringFromNativeUtf8(gnsdk_csharp_marshalPINVOKE.GnVideoLayer_RegionCode_get(swigCPtr) );
	} 

  }

/**
*  Video product region value from the current type, e.g., 1. This is a list/locale dependent value.
*  <p><b>Remarks:</b></p>
*  This is a list-based value requiring that a list or locale be loaded into memory.
*
*  To render locale-dependent information for list-based values, the application must allocate a
*  <code>GnLocale</code> object. A <code>LocaleNotLoaded</code> message is returned when locale information
*  is not set prior to a request for a list-based value.
* @ingroup GDO_ValueKeys_Video
*/
  public string VideoRegion {
	get
	{   
		/* csvarout typemap code */
		return GnMarshalUTF8.StringFromNativeUtf8(gnsdk_csharp_marshalPINVOKE.GnVideoLayer_VideoRegion_get(swigCPtr) );
	} 

  }

/**
*  Video product region, e.g.,  USA, Canada, US Territories, Bermuda, and Cayman Islands.
*  <p><b>Remarks:</b></p>
*  This is a list-based value requiring that a list or locale be loaded into memory.
*
*  To render locale-dependent information for list-based values, the application must allocate a
*  <code>GnLocale</code> object. A <code>LocaleNotLoaded</code> message is returned when locale information
*  is not set prior to a request for a list-based value.
* @ingroup GDO_ValueKeys_Video
*/
  public string VideoRegionDesc {
	get
	{   
		/* csvarout typemap code */
		return GnMarshalUTF8.StringFromNativeUtf8(gnsdk_csharp_marshalPINVOKE.GnVideoLayer_VideoRegionDesc_get(swigCPtr) );
	} 

  }

/**
*  Video media type such as Audio-CD, Blu-ray, DVD, or HD DVD.
*  <p><b>Remarks:</b></p>
*  This is a list-based value requiring that a list or locale be loaded into memory.
*
*  To render locale-dependent information for list-based values, your application must allocate a
*  <code>GnLocale</code> object. A <code>LocaleNotLoaded</code> message is returned when locale information
*  is not set prior to a request for a list-based value.
* @ingroup GDO_ValueKeys_Video
*/
  public string MediaType {
	get
	{   
		/* csvarout typemap code */
		return GnMarshalUTF8.StringFromNativeUtf8(gnsdk_csharp_marshalPINVOKE.GnVideoLayer_MediaType_get(swigCPtr) );
	} 

  }

  public GnVideoFeatureEnumerable Features {
    get {
      IntPtr cPtr = gnsdk_csharp_marshalPINVOKE.GnVideoLayer_Features_get(swigCPtr);
      GnVideoFeatureEnumerable ret = (cPtr == IntPtr.Zero) ? null : new GnVideoFeatureEnumerable(cPtr, true);
      return ret;
    } 
  }

}

}
