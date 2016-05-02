
package com.gracenote.gnsdk;

/** 
* Provides access to {@link GnCredit} iterator object 
*/ 
 
public class GnCreditIterable {
  private transient long swigCPtr;
  protected transient boolean swigCMemOwn;

  protected GnCreditIterable(long cPtr, boolean cMemoryOwn) {
    swigCMemOwn = cMemoryOwn;
    swigCPtr = cPtr;
  }

  protected static long getCPtr(GnCreditIterable obj) {
    return (obj == null) ? 0 : obj.swigCPtr;
  }

  protected void finalize() {
    delete();
  }

  public synchronized void delete() {
    if (swigCPtr != 0) {
      if (swigCMemOwn) {
        swigCMemOwn = false;
        gnsdk_javaJNI.delete_GnCreditIterable(swigCPtr);
      }
      swigCPtr = 0;
    }
  }

  public GnCreditIterable(GnCreditProvider provider, long start) {
    this(gnsdk_javaJNI.new_GnCreditIterable(GnCreditProvider.getCPtr(provider), provider, start), true);
  }

  public GnCreditIterator getIterator() {
    return new GnCreditIterator(gnsdk_javaJNI.GnCreditIterable_getIterator(swigCPtr, this), true);
  }

  public GnCreditIterator end() {
    return new GnCreditIterator(gnsdk_javaJNI.GnCreditIterable_end(swigCPtr, this), true);
  }

  public long count() {
    return gnsdk_javaJNI.GnCreditIterable_count(swigCPtr, this);
  }

  public GnCreditIterator at(long index) {
    return new GnCreditIterator(gnsdk_javaJNI.GnCreditIterable_at(swigCPtr, this, index), true);
  }

  public GnCreditIterator getByIndex(long index) {
    return new GnCreditIterator(gnsdk_javaJNI.GnCreditIterable_getByIndex(swigCPtr, this, index), true);
  }

}
