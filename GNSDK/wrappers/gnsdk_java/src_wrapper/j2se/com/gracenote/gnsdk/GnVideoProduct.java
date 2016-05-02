
package com.gracenote.gnsdk;

/** 
** A Product refers to the commercial release of a Film, TV Series, or video content. Products contain a 
* unique commercial code such as a UPC (Univeral Product Code), Hinban, or EAN (European Article Number). 
* Products are for the most part released on a physical format, such as a DVD or Blu-ray. 
*/ 
 
public class GnVideoProduct extends GnDataObject {
  private long swigCPtr;

  protected GnVideoProduct(long cPtr, boolean cMemoryOwn) {
    super(gnsdk_javaJNI.GnVideoProduct_SWIGUpcast(cPtr), cMemoryOwn);
    swigCPtr = cPtr;
  }

  protected static long getCPtr(GnVideoProduct obj) {
    return (obj == null) ? 0 : obj.swigCPtr;
  }

  protected void finalize() {
    delete();
  }

  public synchronized void delete() {
    if (swigCPtr != 0) {
      if (swigCMemOwn) {
        swigCMemOwn = false;
        gnsdk_javaJNI.delete_GnVideoProduct(swigCPtr);
      }
      swigCPtr = 0;
    }
    super.delete();
  }

  public static String gnType() {
    return gnsdk_javaJNI.GnVideoProduct_gnType();
  }

  public static GnVideoProduct from(GnDataObject obj) throws com.gracenote.gnsdk.GnException {
    return new GnVideoProduct(gnsdk_javaJNI.GnVideoProduct_from(GnDataObject.getCPtr(obj), obj), true);
  }

  public GnVideoProduct(String id, String idTag) throws com.gracenote.gnsdk.GnException {
    this(gnsdk_javaJNI.new_GnVideoProduct(id, idTag), true);
  }

/** 
*  Flag indicating if response result contains full (true) or partial metadata 
*	<p><b>Remarks:</b></p> 
*	Available for the following music and video types: 
*  <ul> 
*  <li>Album 
*  <li>Contributor 
*  <li>Track 
*  <li>Product 
*  <li>Season 
*  <li>Series 
*  <li>Work 
*  </ul> 
*	<p><b>Note:</b></p> 
*   What constitutes a full result varies among the individual response types and results, and also 
*	depends on data availability. 
* 
*/ 
 
  public boolean isFullResult() {
    return gnsdk_javaJNI.GnVideoProduct_isFullResult(swigCPtr, this);
  }

/** 
*	Gracenote ID 
* 
*/ 
 
  public String gnId() {
    return gnsdk_javaJNI.GnVideoProduct_gnId(swigCPtr, this);
  }

/** 
*	Gracenote unique ID 
* 
*/ 
 
  public String gnUId() {
    return gnsdk_javaJNI.GnVideoProduct_gnUId(swigCPtr, this);
  }

/** 
*	Product ID aka Tag ID 
*	<p><b>Remarks:</b></p> 
*	Available for most types, this value which can be stored or transmitted - it can bw used as a static identifier for the current content 
*  and will not change over time. 
* 
*/ 
 
  public String productId() {
    return gnsdk_javaJNI.GnVideoProduct_productId(swigCPtr, this);
  }

/** 
*	Tui (title-unique identifier) 
* 
*/ 
 
  public String tui() {
    return gnsdk_javaJNI.GnVideoProduct_tui(swigCPtr, this);
  }

/** 
*	Tui Tag value 
* 
*/ 
 
  public String tuiTag() {
    return gnsdk_javaJNI.GnVideoProduct_tuiTag(swigCPtr, this);
  }

/** 
*	Package display language, e.g., "English" 
*  <p><b>Remarks:</b></p> 
*	The language depends on availability - information in the language set 
*	for the locale may not be available, and the object's information may be available only in its 
*	default official language. For example, if a locale's set language is Spanish, but the object's 
*	information is available only in English, this value returns as English. 
* 
*/ 
 
  public String packageLanguageDisplay() {
    return gnsdk_javaJNI.GnVideoProduct_packageLanguageDisplay(swigCPtr, this);
  }

/** 
*	Package language ISO code, e.g., "eng". 
*	<p><b>Remarks:</b></p> 
*	GNSDK supports a subset of the ISO 639-2 Language Code List. 
*	Specify a locale language's lower-case three-letter code, which is shown in the macro's C/C++ 
*	syntax section. 
*	<p><b>Note:</b></p> 
*   The following languages use Gracenote-specific three-letter codes: 
*  <ul> 
*  <li>qtb (Simplified Chinese)* 
*  <li>qtd (Traditional Chinese)* 
*  </ul> 
* 
*/ 
 
  public String packageLanguage() {
    return gnsdk_javaJNI.GnVideoProduct_packageLanguage(swigCPtr, this);
  }

/** 
*	Video production type value, e.g., Documentary 
*  <p><b>Remarks:</b></p> 
*  This is a list-based value requiring that a list or locale be loaded into memory. 
* <p> 
*  To render locale-dependent information for list-based values, your application must allocate a 
*  <code>GnLocale</code> object. A <code>LocaleNotLoaded</code> message is returned when locale information 
*  is not set prior to a request for a list-based value. 
* 
*/ 
 
  public String videoProductionType() {
    return gnsdk_javaJNI.GnVideoProduct_videoProductionType(swigCPtr, this);
  }

/** 
*	Video production type identifier value 
* 
*/ 
 
  public long videoProductionTypeId() {
    return gnsdk_javaJNI.GnVideoProduct_videoProductionTypeId(swigCPtr, this);
  }

/** 
*	Original release date in UTC format. 
* 
*/ 
 
  public String dateOriginalRelease() {
    return gnsdk_javaJNI.GnVideoProduct_dateOriginalRelease(swigCPtr, this);
  }

/** 
*	Release date in UTC format 
*	<p><b>Remarks:</b></p> 
*	Release date values are not always available. 
* 
*/ 
 
  public String dateRelease() {
    return gnsdk_javaJNI.GnVideoProduct_dateRelease(swigCPtr, this);
  }

/** 
*	Duration value in seconds, such as "3600" for a 60-minute program. 
* 
*/ 
 
  public long duration() {
    return gnsdk_javaJNI.GnVideoProduct_duration(swigCPtr, this);
  }

/** 
*	Duration units value (seconds, "SEC"). 
* 
*/ 
 
  public String durationUnits() {
    return gnsdk_javaJNI.GnVideoProduct_durationUnits(swigCPtr, this);
  }

/** 
*	Aspect ratio- describes the proportional relationship between the video's width and its height 
* expressed as two numbers separated by a colon 
* 
*/ 
 
  public String aspectRatio() {
    return gnsdk_javaJNI.GnVideoProduct_aspectRatio(swigCPtr, this);
  }

/** 
*	Aspect ratio type, e.g., Standard 
* 
*/ 
 
  public String aspectRatioType() {
    return gnsdk_javaJNI.GnVideoProduct_aspectRatioType(swigCPtr, this);
  }

/** 
*	Video product region value, e.g, 1 
*  <p><b>Remarks:</b></p> 
*  This is a list-based value requiring that a list or locale be loaded into memory. 
* <p> 
*  To render locale-dependent information for list-based values, your application must allocate a 
*  <code>GnLocale</code> object. A <code>LocaleNotLoaded</code> message is returned when locale information 
*  is not set prior to a request for a list-based value. 
* 
*/ 
 
  public String videoRegion() {
    return gnsdk_javaJNI.GnVideoProduct_videoRegion(swigCPtr, this);
  }

/** 
*	Video product region description, e.g., USA, Canada, US Territories, Bermuda, and Cayman Islands 
*  <p><b>Remarks:</b></p> 
*  This is a list-based value requiring that a list or locale be loaded into memory. 
* <p> 
*  To render locale-dependent information for list-based values, your application must allocate a 
*  <code>GnLocale</code> object. A <code>LocaleNotLoaded</code> message is returned when locale information 
*  is not set prior to a request for a list-based value. 
* 
*/ 
 
  public String videoRegionDesc() {
    return gnsdk_javaJNI.GnVideoProduct_videoRegionDesc(swigCPtr, this);
  }

/** 
*	Notes 
* 
*/ 
 
  public String notes() {
    return gnsdk_javaJNI.GnVideoProduct_notes(swigCPtr, this);
  }

/** 
*	Commerce type value 
*	<p><b>Remarks:</b></p> 
*	For information on the specific values this key retrieves, contact your Gracenote Support 
*	Services representative. 
* 
*/ 
 
  public String commerceType() {
    return gnsdk_javaJNI.GnVideoProduct_commerceType(swigCPtr, this);
  }

/** 
*  Genre, e.g., Comedy. This is a list/locale dependent, multi-level field. 
*  <p><b>Remarks:</b></p> 
*  This is a list-based value requiring that a list or locale be loaded into memory. 
* <p> 
*  To render locale-dependent information for list-based values, your application must allocate a 
*  <code>GnLocale</code> object. A <code>LocaleNotLoaded</code> message is returned when locale information 
*  is not set prior to a request for a list-based value. 
* <p> 
*  This is a multi-level field requiring a <code>GnDataLevel</code> parameter 
* <p> 
* 
*/ 
 
  public String genre(GnDataLevel level) {
    return gnsdk_javaJNI.GnVideoProduct_genre(swigCPtr, this, level.swigValue());
  }

/** 
* Rating object. 
* 
*/ 
 
  public GnRating rating() {
    return new GnRating(gnsdk_javaJNI.GnVideoProduct_rating(swigCPtr, this), true);
  }

/** 
*	Official child title object 
* 
*/ 
 
  public GnTitle officialTitle() {
    return new GnTitle(gnsdk_javaJNI.GnVideoProduct_officialTitle(swigCPtr, this), true);
  }

  public GnExternalIdIterable externalIds() {
    return new GnExternalIdIterable(gnsdk_javaJNI.GnVideoProduct_externalIds(swigCPtr, this), true);
  }

  public GnVideoDiscIterable discs() {
    return new GnVideoDiscIterable(gnsdk_javaJNI.GnVideoProduct_discs(swigCPtr, this), true);
  }

  public GnContentIterable contents() {
    return new GnContentIterable(gnsdk_javaJNI.GnVideoProduct_contents(swigCPtr, this), true);
  }

}
