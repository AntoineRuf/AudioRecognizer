
namespace GracenoteSDK {

using System;
using System.Runtime.InteropServices;

/**
* \class GnVideoSeason
*/
public class GnVideoSeason : GnDataObject {
  private HandleRef swigCPtr;

  internal GnVideoSeason(IntPtr cPtr, bool cMemoryOwn) : base(gnsdk_csharp_marshalPINVOKE.GnVideoSeason_SWIGUpcast(cPtr), cMemoryOwn) {
    swigCPtr = new HandleRef(this, cPtr);
  }

  internal static HandleRef getCPtr(GnVideoSeason obj) {
    return (obj == null) ? new HandleRef(null, IntPtr.Zero) : obj.swigCPtr;
  }

  ~GnVideoSeason() {
    Dispose();
  }

  public override void Dispose() {
    lock(this) {
      if (swigCPtr.Handle != IntPtr.Zero) {
        if (swigCMemOwn) {
          swigCMemOwn = false;
          gnsdk_csharp_marshalPINVOKE.delete_GnVideoSeason(swigCPtr);
        }
        swigCPtr = new HandleRef(null, IntPtr.Zero);
      }
      GC.SuppressFinalize(this);
      base.Dispose();
    }
  }

  public static string GnType() {
    string ret = gnsdk_csharp_marshalPINVOKE.GnVideoSeason_GnType();
    return ret;
  }

  public static GnVideoSeason From(GnDataObject obj) {
    GnVideoSeason ret = new GnVideoSeason(gnsdk_csharp_marshalPINVOKE.GnVideoSeason_From(GnDataObject.getCPtr(obj)), true);
    if (gnsdk_csharp_marshalPINVOKE.SWIGPendingException.Pending) throw gnsdk_csharp_marshalPINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

  public GnVideoSeason(string id, string idTag) : this(gnsdk_csharp_marshalPINVOKE.new_GnVideoSeason(id, idTag), true) {
    if (gnsdk_csharp_marshalPINVOKE.SWIGPendingException.Pending) throw gnsdk_csharp_marshalPINVOKE.SWIGPendingException.Retrieve();
  }

/**
*  Genre. This is a list/locale dependent, multi-level field.
*
*  <p><b>Remarks:</b></p>
*  This is a list-based value requiring that the list or locale be loaded into memory through a successful
*  allocation of a <code>GnLocale</code> object
*
*  To render locale-dependent information for list-based values, the application must allocate a GnLocale object.
*  The SDK returns a <code>LocaleNotLoaded</code> message when locale information is not set prior to a request for
*  a list-based value.
* @ingroup GDO_ValueKeys_Misc
*/
  public string Genre(GnDataLevel level) {
    string ret = gnsdk_csharp_marshalPINVOKE.GnVideoSeason_Genre(swigCPtr, (int)level);
    return ret;
  }

/**
*  Origin, e.g., "New York City." List/locale dependent, multi-level field.
*  <p><b>Remarks:</b></p>
*  This is a list-based value requiring that the list or locale be loaded into memory through a successful
*  allocation of a <code>GnLocale</code> object
*
*  To render locale-dependent information for list-based values, the application must allocate a GnLocale object.
*  The SDK returns a <code>LocaleNotLoaded</code> message when locale information is not set prior to a request for
*  a list-based value.
* @ingroup GDO_ValueKeys_Misc
*/
  public string Origin(GnDataLevel level) {
    string ret = gnsdk_csharp_marshalPINVOKE.GnVideoSeason_Origin(swigCPtr, (int)level);
    return ret;
  }

/**
*  Video season's Gracenote identifier.
* @ingroup GDO_ValueKeys_GracenoteIDs
*/
  public string GnId {
	get
	{   
		/* csvarout typemap code */
		return GnMarshalUTF8.StringFromNativeUtf8(gnsdk_csharp_marshalPINVOKE.GnVideoSeason_GnId_get(swigCPtr) );
	} 

  }

/**
*   Video season's Gracenote unique identifier.
* @ingroup GDO_ValueKeys_GracenoteIDs
*/
  public string GnUId {
	get
	{   
		/* csvarout typemap code */
		return GnMarshalUTF8.StringFromNativeUtf8(gnsdk_csharp_marshalPINVOKE.GnVideoSeason_GnUId_get(swigCPtr) );
	} 

  }

/**
*  Video season's TUI (title-unique identifier).
* @ingroup GDO_ValueKeys_GracenoteIDs
*/
  public string Tui {
	get
	{   
		/* csvarout typemap code */
		return GnMarshalUTF8.StringFromNativeUtf8(gnsdk_csharp_marshalPINVOKE.GnVideoSeason_Tui_get(swigCPtr) );
	} 

  }

/**
*  Video season's Tui Tag.
* @ingroup GDO_ValueKeys_GracenoteIDs
*/
  public string TuiTag {
	get
	{   
		/* csvarout typemap code */
		return GnMarshalUTF8.StringFromNativeUtf8(gnsdk_csharp_marshalPINVOKE.GnVideoSeason_TuiTag_get(swigCPtr) );
	} 

  }

/**
*  Video season's product ID (aka Tag ID).
*  <p><b>Remarks:</b></p>
*  Available for most types, this value can be stored or transmitted. Can
*  be used as a static identifier for the current content as it will not change over time.
* @ingroup GDO_ValueKeys_GracenoteIDs
*/
  public string ProductId {
	get
	{   
		/* csvarout typemap code */
		return GnMarshalUTF8.StringFromNativeUtf8(gnsdk_csharp_marshalPINVOKE.GnVideoSeason_ProductId_get(swigCPtr) );
	} 

  }

/**
*  Video production type, e.g., Animation. This is a list/locale dependent value.
*  <p><b>Remarks:</b></p>
*  This is a list-based value requiring that the list or locale be loaded into memory through a successful
*  allocation of a GnLocale object
*
*  To render locale-dependent information for list-based values, the application must allocate a GnLocale object.
*  The SDK returns a <code>LocaleNotLoaded</code> message when locale information is not set prior to a request for
*  a list-based value.
* @ingroup GDO_ValueKeys_Video
*/
  public string VideoProductionType {
	get
	{   
		/* csvarout typemap code */
		return GnMarshalUTF8.StringFromNativeUtf8(gnsdk_csharp_marshalPINVOKE.GnVideoSeason_VideoProductionType_get(swigCPtr) );
	} 

  }

/**
*  Video production type identifier.
* @ingroup GDO_ValueKeys_Video
*/
  public uint VideoProductionTypeId {
    get {
      uint ret = gnsdk_csharp_marshalPINVOKE.GnVideoSeason_VideoProductionTypeId_get(swigCPtr);
      return ret;
    } 
  }

/**
*  Video season's original release date.
* @ingroup GDO_ValueKeys_Video
*/
  public string DateOriginalRelease {
	get
	{   
		/* csvarout typemap code */
		return GnMarshalUTF8.StringFromNativeUtf8(gnsdk_csharp_marshalPINVOKE.GnVideoSeason_DateOriginalRelease_get(swigCPtr) );
	} 

  }

/**
*  Duration in seconds such as "3600" for a 60-minute program.
* @ingroup GDO_ValueKeys_Video
*/
  public uint Duration {
    get {
      uint ret = gnsdk_csharp_marshalPINVOKE.GnVideoSeason_Duration_get(swigCPtr);
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
		return GnMarshalUTF8.StringFromNativeUtf8(gnsdk_csharp_marshalPINVOKE.GnVideoSeason_DurationUnits_get(swigCPtr) );
	} 

  }

/**
*  Franchise number.
* @ingroup GDO_ValueKeys_Video
*/
  public uint FranchiseNum {
    get {
      uint ret = gnsdk_csharp_marshalPINVOKE.GnVideoSeason_FranchiseNum_get(swigCPtr);
      return ret;
    } 
  }

/**
*  Franchise count.
* @ingroup GDO_ValueKeys_Video
*/
  public uint FranchiseCount {
    get {
      uint ret = gnsdk_csharp_marshalPINVOKE.GnVideoSeason_FranchiseCount_get(swigCPtr);
      return ret;
    } 
  }

/**
*  Plot sypnosis, e.g., for Friends episode:."Monica's popularity at a karaoke club might have more to do with her revealing dress than her voice"
* @ingroup GDO_ValueKeys_Video
*/
  public string PlotSynopsis {
	get
	{   
		/* csvarout typemap code */
		return GnMarshalUTF8.StringFromNativeUtf8(gnsdk_csharp_marshalPINVOKE.GnVideoSeason_PlotSynopsis_get(swigCPtr) );
	} 

  }

/**
*  Plot sypnosis language, e.g., English
* @ingroup GDO_ValueKeys_Video
*/
  public string PlotSynopsisLanguage {
	get
	{   
		/* csvarout typemap code */
		return GnMarshalUTF8.StringFromNativeUtf8(gnsdk_csharp_marshalPINVOKE.GnVideoSeason_PlotSynopsisLanguage_get(swigCPtr) );
	} 

  }

/**
*  Plot tagline, e.g., "An adventure as big as life itself."
* @ingroup GDO_ValueKeys_Video
*/
  public string PlotTagline {
	get
	{   
		/* csvarout typemap code */
		return GnMarshalUTF8.StringFromNativeUtf8(gnsdk_csharp_marshalPINVOKE.GnVideoSeason_PlotTagline_get(swigCPtr) );
	} 

  }

/**
*  Serial type, e.g., Series or Episode
* @ingroup GDO_ValueKeys_Video
*/
  public string SerialType {
	get
	{   
		/* csvarout typemap code */
		return GnMarshalUTF8.StringFromNativeUtf8(gnsdk_csharp_marshalPINVOKE.GnVideoSeason_SerialType_get(swigCPtr) );
	} 

  }

/**
*  Work type, e.g., Musical
* @ingroup GDO_ValueKeys_Video
*/
  public string WorkType {
	get
	{   
		/* csvarout typemap code */
		return GnMarshalUTF8.StringFromNativeUtf8(gnsdk_csharp_marshalPINVOKE.GnVideoSeason_WorkType_get(swigCPtr) );
	} 

  }

/**
*  Target audience, e.g., "Kids and Family"
* @ingroup GDO_ValueKeys_Video
*/
  public string Audience {
	get
	{   
		/* csvarout typemap code */
		return GnMarshalUTF8.StringFromNativeUtf8(gnsdk_csharp_marshalPINVOKE.GnVideoSeason_Audience_get(swigCPtr) );
	} 

  }

/**
*  Video mood, e.g., Playful.
* @ingroup GDO_ValueKeys_Video
*/
  public string VideoMood {
	get
	{   
		/* csvarout typemap code */
		return GnMarshalUTF8.StringFromNativeUtf8(gnsdk_csharp_marshalPINVOKE.GnVideoSeason_VideoMood_get(swigCPtr) );
	} 

  }

/**
*  Overall story type, e.g., "Love Story".
* @ingroup GDO_ValueKeys_Video
*/
  public string StoryType {
	get
	{   
		/* csvarout typemap code */
		return GnMarshalUTF8.StringFromNativeUtf8(gnsdk_csharp_marshalPINVOKE.GnVideoSeason_StoryType_get(swigCPtr) );
	} 

  }

/**
*  Reputation, e.g., "Chick flick".
* @ingroup GDO_ValueKeys_Video
*/
  public string Reputation {
	get
	{   
		/* csvarout typemap code */
		return GnMarshalUTF8.StringFromNativeUtf8(gnsdk_csharp_marshalPINVOKE.GnVideoSeason_Reputation_get(swigCPtr) );
	} 

  }

/**
*  Scenario, e.g., Action
* @ingroup GDO_ValueKeys_Video
*/
  public string Scenario {
	get
	{   
		/* csvarout typemap code */
		return GnMarshalUTF8.StringFromNativeUtf8(gnsdk_csharp_marshalPINVOKE.GnVideoSeason_Scenario_get(swigCPtr) );
	} 

  }

/**
*  Setting environment, e.g., "High School"
* @ingroup GDO_ValueKeys_Video
*/
  public string SettingEnvironment {
	get
	{   
		/* csvarout typemap code */
		return GnMarshalUTF8.StringFromNativeUtf8(gnsdk_csharp_marshalPINVOKE.GnVideoSeason_SettingEnvironment_get(swigCPtr) );
	} 

  }

/**
*  Setting time period, e.g., "Jazz Age 1919-1929".
* @ingroup GDO_ValueKeys_Video
*/
  public string SettingTimePeriod {
	get
	{   
		/* csvarout typemap code */
		return GnMarshalUTF8.StringFromNativeUtf8(gnsdk_csharp_marshalPINVOKE.GnVideoSeason_SettingTimePeriod_get(swigCPtr) );
	} 

  }

/**
*  Topic value, e.g., "Teen Angst"
* @ingroup GDO_ValueKeys_Video
*/
  public string Topic {
	get
	{   
		/* csvarout typemap code */
		return GnMarshalUTF8.StringFromNativeUtf8(gnsdk_csharp_marshalPINVOKE.GnVideoSeason_Topic_get(swigCPtr) );
	} 

  }

/**
*  Season number.
* @ingroup GDO_ValueKeys_Video
*/
  public uint SeasonNumber {
    get {
      uint ret = gnsdk_csharp_marshalPINVOKE.GnVideoSeason_SeasonNumber_get(swigCPtr);
      return ret;
    } 
  }

/**
*  Season count - total number of seasons.
* @ingroup GDO_ValueKeys_Video
*/
  public uint SeasonCount {
    get {
      uint ret = gnsdk_csharp_marshalPINVOKE.GnVideoSeason_SeasonCount_get(swigCPtr);
      return ret;
    } 
  }

/**
*  Source, e.g., "Fairy Tales and Nursery Rhymes"
* @ingroup GDO_ValueKeys_Video
*/
  public string Source {
	get
	{   
		/* csvarout typemap code */
		return GnMarshalUTF8.StringFromNativeUtf8(gnsdk_csharp_marshalPINVOKE.GnVideoSeason_Source_get(swigCPtr) );
	} 

  }

/**
*  Style, e.g., "Film Noir"
* @ingroup GDO_ValueKeys_Video
*/
  public string Style {
	get
	{   
		/* csvarout typemap code */
		return GnMarshalUTF8.StringFromNativeUtf8(gnsdk_csharp_marshalPINVOKE.GnVideoSeason_Style_get(swigCPtr) );
	} 

  }

/**
*  Flag indicating if response result contains full (true) or partial metadata.
* <p><b>Note:</b></p>
*   What constitutes a full result varies among response results, and also
*  depends on data availability.
* @ingroup GDO_ValueKeys_Misc
*/
  public bool IsFullResult {
    get {
      bool ret = gnsdk_csharp_marshalPINVOKE.GnVideoSeason_IsFullResult_get(swigCPtr);
      return ret;
    } 
  }

/**
*  Rating object.
* @ingroup GDO_ValueKeys_Misc
*/
  public GnRating Rating {
    get {
      IntPtr cPtr = gnsdk_csharp_marshalPINVOKE.GnVideoSeason_Rating_get(swigCPtr);
      GnRating ret = (cPtr == IntPtr.Zero) ? null : new GnRating(cPtr, true);
      return ret;
    } 
  }

/**
*   Official title object
* @ingroup GDO_ChildKeys_Title
*/
  public GnTitle OfficialTitle {
    get {
      IntPtr cPtr = gnsdk_csharp_marshalPINVOKE.GnVideoSeason_OfficialTitle_get(swigCPtr);
      GnTitle ret = (cPtr == IntPtr.Zero) ? null : new GnTitle(cPtr, true);
      return ret;
    } 
  }

/**
*  Franchise title object.
* @ingroup GDO_ChildKeys_Video
*/
  public GnTitle FranchiseTitle {
    get {
      IntPtr cPtr = gnsdk_csharp_marshalPINVOKE.GnVideoSeason_FranchiseTitle_get(swigCPtr);
      GnTitle ret = (cPtr == IntPtr.Zero) ? null : new GnTitle(cPtr, true);
      return ret;
    } 
  }

  public GnExternalIdEnumerable ExternalIds {
    get {
      IntPtr cPtr = gnsdk_csharp_marshalPINVOKE.GnVideoSeason_ExternalIds_get(swigCPtr);
      GnExternalIdEnumerable ret = (cPtr == IntPtr.Zero) ? null : new GnExternalIdEnumerable(cPtr, true);
      return ret;
    } 
  }

  public GnVideoWorkEnumerable Works {
    get {
      IntPtr cPtr = gnsdk_csharp_marshalPINVOKE.GnVideoSeason_Works_get(swigCPtr);
      GnVideoWorkEnumerable ret = (cPtr == IntPtr.Zero) ? null : new GnVideoWorkEnumerable(cPtr, true);
      return ret;
    } 
  }

  public GnVideoProductEnumerable Products {
    get {
      IntPtr cPtr = gnsdk_csharp_marshalPINVOKE.GnVideoSeason_Products_get(swigCPtr);
      GnVideoProductEnumerable ret = (cPtr == IntPtr.Zero) ? null : new GnVideoProductEnumerable(cPtr, true);
      return ret;
    } 
  }

  public GnVideoCreditEnumerable VideoCredits {
    get {
      IntPtr cPtr = gnsdk_csharp_marshalPINVOKE.GnVideoSeason_VideoCredits_get(swigCPtr);
      GnVideoCreditEnumerable ret = (cPtr == IntPtr.Zero) ? null : new GnVideoCreditEnumerable(cPtr, true);
      return ret;
    } 
  }

  public GnVideoSeriesEnumerable Series {
    get {
      IntPtr cPtr = gnsdk_csharp_marshalPINVOKE.GnVideoSeason_Series_get(swigCPtr);
      GnVideoSeriesEnumerable ret = (cPtr == IntPtr.Zero) ? null : new GnVideoSeriesEnumerable(cPtr, true);
      return ret;
    } 
  }

  public GnContentEnumerable Contents {
    get {
      IntPtr cPtr = gnsdk_csharp_marshalPINVOKE.GnVideoSeason_Contents_get(swigCPtr);
      GnContentEnumerable ret = (cPtr == IntPtr.Zero) ? null : new GnContentEnumerable(cPtr, true);
      return ret;
    } 
  }

}

}
