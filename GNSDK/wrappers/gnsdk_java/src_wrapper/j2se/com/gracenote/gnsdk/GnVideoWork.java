
package com.gracenote.gnsdk;

/** 
**/ 
 
public class GnVideoWork extends GnDataObject {
  private long swigCPtr;

  protected GnVideoWork(long cPtr, boolean cMemoryOwn) {
    super(gnsdk_javaJNI.GnVideoWork_SWIGUpcast(cPtr), cMemoryOwn);
    swigCPtr = cPtr;
  }

  protected static long getCPtr(GnVideoWork obj) {
    return (obj == null) ? 0 : obj.swigCPtr;
  }

  protected void finalize() {
    delete();
  }

  public synchronized void delete() {
    if (swigCPtr != 0) {
      if (swigCMemOwn) {
        swigCMemOwn = false;
        gnsdk_javaJNI.delete_GnVideoWork(swigCPtr);
      }
      swigCPtr = 0;
    }
    super.delete();
  }

  public static String gnType() {
    return gnsdk_javaJNI.GnVideoWork_gnType();
  }

  public static GnVideoWork from(GnDataObject obj) throws com.gracenote.gnsdk.GnException {
    return new GnVideoWork(gnsdk_javaJNI.GnVideoWork_from(GnDataObject.getCPtr(obj), obj), true);
  }

  public GnVideoWork(String id, String idTag) throws com.gracenote.gnsdk.GnException {
    this(gnsdk_javaJNI.new_GnVideoWork(id, idTag), true);
  }

/** 
*  Flag indicating if result contains full (true) or partial metadata. 
* <p><b>Note:</b></p> 
*  What constitutes a full result varies among response types and results and also 
*  depends on data availability. 
* 
*/ 
 
  public boolean isFullResult() {
    return gnsdk_javaJNI.GnVideoWork_isFullResult(swigCPtr, this);
  }

/** 
*   Gracenote ID. 
* 
*/ 
 
  public String gnId() {
    return gnsdk_javaJNI.GnVideoWork_gnId(swigCPtr, this);
  }

/** 
*   Gracenote unique identifier 
* 
*/ 
 
  public String gnUId() {
    return gnsdk_javaJNI.GnVideoWork_gnUId(swigCPtr, this);
  }

/** 
*  Product ID aka Tag ID 
*  <p><b>Remarks:</b></p> 
*  This value which can be stored or transmitted - it can be used as a static identifier for the current 
*  content and will not change over time. 
* 
*/ 
 
  public String productId() {
    return gnsdk_javaJNI.GnVideoWork_productId(swigCPtr, this);
  }

/** 
*  TUI (title-unique identifier) 
* 
*/ 
 
  public String tui() {
    return gnsdk_javaJNI.GnVideoWork_tui(swigCPtr, this);
  }

/** 
*  TUI tag 
* 
*/ 
 
  public String tuiTag() {
    return gnsdk_javaJNI.GnVideoWork_tuiTag(swigCPtr, this);
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
* 
*/ 
 
  public String tuiMatchProduct() {
    return gnsdk_javaJNI.GnVideoWork_tuiMatchProduct(swigCPtr, this);
  }

/** 
*  Video production type ID 
* 
*/ 
 
  public long videoProductionTypeId() {
    return gnsdk_javaJNI.GnVideoWork_videoProductionTypeId(swigCPtr, this);
  }

/** 
*  Video production type, e.g., Animation. This is a list/locale dependent value. 
*  <p><b>Remarks:</b></p> 
*  This is a list-based value requiring that a list or locale be loaded into memory. 
* <p> 
*  To render locale-dependent information for list-based values, the application must allocate a 
*  <code>GnLocale</code> object. A <code>LocaleNotLoaded</code> message is returned when locale information 
*  is not set prior to a request for a list-based value. 
* 
*/ 
 
  public String videoProductionType() {
    return gnsdk_javaJNI.GnVideoWork_videoProductionType(swigCPtr, this);
  }

/** 
*  Video's original release date. 
* 
*/ 
 
  public String dateOriginalRelease() {
    return gnsdk_javaJNI.GnVideoWork_dateOriginalRelease(swigCPtr, this);
  }

/** 
*  Duration value in seconds such as "3600" (seconds) for a 60-minute program. 
* 
*/ 
 
  public long duration() {
    return gnsdk_javaJNI.GnVideoWork_duration(swigCPtr, this);
  }

/** 
*  Duration units value (seconds, "SEC"). 
* 
*/ 
 
  public String durationUnits() {
    return gnsdk_javaJNI.GnVideoWork_durationUnits(swigCPtr, this);
  }

/** 
*  Franchise number 
* 
*/ 
 
  public long franchiseNum() {
    return gnsdk_javaJNI.GnVideoWork_franchiseNum(swigCPtr, this);
  }

/** 
* Franchise count 
* 
*/ 
 
  public long franchiseCount() {
    return gnsdk_javaJNI.GnVideoWork_franchiseCount(swigCPtr, this);
  }

/** 
*  Series episode value 
* 
*/ 
 
  public long seriesEpisode() {
    return gnsdk_javaJNI.GnVideoWork_seriesEpisode(swigCPtr, this);
  }

/** 
*  Series episode count 
* 
*/ 
 
  public long seriesEpisodeCount() {
    return gnsdk_javaJNI.GnVideoWork_seriesEpisodeCount(swigCPtr, this);
  }

/** 
*  Season episode value. 
* 
*/ 
 
  public long seasonEpisode() {
    return gnsdk_javaJNI.GnVideoWork_seasonEpisode(swigCPtr, this);
  }

/** 
*  Season episode count 
* 
*/ 
 
  public long seasonEpisodeCount() {
    return gnsdk_javaJNI.GnVideoWork_seasonEpisodeCount(swigCPtr, this);
  }

/** 
*  Season count value 
* 
*/ 
 
  public long seasonCount() {
    return gnsdk_javaJNI.GnVideoWork_seasonCount(swigCPtr, this);
  }

/** 
* Season number value 
* 
*/ 
 
  public long seasonNumber() {
    return gnsdk_javaJNI.GnVideoWork_seasonNumber(swigCPtr, this);
  }

/** 
*  Plot synopsis e.g., "A semi-autobiographical coming-of-age story" 
* 
*/ 
 
  public String plotSynopsis() {
    return gnsdk_javaJNI.GnVideoWork_plotSynopsis(swigCPtr, this);
  }

/** 
*  Plot tagline, e.g., "The Third Dimension is Terror" 
* 
*/ 
 
  public String plotTagline() {
    return gnsdk_javaJNI.GnVideoWork_plotTagline(swigCPtr, this);
  }

/** 
*  Plot synopis language, e.g., English 
*  <p><b>Remarks:</b></p> 
*  The language of a returned object depends on availability. Information in the language set 
*   for the locale may not be available, and the object's information may be available only in its 
*   default official language. For example, if a locale's set language is Spanish, but the object's 
*   information is available only in English, this value returns as English. 
* 
*/ 
 
  public String plotSynopsisLanguage() {
    return gnsdk_javaJNI.GnVideoWork_plotSynopsisLanguage(swigCPtr, this);
  }

/** 
*  Supported video serial type such as Series or Episode 
*  <p><b>Remarks:</b></p> 
*  This is a list-based value requiring that a list or locale be loaded into memory. 
* <p> 
*  To render locale-dependent information for list-based values, the application must allocate a 
*  <code>GnLocale</code> object. A <code>LocaleNotLoaded</code> message is returned when locale information 
*  is not set prior to a request for a list-based value. 
* 
*/ 
 
  public String serialType() {
    return gnsdk_javaJNI.GnVideoWork_serialType(swigCPtr, this);
  }

/** 
*  Work type, e.g., Musical 
*  <p><b>Remarks:</b></p> 
*  This is a list-based value requiring that the list be loaded into memory through a successful 
*  call to gnsdk_manager_locale_load. 
* <p> 
*  To render locale-dependent information for list-based values, the application must call 
*   <code>gnsdk_manager_locale_load</code> and possibly also <code>gnsdk_sdkmanager_gdo_set_locale</code>. The application returns 
*   a <code>LocaleNotLoaded</code> message when locale information is not set prior to a request for list-based value 
*   information. 
* 
*/ 
 
  public String workType() {
    return gnsdk_javaJNI.GnVideoWork_workType(swigCPtr, this);
  }

/** 
*  Audience type, e.g.,"Kids and Family", "African-American", or "Young Adult". 
*  <p><b>Remarks:</b></p> 
*  This is a list-based value requiring that a list or locale be loaded into memory. 
* <p> 
*  To render locale-dependent information for list-based values, the application must allocate a 
*  <code>GnLocale</code> object. A <code>LocaleNotLoaded</code> message is returned when locale information 
*  is not set prior to a request for a list-based value. 
* 
*/ 
 
  public String audience() {
    return gnsdk_javaJNI.GnVideoWork_audience(swigCPtr, this);
  }

/** 
*  Mood, e.g., Playful 
* 
*/ 
 
  public String videoMood() {
    return gnsdk_javaJNI.GnVideoWork_videoMood(swigCPtr, this);
  }

/** 
*  Story type, e.g., "Love Story". 
*  <p><b>Remarks:</b></p> 
*  This is a list-based value requiring that a list or locale be loaded into memory. 
* <p> 
*  To render locale-dependent information for list-based values, the application must allocate a 
*  <code>GnLocale</code> object. A <code>LocaleNotLoaded</code> message is returned when locale information 
*  is not set prior to a request for a list-based value. 
* 
*/ 
 
  public String storyType() {
    return gnsdk_javaJNI.GnVideoWork_storyType(swigCPtr, this);
  }

/** 
*   Scenario, e.g., "Action", "Comedy", and "Drama". 
*  <p><b>Remarks:</b></p> 
*  This is a list-based value requiring that a list or locale be loaded into memory. 
* <p> 
*  To render locale-dependent information for list-based values, the application must allocate a 
*  <code>GnLocale</code> object. A <code>LocaleNotLoaded</code> message is returned when locale information 
*  is not set prior to a request for a list-based value. 
* 
*/ 
 
  public String scenario() {
    return gnsdk_javaJNI.GnVideoWork_scenario(swigCPtr, this);
  }

/** 
*  Physical environment - this is not specific location, but rather a general (or generic) 
*  location. For example: Prison, High School, Skyscraper, Desert, etc. 
*  <p><b>Remarks:</b></p> 
*  This is a list-based value requiring that a list or locale be loaded into memory. 
* <p> 
*  To render locale-dependent information for list-based values, the application must allocate a 
*  <code>GnLocale</code> object. A <code>LocaleNotLoaded</code> message is returned when locale information 
*  is not set prior to a request for a list-based value. 
* 
*/ 
 
  public String settingEnvironment() {
    return gnsdk_javaJNI.GnVideoWork_settingEnvironment(swigCPtr, this);
  }

/** 
* Historical time setting, e.g., "Elizabethan Era 1558-1603", or "Jazz Age 1919-1929". 
* 
*/ 
 
  public String settingTimePeriod() {
    return gnsdk_javaJNI.GnVideoWork_settingTimePeriod(swigCPtr, this);
  }

/** 
*  Story concept source, e.g., "Fairy Tales and Nursery Rhymes". 
*  <p><b>Remarks:</b></p> 
*  This is a list-based value requiring that a list or locale be loaded into memory. 
* <p> 
*  To render locale-dependent information for list-based values, the application must allocate a 
*  <code>GnLocale</code> object. A <code>LocaleNotLoaded</code> message is returned when locale information 
*  is not set prior to a request for a list-based value. 
* 
*/ 
 
  public String source() {
    return gnsdk_javaJNI.GnVideoWork_source(swigCPtr, this);
  }

/** 
*  Film style, e.g.,  "Film Noir". 
*  <p><b>Remarks:</b></p> 
*  This is a list-based value requiring that a list or locale be loaded into memory. 
* <p> 
*  To render locale-dependent information for list-based values, the application must allocate a 
*  <code>GnLocale</code> object. A <code>LocaleNotLoaded</code> message is returned when locale information 
*  is not set prior to a request for a list-based value. 
* 
*/ 
 
  public String style() {
    return gnsdk_javaJNI.GnVideoWork_style(swigCPtr, this);
  }

/** 
*  Film topic, e.g., "Racing" or "Teen Angst". 
*  <p><b>Remarks:</b></p> 
*  This is a list-based value requiring that a list or locale be loaded into memory. 
* <p> 
*  To render locale-dependent information for list-based values, the application must allocate a 
*  <code>GnLocale</code> object. A <code>LocaleNotLoaded</code> message is returned when locale information 
*  is not set prior to a request for a list-based value. 
* 
*/ 
 
  public String topic() {
    return gnsdk_javaJNI.GnVideoWork_topic(swigCPtr, this);
  }

/** 
*  Film's reputation, e.g., "Classic", "Chick Flick", or "Cult". This is a critical or 
*  popular "value" that is assigned to a work, usually long after the work was released, though some works may qualify 
*  shortly after release (e.g., "instant classic" or "blockbuster release"). 
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
 
  public String reputation() {
    return gnsdk_javaJNI.GnVideoWork_reputation(swigCPtr, this);
  }

/** 
*  Geographic location, e.g., "New York City". This is a list/locale dependent, multi-level field. 
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
 
  public String origin(GnDataLevel level) {
    return gnsdk_javaJNI.GnVideoWork_origin(swigCPtr, this, level.swigValue());
  }

/** 
* Genre - e.g., comedy. This is a list/locale dependent, multi-level field. 
* <p> 
*  <p><b>Remarks:</b></p> 
*  This is a list-based value requiring that a list or locale be loaded into memory. 
* <p> 
*  To render locale-dependent information for list-based values, the application must allocate a 
*  <code>GnLocale</code> object. A <code>LocaleNotLoaded</code> message is returned when locale information 
*  is not set prior to a request for a list-based value. 
* <p> 
*  This is a multi-level field requiring a <code>GnDataLevel</code> parameter 
* 
*/ 
 
  public String genre(GnDataLevel level) {
    return gnsdk_javaJNI.GnVideoWork_genre(swigCPtr, this, level.swigValue());
  }

/** 
*  Rating object 
* 
*/ 
 
  public GnRating rating() {
    return new GnRating(gnsdk_javaJNI.GnVideoWork_rating(swigCPtr, this), true);
  }

/** 
* Official title object 
* 
*/ 
 
  public GnTitle officialTitle() {
    return new GnTitle(gnsdk_javaJNI.GnVideoWork_officialTitle(swigCPtr, this), true);
  }

/** 
*  Franchise title object 
* 
*/ 
 
  public GnTitle franchiseTitle() {
    return new GnTitle(gnsdk_javaJNI.GnVideoWork_franchiseTitle(swigCPtr, this), true);
  }

/** 
*  Series title object. 
* 
*/ 
 
  public GnTitle seriesTitle() {
    return new GnTitle(gnsdk_javaJNI.GnVideoWork_seriesTitle(swigCPtr, this), true);
  }

  public GnVideoProductIterable products() {
    return new GnVideoProductIterable(gnsdk_javaJNI.GnVideoWork_products(swigCPtr, this), true);
  }

  public GnVideoCreditIterable videoCredits() {
    return new GnVideoCreditIterable(gnsdk_javaJNI.GnVideoWork_videoCredits(swigCPtr, this), true);
  }

  public GnVideoSeasonIterable seasons() {
    return new GnVideoSeasonIterable(gnsdk_javaJNI.GnVideoWork_seasons(swigCPtr, this), true);
  }

  public GnVideoSeriesIterable series() {
    return new GnVideoSeriesIterable(gnsdk_javaJNI.GnVideoWork_series(swigCPtr, this), true);
  }

  public GnExternalIdIterable externalIds() {
    return new GnExternalIdIterable(gnsdk_javaJNI.GnVideoWork_externalIds(swigCPtr, this), true);
  }

  public GnContentIterable contents() {
    return new GnContentIterable(gnsdk_javaJNI.GnVideoWork_contents(swigCPtr, this), true);
  }

}
