
package com.gracenote.gnsdk;

/** 
** Both DVDs and Blu-ray Discs can be dual layer. These discs are only writable on one side of the disc, 
* but contain two layers on that single side for writing data to. Dual-Layer recordable DVDs come in two formats: DVD-R DL and DVD+R DL. 
* They can hold up to 8.5GB on the two layers. Dual-layer Blu-ray discs can store 50 GB of data (25GB on each layer) 
*/ 
 
public class GnVideoLayer extends GnDataObject {
  private long swigCPtr;

  protected GnVideoLayer(long cPtr, boolean cMemoryOwn) {
    super(gnsdk_javaJNI.GnVideoLayer_SWIGUpcast(cPtr), cMemoryOwn);
    swigCPtr = cPtr;
  }

  protected static long getCPtr(GnVideoLayer obj) {
    return (obj == null) ? 0 : obj.swigCPtr;
  }

  protected void finalize() {
    delete();
  }

  public synchronized void delete() {
    if (swigCPtr != 0) {
      if (swigCMemOwn) {
        swigCMemOwn = false;
        gnsdk_javaJNI.delete_GnVideoLayer(swigCPtr);
      }
      swigCPtr = 0;
    }
    super.delete();
  }

  public static String gnType() {
    return gnsdk_javaJNI.GnVideoLayer_gnType();
  }

  public static GnVideoLayer from(GnDataObject obj) throws com.gracenote.gnsdk.GnException {
    return new GnVideoLayer(gnsdk_javaJNI.GnVideoLayer_from(GnDataObject.getCPtr(obj), obj), true);
  }

/** 
*  Ordinal value 
* 
*/ 
 
  public long ordinal() {
    return gnsdk_javaJNI.GnVideoLayer_ordinal(swigCPtr, this);
  }

/** 
*  Matched boolean value indicating whether this object 
*   is the one that matched the input criteria. 
* 
*/ 
 
  public boolean matched() {
    return gnsdk_javaJNI.GnVideoLayer_matched(swigCPtr, this);
  }

/** 
*  Aspect ratio - describes the proportional relationship between the video's width and its height 
* expressed as two numbers separated by a colon 
* 
*/ 
 
  public String aspectRatio() {
    return gnsdk_javaJNI.GnVideoLayer_aspectRatio(swigCPtr, this);
  }

/** 
*  Aspect ratio type, e.g. Standard 
* 
*/ 
 
  public String aspectRatioType() {
    return gnsdk_javaJNI.GnVideoLayer_aspectRatioType(swigCPtr, this);
  }

/** 
*  TV system value, e.g., NTSC. 
* 
*/ 
 
  public String tvSystem() {
    return gnsdk_javaJNI.GnVideoLayer_tvSystem(swigCPtr, this);
  }

/** 
*  Region code, e.g., FE - France 
* 
*/ 
 
  public String regionCode() {
    return gnsdk_javaJNI.GnVideoLayer_regionCode(swigCPtr, this);
  }

/** 
*  Video product region value from the current type, e.g., 1. This is a list/locale dependent value. 
*  <p><b>Remarks:</b></p> 
*  This is a list-based value requiring that a list or locale be loaded into memory. 
* <p> 
*  To render locale-dependent information for list-based values, the application must allocate a 
*  <code>GnLocale</code> object. A <code>LocaleNotLoaded</code> message is returned when locale information 
*  is not set prior to a request for a list-based value. 
* 
*/ 
 
  public String videoRegion() {
    return gnsdk_javaJNI.GnVideoLayer_videoRegion(swigCPtr, this);
  }

/** 
*  Video product region, e.g.,  USA, Canada, US Territories, Bermuda, and Cayman Islands. 
*  <p><b>Remarks:</b></p> 
*  This is a list-based value requiring that a list or locale be loaded into memory. 
* <p> 
*  To render locale-dependent information for list-based values, the application must allocate a 
*  <code>GnLocale</code> object. A <code>LocaleNotLoaded</code> message is returned when locale information 
*  is not set prior to a request for a list-based value. 
* 
*/ 
 
  public String videoRegionDesc() {
    return gnsdk_javaJNI.GnVideoLayer_videoRegionDesc(swigCPtr, this);
  }

/** 
*  Video media type such as Audio-CD, Blu-ray, DVD, or HD DVD. 
*  <p><b>Remarks:</b></p> 
*  This is a list-based value requiring that a list or locale be loaded into memory. 
* <p> 
*  To render locale-dependent information for list-based values, your application must allocate a 
*  <code>GnLocale</code> object. A <code>LocaleNotLoaded</code> message is returned when locale information 
*  is not set prior to a request for a list-based value. 
* 
*/ 
 
  public String mediaType() {
    return gnsdk_javaJNI.GnVideoLayer_mediaType(swigCPtr, this);
  }

  public GnVideoFeatureIterable features() {
    return new GnVideoFeatureIterable(gnsdk_javaJNI.GnVideoLayer_features(swigCPtr, this), true);
  }

}
