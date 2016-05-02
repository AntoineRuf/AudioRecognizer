
package com.gracenote.gnsdk;

/** 
* GNSDK internal provider class 
*/ 
 
public class locale_info_provider {
  private transient long swigCPtr;
  protected transient boolean swigCMemOwn;

  protected locale_info_provider(long cPtr, boolean cMemoryOwn) {
    swigCMemOwn = cMemoryOwn;
    swigCPtr = cPtr;
  }

  protected static long getCPtr(locale_info_provider obj) {
    return (obj == null) ? 0 : obj.swigCPtr;
  }

  protected void finalize() {
    delete();
  }

  public synchronized void delete() {
    if (swigCPtr != 0) {
      if (swigCMemOwn) {
        swigCMemOwn = false;
        gnsdk_javaJNI.delete_locale_info_provider(swigCPtr);
      }
      swigCPtr = 0;
    }
  }

/** 
* Constructor 
*/ 
 
  public locale_info_provider() {
    this(gnsdk_javaJNI.new_locale_info_provider(), true);
  }

  public GnLocaleInfo getData(long pos) throws com.gracenote.gnsdk.GnException {
    return new GnLocaleInfo(gnsdk_javaJNI.locale_info_provider_getData(swigCPtr, this, pos), true);
  }

/** 
* Get total count of locales available 
* @return Count 
*/ 
 
  public long count() {
    return gnsdk_javaJNI.locale_info_provider_count(swigCPtr, this);
  }

}
