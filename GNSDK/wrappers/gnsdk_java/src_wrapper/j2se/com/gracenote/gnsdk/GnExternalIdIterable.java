
package com.gracenote.gnsdk;

/** 
* Provides access to {@link GnExternalId} iterator object 
*/ 
 
public class GnExternalIdIterable {
  private transient long swigCPtr;
  protected transient boolean swigCMemOwn;

  protected GnExternalIdIterable(long cPtr, boolean cMemoryOwn) {
    swigCMemOwn = cMemoryOwn;
    swigCPtr = cPtr;
  }

  protected static long getCPtr(GnExternalIdIterable obj) {
    return (obj == null) ? 0 : obj.swigCPtr;
  }

  protected void finalize() {
    delete();
  }

  public synchronized void delete() {
    if (swigCPtr != 0) {
      if (swigCMemOwn) {
        swigCMemOwn = false;
        gnsdk_javaJNI.delete_GnExternalIdIterable(swigCPtr);
      }
      swigCPtr = 0;
    }
  }

  public GnExternalIdIterable(GnExternalIdProvider provider, long start) {
    this(gnsdk_javaJNI.new_GnExternalIdIterable(GnExternalIdProvider.getCPtr(provider), provider, start), true);
  }

  public GnExternalIdIterator getIterator() {
    return new GnExternalIdIterator(gnsdk_javaJNI.GnExternalIdIterable_getIterator(swigCPtr, this), true);
  }

  public GnExternalIdIterator end() {
    return new GnExternalIdIterator(gnsdk_javaJNI.GnExternalIdIterable_end(swigCPtr, this), true);
  }

  public long count() {
    return gnsdk_javaJNI.GnExternalIdIterable_count(swigCPtr, this);
  }

  public GnExternalIdIterator at(long index) {
    return new GnExternalIdIterator(gnsdk_javaJNI.GnExternalIdIterable_at(swigCPtr, this, index), true);
  }

  public GnExternalIdIterator getByIndex(long index) {
    return new GnExternalIdIterator(gnsdk_javaJNI.GnExternalIdIterable_getByIndex(swigCPtr, this, index), true);
  }

}
