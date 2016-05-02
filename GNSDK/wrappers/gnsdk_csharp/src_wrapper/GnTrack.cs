
namespace GracenoteSDK {

using System;
using System.Runtime.InteropServices;

/**
* A song or instrumental recording.
*/
public class GnTrack : GnDataObject {
  private HandleRef swigCPtr;

  internal GnTrack(IntPtr cPtr, bool cMemoryOwn) : base(gnsdk_csharp_marshalPINVOKE.GnTrack_SWIGUpcast(cPtr), cMemoryOwn) {
    swigCPtr = new HandleRef(this, cPtr);
  }

  internal static HandleRef getCPtr(GnTrack obj) {
    return (obj == null) ? new HandleRef(null, IntPtr.Zero) : obj.swigCPtr;
  }

  ~GnTrack() {
    Dispose();
  }

  public override void Dispose() {
    lock(this) {
      if (swigCPtr.Handle != IntPtr.Zero) {
        if (swigCMemOwn) {
          swigCMemOwn = false;
          gnsdk_csharp_marshalPINVOKE.delete_GnTrack(swigCPtr);
        }
        swigCPtr = new HandleRef(null, IntPtr.Zero);
      }
      GC.SuppressFinalize(this);
      base.Dispose();
    }
  }

  public static string GnType() {
    string ret = gnsdk_csharp_marshalPINVOKE.GnTrack_GnType();
    return ret;
  }

  public static GnTrack From(GnDataObject obj) {
    GnTrack ret = new GnTrack(gnsdk_csharp_marshalPINVOKE.GnTrack_From(GnDataObject.getCPtr(obj)), true);
    if (gnsdk_csharp_marshalPINVOKE.SWIGPendingException.Pending) throw gnsdk_csharp_marshalPINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

/** Constructs a GnTrack object from identifier and identifie tag
* @param id	[in] Identifier
* @param idTag	[in] Identifier tag
*/
  public GnTrack(string id, string idTag) : this(gnsdk_csharp_marshalPINVOKE.new_GnTrack(id, idTag), true) {
    if (gnsdk_csharp_marshalPINVOKE.SWIGPendingException.Pending) throw gnsdk_csharp_marshalPINVOKE.SWIGPendingException.Retrieve();
  }

/**
* Track's mood, e.g., Playful. List/locale dependent, multi-level field.
* @param level	[in] Data level
* @return Mood
* <p><b>Remarks:</b></p>
* This is a list-based value requiring that a corresponding locale or list be loaded.
*/
  public string Mood(GnDataLevel level) {
    string ret = gnsdk_csharp_marshalPINVOKE.GnTrack_Mood(swigCPtr, (int)level);
    return ret;
  }

/**
* Track's tempo, e.g., Fast. List/locale dependent, multi-leveled field.
* @param level	[in] Data level
* @return Tempo
* <p><b>Remarks:</b></p>
* This is a list-based value requiring that a corresponding locale or list be loaded.
*/
  public string Tempo(GnDataLevel level) {
    string ret = gnsdk_csharp_marshalPINVOKE.GnTrack_Tempo(swigCPtr, (int)level);
    return ret;
  }

/**
* Track's genre, e.g., Heavy Metal. List/locale dependent, multi-level field
* @param level	[in] Data level
* @return Genre
* <p><b>Remarks:</b></p>
* This is a list-based value requiring that a corresponding locale or list be loaded.
*/
  public string Genre(GnDataLevel level) {
    string ret = gnsdk_csharp_marshalPINVOKE.GnTrack_Genre(swigCPtr, (int)level);
    return ret;
  }

/**
*  Track's content, e.g., cover image, artist image, biography etc.
*  @param GnContentType object
*  @return Content object
*/
  public GnContent Content(GnContentType contentType) {
    GnContent ret = new GnContent(gnsdk_csharp_marshalPINVOKE.GnTrack_Content(swigCPtr, (int)contentType), true);
    return ret;
  }

/**
*  Fetch the album's review content object
*  @return Content object
*/
  public GnContent Review() {
    GnContent ret = new GnContent(gnsdk_csharp_marshalPINVOKE.GnTrack_Review(swigCPtr), true);
    return ret;
  }

/**
* Flag indicating if this is the matched track (true)
* @return True if matched track, false otherwise
*/
  public bool Matched() {
    bool ret = gnsdk_csharp_marshalPINVOKE.GnTrack_Matched(swigCPtr);
    return ret;
  }

/**
* Position in milliseconds of where we matched in the track
* @return Match position in milliseconds
*/
  public uint MatchPosition() {
    uint ret = gnsdk_csharp_marshalPINVOKE.GnTrack_MatchPosition(swigCPtr);
    return ret;
  }

/**
* For MusicID-Stream fingerprint matches, this is the length of matched reference audio in
* milliseconds.
*/
  public uint MatchDuration() {
    uint ret = gnsdk_csharp_marshalPINVOKE.GnTrack_MatchDuration(swigCPtr);
    return ret;
  }

/**
* Current position in milliseconds of the matched track.
* The current position tracks the approximate real time position of the
* playing audio track assuming it is not paused. Only available from
* GnMusicIdStream responses.
* @return Current position in milliseconds
*/
  public uint CurrentPosition() {
    uint ret = gnsdk_csharp_marshalPINVOKE.GnTrack_CurrentPosition(swigCPtr);
    return ret;
  }

/**
* Duration in milliseconds of the track (only available if this is the matched track)
* @return Duration in milliseconds
*/
  public uint Duration() {
    uint ret = gnsdk_csharp_marshalPINVOKE.GnTrack_Duration(swigCPtr);
    return ret;
  }

/**
* Track's official title.
* @return Title
*/
  public GnTitle Title {
    get {
      IntPtr cPtr = gnsdk_csharp_marshalPINVOKE.GnTrack_Title_get(swigCPtr);
      GnTitle ret = (cPtr == IntPtr.Zero) ? null : new GnTitle(cPtr, true);
      return ret;
    } 
  }

/**
* Track's artist.
* @return Artist
*/
  public GnArtist Artist {
    get {
      IntPtr cPtr = gnsdk_csharp_marshalPINVOKE.GnTrack_Artist_get(swigCPtr);
      GnArtist ret = (cPtr == IntPtr.Zero) ? null : new GnArtist(cPtr, true);
      return ret;
    } 
  }

/**
* Track's audio work.
* @return Work
*/
  public GnAudioWork Work {
    get {
      IntPtr cPtr = gnsdk_csharp_marshalPINVOKE.GnTrack_Work_get(swigCPtr);
      GnAudioWork ret = (cPtr == IntPtr.Zero) ? null : new GnAudioWork(cPtr, true);
      return ret;
    } 
  }

/**
*  Title presented using Gracenote's Three Line Solution for classical track (composer/work title/movement title)
*  @return Title
*/
  public GnTitle TitleClassical {
    get {
      IntPtr cPtr = gnsdk_csharp_marshalPINVOKE.GnTrack_TitleClassical_get(swigCPtr);
      GnTitle ret = (cPtr == IntPtr.Zero) ? null : new GnTitle(cPtr, true);
      return ret;
    } 
  }

/**
*  Regional title. Locale/list dependent field.
*  @return Title
*/
  public GnTitle TitleRegional {
    get {
      IntPtr cPtr = gnsdk_csharp_marshalPINVOKE.GnTrack_TitleRegional_get(swigCPtr);
      GnTitle ret = (cPtr == IntPtr.Zero) ? null : new GnTitle(cPtr, true);
      return ret;
    } 
  }

  public GnCreditEnumerable Credits {
    get {
      IntPtr cPtr = gnsdk_csharp_marshalPINVOKE.GnTrack_Credits_get(swigCPtr);
      GnCreditEnumerable ret = (cPtr == IntPtr.Zero) ? null : new GnCreditEnumerable(cPtr, true);
      return ret;
    } 
  }

  public GnExternalIdEnumerable ExternalIds {
    get {
      IntPtr cPtr = gnsdk_csharp_marshalPINVOKE.GnTrack_ExternalIds_get(swigCPtr);
      GnExternalIdEnumerable ret = (cPtr == IntPtr.Zero) ? null : new GnExternalIdEnumerable(cPtr, true);
      return ret;
    } 
  }

  public GnContentEnumerable Contents {
    get {
      IntPtr cPtr = gnsdk_csharp_marshalPINVOKE.GnTrack_Contents_get(swigCPtr);
      GnContentEnumerable ret = (cPtr == IntPtr.Zero) ? null : new GnContentEnumerable(cPtr, true);
      return ret;
    } 
  }

  public GnStringValueEnumerable MatchedIdents {
    get {
      IntPtr cPtr = gnsdk_csharp_marshalPINVOKE.GnTrack_MatchedIdents_get(swigCPtr);
      GnStringValueEnumerable ret = (cPtr == IntPtr.Zero) ? null : new GnStringValueEnumerable(cPtr, true);
      return ret;
    } 
  }

/**
* Track's Gracenote Tui (title-unique identifier).
* @return Tui
*/
  public string Tui {
	get
	{   
		/* csvarout typemap code */
		return GnMarshalUTF8.StringFromNativeUtf8(gnsdk_csharp_marshalPINVOKE.GnTrack_Tui_get(swigCPtr) );
	} 

  }

/**
* Track's Gracenote Tui Tag.
* @return Tui Tag
*/
  public string TuiTag {
	get
	{   
		/* csvarout typemap code */
		return GnMarshalUTF8.StringFromNativeUtf8(gnsdk_csharp_marshalPINVOKE.GnTrack_TuiTag_get(swigCPtr) );
	} 

  }

/**
* Track's Gracenote Tag identifier (same as Product ID)
* @return Gracenote Tag identifier
* <p><b>Remarks:</b></p>
* This method exists primarily to support legacy implementations. We recommend using
* the Product ID method to retrieve product related identifiers
*/
  public string TagId {
	get
	{   
		/* csvarout typemap code */
		return GnMarshalUTF8.StringFromNativeUtf8(gnsdk_csharp_marshalPINVOKE.GnTrack_TagId_get(swigCPtr) );
	} 

  }

/**
* Track's Gracenote identifier
* @return Gracenote identifier
*/
  public string GnId {
	get
	{   
		/* csvarout typemap code */
		return GnMarshalUTF8.StringFromNativeUtf8(gnsdk_csharp_marshalPINVOKE.GnTrack_GnId_get(swigCPtr) );
	} 

  }

/**
* Track's Gracenote unique identifier.
* @return Gracenote unique identifier
*/
  public string GnUId {
	get
	{   
		/* csvarout typemap code */
		return GnMarshalUTF8.StringFromNativeUtf8(gnsdk_csharp_marshalPINVOKE.GnTrack_GnUId_get(swigCPtr) );
	} 

  }

/**
* Track's ordinal number on album.
* @return Track number
*/
  public string TrackNumber {
	get
	{   
		/* csvarout typemap code */
		return GnMarshalUTF8.StringFromNativeUtf8(gnsdk_csharp_marshalPINVOKE.GnTrack_TrackNumber_get(swigCPtr) );
	} 

  }

/**
* Track's year.
* @return Year
*/
  public string Year {
	get
	{   
		/* csvarout typemap code */
		return GnMarshalUTF8.StringFromNativeUtf8(gnsdk_csharp_marshalPINVOKE.GnTrack_Year_get(swigCPtr) );
	} 

  }

/**
* Track's match type - the most authoritative matching type for a given file info object.
* @return Match lookup type
*  <p><b>Remarks:</b></p>
* The match type indicates which query type was the most authoritative matching type for a given file
* information object.
* MusicID-File does a query for each type of input data, and each type of input data has an authoritative rank.
* The match type indicates the highest authoritative matched type for this file information object.
* The match type is only useful in comparison to other match types. By itself it does not indicate
* a strong or poor match. The higher the match type, the more authoritative the identification process
* used.
* The following table lists the possible match type values:
* <table>
* <tr><th>Match Type</th><th>Value</th></tr>
* <tr><td>MIDF_MATCH_TYPE_TUI</td><td>11</td></tr>
* <tr><td>MIDF_MATCH_TYPE_MUI</td><td>10</td></tr>
* <tr><td>MIDF_MATCH_TYPE_TOC</td><td>9</td></tr>
* <tr><td>MIDF_MATCH_TYPE_ASSOCIATED_ID</td><td>8</td></tr>
* <tr><td>MIDF_MATCH_TYPE_WF</td><td>7</td></tr>
* <tr><td>MIDF_MATCH_TYPE_TEXT_ON_WF</td><td>6</td></tr>
* <tr><td>MIDF_MATCH_TYPE_ASSOCIATED_TEXT</td><td>5</td></tr>
* <tr><td>MIDF_MATCH_TYPE_TEXT_TRACK</td><td>4</td></tr>
* <tr><td>MIDF_MATCH_TYPE_TEXT_ALBUM</td><td>3</td></tr>
* <tr><td>MIDF_MATCH_TYPE_TEXT_CONTRIBUTOR</td><td>2</td></tr>
* <tr><td>MIDF_MATCH_TYPE_NONE</td><td>1</td></tr>
* <tr><td>MIDF_MATCH_TYPE_INVALID</td><td>0</td></tr>
* </table>
*/
  public string MatchLookupType {
	get
	{   
		/* csvarout typemap code */
		return GnMarshalUTF8.StringFromNativeUtf8(gnsdk_csharp_marshalPINVOKE.GnTrack_MatchLookupType_get(swigCPtr) );
	} 

  }

/**
*  Confidence score (0-100) for match
*  @return Confidence score
*/
  public string MatchConfidence {
	get
	{   
		/* csvarout typemap code */
		return GnMarshalUTF8.StringFromNativeUtf8(gnsdk_csharp_marshalPINVOKE.GnTrack_MatchConfidence_get(swigCPtr) );
	} 

  }

/**
* Track's match score - correlation between input text and matched track
* @return Match score
* <p><b>Remarks:</b></p>
* The match score gives a correlation between the input text and the matched track,
* indicating how well the input text matched the track. However, any result that is returned
* is considered to be a good match. The match score is only useful in comparison to other match
* scores. By itself it does not indicate a strong or poor match.
*/
  public uint MatchScore {
    get {
      uint ret = gnsdk_csharp_marshalPINVOKE.GnTrack_MatchScore_get(swigCPtr);
      return ret;
    } 
  }

/**
*  Flag indicating if response contains full (true) or partial (false) metadata.
*  @return True if full result, false otherwise
* <p><b>Note:</b></p>
*   What constitutes a full result varies among the individual response types and results, and also
*  depends on data availability.
* @ingroup GDO_ValueKeys_Misc
*/
  public bool IsFullResult {
    get {
      bool ret = gnsdk_csharp_marshalPINVOKE.GnTrack_IsFullResult_get(swigCPtr);
      return ret;
    } 
  }

}

}
