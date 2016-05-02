
namespace GracenoteSDK {

using System;
using System.Runtime.InteropServices;

/**
* \class GnVideoSeries
*/
public class GnVideoSeries : GnDataObject {
  private HandleRef swigCPtr;

  internal GnVideoSeries(IntPtr cPtr, bool cMemoryOwn) : base(gnsdk_csharp_marshalPINVOKE.GnVideoSeries_SWIGUpcast(cPtr), cMemoryOwn) {
    swigCPtr = new HandleRef(this, cPtr);
  }

  internal static HandleRef getCPtr(GnVideoSeries obj) {
    return (obj == null) ? new HandleRef(null, IntPtr.Zero) : obj.swigCPtr;
  }

  ~GnVideoSeries() {
    Dispose();
  }

  public override void Dispose() {
    lock(this) {
      if (swigCPtr.Handle != IntPtr.Zero) {
        if (swigCMemOwn) {
          swigCMemOwn = false;
          gnsdk_csharp_marshalPINVOKE.delete_GnVideoSeries(swigCPtr);
        }
        swigCPtr = new HandleRef(null, IntPtr.Zero);
      }
      GC.SuppressFinalize(this);
      base.Dispose();
    }
  }

  public GnVideoSeries(string id, string idTag) : this(gnsdk_csharp_marshalPINVOKE.new_GnVideoSeries(id, idTag), true) {
    if (gnsdk_csharp_marshalPINVOKE.SWIGPendingException.Pending) throw gnsdk_csharp_marshalPINVOKE.SWIGPendingException.Retrieve();
  }

/**
*  Genre, e.g., Comedy. This ia a list/locale dependent, multi-level object.
*  <p><b>Remarks:</b></p>
*  This is a list-based value requiring that a list or locale be loaded into memory.
*
*  To render locale-dependent information for list-based values, the application must allocate a
*  <code>GnLocale</code> object. A <code>LocaleNotLoaded</code> message is returned when locale information
*  is not set prior to a request for a list-based value.
* @ingroup GDO_ValueKeys_Misc
*/
  public string Genre(GnDataLevel level) {
    string ret = gnsdk_csharp_marshalPINVOKE.GnVideoSeries_Genre(swigCPtr, (int)level);
    return ret;
  }

/**
*  Geographic location, e.g., "New York City". This is a list/locale dependent, multi-level field.
*  <p><b>Remarks:</b></p>
*  This is a list-based value requiring that a list or locale be loaded into memory.
*
*  To render locale-dependent information for list-based values, the application must allocate a
*  <code>GnLocale</code> object. A <code>LocaleNotLoaded</code> message is returned when locale information
*  is not set prior to a request for a list-based value.
* @ingroup GDO_ValueKeys_Misc
*/
  public string Origin(GnDataLevel level) {
    string ret = gnsdk_csharp_marshalPINVOKE.GnVideoSeries_Origin(swigCPtr, (int)level);
    return ret;
  }

/**
*   Gracenote ID.
* @ingroup GDO_ValueKeys_GracenoteIDs
*/
  public string GnId {
	get
	{   
		/* csvarout typemap code */
		return GnMarshalUTF8.StringFromNativeUtf8(gnsdk_csharp_marshalPINVOKE.GnVideoSeries_GnId_get(swigCPtr) );
	} 

  }

/**
*   Gracenote unique ID.
* @ingroup GDO_ValueKeys_GracenoteIDs
*/
  public string GnUId {
	get
	{   
		/* csvarout typemap code */
		return GnMarshalUTF8.StringFromNativeUtf8(gnsdk_csharp_marshalPINVOKE.GnVideoSeries_GnUId_get(swigCPtr) );
	} 

  }

/**
*  TUI (title unique identifier)
* @ingroup GDO_ValueKeys_GracenoteIDs
*/
  public string Tui {
	get
	{   
		/* csvarout typemap code */
		return GnMarshalUTF8.StringFromNativeUtf8(gnsdk_csharp_marshalPINVOKE.GnVideoSeries_Tui_get(swigCPtr) );
	} 

  }

/**
*  TUI tag
* @ingroup GDO_ValueKeys_GracenoteIDs
*/
  public string TuiTag {
	get
	{   
		/* csvarout typemap code */
		return GnMarshalUTF8.StringFromNativeUtf8(gnsdk_csharp_marshalPINVOKE.GnVideoSeries_TuiTag_get(swigCPtr) );
	} 

  }

/**
*  Product ID, aka Tag ID
*  <p><b>Remarks:</b></p>
*  This value can be stored or transmitted - it is a static identifier for the current content and will not change over time.
* @ingroup GDO_ValueKeys_GracenoteIDs
*/
  public string ProductId {
	get
	{   
		/* csvarout typemap code */
		return GnMarshalUTF8.StringFromNativeUtf8(gnsdk_csharp_marshalPINVOKE.GnVideoSeries_ProductId_get(swigCPtr) );
	} 

  }

/**
*  Production type, e.g., Animation. This is a list/locale dependent field.
*  <p><b>Remarks:</b></p>
*  This is a list-based value requiring that a list or locale be loaded into memory.
*  To render locale-dependent information for list-based values, the application must allocate a
*  <code>GnLocale</code> object. The SDK returns
*  a <code>LocaleNotLoaded</code> message when locale information is not set prior to a request for list-based value
*  information.
* @ingroup GDO_ValueKeys_Video
*/
  public string VideoProductionType {
	get
	{   
		/* csvarout typemap code */
		return GnMarshalUTF8.StringFromNativeUtf8(gnsdk_csharp_marshalPINVOKE.GnVideoSeries_VideoProductionType_get(swigCPtr) );
	} 

  }

/**
*  Production type identifier
* @ingroup GDO_ValueKeys_Video
*/
  public uint VideoProductionTypeId {
    get {
      uint ret = gnsdk_csharp_marshalPINVOKE.GnVideoSeries_VideoProductionTypeId_get(swigCPtr);
      return ret;
    } 
  }

/**
*  Original release date. Available for video Products, Features, and
*  Works.
* @ingroup GDO_ValueKeys_Video
*/
  public string DateOriginalRelease {
	get
	{   
		/* csvarout typemap code */
		return GnMarshalUTF8.StringFromNativeUtf8(gnsdk_csharp_marshalPINVOKE.GnVideoSeries_DateOriginalRelease_get(swigCPtr) );
	} 

  }

/**
*  Duration value such as "3600" (seconds) for a 60-minute
*  program. Available for video Chapters, Features, Products, Seasons, Series, and Works.
* @ingroup GDO_ValueKeys_Video
*/
  public uint Duration {
    get {
      uint ret = gnsdk_csharp_marshalPINVOKE.GnVideoSeries_Duration_get(swigCPtr);
      return ret;
    } 
  }

/**
*  Duration units type (seconds, "SEC"). Available for video
*  Chapters, Features, Products, Seasons, Series, and Works.
* @ingroup GDO_ValueKeys_Video
*/
  public string DurationUnits {
	get
	{   
		/* csvarout typemap code */
		return GnMarshalUTF8.StringFromNativeUtf8(gnsdk_csharp_marshalPINVOKE.GnVideoSeries_DurationUnits_get(swigCPtr) );
	} 

  }

/**
*  Franchise number.
* @ingroup GDO_ValueKeys_Video
*/
  public uint FranchiseNum {
    get {
      uint ret = gnsdk_csharp_marshalPINVOKE.GnVideoSeries_FranchiseNum_get(swigCPtr);
      return ret;
    } 
  }

/**
*  Franchise count.
* @ingroup GDO_ValueKeys_Video
*/
  public uint FranchiseCount {
    get {
      uint ret = gnsdk_csharp_marshalPINVOKE.GnVideoSeries_FranchiseCount_get(swigCPtr);
      return ret;
    } 
  }

/**
*  Plot synopsis, e.g., "A semi-autobiographical coming-of-age story"
* @ingroup GDO_ValueKeys_Video
*/
  public string PlotSynopsis {
	get
	{   
		/* csvarout typemap code */
		return GnMarshalUTF8.StringFromNativeUtf8(gnsdk_csharp_marshalPINVOKE.GnVideoSeries_PlotSynopsis_get(swigCPtr) );
	} 

  }

/**
*  Plot tagline, e.g., "If you forgot what terror was like...its back"
* @ingroup GDO_ValueKeys_Video
*/
  public string PlotTagline {
	get
	{   
		/* csvarout typemap code */
		return GnMarshalUTF8.StringFromNativeUtf8(gnsdk_csharp_marshalPINVOKE.GnVideoSeries_PlotTagline_get(swigCPtr) );
	} 

  }

/**
*  Plot synopsis language, e.g., English
*  <p><b>Remarks:</b></p>
*  The language depends on availability: information in the language set
*  for the locale may not be available, and the object's information may be available only in its
*  default official language. For example, if a locale's set language is Spanish, but the object's
*  information is available only in English, this value returns as English.
* @ingroup GDO_ValueKeys_Video
*/
  public string PlotSynopsisLanguage {
	get
	{   
		/* csvarout typemap code */
		return GnMarshalUTF8.StringFromNativeUtf8(gnsdk_csharp_marshalPINVOKE.GnVideoSeries_PlotSynopsisLanguage_get(swigCPtr) );
	} 

  }

/**
*  Video serial type, e.g., Episode.
*  <p><b>Remarks:</b></p>
*  This is a list-based value requiring that a list or locale be loaded into memory
*  To render locale-dependent information for list-based values, the application must allocate a
*  <code>GnLocale</code> objec. The SDK returns
*  a <code>LocaleNotLoaded</code> message when locale information is not set prior to a request for a list-based value
* @ingroup GDO_ValueKeys_Video
*/
  public string SerialType {
	get
	{   
		/* csvarout typemap code */
		return GnMarshalUTF8.StringFromNativeUtf8(gnsdk_csharp_marshalPINVOKE.GnVideoSeries_SerialType_get(swigCPtr) );
	} 

  }

/**
*  Work type, e.g., Musical
*  <p><b>Remarks:</b></p>
*  This is a list-based value requiring that the list be loaded into memory through a successful
*  call to gnsdk_manager_locale_load.
*
*  To render locale-dependent information for list-based values, the application must call
*  <code>gnsdk_manager_locale_load</code> and possibly also <code>gnsdk_sdkmanager_gdo_set_locale</code>. The application returns
*  a <code>LocaleNotLoaded</code> message when locale information is not set prior to a request for list-based value
*  information.
* @ingroup GDO_ValueKeys_Video
*/
  public string WorkType {
	get
	{   
		/* csvarout typemap code */
		return GnMarshalUTF8.StringFromNativeUtf8(gnsdk_csharp_marshalPINVOKE.GnVideoSeries_WorkType_get(swigCPtr) );
	} 

  }

/**
*  Audience, e.g., "Young Adult"
*  <p><b>Remarks:</b></p>
*  This is a list-based value requiring that a list or locale be loaded into memory.
*  To render locale-dependent information for list-based values, the application must allocate a
*  <code>GnLocale</code> object. A <code>LocaleNotLoaded</code> message is returned when locale information
*  is not set prior to a request for a list-based value.
* @ingroup GDO_ValueKeys_Video
*/
  public string Audience {
	get
	{   
		/* csvarout typemap code */
		return GnMarshalUTF8.StringFromNativeUtf8(gnsdk_csharp_marshalPINVOKE.GnVideoSeries_Audience_get(swigCPtr) );
	} 

  }

/**
*  Video mood, e.g., Somber
*  <p><b>Remarks:</b></p>
*  Mood information for music and video, depending on the respective calling type.
* @ingroup GDO_ValueKeys_Music
*/
  public string VideoMood {
	get
	{   
		/* csvarout typemap code */
		return GnMarshalUTF8.StringFromNativeUtf8(gnsdk_csharp_marshalPINVOKE.GnVideoSeries_VideoMood_get(swigCPtr) );
	} 

  }

/**
*  Story type, e.g., "Love Story"
*  <p><b>Remarks:</b></p>
*  This is a list-based value requiring that a list or locale be loaded into memory.
*
*  To render locale-dependent information for list-based values, the application must allocate a
*  <code>GnLocale</code> object. A <code>LocaleNotLoaded</code> message is returned when locale information
*  is not set prior to a request for a list-based value.
* @ingroup GDO_ValueKeys_Video
*/
  public string StoryType {
	get
	{   
		/* csvarout typemap code */
		return GnMarshalUTF8.StringFromNativeUtf8(gnsdk_csharp_marshalPINVOKE.GnVideoSeries_StoryType_get(swigCPtr) );
	} 

  }

/**
*  Reputation, e.g., Cult
*  <p><b>Remarks:</b></p>
*  This is a list-based value requiring that a list or locale be loaded into memory.
*
*  To render locale-dependent information for list-based values, the application must allocate a
*  <code>GnLocale</code> object. A <code>LocaleNotLoaded</code> message is returned when locale information
*  is not set prior to a request for a list-based value.
* @ingroup GDO_ValueKeys_Video
*/
  public string Reputation {
	get
	{   
		/* csvarout typemap code */
		return GnMarshalUTF8.StringFromNativeUtf8(gnsdk_csharp_marshalPINVOKE.GnVideoSeries_Reputation_get(swigCPtr) );
	} 

  }

/**
*  Scenario, e.g., Drama
*  <p><b>Remarks:</b></p>
*  This is a list-based value requiring that the list be loaded into memory through a successful
*  call to gnsdk_manager_locale_load.
*
*  To render locale-dependent information for list-based values, the application must call
*  <code>gnsdk_manager_locale_load</code> and possibly also <code>gnsdk_sdkmanager_gdo_set_locale</code>. The application returns
*  a <code>LocaleNotLoaded</code> message when locale information is not set prior to a request for list-based value
*  information.
* @ingroup GDO_ValueKeys_Video
*/
  public string Scenario {
	get
	{   
		/* csvarout typemap code */
		return GnMarshalUTF8.StringFromNativeUtf8(gnsdk_csharp_marshalPINVOKE.GnVideoSeries_Scenario_get(swigCPtr) );
	} 

  }

/**
*  Setting environment, e.g., Skyscraper.
*  <p><b>Remarks:</b></p>
*  This is a list-based value requiring that a list or locale be loaded into memory.
*
*  To render locale-dependent information for list-based values, the application must allocate a
*  <code>GnLocale</code> object. A <code>LocaleNotLoaded</code> message is returned when locale information
*  is not set prior to a request for a list-based value.
* @ingroup GDO_ValueKeys_Video
*/
  public string SettingEnvironment {
	get
	{   
		/* csvarout typemap code */
		return GnMarshalUTF8.StringFromNativeUtf8(gnsdk_csharp_marshalPINVOKE.GnVideoSeries_SettingEnvironment_get(swigCPtr) );
	} 

  }

/**
*  Historical time period such as "Elizabethan Era, 1558-1603"
* @ingroup GDO_ValueKeys_Video
*/
  public string SettingTimePeriod {
	get
	{   
		/* csvarout typemap code */
		return GnMarshalUTF8.StringFromNativeUtf8(gnsdk_csharp_marshalPINVOKE.GnVideoSeries_SettingTimePeriod_get(swigCPtr) );
	} 

  }

/**
*  Source, e.g., "Phillip K. Dick short story".
*  <p><b>Remarks:</b></p>
*  This is a list-based value requiring that a list or locale be loaded into memory.
*
*  To render locale-dependent information for list-based values, the application must allocate a
*  <code>GnLocale</code> object. A <code>LocaleNotLoaded</code> message is returned when locale information
*  is not set prior to a request for a list-based value.
* @ingroup GDO_ValueKeys_Video
*/
  public string Source {
	get
	{   
		/* csvarout typemap code */
		return GnMarshalUTF8.StringFromNativeUtf8(gnsdk_csharp_marshalPINVOKE.GnVideoSeries_Source_get(swigCPtr) );
	} 

  }

/**
*  Style, such as "Film Noir"
*  <p><b>Remarks:</b></p>
*  This is a list-based value requiring that a list or locale be loaded into memory.
*
*  To render locale-dependent information for list-based values, the application must allocate a
*  <code>GnLocale</code> object. A <code>LocaleNotLoaded</code> message is returned when locale information
*  is not set prior to a request for a list-based value.
* @ingroup GDO_ValueKeys_Video
*/
  public string Style {
	get
	{   
		/* csvarout typemap code */
		return GnMarshalUTF8.StringFromNativeUtf8(gnsdk_csharp_marshalPINVOKE.GnVideoSeries_Style_get(swigCPtr) );
	} 

  }

/**
*  Topic, such as Racing
*  <p><b>Remarks:</b></p>
*  This is a list-based value requiring that a list or locale be loaded into memory.
*
*  To render locale-dependent information for list-based values, the application must allocate a
*  <code>GnLocale</code> object. A <code>LocaleNotLoaded</code> message is returned when locale information
*  is not set prior to a request for a list-based value.
* @ingroup GDO_ValueKeys_Video
*/
  public string Topic {
	get
	{   
		/* csvarout typemap code */
		return GnMarshalUTF8.StringFromNativeUtf8(gnsdk_csharp_marshalPINVOKE.GnVideoSeries_Topic_get(swigCPtr) );
	} 

  }

/**
*  Flag indicating if response result contains full (true) or partial metadata.
* <p><b>Note:</b></p>
*  What constitutes a full result varies among responses and results and also
*  depends on data availability.
* @ingroup GDO_ValueKeys_Misc
*/
  public bool IsFullResult {
    get {
      bool ret = gnsdk_csharp_marshalPINVOKE.GnVideoSeries_IsFullResult_get(swigCPtr);
      return ret;
    } 
  }

/**
*  Rating object
* @ingroup GDO_ValueKeys_Misc
*/
  public GnRating Rating {
    get {
      IntPtr cPtr = gnsdk_csharp_marshalPINVOKE.GnVideoSeries_Rating_get(swigCPtr);
      GnRating ret = (cPtr == IntPtr.Zero) ? null : new GnRating(cPtr, true);
      return ret;
    } 
  }

/**
* Official title object
* @ingroup GDO_ChildKeys_Title
*/
  public GnTitle OfficialTitle {
    get {
      IntPtr cPtr = gnsdk_csharp_marshalPINVOKE.GnVideoSeries_OfficialTitle_get(swigCPtr);
      GnTitle ret = (cPtr == IntPtr.Zero) ? null : new GnTitle(cPtr, true);
      return ret;
    } 
  }

/**
*   Franchise title object.
* @ingroup GDO_ChildKeys_Title
*/
  public GnTitle FranchiseTitle {
    get {
      IntPtr cPtr = gnsdk_csharp_marshalPINVOKE.GnVideoSeries_FranchiseTitle_get(swigCPtr);
      GnTitle ret = (cPtr == IntPtr.Zero) ? null : new GnTitle(cPtr, true);
      return ret;
    } 
  }

  public GnExternalIdEnumerable ExternalIds {
    get {
      IntPtr cPtr = gnsdk_csharp_marshalPINVOKE.GnVideoSeries_ExternalIds_get(swigCPtr);
      GnExternalIdEnumerable ret = (cPtr == IntPtr.Zero) ? null : new GnExternalIdEnumerable(cPtr, true);
      return ret;
    } 
  }

  public GnVideoWorkEnumerable Works {
    get {
      IntPtr cPtr = gnsdk_csharp_marshalPINVOKE.GnVideoSeries_Works_get(swigCPtr);
      GnVideoWorkEnumerable ret = (cPtr == IntPtr.Zero) ? null : new GnVideoWorkEnumerable(cPtr, true);
      return ret;
    } 
  }

  public GnVideoProductEnumerable Products {
    get {
      IntPtr cPtr = gnsdk_csharp_marshalPINVOKE.GnVideoSeries_Products_get(swigCPtr);
      GnVideoProductEnumerable ret = (cPtr == IntPtr.Zero) ? null : new GnVideoProductEnumerable(cPtr, true);
      return ret;
    } 
  }

  public GnVideoCreditEnumerable VideoCredits {
    get {
      IntPtr cPtr = gnsdk_csharp_marshalPINVOKE.GnVideoSeries_VideoCredits_get(swigCPtr);
      GnVideoCreditEnumerable ret = (cPtr == IntPtr.Zero) ? null : new GnVideoCreditEnumerable(cPtr, true);
      return ret;
    } 
  }

  public GnVideoSeasonEnumerable Seasons {
    get {
      IntPtr cPtr = gnsdk_csharp_marshalPINVOKE.GnVideoSeries_Seasons_get(swigCPtr);
      GnVideoSeasonEnumerable ret = (cPtr == IntPtr.Zero) ? null : new GnVideoSeasonEnumerable(cPtr, true);
      return ret;
    } 
  }

  public GnContentEnumerable Contents {
    get {
      IntPtr cPtr = gnsdk_csharp_marshalPINVOKE.GnVideoSeries_Contents_get(swigCPtr);
      GnContentEnumerable ret = (cPtr == IntPtr.Zero) ? null : new GnContentEnumerable(cPtr, true);
      return ret;
    } 
  }

}

}
