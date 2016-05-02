
package com.gracenote.gnsdk;

/** 
* Title of a work or product 
*/ 
 
public class GnTitle extends GnDataObject {
  private long swigCPtr;

  protected GnTitle(long cPtr, boolean cMemoryOwn) {
    super(gnsdk_javaJNI.GnTitle_SWIGUpcast(cPtr), cMemoryOwn);
    swigCPtr = cPtr;
  }

  protected static long getCPtr(GnTitle obj) {
    return (obj == null) ? 0 : obj.swigCPtr;
  }

  protected void finalize() {
    delete();
  }

  public synchronized void delete() {
    if (swigCPtr != 0) {
      if (swigCMemOwn) {
        swigCMemOwn = false;
        gnsdk_javaJNI.delete_GnTitle(swigCPtr);
      }
      swigCPtr = 0;
    }
    super.delete();
  }

  public static String gnType() {
    return gnsdk_javaJNI.GnTitle_gnType();
  }

  public static GnTitle from(GnDataObject obj) throws com.gracenote.gnsdk.GnException {
    return new GnTitle(gnsdk_javaJNI.GnTitle_from(GnDataObject.getCPtr(obj), obj), true);
  }

/** 
*  Title display language 
*  @return Language string 
*/ 
 
  public String language() {
    return gnsdk_javaJNI.GnTitle_language(swigCPtr, this);
  }

/** 
*  3 letter ISO code for display language 
*  @return Language code 
*/ 
 
  public String languageCode() {
    return gnsdk_javaJNI.GnTitle_languageCode(swigCPtr, this);
  }

/** 
*  Title display string 
*  @return Strng suitable for displaying to end user 
*/ 
 
  public String display() {
    return gnsdk_javaJNI.GnTitle_display(swigCPtr, this);
  }

/** 
*  Title prefix, e.g., The 
*  @return Prefix 
*/ 
 
  public String prefix() {
    return gnsdk_javaJNI.GnTitle_prefix(swigCPtr, this);
  }

/** 
*  Sortable title 
*  @return Sortable string 
*/ 
 
  public String sortable() {
    return gnsdk_javaJNI.GnTitle_sortable(swigCPtr, this);
  }

/** 
*  Sortable title scheme 
*  @return Sortable scheme 
*/ 
 
  public String sortableScheme() {
    return gnsdk_javaJNI.GnTitle_sortableScheme(swigCPtr, this);
  }

/** 
* Main title 
* @return Title 
*/ 
 
  public String mainTitle() {
    return gnsdk_javaJNI.GnTitle_mainTitle(swigCPtr, this);
  }

/** 
* Title edition 
* @return Edition 
*/ 
 
  public String edition() {
    return gnsdk_javaJNI.GnTitle_edition(swigCPtr, this);
  }

}
