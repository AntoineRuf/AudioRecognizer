
namespace GracenoteSDK {

using System;
using System.Runtime.InteropServices;

/**
* Collection of audio recordings.
* Provides access to album cover art when received from a query object
* with content enabled in lookup data.
*/
public class GnAlbum : GnDataObject {
  private HandleRef swigCPtr;

  internal GnAlbum(IntPtr cPtr, bool cMemoryOwn) : base(gnsdk_csharp_marshalPINVOKE.GnAlbum_SWIGUpcast(cPtr), cMemoryOwn) {
    swigCPtr = new HandleRef(this, cPtr);
  }

  internal static HandleRef getCPtr(GnAlbum obj) {
    return (obj == null) ? new HandleRef(null, IntPtr.Zero) : obj.swigCPtr;
  }

  ~GnAlbum() {
    Dispose();
  }

  public override void Dispose() {
    lock(this) {
      if (swigCPtr.Handle != IntPtr.Zero) {
        if (swigCMemOwn) {
          swigCMemOwn = false;
          gnsdk_csharp_marshalPINVOKE.delete_GnAlbum(swigCPtr);
        }
        swigCPtr = new HandleRef(null, IntPtr.Zero);
      }
      GC.SuppressFinalize(this);
      base.Dispose();
    }
  }

  public static string GnType() {
    string ret = gnsdk_csharp_marshalPINVOKE.GnAlbum_GnType();
    return ret;
  }

  public static GnAlbum From(GnDataObject obj) {
    GnAlbum ret = new GnAlbum(gnsdk_csharp_marshalPINVOKE.GnAlbum_From(GnDataObject.getCPtr(obj)), true);
    if (gnsdk_csharp_marshalPINVOKE.SWIGPendingException.Pending) throw gnsdk_csharp_marshalPINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

/**
* Constructs a GnAlbum object from identifier and identifier tag
* @param id	[in] Identifier
* @param idTag	[in] Identifier tag
*/
  public GnAlbum(string id, string idTag) : this(gnsdk_csharp_marshalPINVOKE.new_GnAlbum(id, idTag), true) {
    if (gnsdk_csharp_marshalPINVOKE.SWIGPendingException.Pending) throw gnsdk_csharp_marshalPINVOKE.SWIGPendingException.Retrieve();
  }

/**
* Album's genre, e.g., punk rock. List/locale dependent, multi-level field.
* @param level	[in] Data level
* @return Genre
* <p><b>Remarks:</b></p>
* This is a list-based value requiring that a corresponding locale or list be loaded.
*/
  public string Genre(GnDataLevel level) {
    string ret = gnsdk_csharp_marshalPINVOKE.GnAlbum_Genre(swigCPtr, (int)level);
    return ret;
  }

/**
* Album track using the track number.
* @param trackNumber	Ordinal of the desired track (1-based)
* @return Track
*/
  public GnTrack Track(uint trackNumber) {
    GnTrack ret = new GnTrack(gnsdk_csharp_marshalPINVOKE.GnAlbum_Track(swigCPtr, trackNumber), true);
    return ret;
  }

/**
* Ordinal value on album for matching track
* @param ordinal	Ordinal of the desired track (1-based)
* @return Track
*/
  public GnTrack TrackMatched(uint ordinal) {
    GnTrack ret = new GnTrack(gnsdk_csharp_marshalPINVOKE.GnAlbum_TrackMatched__SWIG_0(swigCPtr, ordinal), true);
    return ret;
  }

  public GnTrack TrackMatched() {
    GnTrack ret = new GnTrack(gnsdk_csharp_marshalPINVOKE.GnAlbum_TrackMatched__SWIG_1(swigCPtr), true);
    return ret;
  }

/**
* Track number on album for matching track
* @param ordinal	Ordinal of the desired track (1-based)
* @return Matched number
*/
  public uint TrackMatchNumber(uint ordinal) {
    uint ret = gnsdk_csharp_marshalPINVOKE.GnAlbum_TrackMatchNumber__SWIG_0(swigCPtr, ordinal);
    return ret;
  }

  public uint TrackMatchNumber() {
    uint ret = gnsdk_csharp_marshalPINVOKE.GnAlbum_TrackMatchNumber__SWIG_1(swigCPtr);
    return ret;
  }

/**
*  Content (cover art, biography, review, etc.) object
*  @param GnContentType object
*  @return Content object
*/
  public GnContent Content(GnContentType contentType) {
    GnContent ret = new GnContent(gnsdk_csharp_marshalPINVOKE.GnAlbum_Content(swigCPtr, (int)contentType), true);
    return ret;
  }

/**
*  Fetch the album's cover art content object
*  @return Content object
*/
  public GnContent CoverArt() {
    GnContent ret = new GnContent(gnsdk_csharp_marshalPINVOKE.GnAlbum_CoverArt(swigCPtr), true);
    return ret;
  }

/**
*  Fetch the album's review content object
*  @return Content object
*/
  public GnContent Review() {
    GnContent ret = new GnContent(gnsdk_csharp_marshalPINVOKE.GnAlbum_Review(swigCPtr), true);
    return ret;
  }

/**
* Album's official title.
* @return Title
*/
  public GnTitle Title {
    get {
      IntPtr cPtr = gnsdk_csharp_marshalPINVOKE.GnAlbum_Title_get(swigCPtr);
      GnTitle ret = (cPtr == IntPtr.Zero) ? null : new GnTitle(cPtr, true);
      return ret;
    } 
  }

/**
* Album's artist.
* @return Artist
*/
  public GnArtist Artist {
    get {
      IntPtr cPtr = gnsdk_csharp_marshalPINVOKE.GnAlbum_Artist_get(swigCPtr);
      GnArtist ret = (cPtr == IntPtr.Zero) ? null : new GnArtist(cPtr, true);
      return ret;
    } 
  }

/**
*  Title presented using Gracenote's Three Line Solution for classical track (composer/work title/movement title)
*  @return Title
*/
  public GnTitle TitleClassical {
    get {
      IntPtr cPtr = gnsdk_csharp_marshalPINVOKE.GnAlbum_TitleClassical_get(swigCPtr);
      GnTitle ret = (cPtr == IntPtr.Zero) ? null : new GnTitle(cPtr, true);
      return ret;
    } 
  }

/**
*  Regional title - list/locale dependent field
*  @return Title
*/
  public GnTitle TitleRegional {
    get {
      IntPtr cPtr = gnsdk_csharp_marshalPINVOKE.GnAlbum_TitleRegional_get(swigCPtr);
      GnTitle ret = (cPtr == IntPtr.Zero) ? null : new GnTitle(cPtr, true);
      return ret;
    } 
  }

/**
*  Regional locale title - list/locale dependent field
*  @return Title
*/
  public GnTitle TitleRegionalLocale {
    get {
      IntPtr cPtr = gnsdk_csharp_marshalPINVOKE.GnAlbum_TitleRegionalLocale_get(swigCPtr);
      GnTitle ret = (cPtr == IntPtr.Zero) ? null : new GnTitle(cPtr, true);
      return ret;
    } 
  }

  public GnTrackEnumerable Tracks {
    get {
      IntPtr cPtr = gnsdk_csharp_marshalPINVOKE.GnAlbum_Tracks_get(swigCPtr);
      GnTrackEnumerable ret = (cPtr == IntPtr.Zero) ? null : new GnTrackEnumerable(cPtr, true);
      return ret;
    } 
  }

  public GnTrackEnumerable TracksMatched {
    get {
      IntPtr cPtr = gnsdk_csharp_marshalPINVOKE.GnAlbum_TracksMatched_get(swigCPtr);
      GnTrackEnumerable ret = (cPtr == IntPtr.Zero) ? null : new GnTrackEnumerable(cPtr, true);
      return ret;
    } 
  }

  public GnCreditEnumerable Credits {
    get {
      IntPtr cPtr = gnsdk_csharp_marshalPINVOKE.GnAlbum_Credits_get(swigCPtr);
      GnCreditEnumerable ret = (cPtr == IntPtr.Zero) ? null : new GnCreditEnumerable(cPtr, true);
      return ret;
    } 
  }

  public GnExternalIdEnumerable ExternalIds {
    get {
      IntPtr cPtr = gnsdk_csharp_marshalPINVOKE.GnAlbum_ExternalIds_get(swigCPtr);
      GnExternalIdEnumerable ret = (cPtr == IntPtr.Zero) ? null : new GnExternalIdEnumerable(cPtr, true);
      return ret;
    } 
  }

  public GnContentEnumerable Contents {
    get {
      IntPtr cPtr = gnsdk_csharp_marshalPINVOKE.GnAlbum_Contents_get(swigCPtr);
      GnContentEnumerable ret = (cPtr == IntPtr.Zero) ? null : new GnContentEnumerable(cPtr, true);
      return ret;
    } 
  }

/**
*  Display language
*  @return Language string
*/
  public string Language {
	get
	{   
		/* csvarout typemap code */
		return GnMarshalUTF8.StringFromNativeUtf8(gnsdk_csharp_marshalPINVOKE.GnAlbum_Language_get(swigCPtr) );
	} 

  }

/**
*  Display langauge's 3-letter ISO code
*  @return Language code
*/
  public string LanguageCode {
	get
	{   
		/* csvarout typemap code */
		return GnMarshalUTF8.StringFromNativeUtf8(gnsdk_csharp_marshalPINVOKE.GnAlbum_LanguageCode_get(swigCPtr) );
	} 

  }

  public string Globald {
    get {
      string ret = gnsdk_csharp_marshalPINVOKE.GnAlbum_Globald_get(swigCPtr);
      return ret;
    } 
  }

/**
* Year the album was released.
* @return year
*/
  public string Year {
	get
	{   
		/* csvarout typemap code */
		return GnMarshalUTF8.StringFromNativeUtf8(gnsdk_csharp_marshalPINVOKE.GnAlbum_Year_get(swigCPtr) );
	} 

  }

/**
* Album's compilation value
* @return Compilation
*/
  public string Compilation {
	get
	{   
		/* csvarout typemap code */
		return GnMarshalUTF8.StringFromNativeUtf8(gnsdk_csharp_marshalPINVOKE.GnAlbum_Compilation_get(swigCPtr) );
	} 

  }

/**
* Album's label - record company that released the album, e.g., Atlantic.
* Album label values are not always available.
* @return Label
*/
  public string Label {
	get
	{   
		/* csvarout typemap code */
		return GnMarshalUTF8.StringFromNativeUtf8(gnsdk_csharp_marshalPINVOKE.GnAlbum_Label_get(swigCPtr) );
	} 

  }

/**
* Album's Gracenote Tui (title-unique identifier)
* @return Tui
*/
  public string Tui {
	get
	{   
		/* csvarout typemap code */
		return GnMarshalUTF8.StringFromNativeUtf8(gnsdk_csharp_marshalPINVOKE.GnAlbum_Tui_get(swigCPtr) );
	} 

  }

/**
* Album's Gracenote Tui Tag
* @return Tui Tag
*/
  public string TuiTag {
	get
	{   
		/* csvarout typemap code */
		return GnMarshalUTF8.StringFromNativeUtf8(gnsdk_csharp_marshalPINVOKE.GnAlbum_TuiTag_get(swigCPtr) );
	} 

  }

/**
* Album's Gracenote Tag identifier (Tag ID is same as Product ID)
* @return Gracenote Tag identifier
* <p><b>Remarks:</b></p>
* This method exists primarily to support legacy implementations. We recommend using
* the Product ID method to retrieve product related identifiers
*/
  public string TagId {
	get
	{   
		/* csvarout typemap code */
		return GnMarshalUTF8.StringFromNativeUtf8(gnsdk_csharp_marshalPINVOKE.GnAlbum_TagId_get(swigCPtr) );
	} 

  }

/**
* Album's Gracenote identifier.
* @return Gracenote identifier
*/
  public string GnId {
	get
	{   
		/* csvarout typemap code */
		return GnMarshalUTF8.StringFromNativeUtf8(gnsdk_csharp_marshalPINVOKE.GnAlbum_GnId_get(swigCPtr) );
	} 

  }

/**
* Album's Gracenote unique identifier.
* @return Gracenote unique identifier
*/
  public string GnUId {
	get
	{   
		/* csvarout typemap code */
		return GnMarshalUTF8.StringFromNativeUtf8(gnsdk_csharp_marshalPINVOKE.GnAlbum_GnUId_get(swigCPtr) );
	} 

  }

/**
*  Script used by the display values as ISO 15924 code
*  @return Script value.
*/
  public string Script {
	get
	{   
		/* csvarout typemap code */
		return GnMarshalUTF8.StringFromNativeUtf8(gnsdk_csharp_marshalPINVOKE.GnAlbum_Script_get(swigCPtr) );
	} 

  }

/**
*  Flag indicating if response contains full (true) or partial (false) metadata.
*  @return True if full result, false if partial result
* <p><b>Note:</b></p>
*   What constitutes a full result varies among the individual response types and results, and also
*  depends on data availability.
* @ingroup GDO_ValueKeys_Misc
*/
  public bool IsFullResult {
    get {
      bool ret = gnsdk_csharp_marshalPINVOKE.GnAlbum_IsFullResult_get(swigCPtr);
      return ret;
    } 
  }

/**
* Flag indicating if enhanced classical music data exists
* for this album.
* @return True is this is a classical album, false otherwise
*/
  public bool IsClassical {
    get {
      bool ret = gnsdk_csharp_marshalPINVOKE.GnAlbum_IsClassical_get(swigCPtr);
      return ret;
    } 
  }

/**
* Album's volume number in a multi-volume set.
* This value is not always available.
* @return Disc in set
*/
  public uint DiscInSet {
    get {
      uint ret = gnsdk_csharp_marshalPINVOKE.GnAlbum_DiscInSet_get(swigCPtr);
      return ret;
    } 
  }

/**
* Total number of volumes in album's multi-volume set.
* This value is not always available.
* @return Total in set
*/
  public uint TotalInSet {
    get {
      uint ret = gnsdk_csharp_marshalPINVOKE.GnAlbum_TotalInSet_get(swigCPtr);
      return ret;
    } 
  }

/**
* Match confidence score for top-level match
* @return Match score
*/
  public uint MatchScore {
    get {
      uint ret = gnsdk_csharp_marshalPINVOKE.GnAlbum_MatchScore_get(swigCPtr);
      return ret;
    } 
  }

/**
* Total number of tracks on this album.
* @return Count
*/
  public uint TrackCount {
    get {
      uint ret = gnsdk_csharp_marshalPINVOKE.GnAlbum_TrackCount_get(swigCPtr);
      return ret;
    } 
  }

}

}
