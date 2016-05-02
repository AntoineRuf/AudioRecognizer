
package com.gracenote.gnsdk;

/** 
* Provides access to {@link GnContent} iterator object 
*/ 
 
public class GnContentIterable {
  private transient long swigCPtr;
  protected transient boolean swigCMemOwn;

  protected GnContentIterable(long cPtr, boolean cMemoryOwn) {
    swigCMemOwn = cMemoryOwn;
    swigCPtr = cPtr;
  }

  protected static long getCPtr(GnContentIterable obj) {
    return (obj == null) ? 0 : obj.swigCPtr;
  }

  protected void finalize() {
    delete();
  }

  public synchronized void delete() {
    if (swigCPtr != 0) {
      if (swigCMemOwn) {
        swigCMemOwn = false;
        gnsdk_javaJNI.delete_GnContentIterable(swigCPtr);
      }
      swigCPtr = 0;
    }
  }

  public GnContentIterable(GnContentProvider provider, long start) {
    this(gnsdk_javaJNI.new_GnContentIterable(GnContentProvider.getCPtr(provider), provider, start), true);
  }

  public GnContentIterator getIterator() {
    return new GnContentIterator(gnsdk_javaJNI.GnContentIterable_getIterator(swigCPtr, this), true);
  }

  public GnContentIterator end() {
    return new GnContentIterator(gnsdk_javaJNI.GnContentIterable_end(swigCPtr, this), true);
  }

  public long count() {
    return gnsdk_javaJNI.GnContentIterable_count(swigCPtr, this);
  }

  public GnContentIterator at(long index) {
    return new GnContentIterator(gnsdk_javaJNI.GnContentIterable_at(swigCPtr, this, index), true);
  }

  public GnContentIterator getByIndex(long index) {
    return new GnContentIterator(gnsdk_javaJNI.GnContentIterable_getByIndex(swigCPtr, this, index), true);
  }

}
