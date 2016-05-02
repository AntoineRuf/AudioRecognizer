/* ----------------------------------------------------------------------------
 * This file was automatically generated by SWIG (http://www.swig.org).
 * Version 2.0.12
 *
 * Do not make changes to this file unless you know what you are doing--modify
 * the SWIG interface file instead.
 * ----------------------------------------------------------------------------- */

package com.gracenote.gnsdk;

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

  public locale_info_provider() {
    this(gnsdk_javaJNI.new_locale_info_provider(), true);
  }

  public GnLocaleInfo getData(long pos) throws com.gracenote.gnsdk.GnException {
    return new GnLocaleInfo(gnsdk_javaJNI.locale_info_provider_getData(swigCPtr, this, pos), true);
  }

  public long count() {
    return gnsdk_javaJNI.locale_info_provider_count(swigCPtr, this);
  }

}
