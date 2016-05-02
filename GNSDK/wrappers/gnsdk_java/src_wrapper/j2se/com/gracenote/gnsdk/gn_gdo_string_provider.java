
package com.gracenote.gnsdk;

/** 
* GNSDK internal gdo string provider class 
*/ 
 
public class gn_gdo_string_provider {
  private transient long swigCPtr;
  protected transient boolean swigCMemOwn;

  protected gn_gdo_string_provider(long cPtr, boolean cMemoryOwn) {
    swigCMemOwn = cMemoryOwn;
    swigCPtr = cPtr;
  }

  protected static long getCPtr(gn_gdo_string_provider obj) {
    return (obj == null) ? 0 : obj.swigCPtr;
  }

  protected void finalize() {
    delete();
  }

  public synchronized void delete() {
    if (swigCPtr != 0) {
      if (swigCMemOwn) {
        swigCMemOwn = false;
        gnsdk_javaJNI.delete_gn_gdo_string_provider(swigCPtr);
      }
      swigCPtr = 0;
    }
  }

  public gn_gdo_string_provider(GnDataObject obj, String key) {
    this(gnsdk_javaJNI.new_gn_gdo_string_provider(GnDataObject.getCPtr(obj), obj, key), true);
  }

  public String getData(long pos) {
    return gnsdk_javaJNI.gn_gdo_string_provider_getData(swigCPtr, this, pos);
  }

  public long count() {
    return gnsdk_javaJNI.gn_gdo_string_provider_count(swigCPtr, this);
  }

}
