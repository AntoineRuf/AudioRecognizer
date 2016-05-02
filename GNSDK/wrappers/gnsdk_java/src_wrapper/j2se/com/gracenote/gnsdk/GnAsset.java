
package com.gracenote.gnsdk;

/** 
* Assets for content (cover art, biography etc) 
*/ 
 
public class GnAsset extends GnDataObject {
  private long swigCPtr;

  protected GnAsset(long cPtr, boolean cMemoryOwn) {
    super(gnsdk_javaJNI.GnAsset_SWIGUpcast(cPtr), cMemoryOwn);
    swigCPtr = cPtr;
  }

  protected static long getCPtr(GnAsset obj) {
    return (obj == null) ? 0 : obj.swigCPtr;
  }

  protected void finalize() {
    delete();
  }

  public synchronized void delete() {
    if (swigCPtr != 0) {
      if (swigCMemOwn) {
        swigCMemOwn = false;
        gnsdk_javaJNI.delete_GnAsset(swigCPtr);
      }
      swigCPtr = 0;
    }
    super.delete();
  }

/** 
*  Asset dimension 
*  @return Dimention string 
*/ 
 
  public String dimension() {
    return gnsdk_javaJNI.GnAsset_dimension(swigCPtr, this);
  }

  public int bytes() {
    return gnsdk_javaJNI.GnAsset_bytes(swigCPtr, this);
  }

/** 
*  Pixel image size of asset as defined with a {@link GnImageSize} enum, e.g., kImageSize110 (110x110) 
*  @return Image size 
*/ 
 
  public GnImageSize size() {
    return GnImageSize.swigToEnum(gnsdk_javaJNI.GnAsset_size(swigCPtr, this));
  }

/** 
*  Url for retrieval of asset from Gracenote 
*  @return URL 
*/ 
 
  public String url() {
    return gnsdk_javaJNI.GnAsset_url(swigCPtr, this);
  }

}
