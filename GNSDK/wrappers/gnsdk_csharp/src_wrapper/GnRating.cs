
namespace GracenoteSDK {

using System;
using System.Runtime.InteropServices;

/**
* \class GnRating
*/
public class GnRating : GnDataObject {
  private HandleRef swigCPtr;

  internal GnRating(IntPtr cPtr, bool cMemoryOwn) : base(gnsdk_csharp_marshalPINVOKE.GnRating_SWIGUpcast(cPtr), cMemoryOwn) {
    swigCPtr = new HandleRef(this, cPtr);
  }

  internal static HandleRef getCPtr(GnRating obj) {
    return (obj == null) ? new HandleRef(null, IntPtr.Zero) : obj.swigCPtr;
  }

  ~GnRating() {
    Dispose();
  }

  public override void Dispose() {
    lock(this) {
      if (swigCPtr.Handle != IntPtr.Zero) {
        if (swigCMemOwn) {
          swigCMemOwn = false;
          gnsdk_csharp_marshalPINVOKE.delete_GnRating(swigCPtr);
        }
        swigCPtr = new HandleRef(null, IntPtr.Zero);
      }
      GC.SuppressFinalize(this);
      base.Dispose();
    }
  }

/**
*  Rating description .
* @ingroup GDO_ValueKeys_Video
*/
  public string RatingDesc() {
    string ret = gnsdk_csharp_marshalPINVOKE.GnRating_RatingDesc(swigCPtr);
    return ret;
  }

/**
*  Rating value, e.g., PG
* @ingroup GDO_ValueKeys_Video
*/
  public string Rating {
	get
	{   
		/* csvarout typemap code */
		return GnMarshalUTF8.StringFromNativeUtf8(gnsdk_csharp_marshalPINVOKE.GnRating_Rating_get(swigCPtr) );
	} 

  }

/**
*  Rating type value, e.g., MPAA .
* @ingroup GDO_ValueKeys_Video
*/
  public string RatingType {
	get
	{   
		/* csvarout typemap code */
		return GnMarshalUTF8.StringFromNativeUtf8(gnsdk_csharp_marshalPINVOKE.GnRating_RatingType_get(swigCPtr) );
	} 

  }

/**
*  Rating type Id.
* @ingroup GDO_ValueKeys_Video
*/
  public uint RatingTypeId {
    get {
      uint ret = gnsdk_csharp_marshalPINVOKE.GnRating_RatingTypeId_get(swigCPtr);
      return ret;
    } 
  }

/**
*  Rating reason
* @ingroup GDO_ValueKeys_Video
*/
  public string RatingReason {
	get
	{   
		/* csvarout typemap code */
		return GnMarshalUTF8.StringFromNativeUtf8(gnsdk_csharp_marshalPINVOKE.GnRating_RatingReason_get(swigCPtr) );
	} 

  }

/**
*  AMPAA (Motion Picture Assoc. of America) rating.
* @ingroup GDO_ValueKeys_Video
*/
  public string RatingMPAA {
	get
	{   
		/* csvarout typemap code */
		return GnMarshalUTF8.StringFromNativeUtf8(gnsdk_csharp_marshalPINVOKE.GnRating_RatingMPAA_get(swigCPtr) );
	} 

  }

/**
*  A MPAA (Motion Picture Assoc. of America) TV rating type.
* @ingroup GDO_ValueKeys_Video
*/
  public string RatingMPAATV {
	get
	{   
		/* csvarout typemap code */
		return GnMarshalUTF8.StringFromNativeUtf8(gnsdk_csharp_marshalPINVOKE.GnRating_RatingMPAATV_get(swigCPtr) );
	} 

  }

/**
*  A FAB (Film Advisory Board) rating.
* @ingroup GDO_ValueKeys_Video
*/
  public string RatingFAB {
	get
	{   
		/* csvarout typemap code */
		return GnMarshalUTF8.StringFromNativeUtf8(gnsdk_csharp_marshalPINVOKE.GnRating_RatingFAB_get(swigCPtr) );
	} 

  }

/**
*  A CHVRS (Canadian Home Video Rating System) rating
* @ingroup GDO_ValueKeys_Video
*/
  public string RatingCHVRS {
	get
	{   
		/* csvarout typemap code */
		return GnMarshalUTF8.StringFromNativeUtf8(gnsdk_csharp_marshalPINVOKE.GnRating_RatingCHVRS_get(swigCPtr) );
	} 

  }

/**
*  A Canadian TV rating type value.
* @ingroup GDO_ValueKeys_Video
*/
  public string RatingCanadianTV {
	get
	{   
		/* csvarout typemap code */
		return GnMarshalUTF8.StringFromNativeUtf8(gnsdk_csharp_marshalPINVOKE.GnRating_RatingCanadianTV_get(swigCPtr) );
	} 

  }

/**
*  A BBFC (British Board of Film Classification) rating type value.
* @ingroup GDO_ValueKeys_Video
*/
  public string RatingBBFC {
	get
	{   
		/* csvarout typemap code */
		return GnMarshalUTF8.StringFromNativeUtf8(gnsdk_csharp_marshalPINVOKE.GnRating_RatingBBFC_get(swigCPtr) );
	} 

  }

/**
*  A CBFC (Central Board of Film Certification) rating type value.
* @ingroup GDO_ValueKeys_Video
*/
  public string RatingCBFC {
	get
	{   
		/* csvarout typemap code */
		return GnMarshalUTF8.StringFromNativeUtf8(gnsdk_csharp_marshalPINVOKE.GnRating_RatingCBFC_get(swigCPtr) );
	} 

  }

/**
*  A OFLC (Australia) TV rating type value.
* @ingroup GDO_ValueKeys_Video
*/
  public string RatingOFLC {
	get
	{   
		/* csvarout typemap code */
		return GnMarshalUTF8.StringFromNativeUtf8(gnsdk_csharp_marshalPINVOKE.GnRating_RatingOFLC_get(swigCPtr) );
	} 

  }

/**
*  A Hong Kong rating type value.
* @ingroup GDO_ValueKeys_Video
*/
  public string RatingHongKong {
	get
	{   
		/* csvarout typemap code */
		return GnMarshalUTF8.StringFromNativeUtf8(gnsdk_csharp_marshalPINVOKE.GnRating_RatingHongKong_get(swigCPtr) );
	} 

  }

/**
* A Finnish rating type value.
* @ingroup GDO_ValueKeys_Video
*/
  public string RatingFinnish {
	get
	{   
		/* csvarout typemap code */
		return GnMarshalUTF8.StringFromNativeUtf8(gnsdk_csharp_marshalPINVOKE.GnRating_RatingFinnish_get(swigCPtr) );
	} 

  }

/**
*  A KMRB (Korea Media Rating Board) rating type value.
* @ingroup GDO_ValueKeys_Video
*/
  public string RatingKMRB {
	get
	{   
		/* csvarout typemap code */
		return GnMarshalUTF8.StringFromNativeUtf8(gnsdk_csharp_marshalPINVOKE.GnRating_RatingKMRB_get(swigCPtr) );
	} 

  }

/**
* A DVD Parental rating
* @ingroup GDO_ValueKeys_Video
*/
  public string RatingDVDParental {
	get
	{   
		/* csvarout typemap code */
		return GnMarshalUTF8.StringFromNativeUtf8(gnsdk_csharp_marshalPINVOKE.GnRating_RatingDVDParental_get(swigCPtr) );
	} 

  }

/**
* A EIRIN (Japan) rating
* @ingroup GDO_ValueKeys_Video
*/
  public string RatingEIRIN {
	get
	{   
		/* csvarout typemap code */
		return GnMarshalUTF8.StringFromNativeUtf8(gnsdk_csharp_marshalPINVOKE.GnRating_RatingEIRIN_get(swigCPtr) );
	} 

  }

/**
*  A INCAA (Argentina) rating
* @ingroup GDO_ValueKeys_Video
*/
  public string RatingINCAA {
	get
	{   
		/* csvarout typemap code */
		return GnMarshalUTF8.StringFromNativeUtf8(gnsdk_csharp_marshalPINVOKE.GnRating_RatingINCAA_get(swigCPtr) );
	} 

  }

/**
*  A DJTCQ (Dept of Justice, Rating, Titles and Qualification) (Brazil) rating
* @ingroup GDO_ValueKeys_Video
*/
  public string RatingDJTCQ {
	get
	{   
		/* csvarout typemap code */
		return GnMarshalUTF8.StringFromNativeUtf8(gnsdk_csharp_marshalPINVOKE.GnRating_RatingDJTCQ_get(swigCPtr) );
	} 

  }

/**
*  A Quebecois rating.
* @ingroup GDO_ValueKeys_Video
*/
  public string RatingQuebec {
	get
	{   
		/* csvarout typemap code */
		return GnMarshalUTF8.StringFromNativeUtf8(gnsdk_csharp_marshalPINVOKE.GnRating_RatingQuebec_get(swigCPtr) );
	} 

  }

/**
*  A French rating.
* @ingroup GDO_ValueKeys_Video
*/
  public string RatingFrance {
	get
	{   
		/* csvarout typemap code */
		return GnMarshalUTF8.StringFromNativeUtf8(gnsdk_csharp_marshalPINVOKE.GnRating_RatingFrance_get(swigCPtr) );
	} 

  }

/**
*  A FSK (German) rating.
* @ingroup GDO_ValueKeys_Video
*/
  public string RatingFSK {
	get
	{   
		/* csvarout typemap code */
		return GnMarshalUTF8.StringFromNativeUtf8(gnsdk_csharp_marshalPINVOKE.GnRating_RatingFSK_get(swigCPtr) );
	} 

  }

/**
*  An Italian rating
* @ingroup GDO_ValueKeys_Video
*/
  public string RatingItaly {
	get
	{   
		/* csvarout typemap code */
		return GnMarshalUTF8.StringFromNativeUtf8(gnsdk_csharp_marshalPINVOKE.GnRating_RatingItaly_get(swigCPtr) );
	} 

  }

/**
*  A Spanish rating
* @ingroup GDO_ValueKeys_Video
*/
  public string RatingSpain {
	get
	{   
		/* csvarout typemap code */
		return GnMarshalUTF8.StringFromNativeUtf8(gnsdk_csharp_marshalPINVOKE.GnRating_RatingSpain_get(swigCPtr) );
	} 

  }

}

}
