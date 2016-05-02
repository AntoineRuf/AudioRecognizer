
namespace GracenoteSDK {

using System;
using System.Runtime.InteropServices;

/**
* \class GnVideoFeature 
* Class containing metadata for a video feature, which has a full-length running time usually between 60 and 120 minutes.
* A feature is the main component of a DVD or Blu-ray disc which may, in addition, contain extra, or bonus, video clips and features.
*
*/
public class GnVideoFeature : GnDataObject {
  private HandleRef swigCPtr;

  internal GnVideoFeature(IntPtr cPtr, bool cMemoryOwn) : base(gnsdk_csharp_marshalPINVOKE.GnVideoFeature_SWIGUpcast(cPtr), cMemoryOwn) {
    swigCPtr = new HandleRef(this, cPtr);
  }

  internal static HandleRef getCPtr(GnVideoFeature obj) {
    return (obj == null) ? new HandleRef(null, IntPtr.Zero) : obj.swigCPtr;
  }

  ~GnVideoFeature() {
    Dispose();
  }

  public override void Dispose() {
    lock(this) {
      if (swigCPtr.Handle != IntPtr.Zero) {
        if (swigCMemOwn) {
          swigCMemOwn = false;
          gnsdk_csharp_marshalPINVOKE.delete_GnVideoFeature(swigCPtr);
        }
        swigCPtr = new HandleRef(null, IntPtr.Zero);
      }
      GC.SuppressFinalize(this);
      base.Dispose();
    }
  }

  public static string GnType() {
    string ret = gnsdk_csharp_marshalPINVOKE.GnVideoFeature_GnType();
    return ret;
  }

  public static GnVideoFeature From(GnDataObject obj) {
    GnVideoFeature ret = new GnVideoFeature(gnsdk_csharp_marshalPINVOKE.GnVideoFeature_From(GnDataObject.getCPtr(obj)), true);
    if (gnsdk_csharp_marshalPINVOKE.SWIGPendingException.Pending) throw gnsdk_csharp_marshalPINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

/**
* Genre. e.g., Drama. This is a list/locale dependent,multi-level field
*  <p><b>Remarks:</b></p>
*  This is a list-based value requiring that a list or locale be loaded into memory.
*
*  To render locale-dependent information for list-based values, the application must allocate a
*  <code>GnLocale</code> object. A <code>LocaleNotLoaded</code> message is returned when locale information
*  is not set prior to a request for a list-based value.
*
*  This is a multi-level field requiring a <code>GnDataLevel</code> parameter
*
* @ingroup GDO_ValueKeys_Misc
*/
  public string Genre(GnDataLevel level) {
    string ret = gnsdk_csharp_marshalPINVOKE.GnVideoFeature_Genre(swigCPtr, (int)level);
    return ret;
  }

/**
*  Feature's ordinal value
* @ingroup GDO_ValueKeys_Misc
*/
  public uint Ordinal {
    get {
      uint ret = gnsdk_csharp_marshalPINVOKE.GnVideoFeature_Ordinal_get(swigCPtr);
      return ret;
    } 
  }

/**
*  Matched boolean value indicating whether this type
*  is the one that matched the input criteria. Available from many video types.
* @ingroup GDO_ValueKeys_Misc
*/
  public bool Matched {
    get {
      bool ret = gnsdk_csharp_marshalPINVOKE.GnVideoFeature_Matched_get(swigCPtr);
      return ret;
    } 
  }

/**
*  Video feature type value.
*  <p><b>Remarks:</b></p>
*  This is a list-based value requiring that a list or locale be loaded into memory.
*
*  To render locale-dependent information for list-based values, the application must allocate a
*  <code>GnLocale</code> object. A <code>LocaleNotLoaded</code> message is returned when locale information
*  is not set prior to a request for a list-based value.
* @ingroup GDO_ValueKeys_Video
*/
  public string VideoFeatureType {
	get
	{   
		/* csvarout typemap code */
		return GnMarshalUTF8.StringFromNativeUtf8(gnsdk_csharp_marshalPINVOKE.GnVideoFeature_VideoFeatureType_get(swigCPtr) );
	} 

  }

/**
*  Video production type value.
*  <p><b>Remarks:</b></p>
*  This is a list-based value requiring that a list or locale be loaded into memory.
*
*  To render locale-dependent information for list-based values, the application must allocate a
*  <code>GnLocale</code> object. A <code>LocaleNotLoaded</code> message is returned when locale information
*  is not set prior to a request for a list-based value.
* @ingroup GDO_ValueKeys_Video
*/
  public string VideoProductionType {
	get
	{   
		/* csvarout typemap code */
		return GnMarshalUTF8.StringFromNativeUtf8(gnsdk_csharp_marshalPINVOKE.GnVideoFeature_VideoProductionType_get(swigCPtr) );
	} 

  }

/**
*  Video production ID type value
* @ingroup GDO_ValueKeys_Video
*/
  public uint VideoProductionTypeId {
    get {
      uint ret = gnsdk_csharp_marshalPINVOKE.GnVideoFeature_VideoProductionTypeId_get(swigCPtr);
      return ret;
    } 
  }

/**
*  Release date in UTC format
* @ingroup GDO_ValueKeys_Video
*/
  public string DateRelease {
	get
	{   
		/* csvarout typemap code */
		return GnMarshalUTF8.StringFromNativeUtf8(gnsdk_csharp_marshalPINVOKE.GnVideoFeature_DateRelease_get(swigCPtr) );
	} 

  }

/**
*  Original release date in UTC format.
* @ingroup GDO_ValueKeys_Video
*/
  public string DateOriginalRelease {
	get
	{   
		/* csvarout typemap code */
		return GnMarshalUTF8.StringFromNativeUtf8(gnsdk_csharp_marshalPINVOKE.GnVideoFeature_DateOriginalRelease_get(swigCPtr) );
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
		return GnMarshalUTF8.StringFromNativeUtf8(gnsdk_csharp_marshalPINVOKE.GnVideoFeature_Notes_get(swigCPtr) );
	} 

  }

/**
* Aspect ratio - describes the proportional relationship between the video's width and its height
* expressed as two numbers separated by a colon
* @ingroup GDO_ValueKeys_Video
*/
  public string AspectRatio {
	get
	{   
		/* csvarout typemap code */
		return GnMarshalUTF8.StringFromNativeUtf8(gnsdk_csharp_marshalPINVOKE.GnVideoFeature_AspectRatio_get(swigCPtr) );
	} 

  }

/**
*  Aspect ratio type, e.g., Standard
* @ingroup GDO_ValueKeys_Video
*/
  public string AspectRatioType {
	get
	{   
		/* csvarout typemap code */
		return GnMarshalUTF8.StringFromNativeUtf8(gnsdk_csharp_marshalPINVOKE.GnVideoFeature_AspectRatioType_get(swigCPtr) );
	} 

  }

/**
*  Duration value in seconds.
* @ingroup GDO_ValueKeys_Video
*/
  public uint Duration {
    get {
      uint ret = gnsdk_csharp_marshalPINVOKE.GnVideoFeature_Duration_get(swigCPtr);
      return ret;
    } 
  }

/**
*  Duration units value (e.g., seconds, "SEC")
* @ingroup GDO_ValueKeys_Video
*/
  public string DurationUnits {
	get
	{   
		/* csvarout typemap code */
		return GnMarshalUTF8.StringFromNativeUtf8(gnsdk_csharp_marshalPINVOKE.GnVideoFeature_DurationUnits_get(swigCPtr) );
	} 

  }

/**
*  Plot summary
* @ingroup GDO_ValueKeys_Video
*/
  public string PlotSummary {
	get
	{   
		/* csvarout typemap code */
		return GnMarshalUTF8.StringFromNativeUtf8(gnsdk_csharp_marshalPINVOKE.GnVideoFeature_PlotSummary_get(swigCPtr) );
	} 

  }

/**
*  Plot synopsis, e.g., (for Friends episode) "Monica's popularity at a karaoke club might have more to do with her revealing dress than her voice;
* @ingroup GDO_ValueKeys_Video
*/
  public string PlotSynopsis {
	get
	{   
		/* csvarout typemap code */
		return GnMarshalUTF8.StringFromNativeUtf8(gnsdk_csharp_marshalPINVOKE.GnVideoFeature_PlotSynopsis_get(swigCPtr) );
	} 

  }

/**
*  Plot tagline, e.g., "The terrifying motion picture from the terrifying No. 1 best seller."
*  GNSDK_GDO_VALUE_PLOT_TAGLINE
* @ingroup GDO_ValueKeys_Video
*/
  public string PlotTagline {
	get
	{   
		/* csvarout typemap code */
		return GnMarshalUTF8.StringFromNativeUtf8(gnsdk_csharp_marshalPINVOKE.GnVideoFeature_PlotTagline_get(swigCPtr) );
	} 

  }

/**
*  Plot synopsis language, e.g., English
*  <p><b>Remarks:</b></p>
*  The language depends on availability - information in the language set
*   for the locale may not be available, and the object's information may be available only in its
*   default official language. For example, if a locale's set language is Spanish, but the object's
*   information is available only in English, this value returns as English.
* @ingroup GDO_ValueKeys_Video
*/
  public string PlotSynopsisLanguage {
	get
	{   
		/* csvarout typemap code */
		return GnMarshalUTF8.StringFromNativeUtf8(gnsdk_csharp_marshalPINVOKE.GnVideoFeature_PlotSynopsisLanguage_get(swigCPtr) );
	} 

  }

/**
*  Official title object
* @ingroup GDO_ChildKeys_Title
*/
  public GnTitle OfficialTitle {
    get {
      IntPtr cPtr = gnsdk_csharp_marshalPINVOKE.GnVideoFeature_OfficialTitle_get(swigCPtr);
      GnTitle ret = (cPtr == IntPtr.Zero) ? null : new GnTitle(cPtr, true);
      return ret;
    } 
  }

/**
*  Rating object
* @ingroup GDO_ValueKeys_Misc
*/
  public GnRating Rating {
    get {
      IntPtr cPtr = gnsdk_csharp_marshalPINVOKE.GnVideoFeature_Rating_get(swigCPtr);
      GnRating ret = (cPtr == IntPtr.Zero) ? null : new GnRating(cPtr, true);
      return ret;
    } 
  }

  public GnVideoWorkEnumerable Works {
    get {
      IntPtr cPtr = gnsdk_csharp_marshalPINVOKE.GnVideoFeature_Works_get(swigCPtr);
      GnVideoWorkEnumerable ret = (cPtr == IntPtr.Zero) ? null : new GnVideoWorkEnumerable(cPtr, true);
      return ret;
    } 
  }

  public GnVideoChapterEnumerable Chapters {
    get {
      IntPtr cPtr = gnsdk_csharp_marshalPINVOKE.GnVideoFeature_Chapters_get(swigCPtr);
      GnVideoChapterEnumerable ret = (cPtr == IntPtr.Zero) ? null : new GnVideoChapterEnumerable(cPtr, true);
      return ret;
    } 
  }

  public GnVideoCreditEnumerable VideoCredits {
    get {
      IntPtr cPtr = gnsdk_csharp_marshalPINVOKE.GnVideoFeature_VideoCredits_get(swigCPtr);
      GnVideoCreditEnumerable ret = (cPtr == IntPtr.Zero) ? null : new GnVideoCreditEnumerable(cPtr, true);
      return ret;
    } 
  }

}

}
