
namespace GracenoteSDK {

using System;
using System.Runtime.InteropServices;

/**
* \class GnVideoWork
*/
public class GnVideoWork : GnDataObject {
  private HandleRef swigCPtr;

  internal GnVideoWork(IntPtr cPtr, bool cMemoryOwn) : base(gnsdk_csharp_marshalPINVOKE.GnVideoWork_SWIGUpcast(cPtr), cMemoryOwn) {
    swigCPtr = new HandleRef(this, cPtr);
  }

  internal static HandleRef getCPtr(GnVideoWork obj) {
    return (obj == null) ? new HandleRef(null, IntPtr.Zero) : obj.swigCPtr;
  }

  ~GnVideoWork() {
    Dispose();
  }

  public override void Dispose() {
    lock(this) {
      if (swigCPtr.Handle != IntPtr.Zero) {
        if (swigCMemOwn) {
          swigCMemOwn = false;
          gnsdk_csharp_marshalPINVOKE.delete_GnVideoWork(swigCPtr);
        }
        swigCPtr = new HandleRef(null, IntPtr.Zero);
      }
      GC.SuppressFinalize(this);
      base.Dispose();
    }
  }

  public static string GnType() {
    string ret = gnsdk_csharp_marshalPINVOKE.GnVideoWork_GnType();
    return ret;
  }

  public static GnVideoWork From(GnDataObject obj) {
    GnVideoWork ret = new GnVideoWork(gnsdk_csharp_marshalPINVOKE.GnVideoWork_From(GnDataObject.getCPtr(obj)), true);
    if (gnsdk_csharp_marshalPINVOKE.SWIGPendingException.Pending) throw gnsdk_csharp_marshalPINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

  public GnVideoWork(string id, string idTag) : this(gnsdk_csharp_marshalPINVOKE.new_GnVideoWork(id, idTag), true) {
    if (gnsdk_csharp_marshalPINVOKE.SWIGPendingException.Pending) throw gnsdk_csharp_marshalPINVOKE.SWIGPendingException.Retrieve();
  }

/**
*  Geographic location, e.g., "New York City". This is a list/locale dependent, multi-level field.
*  <p><b>Remarks:</b></p>
*  This is a list-based value requiring that the list be loaded into memory through a successful
*  call to gnsdk_manager_locale_load.
*
*  To render locale-dependent information for list-based values, the application must call
*  <code>gnsdk_manager_locale_load</code> and possibly also <code>gnsdk_sdkmanager_gdo_set_locale</code>. The application returns
*  a <code>LocaleNotLoaded</code> message when locale information is not set prior to a request for list-based value
*  information.
* @ingroup GDO_ValueKeys_Misc
*/
  public string Origin(GnDataLevel level) {
    string ret = gnsdk_csharp_marshalPINVOKE.GnVideoWork_Origin(swigCPtr, (int)level);
    return ret;
  }

/**
* Genre - e.g., comedy. This is a list/locale dependent, multi-level field.
*
*  <p><b>Remarks:</b></p>
*  This is a list-based value requiring that a list or locale be loaded into memory.
*
*  To render locale-dependent information for list-based values, the application must allocate a
*  <code>GnLocale</code> object. A <code>LocaleNotLoaded</code> message is returned when locale information
*  is not set prior to a request for a list-based value.
*
*  This is a multi-level field requiring a <code>GnDataLevel</code> parameter
* @ingroup GDO_ValueKeys_Misc
*/
  public string Genre(GnDataLevel level) {
    string ret = gnsdk_csharp_marshalPINVOKE.GnVideoWork_Genre(swigCPtr, (int)level);
    return ret;
  }

/**
*  Rating object
* @ingroup GDO_ValueKeys_Misc
*/
  public GnRating Rating() {
    GnRating ret = new GnRating(gnsdk_csharp_marshalPINVOKE.GnVideoWork_Rating(swigCPtr), true);
    return ret;
  }

  public GnVideoProductEnumerable Products() {
    GnVideoProductEnumerable ret = new GnVideoProductEnumerable(gnsdk_csharp_marshalPINVOKE.GnVideoWork_Products(swigCPtr), true);
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
		return GnMarshalUTF8.StringFromNativeUtf8(gnsdk_csharp_marshalPINVOKE.GnVideoWork_GnId_get(swigCPtr) );
	} 

  }

/**
*   Gracenote unique identifier
* @ingroup GDO_ValueKeys_GracenoteIDs
*/
  public string GnUId {
	get
	{   
		/* csvarout typemap code */
		return GnMarshalUTF8.StringFromNativeUtf8(gnsdk_csharp_marshalPINVOKE.GnVideoWork_GnUId_get(swigCPtr) );
	} 

  }

/**
*  Product ID aka Tag ID
*  <p><b>Remarks:</b></p>
*  This value which can be stored or transmitted - it can be used as a static identifier for the current
*  content and will not change over time.
* @ingroup GDO_ValueKeys_GracenoteIDs
*/
  public string ProductId {
	get
	{   
		/* csvarout typemap code */
		return GnMarshalUTF8.StringFromNativeUtf8(gnsdk_csharp_marshalPINVOKE.GnVideoWork_ProductId_get(swigCPtr) );
	} 

  }

/**
*  TUI (title-unique identifier)
* @ingroup GDO_ValueKeys_GracenoteIDs
*/
  public string Tui {
	get
	{   
		/* csvarout typemap code */
		return GnMarshalUTF8.StringFromNativeUtf8(gnsdk_csharp_marshalPINVOKE.GnVideoWork_Tui_get(swigCPtr) );
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
		return GnMarshalUTF8.StringFromNativeUtf8(gnsdk_csharp_marshalPINVOKE.GnVideoWork_TuiTag_get(swigCPtr) );
	} 

  }

/**
*  Second TUI, if it exists. This TUI is used
*   for matching partial Products objects to full Works objects.
*  Use this value to ensure correct Tui value matching for cases when a video Product GDO contains
*  multiple partial Work GDOs. Each partial Work GDO corresponds
*  to a full Works object, and each full Works object contains the GNSDK_GDO_VALUE_TUI value,
*  incremented by one digit to maintain data integrity with Gracenote Service.
*  The GNSDK_GDO_VALUE_TUI_MATCH_PRODUCT maps the partial Works object Tui value to the full Works
*   object.
* @ingroup GDO_ValueKeys_GracenoteIDs
*/
  public string TuiMatchProduct {
    get {
      string ret = gnsdk_csharp_marshalPINVOKE.GnVideoWork_TuiMatchProduct_get(swigCPtr);
      return ret;
    } 
  }

/**
*  Video production type, e.g., Animation. This is a list/locale dependent value.
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
		return GnMarshalUTF8.StringFromNativeUtf8(gnsdk_csharp_marshalPINVOKE.GnVideoWork_VideoProductionType_get(swigCPtr) );
	} 

  }

/**
*  Video production type ID
* @ingroup GDO_ValueKeys_Video
*/
  public uint VideoProductionTypeId {
    get {
      uint ret = gnsdk_csharp_marshalPINVOKE.GnVideoWork_VideoProductionTypeId_get(swigCPtr);
      return ret;
    } 
  }

/**
*  Video's original release date.
* @ingroup GDO_ValueKeys_Video
*/
  public string DateOriginalRelease {
	get
	{   
		/* csvarout typemap code */
		return GnMarshalUTF8.StringFromNativeUtf8(gnsdk_csharp_marshalPINVOKE.GnVideoWork_DateOriginalRelease_get(swigCPtr) );
	} 

  }

/**
*  Duration value in seconds such as "3600" (seconds) for a 60-minute program.
* @ingroup GDO_ValueKeys_Video
*/
  public uint Duration {
    get {
      uint ret = gnsdk_csharp_marshalPINVOKE.GnVideoWork_Duration_get(swigCPtr);
      return ret;
    } 
  }

/**
*  Duration units value (seconds, "SEC").
* @ingroup GDO_ValueKeys_Video
*/
  public string DurationUnits {
	get
	{   
		/* csvarout typemap code */
		return GnMarshalUTF8.StringFromNativeUtf8(gnsdk_csharp_marshalPINVOKE.GnVideoWork_DurationUnits_get(swigCPtr) );
	} 

  }

/**
*  Franchise number
* @ingroup GDO_ValueKeys_Video
*/
  public uint FranchiseNum {
    get {
      uint ret = gnsdk_csharp_marshalPINVOKE.GnVideoWork_FranchiseNum_get(swigCPtr);
      return ret;
    } 
  }

/**
* Franchise count
* @ingroup GDO_ValueKeys_Video
*/
  public uint FranchiseCount {
    get {
      uint ret = gnsdk_csharp_marshalPINVOKE.GnVideoWork_FranchiseCount_get(swigCPtr);
      return ret;
    } 
  }

/**
*  Series episode value
* @ingroup GDO_ValueKeys_Video
*/
  public uint SeriesEpisode {
    get {
      uint ret = gnsdk_csharp_marshalPINVOKE.GnVideoWork_SeriesEpisode_get(swigCPtr);
      return ret;
    } 
  }

/**
*  Series episode count
* @ingroup GDO_ValueKeys_Video
*/
  public uint SeriesEpisodeCount {
    get {
      uint ret = gnsdk_csharp_marshalPINVOKE.GnVideoWork_SeriesEpisodeCount_get(swigCPtr);
      return ret;
    } 
  }

/**
*  Season episode value.
* @ingroup GDO_ValueKeys_Video
*/
  public uint SeasonEpisode {
    get {
      uint ret = gnsdk_csharp_marshalPINVOKE.GnVideoWork_SeasonEpisode_get(swigCPtr);
      return ret;
    } 
  }

/**
*  Season episode count
* @ingroup GDO_ValueKeys_Video
*/
  public uint SeasonEpisodeCount {
    get {
      uint ret = gnsdk_csharp_marshalPINVOKE.GnVideoWork_SeasonEpisodeCount_get(swigCPtr);
      return ret;
    } 
  }

/**
*  Season count value
* @ingroup GDO_ValueKeys_Video
*/
  public uint SeasonCount {
    get {
      uint ret = gnsdk_csharp_marshalPINVOKE.GnVideoWork_SeasonCount_get(swigCPtr);
      return ret;
    } 
  }

/**
* Season number value
* @ingroup GDO_ValueKeys_Video
*/
  public uint SeasonNumber {
    get {
      uint ret = gnsdk_csharp_marshalPINVOKE.GnVideoWork_SeasonNumber_get(swigCPtr);
      return ret;
    } 
  }

/**
*  Plot synopsis e.g., "A semi-autobiographical coming-of-age story"
* @ingroup GDO_ValueKeys_Video
*/
  public string PlotSynopsis {
	get
	{   
		/* csvarout typemap code */
		return GnMarshalUTF8.StringFromNativeUtf8(gnsdk_csharp_marshalPINVOKE.GnVideoWork_PlotSynopsis_get(swigCPtr) );
	} 

  }

/**
*  Plot tagline, e.g., "The Third Dimension is Terror"
* @ingroup GDO_ValueKeys_Video
*/
  public string PlotTagline {
	get
	{   
		/* csvarout typemap code */
		return GnMarshalUTF8.StringFromNativeUtf8(gnsdk_csharp_marshalPINVOKE.GnVideoWork_PlotTagline_get(swigCPtr) );
	} 

  }

/**
*  Plot synopis language, e.g., English
*  <p><b>Remarks:</b></p>
*  The language of a returned object depends on availability. Information in the language set
*   for the locale may not be available, and the object's information may be available only in its
*   default official language. For example, if a locale's set language is Spanish, but the object's
*   information is available only in English, this value returns as English.
* @ingroup GDO_ValueKeys_Video
*/
  public string PlotSynopsisLanguage {
	get
	{   
		/* csvarout typemap code */
		return GnMarshalUTF8.StringFromNativeUtf8(gnsdk_csharp_marshalPINVOKE.GnVideoWork_PlotSynopsisLanguage_get(swigCPtr) );
	} 

  }

/**
*  Supported video serial type such as Series or Episode
*  <p><b>Remarks:</b></p>
*  This is a list-based value requiring that a list or locale be loaded into memory.
*
*  To render locale-dependent information for list-based values, the application must allocate a
*  <code>GnLocale</code> object. A <code>LocaleNotLoaded</code> message is returned when locale information
*  is not set prior to a request for a list-based value.
* @ingroup GDO_ValueKeys_Video
*/
  public string SerialType {
	get
	{   
		/* csvarout typemap code */
		return GnMarshalUTF8.StringFromNativeUtf8(gnsdk_csharp_marshalPINVOKE.GnVideoWork_SerialType_get(swigCPtr) );
	} 

  }

/**
*  Work type, e.g., Musical
*  <p><b>Remarks:</b></p>
*  This is a list-based value requiring that the list be loaded into memory through a successful
*  call to gnsdk_manager_locale_load.
*
*  To render locale-dependent information for list-based values, the application must call
*   <code>gnsdk_manager_locale_load</code> and possibly also <code>gnsdk_sdkmanager_gdo_set_locale</code>. The application returns
*   a <code>LocaleNotLoaded</code> message when locale information is not set prior to a request for list-based value
*   information.
* @ingroup GDO_ValueKeys_Video
*/
  public string WorkType {
	get
	{   
		/* csvarout typemap code */
		return GnMarshalUTF8.StringFromNativeUtf8(gnsdk_csharp_marshalPINVOKE.GnVideoWork_WorkType_get(swigCPtr) );
	} 

  }

/**
*  Audience type, e.g.,"Kids and Family", "African-American", or "Young Adult".
*  <p><b>Remarks:</b></p>
*  This is a list-based value requiring that a list or locale be loaded into memory.
*
*  To render locale-dependent information for list-based values, the application must allocate a
*  <code>GnLocale</code> object. A <code>LocaleNotLoaded</code> message is returned when locale information
*  is not set prior to a request for a list-based value.
* @ingroup GDO_ValueKeys_Video
*/
  public string Audience {
	get
	{   
		/* csvarout typemap code */
		return GnMarshalUTF8.StringFromNativeUtf8(gnsdk_csharp_marshalPINVOKE.GnVideoWork_Audience_get(swigCPtr) );
	} 

  }

/**
*  Mood, e.g., Playful
* @ingroup GDO_ValueKeys_Music
*/
  public string VideoMood {
	get
	{   
		/* csvarout typemap code */
		return GnMarshalUTF8.StringFromNativeUtf8(gnsdk_csharp_marshalPINVOKE.GnVideoWork_VideoMood_get(swigCPtr) );
	} 

  }

/**
*  Story type, e.g., "Love Story".
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
		return GnMarshalUTF8.StringFromNativeUtf8(gnsdk_csharp_marshalPINVOKE.GnVideoWork_StoryType_get(swigCPtr) );
	} 

  }

/**
*   Scenario, e.g., "Action", "Comedy", and "Drama".
*  <p><b>Remarks:</b></p>
*  This is a list-based value requiring that a list or locale be loaded into memory.
*
*  To render locale-dependent information for list-based values, the application must allocate a
*  <code>GnLocale</code> object. A <code>LocaleNotLoaded</code> message is returned when locale information
*  is not set prior to a request for a list-based value.
* @ingroup GDO_ValueKeys_Video
*/
  public string Scenario {
	get
	{   
		/* csvarout typemap code */
		return GnMarshalUTF8.StringFromNativeUtf8(gnsdk_csharp_marshalPINVOKE.GnVideoWork_Scenario_get(swigCPtr) );
	} 

  }

/**
*  Physical environment - this is not specific location, but rather a general (or generic)
*  location. For example: Prison, High School, Skyscraper, Desert, etc.
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
		return GnMarshalUTF8.StringFromNativeUtf8(gnsdk_csharp_marshalPINVOKE.GnVideoWork_SettingEnvironment_get(swigCPtr) );
	} 

  }

/**
* Historical time setting, e.g., "Elizabethan Era 1558-1603", or "Jazz Age 1919-1929".
* @ingroup GDO_ValueKeys_Video
*/
  public string SettingTimePeriod {
	get
	{   
		/* csvarout typemap code */
		return GnMarshalUTF8.StringFromNativeUtf8(gnsdk_csharp_marshalPINVOKE.GnVideoWork_SettingTimePeriod_get(swigCPtr) );
	} 

  }

/**
*  Story concept source, e.g., "Fairy Tales and Nursery Rhymes".
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
		return GnMarshalUTF8.StringFromNativeUtf8(gnsdk_csharp_marshalPINVOKE.GnVideoWork_Source_get(swigCPtr) );
	} 

  }

/**
*  Film style, e.g.,  "Film Noir".
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
		return GnMarshalUTF8.StringFromNativeUtf8(gnsdk_csharp_marshalPINVOKE.GnVideoWork_Style_get(swigCPtr) );
	} 

  }

/**
*  Film topic, e.g., "Racing" or "Teen Angst".
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
		return GnMarshalUTF8.StringFromNativeUtf8(gnsdk_csharp_marshalPINVOKE.GnVideoWork_Topic_get(swigCPtr) );
	} 

  }

/**
*  Film's reputation, e.g., "Classic", "Chick Flick", or "Cult". This is a critical or
*  popular "value" that is assigned to a work, usually long after the work was released, though some works may qualify
*  shortly after release (e.g., "instant classic" or "blockbuster release").
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
  public string Reputation {
	get
	{   
		/* csvarout typemap code */
		return GnMarshalUTF8.StringFromNativeUtf8(gnsdk_csharp_marshalPINVOKE.GnVideoWork_Reputation_get(swigCPtr) );
	} 

  }

/**
*  Flag indicating if result contains full (true) or partial metadata.
* <p><b>Note:</b></p>
*  What constitutes a full result varies among response types and results and also
*  depends on data availability.
* @ingroup GDO_ValueKeys_Misc
*/
  public bool IsFullResult {
    get {
      bool ret = gnsdk_csharp_marshalPINVOKE.GnVideoWork_IsFullResult_get(swigCPtr);
      return ret;
    } 
  }

/**
* Official title object
* @ingroup GDO_ChildKeys_Title
*/
  public GnTitle OfficialTitle {
    get {
      IntPtr cPtr = gnsdk_csharp_marshalPINVOKE.GnVideoWork_OfficialTitle_get(swigCPtr);
      GnTitle ret = (cPtr == IntPtr.Zero) ? null : new GnTitle(cPtr, true);
      return ret;
    } 
  }

/**
*  Franchise title object
* @ingroup GDO_ChildKeys_Title
*/
  public GnTitle FranchiseTitle {
    get {
      IntPtr cPtr = gnsdk_csharp_marshalPINVOKE.GnVideoWork_FranchiseTitle_get(swigCPtr);
      GnTitle ret = (cPtr == IntPtr.Zero) ? null : new GnTitle(cPtr, true);
      return ret;
    } 
  }

/**
*  Series title object.
* @ingroup GDO_ChildKeys_Title
*/
  public GnTitle SeriesTitle {
    get {
      IntPtr cPtr = gnsdk_csharp_marshalPINVOKE.GnVideoWork_SeriesTitle_get(swigCPtr);
      GnTitle ret = (cPtr == IntPtr.Zero) ? null : new GnTitle(cPtr, true);
      return ret;
    } 
  }

  public GnExternalIdEnumerable ExternalIds {
    get {
      IntPtr cPtr = gnsdk_csharp_marshalPINVOKE.GnVideoWork_ExternalIds_get(swigCPtr);
      GnExternalIdEnumerable ret = (cPtr == IntPtr.Zero) ? null : new GnExternalIdEnumerable(cPtr, true);
      return ret;
    } 
  }

  public GnVideoCreditEnumerable VideoCredits {
    get {
      IntPtr cPtr = gnsdk_csharp_marshalPINVOKE.GnVideoWork_VideoCredits_get(swigCPtr);
      GnVideoCreditEnumerable ret = (cPtr == IntPtr.Zero) ? null : new GnVideoCreditEnumerable(cPtr, true);
      return ret;
    } 
  }

  public GnVideoSeasonEnumerable Seasons {
    get {
      IntPtr cPtr = gnsdk_csharp_marshalPINVOKE.GnVideoWork_Seasons_get(swigCPtr);
      GnVideoSeasonEnumerable ret = (cPtr == IntPtr.Zero) ? null : new GnVideoSeasonEnumerable(cPtr, true);
      return ret;
    } 
  }

  public GnVideoSeriesEnumerable Series {
    get {
      IntPtr cPtr = gnsdk_csharp_marshalPINVOKE.GnVideoWork_Series_get(swigCPtr);
      GnVideoSeriesEnumerable ret = (cPtr == IntPtr.Zero) ? null : new GnVideoSeriesEnumerable(cPtr, true);
      return ret;
    } 
  }

  public GnContentEnumerable Contents {
    get {
      IntPtr cPtr = gnsdk_csharp_marshalPINVOKE.GnVideoWork_Contents_get(swigCPtr);
      GnContentEnumerable ret = (cPtr == IntPtr.Zero) ? null : new GnContentEnumerable(cPtr, true);
      return ret;
    } 
  }

}

}
