
package com.gracenote.gnsdk;

/** 
**/ 
 
public class GnVideoSeason extends GnDataObject {
  private long swigCPtr;

  protected GnVideoSeason(long cPtr, boolean cMemoryOwn) {
    super(gnsdk_javaJNI.GnVideoSeason_SWIGUpcast(cPtr), cMemoryOwn);
    swigCPtr = cPtr;
  }

  protected static long getCPtr(GnVideoSeason obj) {
    return (obj == null) ? 0 : obj.swigCPtr;
  }

  protected void finalize() {
    delete();
  }

  public synchronized void delete() {
    if (swigCPtr != 0) {
      if (swigCMemOwn) {
        swigCMemOwn = false;
        gnsdk_javaJNI.delete_GnVideoSeason(swigCPtr);
      }
      swigCPtr = 0;
    }
    super.delete();
  }

  public static String gnType() {
    return gnsdk_javaJNI.GnVideoSeason_gnType();
  }

  public static GnVideoSeason from(GnDataObject obj) throws com.gracenote.gnsdk.GnException {
    return new GnVideoSeason(gnsdk_javaJNI.GnVideoSeason_from(GnDataObject.getCPtr(obj), obj), true);
  }

  public GnVideoSeason(String id, String idTag) throws com.gracenote.gnsdk.GnException {
    this(gnsdk_javaJNI.new_GnVideoSeason(id, idTag), true);
  }

/** 
*  Flag indicating if response result contains full (true) or partial metadata. 
* <p><b>Note:</b></p> 
*   What constitutes a full result varies among response results, and also 
*  depends on data availability. 
* 
*/ 
 
  public boolean isFullResult() {
    return gnsdk_javaJNI.GnVideoSeason_isFullResult(swigCPtr, this);
  }

/** 
*  Video season's Gracenote identifier. 
* 
*/ 
 
  public String gnId() {
    return gnsdk_javaJNI.GnVideoSeason_gnId(swigCPtr, this);
  }

/** 
*   Video season's Gracenote unique identifier. 
* 
*/ 
 
  public String gnUId() {
    return gnsdk_javaJNI.GnVideoSeason_gnUId(swigCPtr, this);
  }

/** 
*  Video season's product ID (aka Tag ID). 
*  <p><b>Remarks:</b></p> 
*  Available for most types, this value can be stored or transmitted. Can 
*  be used as a static identifier for the current content as it will not change over time. 
* 
*/ 
 
  public String productId() {
    return gnsdk_javaJNI.GnVideoSeason_productId(swigCPtr, this);
  }

/** 
*  Video season's TUI (title-unique identifier). 
* 
*/ 
 
  public String tui() {
    return gnsdk_javaJNI.GnVideoSeason_tui(swigCPtr, this);
  }

/** 
*  Video season's Tui Tag. 
* 
*/ 
 
  public String tuiTag() {
    return gnsdk_javaJNI.GnVideoSeason_tuiTag(swigCPtr, this);
  }

/** 
*  Video production type, e.g., Animation. This is a list/locale dependent value. 
*  <p><b>Remarks:</b></p> 
*  This is a list-based value requiring that the list or locale be loaded into memory through a successful 
*  allocation of a {@link GnLocale} object 
* <p> 
*  To render locale-dependent information for list-based values, the application must allocate a {@link GnLocale} object. 
*  The SDK returns a <code>LocaleNotLoaded</code> message when locale information is not set prior to a request for 
*  a list-based value. 
* 
*/ 
 
  public String videoProductionType() {
    return gnsdk_javaJNI.GnVideoSeason_videoProductionType(swigCPtr, this);
  }

/** 
*  Video production type identifier. 
* 
*/ 
 
  public long videoProductionTypeId() {
    return gnsdk_javaJNI.GnVideoSeason_videoProductionTypeId(swigCPtr, this);
  }

/** 
*  Video season's original release date. 
* 
*/ 
 
  public String dateOriginalRelease() {
    return gnsdk_javaJNI.GnVideoSeason_dateOriginalRelease(swigCPtr, this);
  }

/** 
*  Duration in seconds such as "3600" for a 60-minute program. 
* 
*/ 
 
  public long duration() {
    return gnsdk_javaJNI.GnVideoSeason_duration(swigCPtr, this);
  }

/** 
*  Duration units value (seconds, "SEC"). 
* 
*/ 
 
  public String durationUnits() {
    return gnsdk_javaJNI.GnVideoSeason_durationUnits(swigCPtr, this);
  }

/** 
*  Franchise number. 
* 
*/ 
 
  public long franchiseNum() {
    return gnsdk_javaJNI.GnVideoSeason_franchiseNum(swigCPtr, this);
  }

/** 
*  Franchise count. 
* 
*/ 
 
  public long franchiseCount() {
    return gnsdk_javaJNI.GnVideoSeason_franchiseCount(swigCPtr, this);
  }

/** 
*  Plot sypnosis, e.g., for Friends episode:."Monica's popularity at a karaoke club might have more to do with her revealing dress than her voice" 
* 
*/ 
 
  public String plotSynopsis() {
    return gnsdk_javaJNI.GnVideoSeason_plotSynopsis(swigCPtr, this);
  }

/** 
*  Plot sypnosis language, e.g., English 
* 
*/ 
 
  public String plotSynopsisLanguage() {
    return gnsdk_javaJNI.GnVideoSeason_plotSynopsisLanguage(swigCPtr, this);
  }

/** 
*  Plot tagline, e.g., "An adventure as big as life itself." 
* 
*/ 
 
  public String plotTagline() {
    return gnsdk_javaJNI.GnVideoSeason_plotTagline(swigCPtr, this);
  }

/** 
*  Serial type, e.g., Series or Episode 
* 
*/ 
 
  public String serialType() {
    return gnsdk_javaJNI.GnVideoSeason_serialType(swigCPtr, this);
  }

/** 
*  Work type, e.g., Musical 
* 
*/ 
 
  public String workType() {
    return gnsdk_javaJNI.GnVideoSeason_workType(swigCPtr, this);
  }

/** 
*  Target audience, e.g., "Kids and Family" 
* 
*/ 
 
  public String audience() {
    return gnsdk_javaJNI.GnVideoSeason_audience(swigCPtr, this);
  }

/** 
*  Video mood, e.g., Playful. 
* 
*/ 
 
  public String videoMood() {
    return gnsdk_javaJNI.GnVideoSeason_videoMood(swigCPtr, this);
  }

/** 
*  Overall story type, e.g., "Love Story". 
* 
*/ 
 
  public String storyType() {
    return gnsdk_javaJNI.GnVideoSeason_storyType(swigCPtr, this);
  }

/** 
*  Reputation, e.g., "Chick flick". 
* 
*/ 
 
  public String reputation() {
    return gnsdk_javaJNI.GnVideoSeason_reputation(swigCPtr, this);
  }

/** 
*  Scenario, e.g., Action 
* 
*/ 
 
  public String scenario() {
    return gnsdk_javaJNI.GnVideoSeason_scenario(swigCPtr, this);
  }

/** 
*  Setting environment, e.g., "High School" 
* 
*/ 
 
  public String settingEnvironment() {
    return gnsdk_javaJNI.GnVideoSeason_settingEnvironment(swigCPtr, this);
  }

/** 
*  Setting time period, e.g., "Jazz Age 1919-1929". 
* 
*/ 
 
  public String settingTimePeriod() {
    return gnsdk_javaJNI.GnVideoSeason_settingTimePeriod(swigCPtr, this);
  }

/** 
*  Topic value, e.g., "Teen Angst" 
* 
*/ 
 
  public String topic() {
    return gnsdk_javaJNI.GnVideoSeason_topic(swigCPtr, this);
  }

/** 
*  Season number. 
* 
*/ 
 
  public long seasonNumber() {
    return gnsdk_javaJNI.GnVideoSeason_seasonNumber(swigCPtr, this);
  }

/** 
*  Season count - total number of seasons. 
* 
*/ 
 
  public long seasonCount() {
    return gnsdk_javaJNI.GnVideoSeason_seasonCount(swigCPtr, this);
  }

/** 
*  Source, e.g., "Fairy Tales and Nursery Rhymes" 
* 
*/ 
 
  public String source() {
    return gnsdk_javaJNI.GnVideoSeason_source(swigCPtr, this);
  }

/** 
*  Style, e.g., "Film Noir" 
* 
*/ 
 
  public String style() {
    return gnsdk_javaJNI.GnVideoSeason_style(swigCPtr, this);
  }

/** 
*  Genre. This is a list/locale dependent, multi-level field. 
* <p> 
*  <p><b>Remarks:</b></p> 
*  This is a list-based value requiring that the list or locale be loaded into memory through a successful 
*  allocation of a <code>GnLocale</code> object 
* <p> 
*  To render locale-dependent information for list-based values, the application must allocate a {@link GnLocale} object. 
*  The SDK returns a <code>LocaleNotLoaded</code> message when locale information is not set prior to a request for 
*  a list-based value. 
* 
*/ 
 
  public String genre(GnDataLevel level) {
    return gnsdk_javaJNI.GnVideoSeason_genre(swigCPtr, this, level.swigValue());
  }

/** 
*  Origin, e.g., "New York City." List/locale dependent, multi-level field. 
*  <p><b>Remarks:</b></p> 
*  This is a list-based value requiring that the list or locale be loaded into memory through a successful 
*  allocation of a <code>GnLocale</code> object 
* <p> 
*  To render locale-dependent information for list-based values, the application must allocate a {@link GnLocale} object. 
*  The SDK returns a <code>LocaleNotLoaded</code> message when locale information is not set prior to a request for 
*  a list-based value. 
* 
*/ 
 
  public String origin(GnDataLevel level) {
    return gnsdk_javaJNI.GnVideoSeason_origin(swigCPtr, this, level.swigValue());
  }

/** 
*  Rating object. 
* 
*/ 
 
  public GnRating rating() {
    return new GnRating(gnsdk_javaJNI.GnVideoSeason_rating(swigCPtr, this), true);
  }

/** 
*   Official title object 
* 
*/ 
 
  public GnTitle officialTitle() {
    return new GnTitle(gnsdk_javaJNI.GnVideoSeason_officialTitle(swigCPtr, this), true);
  }

/** 
*  Franchise title object. 
* 
*/ 
 
  public GnTitle franchiseTitle() {
    return new GnTitle(gnsdk_javaJNI.GnVideoSeason_franchiseTitle(swigCPtr, this), true);
  }

  public GnExternalIdIterable externalIds() {
    return new GnExternalIdIterable(gnsdk_javaJNI.GnVideoSeason_externalIds(swigCPtr, this), true);
  }

  public GnVideoWorkIterable works() {
    return new GnVideoWorkIterable(gnsdk_javaJNI.GnVideoSeason_works(swigCPtr, this), true);
  }

  public GnVideoProductIterable products() {
    return new GnVideoProductIterable(gnsdk_javaJNI.GnVideoSeason_products(swigCPtr, this), true);
  }

  public GnVideoCreditIterable videoCredits() {
    return new GnVideoCreditIterable(gnsdk_javaJNI.GnVideoSeason_videoCredits(swigCPtr, this), true);
  }

  public GnContentIterable contents() {
    return new GnContentIterable(gnsdk_javaJNI.GnVideoSeason_contents(swigCPtr, this), true);
  }

  public GnVideoSeriesIterable series() {
    return new GnVideoSeriesIterable(gnsdk_javaJNI.GnVideoSeason_series(swigCPtr, this), true);
  }

}
