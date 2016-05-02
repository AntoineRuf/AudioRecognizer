
package com.gracenote.gnsdk;

/** 
* A song or instrumental recording. 
*/ 
 
public class GnTrack extends GnDataObject {
  private long swigCPtr;

  protected GnTrack(long cPtr, boolean cMemoryOwn) {
    super(gnsdk_javaJNI.GnTrack_SWIGUpcast(cPtr), cMemoryOwn);
    swigCPtr = cPtr;
  }

  protected static long getCPtr(GnTrack obj) {
    return (obj == null) ? 0 : obj.swigCPtr;
  }

  protected void finalize() {
    delete();
  }

  public synchronized void delete() {
    if (swigCPtr != 0) {
      if (swigCMemOwn) {
        swigCMemOwn = false;
        gnsdk_javaJNI.delete_GnTrack(swigCPtr);
      }
      swigCPtr = 0;
    }
    super.delete();
  }

  public static String gnType() {
    return gnsdk_javaJNI.GnTrack_gnType();
  }

  public static GnTrack from(GnDataObject obj) throws com.gracenote.gnsdk.GnException {
    return new GnTrack(gnsdk_javaJNI.GnTrack_from(GnDataObject.getCPtr(obj), obj), true);
  }

/** Constructs a {@link GnTrack} object from identifier and identifie tag 
* @param id	[in] Identifier 
* @param idTag	[in] Identifier tag 
*/ 
 
  public GnTrack(String id, String idTag) throws com.gracenote.gnsdk.GnException {
    this(gnsdk_javaJNI.new_GnTrack(id, idTag), true);
  }

/** 
*  Flag indicating if response contains full (true) or partial (false) metadata. 
*  @return True if full result, false otherwise 
* <p><b>Note:</b></p> 
*   What constitutes a full result varies among the individual response types and results, and also 
*  depends on data availability. 
* 
*/ 
 
  public boolean isFullResult() {
    return gnsdk_javaJNI.GnTrack_isFullResult(swigCPtr, this);
  }

/** 
* Track's official title. 
* @return Title 
*/ 
 
  public GnTitle title() {
    return new GnTitle(gnsdk_javaJNI.GnTrack_title(swigCPtr, this), true);
  }

/** 
* Track's artist. 
* @return Artist 
*/ 
 
  public GnArtist artist() {
    return new GnArtist(gnsdk_javaJNI.GnTrack_artist(swigCPtr, this), true);
  }

/** 
* Track's audio work. 
* @return Work 
*/ 
 
  public GnAudioWork work() {
    return new GnAudioWork(gnsdk_javaJNI.GnTrack_work(swigCPtr, this), true);
  }

/** 
* Track's mood, e.g., Playful. List/locale dependent, multi-level field. 
* @param level	[in] Data level 
* @return Mood 
* <p><b>Remarks:</b></p> 
* This is a list-based value requiring that a corresponding locale or list be loaded. 
*/ 
 
  public String mood(GnDataLevel level) {
    return gnsdk_javaJNI.GnTrack_mood(swigCPtr, this, level.swigValue());
  }

/** 
* Track's tempo, e.g., Fast. List/locale dependent, multi-leveled field. 
* @param level	[in] Data level 
* @return Tempo 
* <p><b>Remarks:</b></p> 
* This is a list-based value requiring that a corresponding locale or list be loaded. 
*/ 
 
  public String tempo(GnDataLevel level) {
    return gnsdk_javaJNI.GnTrack_tempo(swigCPtr, this, level.swigValue());
  }

/** 
* Track's genre, e.g., Heavy Metal. List/locale dependent, multi-level field 
* @param level	[in] Data level 
* @return Genre 
* <p><b>Remarks:</b></p> 
* This is a list-based value requiring that a corresponding locale or list be loaded. 
*/ 
 
  public String genre(GnDataLevel level) {
    return gnsdk_javaJNI.GnTrack_genre(swigCPtr, this, level.swigValue());
  }

/** 
*  Track's content, e.g., cover image, artist image, biography etc. 
*  @param {@link GnContentType} object 
*  @return Content object 
*/ 
 
  public GnContent content(GnContentType contentType) {
    return new GnContent(gnsdk_javaJNI.GnTrack_content(swigCPtr, this, contentType.swigValue()), true);
  }

/** 
*  Fetch the album's review content object 
*  @return Content object 
*/ 
 
  public GnContent review() {
    return new GnContent(gnsdk_javaJNI.GnTrack_review(swigCPtr, this), true);
  }

/** 
* Flag indicating if this is the matched track (true) 
* @return True if matched track, false otherwise 
*/ 
 
  public boolean matched() {
    return gnsdk_javaJNI.GnTrack_matched(swigCPtr, this);
  }

/** 
* Position in milliseconds of where we matched in the track 
* @return Match position in milliseconds 
*/ 
 
  public long matchPosition() {
    return gnsdk_javaJNI.GnTrack_matchPosition(swigCPtr, this);
  }

/** 
* For MusicID-Stream fingerprint matches, this is the length of matched reference audio in 
* milliseconds. 
*/ 
 
  public long matchDuration() {
    return gnsdk_javaJNI.GnTrack_matchDuration(swigCPtr, this);
  }

/** 
* Current position in milliseconds of the matched track. 
* The current position tracks the approximate real time position of the 
* playing audio track assuming it is not paused. Only available from 
* {@link GnMusicIdStream} responses. 
* @return Current position in milliseconds 
*/ 
 
  public long currentPosition() {
    return gnsdk_javaJNI.GnTrack_currentPosition(swigCPtr, this);
  }

/** 
* Duration in milliseconds of the track (only available if this is the matched track) 
* @return Duration in milliseconds 
*/ 
 
  public long duration() {
    return gnsdk_javaJNI.GnTrack_duration(swigCPtr, this);
  }

  public GnCreditIterable credits() {
    return new GnCreditIterable(gnsdk_javaJNI.GnTrack_credits(swigCPtr, this), true);
  }

  public GnContentIterable contents() {
    return new GnContentIterable(gnsdk_javaJNI.GnTrack_contents(swigCPtr, this), true);
  }

  public GnExternalIdIterable externalIds() {
    return new GnExternalIdIterable(gnsdk_javaJNI.GnTrack_externalIds(swigCPtr, this), true);
  }

/** 
* Track's Gracenote Tui (title-unique identifier). 
* @return Tui 
*/ 
 
  public String tui() {
    return gnsdk_javaJNI.GnTrack_tui(swigCPtr, this);
  }

/** 
* Track's Gracenote Tui Tag. 
* @return Tui Tag 
*/ 
 
  public String tuiTag() {
    return gnsdk_javaJNI.GnTrack_tuiTag(swigCPtr, this);
  }

/** 
* Track's Gracenote Tag identifier (same as Product ID) 
* @return Gracenote Tag identifier 
* <p><b>Remarks:</b></p> 
* This method exists primarily to support legacy implementations. We recommend using 
* the Product ID method to retrieve product related identifiers 
*/ 
 
  public String tagId() {
    return gnsdk_javaJNI.GnTrack_tagId(swigCPtr, this);
  }

/** 
* Track's Gracenote identifier 
* @return Gracenote identifier 
*/ 
 
  public String gnId() {
    return gnsdk_javaJNI.GnTrack_gnId(swigCPtr, this);
  }

/** 
* Track's Gracenote unique identifier. 
* @return Gracenote unique identifier 
*/ 
 
  public String gnUId() {
    return gnsdk_javaJNI.GnTrack_gnUId(swigCPtr, this);
  }

/** 
* Track's ordinal number on album. 
* @return Track number 
*/ 
 
  public String trackNumber() {
    return gnsdk_javaJNI.GnTrack_trackNumber(swigCPtr, this);
  }

/** 
* Track's year. 
* @return Year 
*/ 
 
  public String year() {
    return gnsdk_javaJNI.GnTrack_year(swigCPtr, this);
  }

  public GnStringValueIterable matchedIdents() {
    return new GnStringValueIterable(gnsdk_javaJNI.GnTrack_matchedIdents(swigCPtr, this), true);
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
 
  public String matchLookupType() {
    return gnsdk_javaJNI.GnTrack_matchLookupType(swigCPtr, this);
  }

/** 
*  Confidence score (0-100) for match 
*  @return Confidence score 
*/ 
 
  public String matchConfidence() {
    return gnsdk_javaJNI.GnTrack_matchConfidence(swigCPtr, this);
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
 
  public long matchScore() {
    return gnsdk_javaJNI.GnTrack_matchScore(swigCPtr, this);
  }

/** 
*  Title presented using Gracenote's Three Line Solution for classical track (composer/work title/movement title) 
*  @return Title 
*/ 
 
  public GnTitle titleClassical() {
    return new GnTitle(gnsdk_javaJNI.GnTrack_titleClassical(swigCPtr, this), true);
  }

/** 
*  Regional title. Locale/list dependent field. 
*  @return Title 
*/ 
 
  public GnTitle titleRegional() {
    return new GnTitle(gnsdk_javaJNI.GnTrack_titleRegional(swigCPtr, this), true);
  }

}
