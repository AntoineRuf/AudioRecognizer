
package com.gracenote.gnsdk;

/** 
** A collection of classical music recordings. 
*/ 
 
public class GnAudioWork extends GnDataObject {
  private long swigCPtr;

  protected GnAudioWork(long cPtr, boolean cMemoryOwn) {
    super(gnsdk_javaJNI.GnAudioWork_SWIGUpcast(cPtr), cMemoryOwn);
    swigCPtr = cPtr;
  }

  protected static long getCPtr(GnAudioWork obj) {
    return (obj == null) ? 0 : obj.swigCPtr;
  }

  protected void finalize() {
    delete();
  }

  public synchronized void delete() {
    if (swigCPtr != 0) {
      if (swigCMemOwn) {
        swigCMemOwn = false;
        gnsdk_javaJNI.delete_GnAudioWork(swigCPtr);
      }
      swigCPtr = 0;
    }
    super.delete();
  }

  public static String gnType() {
    return gnsdk_javaJNI.GnAudioWork_gnType();
  }

  public static GnAudioWork from(GnDataObject obj) throws com.gracenote.gnsdk.GnException {
    return new GnAudioWork(gnsdk_javaJNI.GnAudioWork_from(GnDataObject.getCPtr(obj), obj), true);
  }

/** 
* Audio work's official title. 
* @return Title 
*/ 
 
  public GnTitle title() {
    return new GnTitle(gnsdk_javaJNI.GnAudioWork_title(swigCPtr, this), true);
  }

/** 
* Credit object for this audio work. 
* @return Credit 
*/ 
 
  public GnCredit credit() {
    return new GnCredit(gnsdk_javaJNI.GnAudioWork_credit(swigCPtr, this), true);
  }

/** 
* Gracenote Tui (title unique identifier) for this audio work. 
* @return Tui 
*/ 
 
  public String tui() {
    return gnsdk_javaJNI.GnAudioWork_tui(swigCPtr, this);
  }

/** 
* Gracenote Tui Tag for this audio work. 
* @return Tui Tag 
*/ 
 
  public String tuiTag() {
    return gnsdk_javaJNI.GnAudioWork_tuiTag(swigCPtr, this);
  }

/** 
* Gracenote Tag identifier for this audio work (Tag ID is same as Product ID) 
* @return Tag identifier 
* <p><b>Remarks:</b></p> 
* This method exists primarily to support legacy implementations. We recommend using 
* the Product ID method to retrieve product related identifiers 
*/ 
 
  public String tagId() {
    return gnsdk_javaJNI.GnAudioWork_tagId(swigCPtr, this);
  }

/** 
* Audio work's Gracenote identifier 
* @return Gracenote identifier 
*/ 
 
  public String gnId() {
    return gnsdk_javaJNI.GnAudioWork_gnId(swigCPtr, this);
  }

/** 
* Audio work's Gracenote unique identifier. 
* @return Gracenote unique identifier 
*/ 
 
  public String gnUId() {
    return gnsdk_javaJNI.GnAudioWork_gnUId(swigCPtr, this);
  }

/** 
* Audio work's product ID (aka Tag ID). 
* <p><b>Remarks:</b></p> 
* Available for most types, this value can be stored or transmitted. Can 
* be used as a static identifier for the current content as it will not change over time. 
* 
*/ 
 
  public String productId() {
    return gnsdk_javaJNI.GnAudioWork_productId(swigCPtr, this);
  }

/** 
* Audio work's geographic location, e.g., New York City. List/locale dependent multi-leveled field. 
* @param level	[in] Data level 
* @return Origin 
* <p><b>Remarks:</b></p> 
* This is a list-based value requiring that a corresponding locale or list be loaded. 
*/ 
 
  public String origin(GnDataLevel level) {
    return gnsdk_javaJNI.GnAudioWork_origin(swigCPtr, this, level.swigValue());
  }

/** 
* Audio work's era. List/locale dependent, multi-leveled field. 
* @param level	[in] Data level 
* @return Era 
* <p><b>Remarks:</b></p> 
* This is a list-based value requiring that a corresponding locale or list be loaded. 
*/ 
 
  public String era(GnDataLevel level) {
    return gnsdk_javaJNI.GnAudioWork_era(swigCPtr, this, level.swigValue());
  }

/** 
* Audio work's genre, e.g. punk rock, rock opera, etc. List/locale dependent, multi-level field. 
* @param level	[in] Data level 
* @return Genre 
* <p><b>Remarks:</b></p> 
* This is a list-based value requiring that a corresponding locale or list be loaded. 
*/ 
 
  public String genre(GnDataLevel level) {
    return gnsdk_javaJNI.GnAudioWork_genre(swigCPtr, this, level.swigValue());
  }

/** 
* Audio work's classical music composition form value (e.g., Symphony). 
* @return Compsition form 
* <p><b>Remarks:</b></p> 
* This is a list-based value requiring that a corresponding locale or list be loaded. 
*/ 
 
  public String compositionForm() {
    return gnsdk_javaJNI.GnAudioWork_compositionForm(swigCPtr, this);
  }

}
