/* ----------------------------------------------------------------------------
 * This file was automatically generated by SWIG (http://www.swig.org).
 * Version 2.0.12
 *
 * Do not make changes to this file unless you know what you are doing--modify
 * the SWIG interface file instead.
 * ----------------------------------------------------------------------------- */

package com.gracenote.gnsdk;

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

  public GnContributor(String id, String idTag) throws com.gracenote.gnsdk.GnException {
    this(gnsdk_javaJNI.new_GnContributor(id, idTag), true);
  }

  public boolean isFullResult() {
    return gnsdk_javaJNI.GnContributor_isFullResult(swigCPtr, this);
  }

  public String gnId() {
    return gnsdk_javaJNI.GnContributor_gnId(swigCPtr, this);
  }

  public String gnUId() {
    return gnsdk_javaJNI.GnContributor_gnUId(swigCPtr, this);
  }

  public String productId() {
    return gnsdk_javaJNI.GnContributor_productId(swigCPtr, this);
  }

  public String tui() {
    return gnsdk_javaJNI.GnContributor_tui(swigCPtr, this);
  }

  public String tuiTag() {
    return gnsdk_javaJNI.GnContributor_tuiTag(swigCPtr, this);
  }

  public String birthDate() {
    return gnsdk_javaJNI.GnContributor_birthDate(swigCPtr, this);
  }

  public String birthPlace() {
    return gnsdk_javaJNI.GnContributor_birthPlace(swigCPtr, this);
  }

  public String deathDate() {
    return gnsdk_javaJNI.GnContributor_deathDate(swigCPtr, this);
  }

  public String deathPlace() {
    return gnsdk_javaJNI.GnContributor_deathPlace(swigCPtr, this);
  }

  public String mediaSpace() {
    return gnsdk_javaJNI.GnContributor_mediaSpace(swigCPtr, this);
  }

  public GnContent content(GnContentType contentType) {
    return new GnContent(gnsdk_javaJNI.GnContributor_content(swigCPtr, this, contentType.swigValue()), true);
  }

  public GnContent image() {
    return new GnContent(gnsdk_javaJNI.GnContributor_image(swigCPtr, this), true);
  }

  public String biographyVideo() {
    return gnsdk_javaJNI.GnContributor_biographyVideo(swigCPtr, this);
  }

  public GnContent biography() {
    return new GnContent(gnsdk_javaJNI.GnContributor_biography(swigCPtr, this), true);
  }

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

  public GnContributor collaborator() {
    return new GnContributor(gnsdk_javaJNI.GnContributor_collaborator(swigCPtr, this), true);
  }

  public String genre(GnDataLevel level) {
    return gnsdk_javaJNI.GnContributor_genre(swigCPtr, this, level.swigValue());
  }

  public String origin(GnDataLevel level) {
    return gnsdk_javaJNI.GnContributor_origin(swigCPtr, this, level.swigValue());
  }

  public String era(GnDataLevel level) {
    return gnsdk_javaJNI.GnContributor_era(swigCPtr, this, level.swigValue());
  }

  public String artistType(GnDataLevel level) {
    return gnsdk_javaJNI.GnContributor_artistType(swigCPtr, this, level.swigValue());
  }

  public boolean collaboratorResult() {
    return gnsdk_javaJNI.GnContributor_collaboratorResult(swigCPtr, this);
  }

}
