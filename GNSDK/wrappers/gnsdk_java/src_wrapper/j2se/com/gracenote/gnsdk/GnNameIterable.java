
package com.gracenote.gnsdk;

/** 
* Provides access to {@link GnName} iterator object 
*/ 
 
public class GnNameIterable {
  private transient long swigCPtr;
  protected transient boolean swigCMemOwn;

  protected GnNameIterable(long cPtr, boolean cMemoryOwn) {
    swigCMemOwn = cMemoryOwn;
    swigCPtr = cPtr;
  }

  protected static long getCPtr(GnNameIterable obj) {
    return (obj == null) ? 0 : obj.swigCPtr;
  }

  protected void finalize() {
    delete();
  }

  public synchronized void delete() {
    if (swigCPtr != 0) {
      if (swigCMemOwn) {
        swigCMemOwn = false;
        gnsdk_javaJNI.delete_GnNameIterable(swigCPtr);
      }
      swigCPtr = 0;
    }
  }

  public GnNameIterable(GnNameProvider provider, long start) {
    this(gnsdk_javaJNI.new_GnNameIterable(GnNameProvider.getCPtr(provider), provider, start), true);
  }

  public GnNameIterator getIterator() {
    return new GnNameIterator(gnsdk_javaJNI.GnNameIterable_getIterator(swigCPtr, this), true);
  }

  public GnNameIterator end() {
    return new GnNameIterator(gnsdk_javaJNI.GnNameIterable_end(swigCPtr, this), true);
  }

  public long count() {
    return gnsdk_javaJNI.GnNameIterable_count(swigCPtr, this);
  }

  public GnNameIterator at(long index) {
    return new GnNameIterator(gnsdk_javaJNI.GnNameIterable_at(swigCPtr, this, index), true);
  }

  public GnNameIterator getByIndex(long index) {
    return new GnNameIterator(gnsdk_javaJNI.GnNameIterable_getByIndex(swigCPtr, this, index), true);
  }

}
