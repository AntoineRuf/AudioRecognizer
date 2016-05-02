
package com.gracenote.gnsdk;

/** 
* A person participating Album or Track creation. 
* Provides access to artist image when received from a query object 
* with content enabled in lookup data. 
*/ 
 
public class GnContributor extends GnDataObject {
  private long swigCPtr;

  protected GnContributor(long cPtr, boolean cMemoryOwn) {
    super(gnsdk_javaJNI.GnContributor_SWIGUpcast(cPtr), cMemoryOwn);
    swigCPtr = cPtr;
  }

  protected static long getCPtr(GnContributor obj) {
    return (obj == null) ? 0 : obj.swigCPtr;
  }

  protected void finalize() {
    delete();
  }

  public synchronized void delete() {
    if (swigCPtr != 0) {
      if (swigCMemOwn) {
        swigCMemOwn = false;
        gnsdk_javaJNI.delete_GnContributor(swigCPtr);
      }
      swigCPtr = 0;
    }
    super.delete();
  }

  public static String gnType() {
    return gnsdk_javaJNI.GnContributor_gnType();
  }

  public static GnContributor from(GnDataObject obj) throws com.gracenote.gnsdk.GnException {
    return new GnContributor(gnsdk_javaJNI.GnContributor_from(GnDataObject.getCPtr(obj), obj), true);
  }

/** 
* Constructs a {@link GnContributor} from a Gracenote identifier and identifier tag 
* @param id	[in] Identifier 
* @param idTag [in] Identifier tag 
*/ 
 
  public GnContributor(String id, String idTag) throws com.gracenote.gnsdk.GnException {
    this(gnsdk_javaJNI.new_GnContributor(id, idTag), true);
  }

/** 
*  Flag indicating if data object response contains full (true) or partial metadata. 
*  Returns true if full, false if partial. 
* <p><b>Note:</b></p> 
*   What constitutes a full result varies among the individual response types and results, and also 
*  depends on data availability. 
* 
*/ 
 
  public boolean isFullResult() {
    return gnsdk_javaJNI.GnContributor_isFullResult(swigCPtr, this);
  }

/** 
* Contributor's Gracenote identifier 
* @return Gracenote ID 
*/ 
 
  public String gnId() {
    return gnsdk_javaJNI.GnContributor_gnId(swigCPtr, this);
  }

/** 
* Contributor's Gracenote unique identifier. 
* @return Gracenote Unique ID 
*/ 
 
  public String gnUId() {
    return gnsdk_javaJNI.GnContributor_gnUId(swigCPtr, this);
  }

/** 
* Retrieves the contributor's product identifier. 
* @return Gracenote Product ID 
* <p><b>Remarks:</b></p> 
* Available for most types, this retrieves a value which can be stored or transmitted. This 
* value can be used as a static identifier for the current content as it will not change over time. 
*/ 
 
  public String productId() {
    return gnsdk_javaJNI.GnContributor_productId(swigCPtr, this);
  }

/** 
* Contributor's Gracenote Tui (title-unique identifier) 
* @return Tui 
*/ 
 
  public String tui() {
    return gnsdk_javaJNI.GnContributor_tui(swigCPtr, this);
  }

/** 
* Contributor's Gracenote Tui Tag 
* @return Tui Tag 
*/ 
 
  public String tuiTag() {
    return gnsdk_javaJNI.GnContributor_tuiTag(swigCPtr, this);
  }

/** 
* Contributor's birth date. 
* @return Date of birth 
*/ 
 
  public String birthDate() {
    return gnsdk_javaJNI.GnContributor_birthDate(swigCPtr, this);
  }

/** 
* Contributor's place of birth. 
* @return Place of birth 
*/ 
 
  public String birthPlace() {
    return gnsdk_javaJNI.GnContributor_birthPlace(swigCPtr, this);
  }

/** 
* Date contributor died 
* @return Date of death 
*/ 
 
  public String deathDate() {
    return gnsdk_javaJNI.GnContributor_deathDate(swigCPtr, this);
  }

/** 
* Contributor's place of death. 
* @return Place of death 
*/ 
 
  public String deathPlace() {
    return gnsdk_javaJNI.GnContributor_deathPlace(swigCPtr, this);
  }

/** 
* Contributor's media space, e.g., music, film, stage. List/locale dependent field. 
* @return Media space 
* <p><b>Remarks:</b></p> 
* This is a list-based value requiring that a corresponding locale or list be loaded. 
*/ 
 
  public String mediaSpace() {
    return gnsdk_javaJNI.GnContributor_mediaSpace(swigCPtr, this);
  }

/** 
*  Content (cover art, review, etc) object 
*  @param {@link GnContentType} object 
*  @return Content object 
*/ 
 
  public GnContent content(GnContentType contentType) {
    return new GnContent(gnsdk_javaJNI.GnContributor_content(swigCPtr, this, contentType.swigValue()), true);
  }

/** 
*  Fetch the contributor's image content object 
*  @return Content object 
*/ 
 
  public GnContent image() {
    return new GnContent(gnsdk_javaJNI.GnContributor_image(swigCPtr, this), true);
  }

/** 
* Contributor's biography when received from a video response. 
* When the contributor object was derived from a video response use this 
* method to btain the biography. 
* @return Biography 
*/ 
 
  public String biographyVideo() {
    return gnsdk_javaJNI.GnContributor_biographyVideo(swigCPtr, this);
  }

/** 
* Fetch the contributor's biography content object. 
* @return Content object 
*/ 
 
  public GnContent biography() {
    return new GnContent(gnsdk_javaJNI.GnContributor_biography(swigCPtr, this), true);
  }

/** 
* Contributor name object 
* @return Name 
*/ 
 
  public GnName name() {
    return new GnName(gnsdk_javaJNI.GnContributor_name(swigCPtr, this), true);
  }

  public GnNameIterable namesOfficial() {
    return new GnNameIterable(gnsdk_javaJNI.GnContributor_namesOfficial(swigCPtr, this), true);
  }

  public GnNameIterable namesRegional() {
    return new GnNameIterable(gnsdk_javaJNI.GnContributor_namesRegional(swigCPtr, this), true);
  }

  public GnContentIterable contents() {
    return new GnContentIterable(gnsdk_javaJNI.GnContributor_contents(swigCPtr, this), true);
  }

  public GnExternalIdIterable externalIds() {
    return new GnExternalIdIterable(gnsdk_javaJNI.GnContributor_externalIds(swigCPtr, this), true);
  }

/** 
* Contributor that collaborated with this contributor in the context of the returned result. 
* @return Contributor 
*/ 
 
  public GnContributor collaborator() {
    return new GnContributor(gnsdk_javaJNI.GnContributor_collaborator(swigCPtr, this), true);
  }

/** 
* Contributor's genre. List/locale, multi-level field. 
* @param level	[in] Data level 
* @return Genre 
* <p><b>Remarks:</b></p> 
* This is a list-based value requiring that a corresponding locale or list be loaded. 
*/ 
 
  public String genre(GnDataLevel level) {
    return gnsdk_javaJNI.GnContributor_genre(swigCPtr, this, level.swigValue());
  }

/** 
* Contributor's origin, e.g., New York City 
* @param level 	[in] Data level 
* @return Origin 
* <p><b>Remarks:</b></p> 
* This is a list-based value requiring that a corresponding locale or list be loaded. 
*/ 
 
  public String origin(GnDataLevel level) {
    return gnsdk_javaJNI.GnContributor_origin(swigCPtr, this, level.swigValue());
  }

/** 
* Contributor's era. List/locale dependent, multi-level field. 
* @param level	[in] Data level 
* @return Era 
* <p><b>Remarks:</b></p> 
* This is a list-based value requiring that a corresponding locale or list be loaded. 
*/ 
 
  public String era(GnDataLevel level) {
    return gnsdk_javaJNI.GnContributor_era(swigCPtr, this, level.swigValue());
  }

/** 
* Contributor's artist type. List/locale dependent, multi-level field. 
* @param level	[in] Data level 
* @return Artist type 
* <p><b>Remarks:</b></p> 
* This is a list-based value requiring that a corresponding locale or list be loaded. 
*/ 
 
  public String artistType(GnDataLevel level) {
    return gnsdk_javaJNI.GnContributor_artistType(swigCPtr, this, level.swigValue());
  }

/** 
*  Get flag indicating if this is a collaborator result 
*  @return True if a collaborator result, false otherwise 
*/ 
 
  public boolean collaboratorResult() {
    return gnsdk_javaJNI.GnContributor_collaboratorResult(swigCPtr, this);
  }

}
