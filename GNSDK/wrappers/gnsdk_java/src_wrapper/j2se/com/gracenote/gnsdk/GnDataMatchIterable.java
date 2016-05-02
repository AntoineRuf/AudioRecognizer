
package com.gracenote.gnsdk;

/** 
* Provides access to {@link GnDataMatch} iterator object 
*/ 
 
public class GnDataMatchIterable {
  private transient long swigCPtr;
  protected transient boolean swigCMemOwn;

  protected GnDataMatchIterable(long cPtr, boolean cMemoryOwn) {
    swigCMemOwn = cMemoryOwn;
    swigCPtr = cPtr;
  }

  protected static long getCPtr(GnDataMatchIterable obj) {
    return (obj == null) ? 0 : obj.swigCPtr;
  }

  protected void finalize() {
    delete();
  }

  public synchronized void delete() {
    if (swigCPtr != 0) {
      if (swigCMemOwn) {
        swigCMemOwn = false;
        gnsdk_javaJNI.delete_GnDataMatchIterable(swigCPtr);
      }
      swigCPtr = 0;
    }
  }

  public GnDataMatchIterable(GnDataMatchProvider provider, long start) {
    this(gnsdk_javaJNI.new_GnDataMatchIterable(GnDataMatchProvider.getCPtr(provider), provider, start), true);
  }

  public GnDataMatchIterator getIterator() {
    return new GnDataMatchIterator(gnsdk_javaJNI.GnDataMatchIterable_getIterator(swigCPtr, this), true);
  }

  public GnDataMatchIterator end() {
    return new GnDataMatchIterator(gnsdk_javaJNI.GnDataMatchIterable_end(swigCPtr, this), true);
  }

  public long count() {
    return gnsdk_javaJNI.GnDataMatchIterable_count(swigCPtr, this);
  }

  public GnDataMatchIterator at(long index) {
    return new GnDataMatchIterator(gnsdk_javaJNI.GnDataMatchIterable_at(swigCPtr, this, index), true);
  }

  public GnDataMatchIterator getByIndex(long index) {
    return new GnDataMatchIterator(gnsdk_javaJNI.GnDataMatchIterable_getByIndex(swigCPtr, this, index), true);
  }

}
