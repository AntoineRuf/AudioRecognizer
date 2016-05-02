
namespace GracenoteSDK {

using System;
using System.Runtime.InteropServices;

/**
* \class GnVideoProduct
* A Product refers to the commercial release of a Film, TV Series, or video content. Products contain a
* unique commercial code such as a UPC (Univeral Product Code), Hinban, or EAN (European Article Number).
* Products are for the most part released on a physical format, such as a DVD or Blu-ray.
*/
public class GnVideoProduct : GnDataObject {
  private HandleRef swigCPtr;

  internal GnVideoProduct(IntPtr cPtr, bool cMemoryOwn) : base(gnsdk_csharp_marshalPINVOKE.GnVideoProduct_SWIGUpcast(cPtr), cMemoryOwn) {
    swigCPtr = new HandleRef(this, cPtr);
  }

  internal static HandleRef getCPtr(GnVideoProduct obj) {
    return (obj == null) ? new HandleRef(null, IntPtr.Zero) : obj.swigCPtr;
  }

  ~GnVideoProduct() {
    Dispose();
  }

  public override void Dispose() {
    lock(this) {
      if (swigCPtr.Handle != IntPtr.Zero) {
        if (swigCMemOwn) {
          swigCMemOwn = false;
          gnsdk_csharp_marshalPINVOKE.delete_GnVideoProduct(swigCPtr);
        }
        swigCPtr = new HandleRef(null, IntPtr.Zero);
      }
      GC.SuppressFinalize(this);
      base.Dispose();
    }
  }

  public static string GnType() {
    string ret = gnsdk_csharp_marshalPINVOKE.GnVideoProduct_GnType();
    return ret;
  }

  public static GnVideoProduct From(GnDataObject obj) {
    GnVideoProduct ret = new GnVideoProduct(gnsdk_csharp_marshalPINVOKE.GnVideoProduct_From(GnDataObject.getCPtr(obj)), true);
    if (gnsdk_csharp_marshalPINVOKE.SWIGPendingException.Pending) throw gnsdk_csharp_marshalPINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

  public GnVideoProduct(string id, string idTag) : this(gnsdk_csharp_marshalPINVOKE.new_GnVideoProduct(id, idTag), true) {
    if (gnsdk_csharp_marshalPINVOKE.SWIGPendingException.Pending) throw gnsdk_csharp_marshalPINVOKE.SWIGPendingException.Retrieve();
  }

/**
*  Genre, e.g., Comedy. This is a list/locale dependent, multi-level field.
*  <p><b>Remarks:</b></p>
*  This is a list-based value requiring that a list or locale be loaded into memory.
*
*  To render locale-dependent information for list-based values, your application must allocate a
*  <code>GnLocale</code> object. A <code>LocaleNotLoaded</code> message is returned when locale information
*  is not set prior to a request for a list-based value.
*
*  This is a multi-level field requiring a <code>GnDataLevel</code> parameter
*
* @ingroup GDO_ValueKeys_Misc
*/
  public string Genre(GnDataLevel level) {
    string ret = gnsdk_csharp_marshalPINVOKE.GnVideoProduct_Genre(swigCPtr, (int)level);
    return ret;
  }

  public GnContentEnumerable Contents() {
    GnContentEnumerable ret = new GnContentEnumerable(gnsdk_csharp_marshalPINVOKE.GnVideoProduct_Contents(swigCPtr), true);
    return ret;
  }

/**
*	Gracenote ID
* @ingroup GDO_ValueKeys_GracenoteIDs
*/
  public string GnId {
	get
	{   
		/* csvarout typemap code */
		return GnMarshalUTF8.StringFromNativeUtf8(gnsdk_csharp_marshalPINVOKE.GnVideoProduct_GnId_get(swigCPtr) );
	} 

  }

/**
*	Gracenote unique ID
* @ingroup GDO_ValueKeys_GracenoteIDs
*/
  public string GnUId {
	get
	{   
		/* csvarout typemap code */
		return GnMarshalUTF8.StringFromNativeUtf8(gnsdk_csharp_marshalPINVOKE.GnVideoProduct_GnUId_get(swigCPtr) );
	} 

  }

/**
*	Product ID aka Tag ID
*	<p><b>Remarks:</b></p>
*	Available for most types, this value which can be stored or transmitted - it can bw used as a static identifier for the current content
*  and will not change over time.
*	@ingroup GDO_ValueKeys_GracenoteIDs
*/
  public string ProductId {
	get
	{   
		/* csvarout typemap code */
		return GnMarshalUTF8.StringFromNativeUtf8(gnsdk_csharp_marshalPINVOKE.GnVideoProduct_ProductId_get(swigCPtr) );
	} 

  }

/**
*	Tui (title-unique identifier)
*	@ingroup GDO_ValueKeys_GracenoteIDs
*/
  public string Tui {
	get
	{   
		/* csvarout typemap code */
		return GnMarshalUTF8.StringFromNativeUtf8(gnsdk_csharp_marshalPINVOKE.GnVideoProduct_Tui_get(swigCPtr) );
	} 

  }

/**
*	Tui Tag value
*	@ingroup GDO_ValueKeys_GracenoteIDs
*/
  public string TuiTag {
	get
	{   
		/* csvarout typemap code */
		return GnMarshalUTF8.StringFromNativeUtf8(gnsdk_csharp_marshalPINVOKE.GnVideoProduct_TuiTag_get(swigCPtr) );
	} 

  }

/**
*	Package display language, e.g., "English"
*  <p><b>Remarks:</b></p>
*	The language depends on availability - information in the language set
*	for the locale may not be available, and the object's information may be available only in its
*	default official language. For example, if a locale's set language is Spanish, but the object's
*	information is available only in English, this value returns as English.
*	@ingroup GDO_ValueKeys_Misc
*/
  public string PackageLanguageDisplay {
	get
	{   
		/* csvarout typemap code */
		return GnMarshalUTF8.StringFromNativeUtf8(gnsdk_csharp_marshalPINVOKE.GnVideoProduct_PackageLanguageDisplay_get(swigCPtr) );
	} 

  }

/**
*	Package language ISO code, e.g., "eng".
*	<p><b>Remarks:</b></p>
*	GNSDK supports a subset of the ISO 639-2 Language Code List.
*	Specify a locale language's lower-case three-letter code, which is shown in the macro's C/C++
*	syntax section.
*	<p><b>Note:</b></p>
*   The following languages use Gracenote-specific three-letter codes:
*  <ul>
*  <li>qtb (Simplified Chinese)*
*  <li>qtd (Traditional Chinese)*
*  </ul>
*	@ingroup GDO_ValueKeys_Misc
*/
  public string PackageLanguage {
	get
	{   
		/* csvarout typemap code */
		return GnMarshalUTF8.StringFromNativeUtf8(gnsdk_csharp_marshalPINVOKE.GnVideoProduct_PackageLanguage_get(swigCPtr) );
	} 

  }

/**
*	Video production type value, e.g., Documentary
*  <p><b>Remarks:</b></p>
*  This is a list-based value requiring that a list or locale be loaded into memory.
*
*  To render locale-dependent information for list-based values, your application must allocate a
*  <code>GnLocale</code> object. A <code>LocaleNotLoaded</code> message is returned when locale information
*  is not set prior to a request for a list-based value.
*	@ingroup GDO_ValueKeys_Video
*/
  public string VideoProductionType {
	get
	{   
		/* csvarout typemap code */
		return GnMarshalUTF8.StringFromNativeUtf8(gnsdk_csharp_marshalPINVOKE.GnVideoProduct_VideoProductionType_get(swigCPtr) );
	} 

  }

/**
*	Video production type identifier value
*	@ingroup GDO_ValueKeys_Video
*/
  public uint VideoProductionTypeId {
    get {
      uint ret = gnsdk_csharp_marshalPINVOKE.GnVideoProduct_VideoProductionTypeId_get(swigCPtr);
      return ret;
    } 
  }

/**
*	Original release date in UTC format.
*	@ingroup GDO_ValueKeys_Video
*/
  public string DateOriginalRelease {
	get
	{   
		/* csvarout typemap code */
		return GnMarshalUTF8.StringFromNativeUtf8(gnsdk_csharp_marshalPINVOKE.GnVideoProduct_DateOriginalRelease_get(swigCPtr) );
	} 

  }

/**
*	Release date in UTC format
*	<p><b>Remarks:</b></p>
*	Release date values are not always available.
*	@ingroup GDO_ValueKeys_Video
*/
  public string DateRelease {
	get
	{   
		/* csvarout typemap code */
		return GnMarshalUTF8.StringFromNativeUtf8(gnsdk_csharp_marshalPINVOKE.GnVideoProduct_DateRelease_get(swigCPtr) );
	} 

  }

/**
*	Duration value in seconds, such as "3600" for a 60-minute program.
*	@ingroup GDO_ValueKeys_Video
*/
  public uint Duration {
    get {
      uint ret = gnsdk_csharp_marshalPINVOKE.GnVideoProduct_Duration_get(swigCPtr);
      return ret;
    } 
  }

/**
*	Duration units value (seconds, "SEC").
*	@ingroup GDO_ValueKeys_Video
*/
  public string DurationUnits {
	get
	{   
		/* csvarout typemap code */
		return GnMarshalUTF8.StringFromNativeUtf8(gnsdk_csharp_marshalPINVOKE.GnVideoProduct_DurationUnits_get(swigCPtr) );
	} 

  }

/**
*	Aspect ratio- describes the proportional relationship between the video's width and its height
* expressed as two numbers separated by a colon
*	@ingroup GDO_ValueKeys_Video
*/
  public string AspectRatio {
	get
	{   
		/* csvarout typemap code */
		return GnMarshalUTF8.StringFromNativeUtf8(gnsdk_csharp_marshalPINVOKE.GnVideoProduct_AspectRatio_get(swigCPtr) );
	} 

  }

/**
*	Aspect ratio type, e.g., Standard
*	@ingroup GDO_ValueKeys_Video
*/
  public string AspectRatioType {
	get
	{   
		/* csvarout typemap code */
		return GnMarshalUTF8.StringFromNativeUtf8(gnsdk_csharp_marshalPINVOKE.GnVideoProduct_AspectRatioType_get(swigCPtr) );
	} 

  }

/**
*	Video product region value, e.g, 1
*  <p><b>Remarks:</b></p>
*  This is a list-based value requiring that a list or locale be loaded into memory.
*
*  To render locale-dependent information for list-based values, your application must allocate a
*  <code>GnLocale</code> object. A <code>LocaleNotLoaded</code> message is returned when locale information
*  is not set prior to a request for a list-based value.
*	@ingroup GDO_ValueKeys_Video
*/
  public string VideoRegion {
	get
	{   
		/* csvarout typemap code */
		return GnMarshalUTF8.StringFromNativeUtf8(gnsdk_csharp_marshalPINVOKE.GnVideoProduct_VideoRegion_get(swigCPtr) );
	} 

  }

/**
*	Video product region description, e.g., USA, Canada, US Territories, Bermuda, and Cayman Islands
*  <p><b>Remarks:</b></p>
*  This is a list-based value requiring that a list or locale be loaded into memory.
*
*  To render locale-dependent information for list-based values, your application must allocate a
*  <code>GnLocale</code> object. A <code>LocaleNotLoaded</code> message is returned when locale information
*  is not set prior to a request for a list-based value.
*	@ingroup GDO_ValueKeys_Video
*/
  public string VideoRegionDesc {
	get
	{   
		/* csvarout typemap code */
		return GnMarshalUTF8.StringFromNativeUtf8(gnsdk_csharp_marshalPINVOKE.GnVideoProduct_VideoRegionDesc_get(swigCPtr) );
	} 

  }

/**
*	Notes
*	@ingroup GDO_ValueKeys_Video
*/
  public string Notes {
	get
	{   
		/* csvarout typemap code */
		return GnMarshalUTF8.StringFromNativeUtf8(gnsdk_csharp_marshalPINVOKE.GnVideoProduct_Notes_get(swigCPtr) );
	} 

  }

/**
*	Commerce type value
*	<p><b>Remarks:</b></p>
*	For information on the specific values this key retrieves, contact your Gracenote Support
*	Services representative.
*	@ingroup GDO_ValueKeys_Video
*/
  public string CommerceType {
	get
	{   
		/* csvarout typemap code */
		return GnMarshalUTF8.StringFromNativeUtf8(gnsdk_csharp_marshalPINVOKE.GnVideoProduct_CommerceType_get(swigCPtr) );
	} 

  }

/**
*  Flag indicating if response result contains full (true) or partial metadata
*	<p><b>Remarks:</b></p>
*	Available for the following music and video types:
*  <ul>
*  <li>Album
*  <li>Contributor
*  <li>Track
*  <li>Product
*  <li>Season
*  <li>Series
*  <li>Work
*  </ul>
*	<p><b>Note:</b></p>
*   What constitutes a full result varies among the individual response types and results, and also
*	depends on data availability.
*	@ingroup GDO_ValueKeys_Misc
*/
  public bool IsFullResult {
    get {
      bool ret = gnsdk_csharp_marshalPINVOKE.GnVideoProduct_IsFullResult_get(swigCPtr);
      return ret;
    } 
  }

/**
*	Official child title object
*	@ingroup GDO_ChildKeys_Title
*/
  public GnTitle OfficialTitle {
    get {
      IntPtr cPtr = gnsdk_csharp_marshalPINVOKE.GnVideoProduct_OfficialTitle_get(swigCPtr);
      GnTitle ret = (cPtr == IntPtr.Zero) ? null : new GnTitle(cPtr, true);
      return ret;
    } 
  }

/**
* Rating object.
* @ingroup GDO_ValueKeys_Misc
*/
  public GnRating Rating {
    get {
      IntPtr cPtr = gnsdk_csharp_marshalPINVOKE.GnVideoProduct_Rating_get(swigCPtr);
      GnRating ret = (cPtr == IntPtr.Zero) ? null : new GnRating(cPtr, true);
      return ret;
    } 
  }

  public GnExternalIdEnumerable ExternalIds {
    get {
      IntPtr cPtr = gnsdk_csharp_marshalPINVOKE.GnVideoProduct_ExternalIds_get(swigCPtr);
      GnExternalIdEnumerable ret = (cPtr == IntPtr.Zero) ? null : new GnExternalIdEnumerable(cPtr, true);
      return ret;
    } 
  }

  public GnVideoDiscEnumerable Discs {
    get {
      IntPtr cPtr = gnsdk_csharp_marshalPINVOKE.GnVideoProduct_Discs_get(swigCPtr);
      GnVideoDiscEnumerable ret = (cPtr == IntPtr.Zero) ? null : new GnVideoDiscEnumerable(cPtr, true);
      return ret;
    } 
  }

}

}
