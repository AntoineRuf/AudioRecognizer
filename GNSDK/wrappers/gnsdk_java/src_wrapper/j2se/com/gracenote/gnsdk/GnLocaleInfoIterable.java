
package com.gracenote.gnsdk;

/** 
* Provides access to {@link GnLocaleInfo} iterator object 
*/ 
 
public class GnLocaleInfoIterable {
  private transient long swigCPtr;
  protected transient boolean swigCMemOwn;

  protected GnLocaleInfoIterable(long cPtr, boolean cMemoryOwn) {
    swigCMemOwn = cMemoryOwn;
    swigCPtr = cPtr;
  }

  protected static long getCPtr(GnLocaleInfoIterable obj) {
    return (obj == null) ? 0 : obj.swigCPtr;
  }

  protected void finalize() {
    delete();
  }

  public synchronized void delete() {
    if (swigCPtr != 0) {
      if (swigCMemOwn) {
        swigCMemOwn = false;
        gnsdk_javaJNI.delete_GnLocaleInfoIterable(swigCPtr);
      }
      swigCPtr = 0;
    }
  }

  public GnLocaleInfoIterable(locale_info_provider provider, long start) {
    this(gnsdk_javaJNI.new_GnLocaleInfoIterable(locale_info_provider.getCPtr(provider), provider, start), true);
  }

  public GnLocaleInfoIterator getIterator() {
    return new GnLocaleInfoIterator(gnsdk_javaJNI.GnLocaleInfoIterable_getIterator(swigCPtr, this), true);
  }

  public GnLocaleInfoIterator end() {
    return new GnLocaleInfoIterator(gnsdk_javaJNI.GnLocaleInfoIterable_end(swigCPtr, this), true);
  }

  public long count() {
    return gnsdk_javaJNI.GnLocaleInfoIterable_count(swigCPtr, this);
  }

  public GnLocaleInfoIterator at(long index) {
    return new GnLocaleInfoIterator(gnsdk_javaJNI.GnLocaleInfoIterable_at(swigCPtr, this, index), true);
  }

  public GnLocaleInfoIterator getByIndex(long index) {
    return new GnLocaleInfoIterator(gnsdk_javaJNI.GnLocaleInfoIterable_getByIndex(swigCPtr, this, index), true);
  }

}
