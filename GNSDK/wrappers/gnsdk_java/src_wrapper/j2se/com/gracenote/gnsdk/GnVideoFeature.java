
package com.gracenote.gnsdk;

/** 
** Class containing metadata for a video feature, which has a full-length running time usually between 60 and 120 minutes. 
* A feature is the main component of a DVD or Blu-ray disc which may, in addition, contain extra, or bonus, video clips and features. 
* <p> 
*/ 
 
public class GnVideoFeature extends GnDataObject {
  private long swigCPtr;

  protected GnVideoFeature(long cPtr, boolean cMemoryOwn) {
    super(gnsdk_javaJNI.GnVideoFeature_SWIGUpcast(cPtr), cMemoryOwn);
    swigCPtr = cPtr;
  }

  protected static long getCPtr(GnVideoFeature obj) {
    return (obj == null) ? 0 : obj.swigCPtr;
  }

  protected void finalize() {
    delete();
  }

  public synchronized void delete() {
    if (swigCPtr != 0) {
      if (swigCMemOwn) {
        swigCMemOwn = false;
        gnsdk_javaJNI.delete_GnVideoFeature(swigCPtr);
      }
      swigCPtr = 0;
    }
    super.delete();
  }

  public static String gnType() {
    return gnsdk_javaJNI.GnVideoFeature_gnType();
  }

  public static GnVideoFeature from(GnDataObject obj) throws com.gracenote.gnsdk.GnException {
    return new GnVideoFeature(gnsdk_javaJNI.GnVideoFeature_from(GnDataObject.getCPtr(obj), obj), true);
  }

/** 
*  Feature's ordinal value 
* 
*/ 
 
  public long ordinal() {
    return gnsdk_javaJNI.GnVideoFeature_ordinal(swigCPtr, this);
  }

/** 
*  Matched boolean value indicating whether this type 
*  is the one that matched the input criteria. Available from many video types. 
* 
*/ 
 
  public boolean matched() {
    return gnsdk_javaJNI.GnVideoFeature_matched(swigCPtr, this);
  }

/** 
*  Video feature type value. 
*  <p><b>Remarks:</b></p> 
*  This is a list-based value requiring that a list or locale be loaded into memory. 
* <p> 
*  To render locale-dependent information for list-based values, the application must allocate a 
*  <code>GnLocale</code> object. A <code>LocaleNotLoaded</code> message is returned when locale information 
*  is not set prior to a request for a list-based value. 
* 
*/ 
 
  public String videoFeatureType() {
    return gnsdk_javaJNI.GnVideoFeature_videoFeatureType(swigCPtr, this);
  }

/** 
*  Video production type value. 
*  <p><b>Remarks:</b></p> 
*  This is a list-based value requiring that a list or locale be loaded into memory. 
* <p> 
*  To render locale-dependent information for list-based values, the application must allocate a 
*  <code>GnLocale</code> object. A <code>LocaleNotLoaded</code> message is returned when locale information 
*  is not set prior to a request for a list-based value. 
* 
*/ 
 
  public String videoProductionType() {
    return gnsdk_javaJNI.GnVideoFeature_videoProductionType(swigCPtr, this);
  }

/** 
*  Video production ID type value 
* 
*/ 
 
  public long videoProductionTypeId() {
    return gnsdk_javaJNI.GnVideoFeature_videoProductionTypeId(swigCPtr, this);
  }

/** 
*  Release date in UTC format 
* 
*/ 
 
  public String dateRelease() {
    return gnsdk_javaJNI.GnVideoFeature_dateRelease(swigCPtr, this);
  }

/** 
*  Original release date in UTC format. 
* 
*/ 
 
  public String dateOriginalRelease() {
    return gnsdk_javaJNI.GnVideoFeature_dateOriginalRelease(swigCPtr, this);
  }

/** 
*  Notes 
* 
*/ 
 
  public String notes() {
    return gnsdk_javaJNI.GnVideoFeature_notes(swigCPtr, this);
  }

/** 
* Aspect ratio - describes the proportional relationship between the video's width and its height 
* expressed as two numbers separated by a colon 
* 
*/ 
 
  public String aspectRatio() {
    return gnsdk_javaJNI.GnVideoFeature_aspectRatio(swigCPtr, this);
  }

/** 
*  Aspect ratio type, e.g., Standard 
* 
*/ 
 
  public String aspectRatioType() {
    return gnsdk_javaJNI.GnVideoFeature_aspectRatioType(swigCPtr, this);
  }

/** 
*  Duration value in seconds. 
* 
*/ 
 
  public long duration() {
    return gnsdk_javaJNI.GnVideoFeature_duration(swigCPtr, this);
  }

/** 
*  Duration units value (e.g., seconds, "SEC") 
* 
*/ 
 
  public String durationUnits() {
    return gnsdk_javaJNI.GnVideoFeature_durationUnits(swigCPtr, this);
  }

/** 
*  Plot summary 
* 
*/ 
 
  public String plotSummary() {
    return gnsdk_javaJNI.GnVideoFeature_plotSummary(swigCPtr, this);
  }

/** 
*  Plot synopsis, e.g., (for Friends episode) "Monica's popularity at a karaoke club might have more to do with her revealing dress than her voice; 
* 
*/ 
 
  public String plotSynopsis() {
    return gnsdk_javaJNI.GnVideoFeature_plotSynopsis(swigCPtr, this);
  }

/** 
*  Plot tagline, e.g., "The terrifying motion picture from the terrifying No. 1 best seller." 
*  GNSDK_GDO_VALUE_PLOT_TAGLINE 
* 
*/ 
 
  public String plotTagline() {
    return gnsdk_javaJNI.GnVideoFeature_plotTagline(swigCPtr, this);
  }

/** 
*  Plot synopsis language, e.g., English 
*  <p><b>Remarks:</b></p> 
*  The language depends on availability - information in the language set 
*   for the locale may not be available, and the object's information may be available only in its 
*   default official language. For example, if a locale's set language is Spanish, but the object's 
*   information is available only in English, this value returns as English. 
* 
*/ 
 
  public String plotSynopsisLanguage() {
    return gnsdk_javaJNI.GnVideoFeature_plotSynopsisLanguage(swigCPtr, this);
  }

/** 
* Genre. e.g., Drama. This is a list/locale dependent,multi-level field 
*  <p><b>Remarks:</b></p> 
*  This is a list-based value requiring that a list or locale be loaded into memory. 
* <p> 
*  To render locale-dependent information for list-based values, the application must allocate a 
*  <code>GnLocale</code> object. A <code>LocaleNotLoaded</code> message is returned when locale information 
*  is not set prior to a request for a list-based value. 
* <p> 
*  This is a multi-level field requiring a <code>GnDataLevel</code> parameter 
* <p> 
* 
*/ 
 
  public String genre(GnDataLevel level) {
    return gnsdk_javaJNI.GnVideoFeature_genre(swigCPtr, this, level.swigValue());
  }

/** 
*  Official title object 
* 
*/ 
 
  public GnTitle officialTitle() {
    return new GnTitle(gnsdk_javaJNI.GnVideoFeature_officialTitle(swigCPtr, this), true);
  }

/** 
*  Rating object 
* 
*/ 
 
  public GnRating rating() {
    return new GnRating(gnsdk_javaJNI.GnVideoFeature_rating(swigCPtr, this), true);
  }

  public GnVideoWorkIterable works() {
    return new GnVideoWorkIterable(gnsdk_javaJNI.GnVideoFeature_works(swigCPtr, this), true);
  }

  public GnVideoChapterIterable chapters() {
    return new GnVideoChapterIterable(gnsdk_javaJNI.GnVideoFeature_chapters(swigCPtr, this), true);
  }

  public GnVideoCreditIterable videoCredits() {
    return new GnVideoCreditIterable(gnsdk_javaJNI.GnVideoFeature_videoCredits(swigCPtr, this), true);
  }

}
