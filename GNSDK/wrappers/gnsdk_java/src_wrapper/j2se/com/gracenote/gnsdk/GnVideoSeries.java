
package com.gracenote.gnsdk;

/** 
**/ 
 
public class GnVideoSeries extends GnDataObject {
  private long swigCPtr;

  protected GnVideoSeries(long cPtr, boolean cMemoryOwn) {
    super(gnsdk_javaJNI.GnVideoSeries_SWIGUpcast(cPtr), cMemoryOwn);
    swigCPtr = cPtr;
  }

  protected static long getCPtr(GnVideoSeries obj) {
    return (obj == null) ? 0 : obj.swigCPtr;
  }

  protected void finalize() {
    delete();
  }

  public synchronized void delete() {
    if (swigCPtr != 0) {
      if (swigCMemOwn) {
        swigCMemOwn = false;
        gnsdk_javaJNI.delete_GnVideoSeries(swigCPtr);
      }
      swigCPtr = 0;
    }
    super.delete();
  }

  public GnVideoSeries(String id, String idTag) throws com.gracenote.gnsdk.GnException {
    this(gnsdk_javaJNI.new_GnVideoSeries(id, idTag), true);
  }

/** 
*  Flag indicating if response result contains full (true) or partial metadata. 
* <p><b>Note:</b></p> 
*  What constitutes a full result varies among responses and results and also 
*  depends on data availability. 
* 
*/ 
 
  public boolean isFullResult() {
    return gnsdk_javaJNI.GnVideoSeries_isFullResult(swigCPtr, this);
  }

/** 
*   Gracenote ID. 
* 
*/ 
 
  public String gnId() {
    return gnsdk_javaJNI.GnVideoSeries_gnId(swigCPtr, this);
  }

/** 
*   Gracenote unique ID. 
* 
*/ 
 
  public String gnUId() {
    return gnsdk_javaJNI.GnVideoSeries_gnUId(swigCPtr, this);
  }

/** 
*  Product ID, aka Tag ID 
*  <p><b>Remarks:</b></p> 
*  This value can be stored or transmitted - it is a static identifier for the current content and will not change over time. 
* 
*/ 
 
  public String productId() {
    return gnsdk_javaJNI.GnVideoSeries_productId(swigCPtr, this);
  }

/** 
*  TUI (title unique identifier) 
* 
*/ 
 
  public String tui() {
    return gnsdk_javaJNI.GnVideoSeries_tui(swigCPtr, this);
  }

/** 
*  TUI tag 
* 
*/ 
 
  public String tuiTag() {
    return gnsdk_javaJNI.GnVideoSeries_tuiTag(swigCPtr, this);
  }

/** 
*  Production type, e.g., Animation. This is a list/locale dependent field. 
*  <p><b>Remarks:</b></p> 
*  This is a list-based value requiring that a list or locale be loaded into memory. 
*  To render locale-dependent information for list-based values, the application must allocate a 
*  <code>GnLocale</code> object. The SDK returns 
*  a <code>LocaleNotLoaded</code> message when locale information is not set prior to a request for list-based value 
*  information. 
* 
*/ 
 
  public String videoProductionType() {
    return gnsdk_javaJNI.GnVideoSeries_videoProductionType(swigCPtr, this);
  }

/** 
*  Production type identifier 
* 
*/ 
 
  public long videoProductionTypeId() {
    return gnsdk_javaJNI.GnVideoSeries_videoProductionTypeId(swigCPtr, this);
  }

/** 
*  Original release date. Available for video Products, Features, and 
*  Works. 
* 
*/ 
 
  public String dateOriginalRelease() {
    return gnsdk_javaJNI.GnVideoSeries_dateOriginalRelease(swigCPtr, this);
  }

/** 
*  Duration value such as "3600" (seconds) for a 60-minute 
*  program. Available for video Chapters, Features, Products, Seasons, Series, and Works. 
* 
*/ 
 
  public long duration() {
    return gnsdk_javaJNI.GnVideoSeries_duration(swigCPtr, this);
  }

/** 
*  Duration units type (seconds, "SEC"). Available for video 
*  Chapters, Features, Products, Seasons, Series, and Works. 
* 
*/ 
 
  public String durationUnits() {
    return gnsdk_javaJNI.GnVideoSeries_durationUnits(swigCPtr, this);
  }

/** 
*  Franchise number. 
* 
*/ 
 
  public long franchiseNum() {
    return gnsdk_javaJNI.GnVideoSeries_franchiseNum(swigCPtr, this);
  }

/** 
*  Franchise count. 
* 
*/ 
 
  public long franchiseCount() {
    return gnsdk_javaJNI.GnVideoSeries_franchiseCount(swigCPtr, this);
  }

/** 
*  Plot synopsis, e.g., "A semi-autobiographical coming-of-age story" 
* 
*/ 
 
  public String plotSynopsis() {
    return gnsdk_javaJNI.GnVideoSeries_plotSynopsis(swigCPtr, this);
  }

/** 
*  Plot tagline, e.g., "If you forgot what terror was like...its back" 
* 
*/ 
 
  public String plotTagline() {
    return gnsdk_javaJNI.GnVideoSeries_plotTagline(swigCPtr, this);
  }

/** 
*  Plot synopsis language, e.g., English 
*  <p><b>Remarks:</b></p> 
*  The language depends on availability: information in the language set 
*  for the locale may not be available, and the object's information may be available only in its 
*  default official language. For example, if a locale's set language is Spanish, but the object's 
*  information is available only in English, this value returns as English. 
* 
*/ 
 
  public String plotSynopsisLanguage() {
    return gnsdk_javaJNI.GnVideoSeries_plotSynopsisLanguage(swigCPtr, this);
  }

/** 
*  Video serial type, e.g., Episode. 
*  <p><b>Remarks:</b></p> 
*  This is a list-based value requiring that a list or locale be loaded into memory 
*  To render locale-dependent information for list-based values, the application must allocate a 
*  <code>GnLocale</code> objec. The SDK returns 
*  a <code>LocaleNotLoaded</code> message when locale information is not set prior to a request for a list-based value 
* 
*/ 
 
  public String serialType() {
    return gnsdk_javaJNI.GnVideoSeries_serialType(swigCPtr, this);
  }

/** 
*  Work type, e.g., Musical 
*  <p><b>Remarks:</b></p> 
*  This is a list-based value requiring that the list be loaded into memory through a successful 
*  call to gnsdk_manager_locale_load. 
* <p> 
*  To render locale-dependent information for list-based values, the application must call 
*  <code>gnsdk_manager_locale_load</code> and possibly also <code>gnsdk_sdkmanager_gdo_set_locale</code>. The application returns 
*  a <code>LocaleNotLoaded</code> message when locale information is not set prior to a request for list-based value 
*  information. 
* 
*/ 
 
  public String workType() {
    return gnsdk_javaJNI.GnVideoSeries_workType(swigCPtr, this);
  }

/** 
*  Audience, e.g., "Young Adult" 
*  <p><b>Remarks:</b></p> 
*  This is a list-based value requiring that a list or locale be loaded into memory. 
*  To render locale-dependent information for list-based values, the application must allocate a 
*  <code>GnLocale</code> object. A <code>LocaleNotLoaded</code> message is returned when locale information 
*  is not set prior to a request for a list-based value. 
* 
*/ 
 
  public String audience() {
    return gnsdk_javaJNI.GnVideoSeries_audience(swigCPtr, this);
  }

/** 
*  Video mood, e.g., Somber 
*  <p><b>Remarks:</b></p> 
*  Mood information for music and video, depending on the respective calling type. 
* 
*/ 
 
  public String videoMood() {
    return gnsdk_javaJNI.GnVideoSeries_videoMood(swigCPtr, this);
  }

/** 
*  Story type, e.g., "Love Story" 
*  <p><b>Remarks:</b></p> 
*  This is a list-based value requiring that a list or locale be loaded into memory. 
* <p> 
*  To render locale-dependent information for list-based values, the application must allocate a 
*  <code>GnLocale</code> object. A <code>LocaleNotLoaded</code> message is returned when locale information 
*  is not set prior to a request for a list-based value. 
* 
*/ 
 
  public String storyType() {
    return gnsdk_javaJNI.GnVideoSeries_storyType(swigCPtr, this);
  }

/** 
*  Reputation, e.g., Cult 
*  <p><b>Remarks:</b></p> 
*  This is a list-based value requiring that a list or locale be loaded into memory. 
* <p> 
*  To render locale-dependent information for list-based values, the application must allocate a 
*  <code>GnLocale</code> object. A <code>LocaleNotLoaded</code> message is returned when locale information 
*  is not set prior to a request for a list-based value. 
* 
*/ 
 
  public String reputation() {
    return gnsdk_javaJNI.GnVideoSeries_reputation(swigCPtr, this);
  }

/** 
*  Scenario, e.g., Drama 
*  <p><b>Remarks:</b></p> 
*  This is a list-based value requiring that the list be loaded into memory through a successful 
*  call to gnsdk_manager_locale_load. 
* <p> 
*  To render locale-dependent information for list-based values, the application must call 
*  <code>gnsdk_manager_locale_load</code> and possibly also <code>gnsdk_sdkmanager_gdo_set_locale</code>. The application returns 
*  a <code>LocaleNotLoaded</code> message when locale information is not set prior to a request for list-based value 
*  information. 
* 
*/ 
 
  public String scenario() {
    return gnsdk_javaJNI.GnVideoSeries_scenario(swigCPtr, this);
  }

/** 
*  Setting environment, e.g., Skyscraper. 
*  <p><b>Remarks:</b></p> 
*  This is a list-based value requiring that a list or locale be loaded into memory. 
* <p> 
*  To render locale-dependent information for list-based values, the application must allocate a 
*  <code>GnLocale</code> object. A <code>LocaleNotLoaded</code> message is returned when locale information 
*  is not set prior to a request for a list-based value. 
* 
*/ 
 
  public String settingEnvironment() {
    return gnsdk_javaJNI.GnVideoSeries_settingEnvironment(swigCPtr, this);
  }

/** 
*  Historical time period such as "Elizabethan Era, 1558-1603" 
* 
*/ 
 
  public String settingTimePeriod() {
    return gnsdk_javaJNI.GnVideoSeries_settingTimePeriod(swigCPtr, this);
  }

/** 
*  Source, e.g., "Phillip K. Dick short story". 
*  <p><b>Remarks:</b></p> 
*  This is a list-based value requiring that a list or locale be loaded into memory. 
* <p> 
*  To render locale-dependent information for list-based values, the application must allocate a 
*  <code>GnLocale</code> object. A <code>LocaleNotLoaded</code> message is returned when locale information 
*  is not set prior to a request for a list-based value. 
* 
*/ 
 
  public String source() {
    return gnsdk_javaJNI.GnVideoSeries_source(swigCPtr, this);
  }

/** 
*  Style, such as "Film Noir" 
*  <p><b>Remarks:</b></p> 
*  This is a list-based value requiring that a list or locale be loaded into memory. 
* <p> 
*  To render locale-dependent information for list-based values, the application must allocate a 
*  <code>GnLocale</code> object. A <code>LocaleNotLoaded</code> message is returned when locale information 
*  is not set prior to a request for a list-based value. 
* 
*/ 
 
  public String style() {
    return gnsdk_javaJNI.GnVideoSeries_style(swigCPtr, this);
  }

/** 
*  Topic, such as Racing 
*  <p><b>Remarks:</b></p> 
*  This is a list-based value requiring that a list or locale be loaded into memory. 
* <p> 
*  To render locale-dependent information for list-based values, the application must allocate a 
*  <code>GnLocale</code> object. A <code>LocaleNotLoaded</code> message is returned when locale information 
*  is not set prior to a request for a list-based value. 
* 
*/ 
 
  public String topic() {
    return gnsdk_javaJNI.GnVideoSeries_topic(swigCPtr, this);
  }

/** 
*  Genre, e.g., Comedy. This ia a list/locale dependent, multi-level object. 
*  <p><b>Remarks:</b></p> 
*  This is a list-based value requiring that a list or locale be loaded into memory. 
* <p> 
*  To render locale-dependent information for list-based values, the application must allocate a 
*  <code>GnLocale</code> object. A <code>LocaleNotLoaded</code> message is returned when locale information 
*  is not set prior to a request for a list-based value. 
* 
*/ 
 
  public String genre(GnDataLevel level) {
    return gnsdk_javaJNI.GnVideoSeries_genre(swigCPtr, this, level.swigValue());
  }

/** 
*  Geographic location, e.g., "New York City". This is a list/locale dependent, multi-level field. 
*  <p><b>Remarks:</b></p> 
*  This is a list-based value requiring that a list or locale be loaded into memory. 
* <p> 
*  To render locale-dependent information for list-based values, the application must allocate a 
*  <code>GnLocale</code> object. A <code>LocaleNotLoaded</code> message is returned when locale information 
*  is not set prior to a request for a list-based value. 
* 
*/ 
 
  public String origin(GnDataLevel level) {
    return gnsdk_javaJNI.GnVideoSeries_origin(swigCPtr, this, level.swigValue());
  }

/** 
*  Rating object 
* 
*/ 
 
  public GnRating rating() {
    return new GnRating(gnsdk_javaJNI.GnVideoSeries_rating(swigCPtr, this), true);
  }

/** 
* Official title object 
* 
*/ 
 
  public GnTitle officialTitle() {
    return new GnTitle(gnsdk_javaJNI.GnVideoSeries_officialTitle(swigCPtr, this), true);
  }

/** 
*   Franchise title object. 
* 
*/ 
 
  public GnTitle franchiseTitle() {
    return new GnTitle(gnsdk_javaJNI.GnVideoSeries_franchiseTitle(swigCPtr, this), true);
  }

  public GnExternalIdIterable externalIds() {
    return new GnExternalIdIterable(gnsdk_javaJNI.GnVideoSeries_externalIds(swigCPtr, this), true);
  }

  public GnVideoWorkIterable works() {
    return new GnVideoWorkIterable(gnsdk_javaJNI.GnVideoSeries_works(swigCPtr, this), true);
  }

  public GnVideoProductIterable products() {
    return new GnVideoProductIterable(gnsdk_javaJNI.GnVideoSeries_products(swigCPtr, this), true);
  }

  public GnVideoSeasonIterable seasons() {
    return new GnVideoSeasonIterable(gnsdk_javaJNI.GnVideoSeries_seasons(swigCPtr, this), true);
  }

  public GnVideoCreditIterable videoCredits() {
    return new GnVideoCreditIterable(gnsdk_javaJNI.GnVideoSeries_videoCredits(swigCPtr, this), true);
  }

  public GnContentIterable contents() {
    return new GnContentIterable(gnsdk_javaJNI.GnVideoSeries_contents(swigCPtr, this), true);
  }

}
