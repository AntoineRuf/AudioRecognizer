
package com.gracenote.gnsdk;

/** 
* Collection of audio recordings. 
* Provides access to album cover art when received from a query object 
* with content enabled in lookup data. 
*/ 
 
public class GnAlbum extends GnDataObject {
  private long swigCPtr;

  protected GnAlbum(long cPtr, boolean cMemoryOwn) {
    super(gnsdk_javaJNI.GnAlbum_SWIGUpcast(cPtr), cMemoryOwn);
    swigCPtr = cPtr;
  }

  protected static long getCPtr(GnAlbum obj) {
    return (obj == null) ? 0 : obj.swigCPtr;
  }

  protected void finalize() {
    delete();
  }

  public synchronized void delete() {
    if (swigCPtr != 0) {
      if (swigCMemOwn) {
        swigCMemOwn = false;
        gnsdk_javaJNI.delete_GnAlbum(swigCPtr);
      }
      swigCPtr = 0;
    }
    super.delete();
  }

  public static String gnType() {
    return gnsdk_javaJNI.GnAlbum_gnType();
  }

  public static GnAlbum from(GnDataObject obj) throws com.gracenote.gnsdk.GnException {
    return new GnAlbum(gnsdk_javaJNI.GnAlbum_from(GnDataObject.getCPtr(obj), obj), true);
  }

/** 
* Constructs a {@link GnAlbum} object from identifier and identifier tag 
* @param id	[in] Identifier 
* @param idTag	[in] Identifier tag 
*/ 
 
  public GnAlbum(String id, String idTag) throws com.gracenote.gnsdk.GnException {
    this(gnsdk_javaJNI.new_GnAlbum(id, idTag), true);
  }

/** 
*  Flag indicating if response contains full (true) or partial (false) metadata. 
*  @return True if full result, false if partial result 
* <p><b>Note:</b></p> 
*   What constitutes a full result varies among the individual response types and results, and also 
*  depends on data availability. 
* 
*/ 
 
  public boolean isFullResult() {
    return gnsdk_javaJNI.GnAlbum_isFullResult(swigCPtr, this);
  }

/** 
* Album's official title. 
* @return Title 
*/ 
 
  public GnTitle title() {
    return new GnTitle(gnsdk_javaJNI.GnAlbum_title(swigCPtr, this), true);
  }

/** 
* Album's artist. 
* @return Artist 
*/ 
 
  public GnArtist artist() {
    return new GnArtist(gnsdk_javaJNI.GnAlbum_artist(swigCPtr, this), true);
  }

/** 
* Album's genre, e.g., punk rock. List/locale dependent, multi-level field. 
* @param level	[in] Data level 
* @return Genre 
* <p><b>Remarks:</b></p> 
* This is a list-based value requiring that a corresponding locale or list be loaded. 
*/ 
 
  public String genre(GnDataLevel level) {
    return gnsdk_javaJNI.GnAlbum_genre(swigCPtr, this, level.swigValue());
  }

/** 
* Album's label - record company that released the album, e.g., Atlantic. 
* Album label values are not always available. 
* @return Label 
*/ 
 
  public String label() {
    return gnsdk_javaJNI.GnAlbum_label(swigCPtr, this);
  }

/** 
*  Display language 
*  @return Language string 
*/ 
 
  public String language() {
    return gnsdk_javaJNI.GnAlbum_language(swigCPtr, this);
  }

/** 
*  Display langauge's 3-letter ISO code 
*  @return Language code 
*/ 
 
  public String languageCode() {
    return gnsdk_javaJNI.GnAlbum_languageCode(swigCPtr, this);
  }

/** 
* Album's Gracenote Tui (title-unique identifier) 
* @return Tui 
*/ 
 
  public String tui() {
    return gnsdk_javaJNI.GnAlbum_tui(swigCPtr, this);
  }

/** 
* Album's Gracenote Tui Tag 
* @return Tui Tag 
*/ 
 
  public String tuiTag() {
    return gnsdk_javaJNI.GnAlbum_tuiTag(swigCPtr, this);
  }

/** 
* Album's Gracenote Tag identifier (Tag ID is same as Product ID) 
* @return Gracenote Tag identifier 
* <p><b>Remarks:</b></p> 
* This method exists primarily to support legacy implementations. We recommend using 
* the Product ID method to retrieve product related identifiers 
*/ 
 
  public String tagId() {
    return gnsdk_javaJNI.GnAlbum_tagId(swigCPtr, this);
  }

/** 
* Album's Gracenote identifier. 
* @return Gracenote identifier 
*/ 
 
  public String gnId() {
    return gnsdk_javaJNI.GnAlbum_gnId(swigCPtr, this);
  }

/** 
* Album's Gracenote unique identifier. 
* @return Gracenote unique identifier 
*/ 
 
  public String gnUId() {
    return gnsdk_javaJNI.GnAlbum_gnUId(swigCPtr, this);
  }

/** 
* Album's global identifier (used for transcriptions). 
* @return Gracenote Global identifier 
*/ 
 
  public String globalId() {
    return gnsdk_javaJNI.GnAlbum_globalId(swigCPtr, this);
  }

/** 
* Album's volume number in a multi-volume set. 
* This value is not always available. 
* @return Disc in set 
*/ 
 
  public long discInSet() {
    return gnsdk_javaJNI.GnAlbum_discInSet(swigCPtr, this);
  }

/** 
* Total number of volumes in album's multi-volume set. 
* This value is not always available. 
* @return Total in set 
*/ 
 
  public long totalInSet() {
    return gnsdk_javaJNI.GnAlbum_totalInSet(swigCPtr, this);
  }

/** 
* Year the album was released. 
* @return year 
*/ 
 
  public String year() {
    return gnsdk_javaJNI.GnAlbum_year(swigCPtr, this);
  }

/** 
* Flag indicating if enhanced classical music data exists 
* for this album. 
* @return True is this is a classical album, false otherwise 
*/ 
 
  public boolean isClassical() {
    return gnsdk_javaJNI.GnAlbum_isClassical(swigCPtr, this);
  }

/** 
* Total number of tracks on this album. 
* @return Count 
*/ 
 
  public long trackCount() {
    return gnsdk_javaJNI.GnAlbum_trackCount(swigCPtr, this);
  }

/** 
* Album's compilation value 
* @return Compilation 
*/ 
 
  public String compilation() {
    return gnsdk_javaJNI.GnAlbum_compilation(swigCPtr, this);
  }

/** 
* Match confidence score for top-level match 
* @return Match score 
*/ 
 
  public long matchScore() {
    return gnsdk_javaJNI.GnAlbum_matchScore(swigCPtr, this);
  }

/** 
* Album track using the track number. 
* @param trackNumber	Ordinal of the desired track (1-based) 
* @return Track 
*/ 
 
  public GnTrack track(long trackNumber) {
    return new GnTrack(gnsdk_javaJNI.GnAlbum_track(swigCPtr, this, trackNumber), true);
  }

/** 
* Ordinal value on album for matching track 
* @param ordinal	Ordinal of the desired track (1-based) 
* @return Track 
*/ 
 
  public GnTrack trackMatched(long ordinal) {
    return new GnTrack(gnsdk_javaJNI.GnAlbum_trackMatched__SWIG_0(swigCPtr, this, ordinal), true);
  }

  public GnTrack trackMatched() {
    return new GnTrack(gnsdk_javaJNI.GnAlbum_trackMatched__SWIG_1(swigCPtr, this), true);
  }

/** 
* Track number on album for matching track 
* @param ordinal	Ordinal of the desired track (1-based) 
* @return Matched number 
*/ 
 
  public long trackMatchNumber(long ordinal) {
    return gnsdk_javaJNI.GnAlbum_trackMatchNumber__SWIG_0(swigCPtr, this, ordinal);
  }

  public long trackMatchNumber() {
    return gnsdk_javaJNI.GnAlbum_trackMatchNumber__SWIG_1(swigCPtr, this);
  }

/** 
*  Content (cover art, biography, review, etc.) object 
*  @param {@link GnContentType} object 
*  @return Content object 
*/ 
 
  public GnContent content(GnContentType contentType) {
    return new GnContent(gnsdk_javaJNI.GnAlbum_content(swigCPtr, this, contentType.swigValue()), true);
  }

/** 
*  Fetch the album's cover art content object 
*  @return Content object 
*/ 
 
  public GnContent coverArt() {
    return new GnContent(gnsdk_javaJNI.GnAlbum_coverArt(swigCPtr, this), true);
  }

/** 
*  Fetch the album's review content object 
*  @return Content object 
*/ 
 
  public GnContent review() {
    return new GnContent(gnsdk_javaJNI.GnAlbum_review(swigCPtr, this), true);
  }

  public GnTrackIterable tracks() {
    return new GnTrackIterable(gnsdk_javaJNI.GnAlbum_tracks(swigCPtr, this), true);
  }

  public GnTrackIterable tracksMatched() {
    return new GnTrackIterable(gnsdk_javaJNI.GnAlbum_tracksMatched(swigCPtr, this), true);
  }

  public GnCreditIterable credits() {
    return new GnCreditIterable(gnsdk_javaJNI.GnAlbum_credits(swigCPtr, this), true);
  }

  public GnContentIterable contents() {
    return new GnContentIterable(gnsdk_javaJNI.GnAlbum_contents(swigCPtr, this), true);
  }

  public GnExternalIdIterable externalIds() {
    return new GnExternalIdIterable(gnsdk_javaJNI.GnAlbum_externalIds(swigCPtr, this), true);
  }

/** 
*  Title presented using Gracenote's Three Line Solution for classical track (composer/work title/movement title) 
*  @return Title 
*/ 
 
  public GnTitle titleClassical() {
    return new GnTitle(gnsdk_javaJNI.GnAlbum_titleClassical(swigCPtr, this), true);
  }

/** 
*  Regional title - list/locale dependent field 
*  @return Title 
*/ 
 
  public GnTitle titleRegional() {
    return new GnTitle(gnsdk_javaJNI.GnAlbum_titleRegional(swigCPtr, this), true);
  }

/** 
*  Regional locale title - list/locale dependent field 
*  @return Title 
*/ 
 
  public GnTitle titleRegionalLocale() {
    return new GnTitle(gnsdk_javaJNI.GnAlbum_titleRegionalLocale(swigCPtr, this), true);
  }

/** 
*  Script used by the display values as ISO 15924 code 
*  @return Script value. 
*/ 
 
  public String script() {
    return gnsdk_javaJNI.GnAlbum_script(swigCPtr, this);
  }

}
